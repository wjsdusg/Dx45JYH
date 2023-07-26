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
std::vector<float4> Minion::OutSideTargetPos;
std::vector<float4> Minion::InSideTargetPos;

void Minion::Update(float _DeltaTime)
{


}
void Minion::Start()
{
	MyTeam = Team::Enemy;
	
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

void Unit::StateInit()
{
	
	FSM.CreateState(
		{ .Name = "Move",
		.Start = [this]() {
			//경로계산


			if (0 != PathPos.size())
			{
				TargetPos = PathPos.front();
				PathPos.pop_front();
			}


			MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, 0);
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
			if (nullptr != TargetCol)
			{
				TargetCol = nullptr;
			}
		},
		.Update = [this](float _DeltaTime)
		{
			GetTransform()->AddLocalPosition(MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, _DeltaTime));
			float4 asd = GetTransform()->GetLocalPosition();
			if (TargetPos.XYDistance(GetTransform()->GetLocalPosition()) <= 2.f)
			{
				if (0 == PathPos.size())
				{
					FSM.ChangeState("Stay");
				}
				else
				{
					FSM.ChangeState("Move");
				}
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
			auto it = std::find(Units.begin(), Units.end(), DynamicThis<Unit>());
			if (it != Units.end())
			{
				std::swap(*it, Units.back());
				Units.pop_back();
			}
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

	FSM.ChangeState("Stay");
}