#include "PrecompileHeader.h"
#include "Barrack.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <algorithm>
#include <GameEngineBase/GameEngineRandom.h>
#include "DefenseMapEditor.h"
#include "ContentsEnum.h"
#include "MapOverlay.h"
#include "MapEditor.h"
#include "Ksword.h"
#include "Karcher.h"
#include "GlobalValue.h"
extern float4 MainMouse;
extern  float CalAngle1To2(float4 _Pos1, float4 _Pos2);

Barrack::Barrack()
{
}

Barrack::~Barrack()
{
}

bool check = false;
void Barrack::Update(float _DeltaTime)
{
	Building::Update(_DeltaTime);
	
	if (GetLiveTime() > 2.f )
	{
		Synthesis();
		CreateUnit(1);		
		ResetLiveTime();
	}
	float4 Pos = GetTransform()->GetLocalPosition();
	float4 Pos2 = Render0->GetTransform()->GetLocalPosition();
	


}
//
void Barrack::Start()
{	
	if (nullptr == GameEngineSprite::Find("Barrack.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Building");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("Barrack.png").GetFullPath(), 1, 1);
	}
	if (nullptr == GameEngineSprite::Find("exp11.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Boom");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("exp11.png").GetFullPath(), 5, 4);
	}
	GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(2, 24));
	Render0 = CreateComponent<GameEngineSpriteRenderer>();	
	Render0->CreateAnimation({ "Stay", "Barrack.png",0,0,0.1f,true,false });
	Render0->CreateAnimation({ "Die", "exp11.png",0,18,0.1f,false,true });
	Render0->GetTransform()->SetLocalScale({ 250,250 });
	
	Collision = CreateComponent<GameEngineCollision>();
	
	Collision->SetColType(ColType::AABBBOX2D);
	Collision->SetOrder(static_cast<int>(ColEnum::Unit));
	Collision->GetTransform()->SetLocalScale(Render0->GetTransform()->GetLocalScale());
	MyTeam = Team::Mine;
	//MyBuildingType = BuildingType::IncludeUnit;

	Building::Start();
	float4 Pos2 = Render0->GetTransform()->GetLocalPosition();

	EnemyNum = GameEngineRandom::MainRandom.RandomInt(4, 6);
	EnemyUnits.resize(EnemyNum);
	for (int i = 0; i < EnemyNum; i++)
	{
		
	}
}

// 이건 디버깅용도나 
void Barrack::Render(float _Delta)
{

};
//
void Barrack::SummonPosLoad(GameEngineSerializer& _Ser)
{
	_Ser.Read(SaveNum);
	int x;
	int y;
	SummonPos.resize(SaveNum);
	for (int i = 0; i < SaveNum; i++)
	{

		_Ser.Read(x);
		_Ser.Read(y);

		float4 CheckPos =DefenseMapEditor::ConvertPosToTileXY({ static_cast<float>(x), static_cast<float>(y) });

		SummonPos[i] = CheckPos;
	}
}

void Barrack::CreateUnit(int _Level)
{
	int RandomNum = GameEngineRandom::MainRandom.RandomInt(0, 1);
	std::shared_ptr<Ksword> NewKsword = nullptr;	
	std::shared_ptr<Karcher>NewKarcher = nullptr;
	switch (RandomNum) {
	case 0:
		
		for (int i = 0; i < SummonPos.size(); i++)
		{
			if (false == DefenseGlobalValue::Collision->IsCollision(SummonPos[i].ix(), SummonPos[i].iy()))
			{
				NewKsword = GetLevel()->CreateActor<Ksword >();
				NewKsword->GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(SummonPos[i].ix(), SummonPos[i].iy()));
				NewKsword->Level = _Level;
				NewKsword->LevelSetting();
				BarrackUnits.push_back(NewKsword);
				LevelInfos.push_back(NewKsword->Level);
				NewKsword->DefenseMapFSM.ChangeState("Summoning");
				break;
			}
			
		}
		break;
	case 1:
		
		for (int i = 0; i < SummonPos.size(); i++)
		{
			if (false == DefenseGlobalValue::Collision->IsCollision(SummonPos[i].ix(), SummonPos[i].iy()))
			{
				NewKarcher = GetLevel()->CreateActor<Karcher >();
				NewKarcher->GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(SummonPos[i].ix(), SummonPos[i].iy()));
				NewKarcher->Level = _Level;
				NewKarcher->LevelSetting();
				BarrackUnits.push_back(NewKarcher);
				LevelInfos.push_back(NewKarcher->Level);
				NewKarcher->DefenseMapFSM.ChangeState("Summoning");
				break;
			}
		}
		break;	
	default:
		break;
	}
}

void Barrack::Synthesis()
{
	/*if (true == IsShamonAniEnd)
	{

	}*/
	if (2 > LevelInfos.size())
	{
		return;
	}
	for (int i = 1; i < LevelInfos.size() - 1; i++)
	{
		if (5 < LevelInfos[i-1])
		{
			continue;
		}
		auto It = std::find(LevelInfos.begin()+i, LevelInfos.end(), LevelInfos[i-1]);
		if (LevelInfos.end() != It)
		{
			int Level = LevelInfos[i-1];
			int index = std::distance(LevelInfos.begin(), It);
			//(BarrackUnits.begin()+i-1)->get()->DefenseMapFSM.ChangeState("Die");

			BarrackUnits[i-1]->DefenseMapFSM.ChangeState("Die");
			BarrackUnits[index]->DefenseMapFSM.ChangeState("Die");

			BarrackUnits.erase(BarrackUnits.begin()+i - 1);
			BarrackUnits.erase(BarrackUnits.begin() + index-1);
			LevelInfos.erase(LevelInfos.begin() + i - 1);
			LevelInfos.erase(LevelInfos.begin() + index-1);
			Level += 1;
			CreateUnit(Level);
			return;
		}
	}

	return;
}