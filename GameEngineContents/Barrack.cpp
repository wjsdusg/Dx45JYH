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
#include "PlayLevel.h"
#include "Mouse.h"

#include "Wakizaka.h"
#include "Asako.h"
#include "Gato.h"
#include "Gonisi.h"
#include "Mitsunari.h"
#include "Seisho.h"
#include "Tokugawa.h"
#include "Ugida.h"
extern float4 MainMouse;
extern  float CalAngle1To2(float4 _Pos1, float4 _Pos2);

Barrack::Barrack()
{
	MainBarrack = this;
}

Barrack::~Barrack()
{
}


Barrack* Barrack::MainBarrack = nullptr;
void Barrack::Update(float _DeltaTime)
{
	Building::Update(_DeltaTime);


	if (GetLiveTime() > 2.f)
	{
		Synthesis();
		CreateUnit(3);
		ResetLiveTime();

	}
	float4 Pos = GetTransform()->GetLocalPosition();
	float4 Pos2 = Render0->GetTransform()->GetLocalPosition();

	//if (true == DoorRender->IsUpdate())
	{
		if (true == DoorCollision->IsUpdate())
		{
			std::vector<std::shared_ptr<GameEngineCollision>> ColTest;

			if (DoorCollision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::AABBBOX2D, ColType::AABBBOX2D), 0 != ColTest.size())
			{
				for (std::shared_ptr<GameEngineCollision> Col : ColTest)
				{
					std::shared_ptr<Unit> NewUnit = Col->GetActor()->DynamicThis<Unit>();
					if (nullptr == NewUnit)
					{
						continue;
					}
					else
					{
						if (Team::Mine == NewUnit->MyTeam)
						{
							NewUnit->SetIsClick(false);
							MoveDoorPos(NewUnit);
						}

					}
				}
			}
		}
		
	}
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
	if (nullptr == GameEngineSprite::Find("Door"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Door").GetFullPath());

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
	MyField = Field::DefenseMap;
	Building::Start();

	DoorRender = CreateComponent<GameEngineSpriteRenderer>();
	DoorRender->CreateAnimation({ .AnimationName = "Open", .SpriteName = "Door",.Loop = true,.ScaleToTexture = false });
	DoorRender->ChangeAnimation("Open");
	DoorRender->GetTransform()->SetLocalScale({ 100.f,200.f });
	DoorRender->GetTransform()->SetWorldPosition(DefenseMapEditor::ConvertTileXYToPos(16, 4));
	DoorCollision = CreateComponent<GameEngineCollision>();
	DoorCollision->SetOrder(static_cast<int>(ColEnum::Player));
	DoorCollision->GetTransform()->SetWorldPosition(DefenseMapEditor::ConvertTileXYToPos(16, 4));
	DoorCollision->GetTransform()->SetLocalScale({ 200.f,200.f });
	DoorRender->Off();
	DoorCollision->Off();
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
		float4 CheckPos = DefenseMapEditor::ConvertPosToTileXY({ static_cast<float>(x), static_cast<float>(y) });
		SummonPos[i] = CheckPos;
	}
}

void Barrack::DoorPosLoad(GameEngineSerializer& _Ser)
{
	_Ser.Read(SaveNum);
	int x;
	int y;
	DoorPos.resize(SaveNum);
	for (int i = 0; i < SaveNum; i++)
	{
		_Ser.Read(x);
		_Ser.Read(y);
		float4 CheckPos = DefenseMapEditor::ConvertPosToTileXY({ static_cast<float>(x), static_cast<float>(y) });
		DoorPos[i] = CheckPos;
	}
}

