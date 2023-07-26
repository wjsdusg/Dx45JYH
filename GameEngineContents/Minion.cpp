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
//
//void Unit::StateInit()
//{
//	FSM.CreateState(
//		{ .Name = "Stay",
//		.Start = [this]()
//		{
//
//			if (Angle < 10 || Angle >= 350)
//			{
//				Render0->ChangeAnimation("LStay");
//				if (false == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = true;
//				}
//			}
//			if (Angle < 80 && Angle >= 10)
//			{
//				Render0->ChangeAnimation("LUp45Stay");
//				if (false == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = true;
//				}
//			}
//
//			if (Angle < 100 && Angle >= 80)
//			{
//				Render0->ChangeAnimation("UpStay");
//			}
//			if (Angle < 170 && Angle >= 100)
//			{
//				if (true == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = false;
//				}
//				Render0->ChangeAnimation("LUp45Stay");
//			}
//			if (Angle < 190 && Angle >= 170)
//			{
//				Render0->ChangeAnimation("LStay");
//				if (true == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = false;
//				}
//			}
//			if (Angle < 260 && Angle >= 190)
//			{
//				Render0->ChangeAnimation("LDown45Stay");
//				if (true == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = false;
//				}
//			}
//			if (Angle < 280 && Angle >= 260)
//			{
//				Render0->ChangeAnimation("DownStay");
//
//			}
//			if (Angle < 350 && Angle >= 280)
//			{
//				Render0->ChangeAnimation("LDown45Stay");
//				if (false == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = true;
//				}
//			}
//		},
//		.Update = [this](float _DeltaTime)
//		{
//
//			if (nullptr != FOVCollision && nullptr != FOVCollision->Collision(ColEnum::Enemy,ColType::SPHERE2D,ColType::AABBBOX2D) && false == IsHold)
//			{
//				TargetCol = FOVCollision->Collision(ColEnum::Enemy, ColType::SPHERE2D, ColType::AABBBOX2D);
//				TargetPos = TargetCol->GetActor()->GetTransform()->GetLocalPosition();
//				PrePos = GetTransform()->GetLocalPosition();
//				float s2 = GetTransform()->GetLocalPosition().XYDistance(TargetCol->GetTransform()->GetWorldPosition());
//				FSM.ChangeState("Chase");
//			}
//			if (true == IsHold && nullptr != Collision->Collision(ColEnum::Enemy, ColType::SPHERE2D, ColType::AABBBOX2D))
//			{
//				TargetPos = Collision->Collision(ColEnum::Enemy, ColType::SPHERE2D, ColType::AABBBOX2D)->GetActor()->GetTransform()->GetLocalPosition();
//				FSM.ChangeState("HoldAttack");
//			}
//		},
//		.End = []() {}
//		}
//	);
//	FSM.CreateState(
//		{ .Name = "Move",
//		.Start = [this]() {
//			//경로계산
//
//
//			if (0 != PathPos.size())
//			{
//				TargetPos = PathPos.front();
//				PathPos.pop_front();
//			}
//
//
//			MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, 0);
//			if (Angle < 10 || Angle >= 350)
//			{
//				Render0->ChangeAnimation("LMove");
//				if (false == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = true;
//				}
//			}
//			if (Angle < 80 && Angle >= 10)
//			{
//				Render0->ChangeAnimation("LUp45Move");
//
//				if (false == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = true;
//				}
//			}
//
//			if (Angle < 100 && Angle >= 80)
//			{
//				Render0->ChangeAnimation("UpMove");
//			}
//			if (Angle < 170 && Angle >= 100)
//			{
//				if (true == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = false;
//				}
//				Render0->ChangeAnimation("LUp45Move");
//			}
//			if (Angle < 190 && Angle >= 170)
//			{
//				Render0->ChangeAnimation("LMove");
//				if (true == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = false;
//				}
//			}
//			if (Angle < 260 && Angle >= 190)
//			{
//				Render0->ChangeAnimation("LDown45Move");
//				if (true == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = false;
//				}
//			}
//			if (Angle < 280 && Angle >= 260)
//			{
//				Render0->ChangeAnimation("DownMove");
//
//			}
//			if (Angle < 350 && Angle >= 280)
//			{
//				Render0->ChangeAnimation("LDown45Move");
//				if (false == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = true;
//				}
//			}
//			if (nullptr != TargetCol)
//			{
//				TargetCol = nullptr;
//			}
//		},
//		.Update = [this](float _DeltaTime)
//		{
//			GetTransform()->AddLocalPosition(MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, _DeltaTime));
//			float4 asd = GetTransform()->GetLocalPosition();
//			if (TargetPos.XYDistance(GetTransform()->GetLocalPosition()) <= 2.f)
//			{
//				if (0 == PathPos.size())
//				{
//					FSM.ChangeState("Stay");
//				}
//				else
//				{
//					FSM.ChangeState("Move");
//				}
//			}
//
//		},
//		.End = [this]()
//		{
//
//		}
//		}
//	);
//	FSM.CreateState(
//		{ .Name = "Chase",
//		.Start = [this]() {
//			//Angle계산
//			MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, 0);
//			if (Angle < 10 || Angle >= 350)
//			{
//				Render0->ChangeAnimation("LMove");
//				if (false == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = true;
//				}
//			}
//			if (Angle < 80 && Angle >= 10)
//			{
//				Render0->ChangeAnimation("LUp45Move");
//				if (false == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = true;
//				}
//			}
//
//			if (Angle < 100 && Angle >= 80)
//			{
//				Render0->ChangeAnimation("UpMove");
//			}
//			if (Angle < 170 && Angle >= 100)
//			{
//				if (true == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = false;
//				}
//				Render0->ChangeAnimation("LUp45Move");
//			}
//			if (Angle < 190 && Angle >= 170)
//			{
//				Render0->ChangeAnimation("LMove");
//				if (true == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = false;
//				}
//			}
//			if (Angle < 260 && Angle >= 190)
//			{
//				Render0->ChangeAnimation("LDown45Move");
//				if (true == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = false;
//				}
//			}
//			if (Angle < 280 && Angle >= 260)
//			{
//				Render0->ChangeAnimation("DownMove");
//
//			}
//			if (Angle < 350 && Angle >= 280)
//			{
//				Render0->ChangeAnimation("LDown45Move");
//				if (false == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = true;
//				}
//			}
//			PreAngle = Angle;
//		},
//		.Update = [this](float _DeltaTime)
//		{
//			float s = abs(FOVCollision->GetTransform()->GetLocalScale().x);
//			float s2 = GetTransform()->GetLocalPosition().XYDistance(TargetCol->GetTransform()->GetWorldPosition());
//
//			if (nullptr != FOVCollision && nullptr != TargetCol)
//			{
//				TargetPos = TargetCol->GetActor()->GetTransform()->GetLocalPosition();
//			}
//			if (20.f <= abs(PreAngle - Angle))
//			{
//				FSM.ChangeState("Chase");
//			}
//
//			if (nullptr == TargetCol || true == TargetCol->GetActor()->IsDeath())
//			{
//				TargetCol = nullptr;
//				FSM.ChangeState("Stay");
//			}
//			//시야 범위 벗어나면 기존자리 복귀
//
//			else if (s
//				< s2
//				)
//			{
//				//TargetCol = FOVCollision->Collision(ColEnum::Enemy, ColType::SPHERE2D, ColType::AABBBOX2D);
//				TargetCol = nullptr;
//				TargetPos = PrePos;
//				FSM.ChangeState("Move");
//			}
//			//적크기와같아지면 공격
//			else if (
//				TargetPos.XYDistance(GetTransform()->GetLocalPosition())
//				<= (TargetCol->GetActor()->DynamicThis<Unit>()->GetCollsion()->GetTransform()->GetLocalScale().x)
//				)
//			{
//				FSM.ChangeState("Attack");
//			}
//			//안에서 각도계산도해줌
//			GetTransform()->AddLocalPosition(MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, _DeltaTime));
//		},
//		.End = []() {}
//		}
//	);
//
//	FSM.CreateState(
//		{ .Name = "Attack",
//		.Start = [this]()
//		{
//			MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, 0);
//			if (Angle < 10 || Angle >= 350)
//			{
//				Render0->ChangeAnimation("LAttack");
//				if (false == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = true;
//				}
//			}
//			if (Angle < 80 && Angle >= 10)
//			{
//				Render0->ChangeAnimation("LUp45Attack");
//				if (false == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = true;
//				}
//			}
//
//			if (Angle < 100 && Angle >= 80)
//			{
//				Render0->ChangeAnimation("UpAttack");
//			}
//			if (Angle < 170 && Angle >= 100)
//			{
//				if (true == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = false;
//				}
//				Render0->ChangeAnimation("LUp45Attack");
//			}
//			if (Angle < 190 && Angle >= 170)
//			{
//				Render0->ChangeAnimation("LAttack");
//				if (true == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = false;
//				}
//			}
//			if (Angle < 260 && Angle >= 190)
//			{
//				Render0->ChangeAnimation("LDown45Attack");
//				if (true == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = false;
//				}
//			}
//			if (Angle < 280 && Angle >= 260)
//			{
//				Render0->ChangeAnimation("DownAttack");
//
//			}
//			if (Angle < 350 && Angle >= 280)
//			{
//				Render0->ChangeAnimation("LDown45Attack");
//				if (false == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = true;
//				}
//			}
//			PreAngle = Angle;
//		},
//		.Update = [this](float _DeltaTime)
//		{
//			if (Render0->IsAnimationEnd())
//			{
//				//AnimationEnd = true;
//				//각도계산용
//				MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, 0);
//
//				if (true == TargetCol->GetActor()->IsDeath())
//				{
//					TargetCol = nullptr;
//					FSM.ChangeState("Stay");
//				}
//				else
//				{
//					TargetPos = TargetCol->GetActor()->DynamicThis<Unit>()->GetTransform()->GetLocalPosition();
//					if (
//						TargetPos.XYDistance(GetTransform()->GetLocalPosition())
//						> (TargetCol->GetActor()->DynamicThis<Unit>()->GetCollsion()->GetTransform()->GetLocalScale().x)
//						)
//					{
//						FSM.ChangeState("Chase");
//					}
//				}
//
//				if (20.f <= abs(PreAngle - Angle))
//				{
//					FSM.ChangeState("Attack");
//				}
//
//			}
//
//		},
//		.End = []() {}
//		}
//	);
//	FSM.CreateState(
//		{ .Name = "HoldAttack",
//		.Start = [this]()
//		{
//			//각도계산용
//			MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, 0);
//
//			if (Angle < 10 || Angle >= 350)
//			{
//				Render0->ChangeAnimation("LAttack");
//				if (false == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = true;
//				}
//			}
//			if (Angle < 80 && Angle >= 10)
//			{
//				Render0->ChangeAnimation("LUp45Attack");
//				if (false == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = true;
//				}
//			}
//
//			if (Angle < 100 && Angle >= 80)
//			{
//				Render0->ChangeAnimation("UpAttack");
//			}
//			if (Angle < 170 && Angle >= 100)
//			{
//				if (true == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = false;
//				}
//				Render0->ChangeAnimation("LUp45Attack");
//			}
//			if (Angle < 190 && Angle >= 170)
//			{
//				Render0->ChangeAnimation("LAttack");
//				if (true == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = false;
//				}
//			}
//			if (Angle < 260 && Angle >= 190)
//			{
//				Render0->ChangeAnimation("LDown45Attack");
//				if (true == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = false;
//				}
//			}
//			if (Angle < 280 && Angle >= 260)
//			{
//				Render0->ChangeAnimation("DownAttack");
//
//			}
//			if (Angle < 350 && Angle >= 280)
//			{
//				Render0->ChangeAnimation("LDown45Attack");
//				if (false == IsFlip)
//				{
//					Render0->SetFlipX();
//					IsFlip = true;
//				}
//			}
//			PreAngle = Angle;
//		},
//		.Update = [this](float _DeltaTime)
//		{
//			if (Render0->IsAnimationEnd())
//			{
//			MovePointTowardsTarget(GetTransform()->GetLocalPosition(), TargetPos, Speed, 0);
//				if (20.f <= abs(PreAngle - Angle))
//				{
//					FSM.ChangeState("HoldAttack");
//				}
//				if (nullptr == Collision->Collision(ColEnum::Enemy, ColType::SPHERE2D, ColType::AABBBOX2D))
//				{
//					FSM.ChangeState("Stay");
//				}
//			}
//		},
//		.End = []() {}
//		}
//	);
//	FSM.CreateState(
//		{ .Name = "Die",
//		.Start = [this]()
//		{
//			Render0->ChangeAnimation("Die");
//			auto it = std::find(Units.begin(), Units.end(), DynamicThis<Unit>());
//			if (it != Units.end())
//			{
//				std::swap(*it, Units.back());
//				Units.pop_back();
//			}
//			this->ObjectDeath();
//		},
//		.Update = [this](float _DeltaTime)
//		{
//			if (true == Render0->IsAnimationEnd())
//			{
//				Death();
//			}
//		},
//		.End = []() {}
//		}
//	);
//
//	FSM.ChangeState("Stay");
//}