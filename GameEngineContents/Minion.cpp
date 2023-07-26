#include "PrecompileHeader.h"
#include "Minion.h"
#include "DefenseMapEditor.h"
#include "ContentsEnum.h"

Minion::Minion()
{

}

Minion::~Minion()
{
}
extern float4 TileScale;
std::vector<float4> Minion::OutSideTargetPos;
std::vector<float4> Minion::InSideTargetPos;
bool Minion::IsOutside = false;
int Minion::MinionNum = 0;
int Minion::GetMoney = 5;
void Minion::Update(float _DeltaTime)
{
	FSM.Update(_DeltaTime);

}
void Minion::Start()
{
	MyTeam = Team::Enemy;	
	float HalfY = Render0->GetTransform()->GetLocalScale().hy();
	HalfY -= 10.f;
	Render0->GetTransform()->SetLocalPosition({ 0,HalfY });
	SelectionCircle = CreateComponent<GameEngineSpriteRenderer>();
	SelectionCircle->GetTransform()->SetLocalPosition(Render0->GetTransform()->GetLocalPosition());
	SelectionCircle->Off();	
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale(TileScale);
	Collision->GetTransform()->AddLocalScale({ -10.f, 0 });
	Collision->SetOrder(static_cast<int>(ColEnum::Unit));
	Collision->SetColType(ColType::AABBBOX2D);
	MinionNum++;	
	HP = 50;
	CurHp = 50;	
	Object::Start();
	if (true == IsOutside)
	{
		GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(1, 1));
		OutsideStateInit();
		IsOutside = !IsOutside;
	}
	else
	{
		GetTransform()->SetLocalPosition(DefenseMapEditor::ConvertTileXYToPos(2,2));
		InsideStateInit();
		IsOutside = !IsOutside;
	}
}

void Minion::OutSideTargetPosLoad(GameEngineSerializer& _Ser)
{
	int SaveNum;
	_Ser.Read(SaveNum);
	int x;
	int y;
	OutSideTargetPos.resize(SaveNum);
	for (int i = 0; i < SaveNum; i++)
	{

		_Ser.Read(x);
		_Ser.Read(y);

		float4 CheckPos = { static_cast<float>(x), static_cast<float>(y) };

		OutSideTargetPos[i] = CheckPos;
	}
}


void Minion::InSideTargetPosLoad(GameEngineSerializer& _Ser)
{
	int SaveNum;
	_Ser.Read(SaveNum);
	int x;
	int y;
	InSideTargetPos.resize(SaveNum);
	for (int i = 0; i < SaveNum; i++)
	{

		_Ser.Read(x);
		_Ser.Read(y);

		float4 CheckPos = { static_cast<float>(x), static_cast<float>(y) };

		InSideTargetPos[i] = CheckPos;
	}
}