void Barrack::CreateUnit(int _Level)
{
	int RandomNum = GameEngineRandom::MainRandom.RandomInt(0, 1);
	std::shared_ptr<Ksword> NewKsword = nullptr;
	std::shared_ptr<Karcher>NewKarcher = nullptr;

	if (_Level <= 5)
	{
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
	else
	{

		std::shared_ptr<Wakizaka>NewWakizaka = nullptr;
		std::shared_ptr<Asako>NewAsako = nullptr;
		std::shared_ptr<Gato>NewGato = nullptr;
		std::shared_ptr<Gonisi>NewGonisi = nullptr;
		std::shared_ptr<Mitsunari>NewMitsunari = nullptr;
		std::shared_ptr<Seisho>NewSeisho = nullptr;
		std::shared_ptr<Tokugawa>NewTokugawa = nullptr;
		std::shared_ptr<Ugida>NewUgida = nullptr;
		RandomNum = GameEngineRandom::MainRandom.RandomInt(0, 7);
		switch (RandomNum) {
		case 0:

			for (int i = 0; i < SummonPos.size(); i++)
			{
				if (false == DefenseGlobalValue::Collision->IsCollision(SummonPos[i].ix(), SummonPos[i].iy()))
				{
					NewWakizaka = GetLevel()->CreateActor<Wakizaka >();
					NewWakizaka->GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(SummonPos[i].ix(), SummonPos[i].iy()));
					NewWakizaka->Level = _Level;
					NewWakizaka->LevelSetting();
					BarrackUnits.push_back(NewWakizaka);
					LevelInfos.push_back(NewWakizaka->Level);
					NewWakizaka->DefenseMapFSM.ChangeState("Summoning");
					break;
				}

			}
			break;
		case 1:

			for (int i = 0; i < SummonPos.size(); i++)
			{
				if (false == DefenseGlobalValue::Collision->IsCollision(SummonPos[i].ix(), SummonPos[i].iy()))
				{
					NewAsako = GetLevel()->CreateActor<Asako >();
					NewAsako->GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(SummonPos[i].ix(), SummonPos[i].iy()));
					NewAsako->Level = _Level;
					NewAsako->LevelSetting();
					BarrackUnits.push_back(NewAsako);
					LevelInfos.push_back(NewAsako->Level);
					NewAsako->DefenseMapFSM.ChangeState("Summoning");
					break;
				}
			}
			break;
		case 2:

			for (int i = 0; i < SummonPos.size(); i++)
			{
				if (false == DefenseGlobalValue::Collision->IsCollision(SummonPos[i].ix(), SummonPos[i].iy()))
				{
					NewGato = GetLevel()->CreateActor<Gato>();
					NewGato->GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(SummonPos[i].ix(), SummonPos[i].iy()));
					NewGato->Level = _Level;
					NewGato->LevelSetting();
					BarrackUnits.push_back(NewGato);
					LevelInfos.push_back(NewGato->Level);
					NewGato->DefenseMapFSM.ChangeState("Summoning");
					break;
				}
			}
			break;
		case 3:

			for (int i = 0; i < SummonPos.size(); i++)
			{
				if (false == DefenseGlobalValue::Collision->IsCollision(SummonPos[i].ix(), SummonPos[i].iy()))
				{
					NewMitsunari = GetLevel()->CreateActor<Mitsunari>();
					NewMitsunari->GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(SummonPos[i].ix(), SummonPos[i].iy()));
					NewMitsunari->Level = _Level;
					NewMitsunari->LevelSetting();
					BarrackUnits.push_back(NewMitsunari);
					LevelInfos.push_back(NewMitsunari->Level);
					NewMitsunari->DefenseMapFSM.ChangeState("Summoning");
					break;
				}
			}
			break;
		case 4:

			for (int i = 0; i < SummonPos.size(); i++)
			{
				if (false == DefenseGlobalValue::Collision->IsCollision(SummonPos[i].ix(), SummonPos[i].iy()))
				{
					NewSeisho = GetLevel()->CreateActor<Seisho >();
					NewSeisho->GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(SummonPos[i].ix(), SummonPos[i].iy()));
					NewSeisho->Level = _Level;
					NewSeisho->LevelSetting();
					BarrackUnits.push_back(NewSeisho);
					LevelInfos.push_back(NewSeisho->Level);
					NewSeisho->DefenseMapFSM.ChangeState("Summoning");
					break;
				}
			}
			break;
		case 5:

			for (int i = 0; i < SummonPos.size(); i++)
			{
				if (false == DefenseGlobalValue::Collision->IsCollision(SummonPos[i].ix(), SummonPos[i].iy()))
				{
					NewTokugawa = GetLevel()->CreateActor<Tokugawa >();
					NewTokugawa->GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(SummonPos[i].ix(), SummonPos[i].iy()));
					NewTokugawa->Level = _Level;
					NewTokugawa->LevelSetting();
					BarrackUnits.push_back(NewTokugawa);
					LevelInfos.push_back(NewTokugawa->Level);
					NewTokugawa->DefenseMapFSM.ChangeState("Summoning");
					break;
				}
			}
			break;
		case 6:

			for (int i = 0; i < SummonPos.size(); i++)
			{
				if (false == DefenseGlobalValue::Collision->IsCollision(SummonPos[i].ix(), SummonPos[i].iy()))
				{
					NewUgida = GetLevel()->CreateActor<Ugida >();
					NewUgida->GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(SummonPos[i].ix(), SummonPos[i].iy()));
					NewUgida->Level = _Level;
					NewUgida->LevelSetting();
					BarrackUnits.push_back(NewUgida);
					LevelInfos.push_back(NewUgida->Level);
					NewUgida->DefenseMapFSM.ChangeState("Summoning");
					break;
				}
			}
			break;
		case 7:

			for (int i = 0; i < SummonPos.size(); i++)
			{
				if (false == DefenseGlobalValue::Collision->IsCollision(SummonPos[i].ix(), SummonPos[i].iy()))
				{
					NewGonisi = GetLevel()->CreateActor<Gonisi >();
					NewGonisi->GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(SummonPos[i].ix(), SummonPos[i].iy()));
					NewGonisi->Level = _Level;
					NewGonisi->LevelSetting();
					BarrackUnits.push_back(NewGonisi);
					LevelInfos.push_back(NewGonisi->Level);
					NewGonisi->DefenseMapFSM.ChangeState("Summoning");
					break;
				}
			}
			break;
		default:
			break;
		}
	}
	
}
//던전입장전집합
void Barrack::MoveDoorPos(std::shared_ptr<Unit> _CopyUnit)
{
	//DoorUnits.clear();
	std::shared_ptr<Unit> NewUnit = _CopyUnit;
	for (int i = 0; i < DoorPos.size(); i++)
	{
		if (false == DefenseGlobalValue::Collision->IsCollision(DoorPos[i].ix(), DoorPos[i].iy()))
		{

			NewUnit->MyTeam = Team::Ally;
			DoorUnits.push_back(NewUnit);
			float4 _Pos = DefenseMapEditor::ConvertPosToTileXY(NewUnit->GetTransform()->GetWorldPosition());
			NewUnit->GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(DoorPos[i].ix(), DoorPos[i].iy()));
			NewUnit->DefenseMapFSM.ChangeState("Summoning");
			DefenseGlobalValue::Collision->ClrAt(17, 7);
			DefenseGlobalValue::Collision->ClrAt(16, 6);
			DefenseGlobalValue::Collision->ClrAt(15, 5);
			DefenseGlobalValue::Collision->ClrAt(15, 6);
			int a = 0;
			break;
		}

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
		if (5 < LevelInfos[i - 1])
		{
			continue;
		}
		auto It = std::find(LevelInfos.begin() + i, LevelInfos.end(), LevelInfos[i - 1]);
		if (LevelInfos.end() != It)
		{
			int Level = LevelInfos[i - 1];
			int index = static_cast<int>(std::distance(LevelInfos.begin(), It));
			//(BarrackUnits.begin()+i-1)->get()->DefenseMapFSM.ChangeState("Die");

			BarrackUnits[i - 1]->DefenseMapFSM.ChangeState("Die");
			BarrackUnits[index]->DefenseMapFSM.ChangeState("Die");

			BarrackUnits.erase(BarrackUnits.begin() + i - 1);
			BarrackUnits.erase(BarrackUnits.begin() + index - 1);
			LevelInfos.erase(LevelInfos.begin() + i - 1);
			LevelInfos.erase(LevelInfos.begin() + index - 1);
			Level += 1;
			CreateUnit(Level);
			return;
		}
	}

	return;
}