void Minion::OutsideStateInit()
{

	FSM.CreateState(
		{ .Name = "Move",
		.Start = [this]() {
			if (0 != MPathPos.size())
			{
				TargetPos = *MPathPos.begin();
				MPathPos.erase(MPathPos.begin());
			}
			else
			{
				MPathPos = OutSideTargetPos;
				TargetPos = *MPathPos.begin();
				MPathPos.erase(MPathPos.begin());
			}
			MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, 0);
			{
				if (Angle < 10 || Angle >= 350)
				{
					Render0->ChangeAnimation("LMove");
					if (false == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = true;
					}
				}
				if (Angle < 80 && Angle >= 10)
				{
					Render0->ChangeAnimation("LUp45Move");

					if (false == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = true;
					}
				}

				if (Angle < 100 && Angle >= 80)
				{
					Render0->ChangeAnimation("UpMove");
				}
				if (Angle < 170 && Angle >= 100)
				{
					if (true == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = false;
					}
					Render0->ChangeAnimation("LUp45Move");
				}
				if (Angle < 190 && Angle >= 170)
				{
					Render0->ChangeAnimation("LMove");
					if (true == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = false;
					}
				}
				if (Angle < 260 && Angle >= 190)
				{
					Render0->ChangeAnimation("LDown45Move");
					if (true == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = false;
					}
				}
				if (Angle < 280 && Angle >= 260)
				{
					Render0->ChangeAnimation("DownMove");

				}
				if (Angle < 350 && Angle >= 280)
				{
					Render0->ChangeAnimation("LDown45Move");
					if (false == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = true;
					}
				}
			}
		},
		.Update = [this](float _DeltaTime)
		{
			GetTransform()->AddLocalPosition(MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, _DeltaTime));
			if (CurHp <= 0)
			{
				FSM.ChangeState("Die");
				return;
			}
			if (TargetPos.XYDistance(GetTransform()->GetLocalPosition()) <= 2.f)
			{
				FSM.ChangeState("Move");
			}

		},
		.End = [this]()
		{

		}
		}
	);

	FSM.CreateState(
		{ .Name = "Die",
		.Start = [this]()
		{
			Render0->ChangeAnimation("Die");
			Money += GetMoney;
			MinionNum--;
			this->ObjectDeath();
		},
		.Update = [this](float _DeltaTime)
		{
			if (true == Render0->IsAnimationEnd())
			{
				Death();
			}
		},
		.End = []() {}
		}
	);

	FSM.ChangeState("Move");
}

void Minion::InsideStateInit()
{

	FSM.CreateState(
		{ .Name = "Move",
		.Start = [this]() {
			if (0 != MPathPos.size())
			{
				TargetPos = *MPathPos.begin();
				MPathPos.erase(MPathPos.begin());
			}
			else
			{
				MPathPos = InSideTargetPos;
				TargetPos = *MPathPos.begin();
				MPathPos.erase(MPathPos.begin());
			}
			MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, 0);
			{
				if (Angle < 10 || Angle >= 350)
				{
					Render0->ChangeAnimation("LMove");
					if (false == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = true;
					}
				}
				if (Angle < 80 && Angle >= 10)
				{
					Render0->ChangeAnimation("LUp45Move");

					if (false == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = true;
					}
				}

				if (Angle < 100 && Angle >= 80)
				{
					Render0->ChangeAnimation("UpMove");
				}
				if (Angle < 170 && Angle >= 100)
				{
					if (true == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = false;
					}
					Render0->ChangeAnimation("LUp45Move");
				}
				if (Angle < 190 && Angle >= 170)
				{
					Render0->ChangeAnimation("LMove");
					if (true == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = false;
					}
				}
				if (Angle < 260 && Angle >= 190)
				{
					Render0->ChangeAnimation("LDown45Move");
					if (true == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = false;
					}
				}
				if (Angle < 280 && Angle >= 260)
				{
					Render0->ChangeAnimation("DownMove");

				}
				if (Angle < 350 && Angle >= 280)
				{
					Render0->ChangeAnimation("LDown45Move");
					if (false == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = true;
					}
				}
			}
		},
		.Update = [this](float _DeltaTime)
		{
			GetTransform()->AddLocalPosition(MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, _DeltaTime));
			if (CurHp <= 0)
			{
				FSM.ChangeState("Die");
				return;
			}
			if (TargetPos.XYDistance(GetTransform()->GetLocalPosition()) <= 2.f)
			{
				FSM.ChangeState("Move");
			}

		},
		.End = [this]()
		{

		}
		}
	);

	FSM.CreateState(
		{ .Name = "Die",
		.Start = [this]()
		{
			Render0->ChangeAnimation("Die");
			Money += GetMoney;
			MinionNum--;
			this->ObjectDeath();
		},
		.Update = [this](float _DeltaTime)
		{
			if (true == Render0->IsAnimationEnd())
			{
				Death();
			}
		},
		.End = []() {}
		}
	);

	FSM.ChangeState("Move");
}