void Barrack::TransunitToMap()
{

	int x = 7;
	int y = 7;
	int num = 0;

	for (int n = 1; n <= 10; n++) {
		for (int dy = -n; dy <= n; dy++) {
			for (int dx = -n; dx <= n; dx++) {

				int nx = x + dx;
				int ny = y + dy;
				if (true == DefenseGlobalValue::Collision->IsOutBound(nx, ny))
				{
					return;
				}
				if (false == DefenseGlobalValue::Collision->IsCollision(nx, ny))
				{
					float4 Pos = DefenseMapEditor::ConvertTileXYToPos(nx, ny);
					if (nullptr != BarrackUnits[num])
					{
						BarrackUnits[num]->GetTransform()->SetLocalPosition(Pos);
						BarrackUnits[num]->SetTeam(Team::Mine);
						BarrackUnits[num]->MyField = Field::DefenseMap;
						BarrackUnits[num]->DefenseMapFSM.ChangeState("Stay");
						num++;
					}
				}
				if (BarrackUnits.size() == num)
				{
					BarrackUnits.clear();
					LevelInfos.clear();
					return;
				}

			}
		}
	}
}

void Barrack::RespawnPosLoad(GameEngineSerializer& _Ser)
{
	_Ser.Read(SaveNum);
	int x;
	int y;
	RespawnPos.resize(SaveNum);
	for (int i = 0; i < SaveNum; i++)
	{

		_Ser.Read(x);
		_Ser.Read(y);

		float4 CheckPos = MapEditor::ConvertPosToTileXY({ static_cast<float>(x), static_cast<float>(y) });

		RespawnPos[i] = CheckPos;
	}
}

void Barrack::GotoDengeon()
{
	PlayLevel::MainPlayLevel->SetField(Field::DungeonMap);
	PlayLevel::MainPlayLevel->BgmPlayer.Stop();
	PlayLevel::MainPlayLevel->BgmPlayer= GameEngineSound::Play("Track05.mp3");
	Mouse::NewMainMouse->SetMyField(Field::DungeonMap);

	if (0 != DoorUnits.size() && 0 != RespawnPos.size())
	{
		for (int i = 0; i < DoorUnits.size(); i++)
		{
			DoorUnits[i]->GetTransform()->SetWorldPosition(MapEditor::ConvertTileXYToPos(RespawnPos[i].ix(), RespawnPos[i].iy()));
			DoorUnits[i]->MyField = Field::DungeonMap;
			DoorUnits[i]->MyTeam = Team::Mine;
			DoorUnits[i]->FSM.ChangeState("Stay");
		}
		GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition(DoorUnits[0]->GetTransform()->GetWorldPosition());
		//DoorUnits.clear();
	}

}

void Barrack::GotoDenFensceMap()
{
	PlayLevel::MainPlayLevel->SetField(Field::DefenseMap);
	PlayLevel::MainPlayLevel->BgmPlayer.Stop();
	PlayLevel::MainPlayLevel->BgmPlayer = GameEngineSound::Play("Track02.mp3");
	Mouse::NewMainMouse->SetMyField(Field::DefenseMap);

	GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition({ 4800.f,-2400.f });

	int x = 7;
	int y = 7;
	int num = 0;
	for (int n = 1; n <= 10; n++) {
		for (int dy = -n; dy <= n; dy++) {
			for (int dx = -n; dx <= n; dx++) {

				int nx = x + dx;
				int ny = y + dy;
				if (true == DefenseGlobalValue::Collision->IsOutBound(nx, ny))
				{
					return;
				}
				if (false == DefenseGlobalValue::Collision->IsCollision(nx, ny))
				{
					float4 Pos = DefenseMapEditor::ConvertTileXYToPos(nx, ny);
					if (0 == DoorUnits.size())
					{
						return;
					}
					if (nullptr != DoorUnits[num])
					{
						if (DoorUnits[num]->IsDeath())
						{
							num++;
						}
						else 
						{
							float4 sdsd= DefenseMapEditor::ConvertTileXYToPos(Pos.ix(), Pos.iy());
							DoorUnits[num]->GetTransform()->SetWorldPosition(Pos);
							DoorUnits[num]->MyField = Field::DefenseMap;
							DoorUnits[num]->MyTeam = Team::Mine;
							DoorUnits[num]->DefenseMapFSM.ChangeState("Stay");
							num++;
						}
						

					}
				}
				if (DoorUnits.size() == num)
				{
					DoorUnits.clear();
					return;
				}

			}
		}
	}
}

int numm = 0;
void Barrack::CreateHero()
{
	std::shared_ptr<Wakizaka>NewWakizaka = nullptr;
	std::shared_ptr<Asako>NewAsako = nullptr;
	std::shared_ptr<Gato>NewGato = nullptr;
	std::shared_ptr<Gonisi>NewGonisi = nullptr;
	std::shared_ptr<Mitsunari>NewMitsunari = nullptr;
	std::shared_ptr<Seisho>NewSeisho = nullptr;
	std::shared_ptr<Tokugawa>NewTokugawa = nullptr;
	std::shared_ptr<Ugida>NewUgida = nullptr;	
	switch (numm) {
	case 0:

		for (int i = 0; i < SummonPos.size(); i++)
		{
			if (false == DefenseGlobalValue::Collision->IsCollision(SummonPos[i].ix(), SummonPos[i].iy()))
			{
				NewWakizaka = GetLevel()->CreateActor<Wakizaka >();
				NewWakizaka->GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(SummonPos[i].ix(), SummonPos[i].iy()));
				NewWakizaka->Level = 6;
				NewWakizaka->LevelSetting();
				BarrackUnits.push_back(NewWakizaka);
				LevelInfos.push_back(NewWakizaka->Level);
				NewWakizaka->DefenseMapFSM.ChangeState("Summoning");
				break;
			}

		}
		break;
	case 1:

		for (int i = 0; i < SummonPos.size(); i++)
		{
			if (false == DefenseGlobalValue::Collision->IsCollision(SummonPos[i].ix(), SummonPos[i].iy()))
			{
				NewAsako = GetLevel()->CreateActor<Asako >();
				NewAsako->GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(SummonPos[i].ix(), SummonPos[i].iy()));
				NewAsako->Level = 6;
				NewAsako->LevelSetting();
				BarrackUnits.push_back(NewAsako);
				LevelInfos.push_back(NewAsako->Level);
				NewAsako->DefenseMapFSM.ChangeState("Summoning");
				break;
			}
		}
		break;
	case 2:

		for (int i = 0; i < SummonPos.size(); i++)
		{
			if (false == DefenseGlobalValue::Collision->IsCollision(SummonPos[i].ix(), SummonPos[i].iy()))
			{
				NewGato = GetLevel()->CreateActor<Gato>();
				NewGato->GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(SummonPos[i].ix(), SummonPos[i].iy()));
				NewGato->Level = 6;
				NewGato->LevelSetting();
				BarrackUnits.push_back(NewGato);
				LevelInfos.push_back(NewGato->Level);
				NewGato->DefenseMapFSM.ChangeState("Summoning");
				break;
			}
		}
		break;
	case 3:

		for (int i = 0; i < SummonPos.size(); i++)
		{
			if (false == DefenseGlobalValue::Collision->IsCollision(SummonPos[i].ix(), SummonPos[i].iy()))
			{
				NewMitsunari = GetLevel()->CreateActor<Mitsunari>();
				NewMitsunari->GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(SummonPos[i].ix(), SummonPos[i].iy()));
				NewMitsunari->Level = 6;
				NewMitsunari->LevelSetting();
				BarrackUnits.push_back(NewMitsunari);
				LevelInfos.push_back(NewMitsunari->Level);
				NewMitsunari->DefenseMapFSM.ChangeState("Summoning");
				break;
			}
		}
		break;
	case 4:

		for (int i = 0; i < SummonPos.size(); i++)
		{
			if (false == DefenseGlobalValue::Collision->IsCollision(SummonPos[i].ix(), SummonPos[i].iy()))
			{
				NewSeisho = GetLevel()->CreateActor<Seisho >();
				NewSeisho->GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(SummonPos[i].ix(), SummonPos[i].iy()));
				NewSeisho->Level = 6;
				NewSeisho->LevelSetting();
				BarrackUnits.push_back(NewSeisho);
				LevelInfos.push_back(NewSeisho->Level);
				NewSeisho->DefenseMapFSM.ChangeState("Summoning");
				break;
			}
		}
		break;
	case 5:

		for (int i = 0; i < SummonPos.size(); i++)
		{
			if (false == DefenseGlobalValue::Collision->IsCollision(SummonPos[i].ix(), SummonPos[i].iy()))
			{
				NewTokugawa = GetLevel()->CreateActor<Tokugawa >();
				NewTokugawa->GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(SummonPos[i].ix(), SummonPos[i].iy()));
				NewTokugawa->Level = 6;
				NewTokugawa->LevelSetting();
				BarrackUnits.push_back(NewTokugawa);
				LevelInfos.push_back(NewTokugawa->Level);
				NewTokugawa->DefenseMapFSM.ChangeState("Summoning");
				break;
			}
		}
		break;
	case 6:

		for (int i = 0; i < SummonPos.size(); i++)
		{
			if (false == DefenseGlobalValue::Collision->IsCollision(SummonPos[i].ix(), SummonPos[i].iy()))
			{
				NewUgida = GetLevel()->CreateActor<Ugida >();
				NewUgida->GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(SummonPos[i].ix(), SummonPos[i].iy()));
				NewUgida->Level = 6;
				NewUgida->LevelSetting();
				BarrackUnits.push_back(NewUgida);
				LevelInfos.push_back(NewUgida->Level);
				NewUgida->DefenseMapFSM.ChangeState("Summoning");
				break;
			}
		}
		break;
	case 7:

		for (int i = 0; i < SummonPos.size(); i++)
		{
			if (false == DefenseGlobalValue::Collision->IsCollision(SummonPos[i].ix(), SummonPos[i].iy()))
			{
				NewGonisi = GetLevel()->CreateActor<Gonisi >();
				NewGonisi->GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(SummonPos[i].ix(), SummonPos[i].iy()));
				NewGonisi->Level = 6;
				NewGonisi->LevelSetting();
				BarrackUnits.push_back(NewGonisi);
				LevelInfos.push_back(NewGonisi->Level);
				NewGonisi->DefenseMapFSM.ChangeState("Summoning");
				break;
			}
		}
		break;
	default:
		break;
	}
	numm++;
}
