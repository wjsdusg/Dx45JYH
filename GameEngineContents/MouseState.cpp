#include "PrecompileHeader.h"
#include "Mouse.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include "UIButton.h"
#include "Unit.h"
#include "Building.h"
#include "Object.h"
#include "DragBox.h"
#include "UIButton.h"
#include "DefenseMapEditor.h"

void Mouse::DefenseFSMInit()
{
	DefenseFSM.CreateState
	(
		{
			.Name = "Default",
		.Start = [this]()
		{
			NewDragBox->Area = 0;
			Render0->ChangeAnimation("Default");
			UIButton::MainUIButton->FSM.ChangeState("Default");
		},
		.Update = [this](float _DeltaTime)
		{

			std::vector<std::shared_ptr<GameEngineCollision>> ColTest;

			if (nullptr != Collision->Collision(static_cast<int>(ColEnum::UIPannel), ColType::SPHERE2D, ColType::AABBBOX2D))
			{
				return;
			}
			if (Collision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::AABBBOX2D), 0 != ColTest.size())
			{
				if (AnimationEnd == false)
				{
					Render0->ChangeAnimation("MyTeamCusor");


					AnimationEnd = true;
				}
				bool check = false;
				if (true == GameEngineInput::IsUp("EngineMouseLeft"))
				{
					for (std::shared_ptr<GameEngineCollision> Col : ColTest)
					{
						std::shared_ptr<Unit> NewUnit = Col->GetActor()->DynamicThis<Unit>();
						std::shared_ptr<Building> NewBuilding = Col->GetActor()->DynamicThis<Building>();
						if (nullptr != NewUnit)
						{
							CopyUnit = NewUnit;
							ID = CopyUnit->UnitID;
							std::vector<std::shared_ptr<Unit>> Units = Unit::GetUnits();
							for (auto Start = Units.begin(); Start != Units.end(); Start++)
							{
								(*Start)->SetIsClick(false);
							}
							CopyUnit->SetIsClick(true);
							DefenseFSM.ChangeState("UnitClick");
							if (nullptr != CopyBuilding)
							{
								CopyBuilding->IsClick = false;
								CopyBuilding = nullptr;
							}
							return;
						}
						else if (nullptr != NewBuilding)
						{
							CopyBuilding = NewBuilding;							
							CopyBuilding->SetIsClick(true);
							DefenseFSM.ChangeState("BuildingClick");
						}
					}
					
				}
			}
			else
			{
				Render0->ChangeAnimation("Default");
			}

			if (true == GameEngineInput::IsPress("EngineMouseLeft"))
			{
				if (false == NewDragBox->IsUpdate())
				{
					NewDragBox->On();
					NewDragBox->SetMousePos(Collision->GetTransform()->GetLocalPosition());
				}
				NewDragBox->SetMouseMovePos(Collision->GetTransform()->GetLocalPosition());
				if (120.f < NewDragBox->Area)
				{
					DefenseFSM.ChangeState("DragBoxOn");
				}
			}
			else
			{
				NewDragBox->Off();
			}
		}
		,
		.End = []() {}
		}
	);
	DefenseFSM.CreateState
	(
		{
			.Name = "UnitClick",
		.Start = [this]()
		{
			NewDragBox->Area = 0;
			DoubleClickTimer = 0.f;
			UIButton::MainUIButton->FSM.ChangeState("UnitControl");
		},
		.Update = [this](float _DeltaTime)
		{
			if (nullptr != Collision->Collision(static_cast<int>(ColEnum::UIPannel), ColType::SPHERE2D, ColType::AABBBOX2D))
			{
				return;
			}
			std::vector<std::shared_ptr<GameEngineCollision>> ColTest;
			if (nullptr == CopyUnit)
			{
				DefenseFSM.ChangeState("Default");
			}//유닛클릭
			else if (Collision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::AABBBOX2D), 0 != ColTest.size())
			{
				if (AnimationEnd == false)
				{
					Render0->ChangeAnimation("MyTeamCusor");
					AnimationEnd = true;
				}
				bool check = false;
				if (true == GameEngineInput::IsUp("EngineMouseLeft"))
				{
					if (nullptr != CopyUnit)
					{
						for (std::shared_ptr<GameEngineCollision> Col : ColTest)
						{
							std::shared_ptr<Unit> NewUnit = Col->GetActor()->DynamicThis<Unit>();
							if (nullptr!= NewUnit&&ID == NewUnit->UnitID)
							{
								check = true;
							}

						}
					}
					if (nullptr != CopyUnit && true == CopyUnit->GetIsClick() && DoubleClickTimer < 0.5f && true == check && CopyUnit->MyTeam == Team::Mine)
					{
						std::vector<std::shared_ptr<Unit>> Units = Unit::GetUnits();
						for (auto Start = Units.begin(); Start != Units.end(); Start++)
						{
							if ((*Start)->MyTeam == Team::Mine && true == (*Start)->IsUpdate())
							{
								(*Start)->SetIsClick(true);
							}
						}
						DefenseFSM.ChangeState("UnitsClick");
					}
					else
					{
						for (std::shared_ptr<GameEngineCollision> Col : ColTest)
						{
							std::shared_ptr<Unit> NewUnit = Col->GetActor()->DynamicThis<Unit>();
							std::shared_ptr<Building> NewBuilding = Col->GetActor()->DynamicThis<Building>();
							if (nullptr != NewUnit)
							{
								CopyUnit = NewUnit;
								ID = CopyUnit->UnitID;
								std::vector<std::shared_ptr<Unit>> Units = Unit::GetUnits();
								for (auto Start = Units.begin(); Start != Units.end(); Start++)
								{
									(*Start)->SetIsClick(false);
								}
								CopyUnit->SetIsClick(true);
								DefenseFSM.ChangeState("UnitClick");
								if (nullptr != CopyBuilding)
								{
									CopyBuilding->IsClick = false;
									//CopyBuilding = nullptr;
								}
								return;
							}
							else if (nullptr != NewBuilding)
							{
								CopyBuilding = NewBuilding;
								CopyBuilding->SetIsClick(true);
								DefenseFSM.ChangeState("BuildingClick");
								if (nullptr != CopyUnit)
								{
									CopyUnit->IsClick = false;
									CopyUnit = nullptr;
								}

							}
						}

					}
				}
			}
			//유닛이 없는데 클릭하면 디폴트상태로 변경
			else if (false == Collision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::AABBBOX2D) && GameEngineInput::IsUp("EngineMouseLeft"))
			{
				std::vector<std::shared_ptr<Unit>> Units = Unit::GetUnits();
				for (auto Start = Units.begin(); Start != Units.end(); Start++)
				{
					(*Start)->SetIsClick(false);
				}
				if (nullptr != CopyUnit)
				{
					CopyUnit = nullptr;
				}
				Render0->ChangeAnimation("Default");
			}
			else if (true == GameEngineInput::IsUp("A"))
			{
				DefenseFSM.ChangeState("UnitClickAttack");
			}
			
			else if (true == GameEngineInput::IsUp("EngineMouseRight"))
			{
				CopyUnit->TargetPos = Collision->GetTransform()->GetLocalPosition();
			}
			else
			{
				Render0->ChangeAnimation("Default");
			}
			//드래그박스
			if (true == GameEngineInput::IsPress("EngineMouseLeft"))
			{
				if (false == NewDragBox->IsUpdate())
				{
					NewDragBox->On();
					NewDragBox->SetMousePos(Collision->GetTransform()->GetLocalPosition());
				}
				NewDragBox->SetMouseMovePos(Collision->GetTransform()->GetLocalPosition());
				if (120.f < NewDragBox->Area)
				{
					DefenseFSM.ChangeState("DragBoxOn");
				}
			}
			else
			{
				NewDragBox->Off();
			}
			//우클릭시 무브마커표시
			if (true == GameEngineInput::IsUp("EngineMouseRight"))
			{
				GetMoveMark(Collision->GetTransform()->GetLocalPosition());
			}
			DoubleClickTimer += _DeltaTime;
		}
		,
		.End = []()
			{

			}
		}
	);
	DefenseFSM.CreateState
	(
		{
			.Name = "UnitsClick",
		.Start = [this]()
		{
			CopyUnit = nullptr;
			NewDragBox->Area = 0;
			UIButton::MainUIButton->FSM.ChangeState("UnitControl");
		},
		.Update = [this](float _DeltaTime)
		{
			if (nullptr != Collision->Collision(static_cast<int>(ColEnum::UIPannel), ColType::SPHERE2D, ColType::AABBBOX2D))
			{
				return;
			}
			bool check = false;
			float MinDistance = 100000.f;
			std::vector<std::shared_ptr<GameEngineCollision>> ColTest;
			//유닛클릭시 유닛클릭상태로 이동
			if (Collision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::AABBBOX2D), 0 != ColTest.size())
			{

				if (AnimationEnd == false)
				{
					Render0->ChangeAnimation("MyTeamCusor");
					AnimationEnd = true;
				}

				if (true == GameEngineInput::IsUp("EngineMouseLeft"))
				{
					for (std::shared_ptr<GameEngineCollision> Col : ColTest)
					{
						std::shared_ptr<Unit> NewUnit = Col->GetActor()->DynamicThis<Unit>();
						if (nullptr == NewUnit)
						{
							continue;
						}
						CopyUnit = NewUnit;
						ID = CopyUnit->UnitID;
						std::vector<std::shared_ptr<Unit>> Units = Unit::GetUnits();
						for (auto Start = Units.begin(); Start != Units.end(); Start++)
						{
							(*Start)->SetIsClick(false);
						}
						CopyUnit->SetIsClick(true);

					}
					DefenseFSM.ChangeState("UnitClick");
				}

			}
			//빈공간클릭시 디폴트상태
			else if (false == Collision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::AABBBOX2D) && GameEngineInput::IsUp("EngineMouseLeft"))
			{
				std::vector<std::shared_ptr<Unit>> Units = Unit::GetUnits();
				for (auto Start = Units.begin(); Start != Units.end(); Start++)
				{
					(*Start)->SetIsClick(false);
				}
				DefenseFSM.ChangeState("Default");
			}
			//유닛이 한마리라도 클릭중인지 체크			
			else if (false == check)
			{
				std::vector<std::shared_ptr<Unit>> Units = Unit::GetUnits();
				for (auto Start = Units.begin(); Start != Units.end(); Start++)
				{
					if (true == (*Start)->GetIsClick())
					{
						check = true;
						break;
					}
				}
				if (false == check)
				{
					DefenseFSM.ChangeState("Default");
				}
				else if (true == check && true == GameEngineInput::IsUp("A"))
				{
					DefenseFSM.ChangeState("UnitsClickAttack");
				}
				
				else if (true == GameEngineInput::IsUp("EngineMouseRight"))
				{

					std::vector<std::shared_ptr<Unit>> Units = Unit::GetUnits();
					for (auto Start = Units.begin(); Start != Units.end(); Start++)
					{
						if (true == (*Start)->IsClick && (*Start)->GetTransform()->GetLocalPosition().XYDistance(Collision->GetTransform()->GetLocalPosition()) < MinDistance)
						{
							MinDistance = (*Start)->GetTransform()->GetLocalPosition().XYDistance(Collision->GetTransform()->GetLocalPosition());
							CopyUnit = *Start;

						}
					}
					float4 TargetIndex = DefenseMapEditor::ConvertPosToTileXY(Collision->GetTransform()->GetLocalPosition());
					int IndexX = TargetIndex.ix() - CopyUnit->IndexX;
					int IndexY = TargetIndex.iy() - CopyUnit->IndexY;
					float TargetAngle = CopyUnit->CalAngle(CopyUnit->GetTransform()->GetLocalPosition(), Collision->GetTransform()->GetLocalPosition());
					for (auto Start = Units.begin(); Start != Units.end(); Start++)
					{
						if (true == (*Start)->GetIsClick())
						{
							float4 UnitIndex = DefenseMapEditor::ConvertPosToTileXY((*Start)->GetTransform()->GetLocalPosition());
							int IndexUX = UnitIndex.ix();
							int IndexUY = UnitIndex.iy();
							IndexUX += IndexX;
							IndexUY += IndexY;
							(*Start)->TargetPos = DefenseMapEditor::ConvertTileXYToPos(IndexUX, IndexUY);
							
						}
					}
				}
				else
				{
					Render0->ChangeAnimation("Default");
				}
			}
			//가장가까운유닛 기준으로 이동

			//드래그박스
			if (true == GameEngineInput::IsPress("EngineMouseLeft"))
			{
				if (false == NewDragBox->IsUpdate())
				{
					NewDragBox->On();
					NewDragBox->SetMousePos(Collision->GetTransform()->GetLocalPosition());
				}
				NewDragBox->SetMouseMovePos(Collision->GetTransform()->GetLocalPosition());
				if (120.f < NewDragBox->Area)
				{
					DefenseFSM.ChangeState("DragBoxOn");
				}
			}
			else
			{
				NewDragBox->Off();
			}
			//우클릭시 무브마커표시
			if (true == GameEngineInput::IsUp("EngineMouseRight"))
			{
				GetMoveMark(Collision->GetTransform()->GetLocalPosition());
			}
		}
		,
		.End = []() {}
		}
	);
	DefenseFSM.CreateState
	(
		{
		.Name = "DragBoxOn",
		.Start = [this]()
		{

		}
		,
		.Update = [this](float _DeltaTime)
		{
			NewDragBox->SetMouseMovePos(Collision->GetTransform()->GetLocalPosition());
			if (true == GameEngineInput::IsUp("EngineMouseLeft"))
			{
				if (true == NewDragBox->AllCollision())
				{
					DefenseFSM.ChangeState("UnitsClick");
				}
				else
				{
					std::vector<std::shared_ptr<Unit>> Units = Unit::GetUnits();
					for (auto Start = Units.begin(); Start != Units.end(); Start++)
					{
						(*Start)->SetIsClick(false);
					}
					DefenseFSM.ChangeState("Default");
				}
			}

		}
		,
		.End = [this]()
		{
			if (nullptr != CopyBuilding)
			{
				CopyBuilding->IsClick = false;
			}
			NewDragBox->Area = 0;
			NewDragBox->Off();
		}
		}
	);
	DefenseFSM.CreateState
	(
		{
			.Name = "UnitClickAttack",
		.Start = [this]()
		{
			Render0->ChangeAnimation("AClick");
		},
		.Update = [this](float _DeltaTime)
		{


			if (true == CopyUnit->IsDeath())
			{
				DefenseFSM.ChangeState("Default");
			}
			else if (true == GameEngineInput::IsUp("EngineMouseLeft"))
			{
				CopyUnit->TargetPos = Collision->GetTransform()->GetLocalPosition();
				GetMoveMark(Collision->GetTransform()->GetLocalPosition());
				DefenseFSM.ChangeState("UnitsClick");
			}
			else if (true == GameEngineInput::IsUp("EngineMouseRight"))
			{
				DefenseFSM.ChangeState("UnitsClick");
			}
		}
		,
		.End = []()
		{

		}
		}
	);
	DefenseFSM.CreateState
	(
		{
			.Name = "UnitsClickAttack",
		.Start = [this]()
		{
			Render0->ChangeAnimation("AClick");
		},
		.Update = [this](float _DeltaTime)
		{
			if (nullptr != Collision->Collision(static_cast<int>(ColEnum::UIPannel), ColType::SPHERE2D, ColType::AABBBOX2D))
			{
				return;
			}
			bool check = false;
			float MinDistance = 100000.f;
			std::vector<std::shared_ptr<GameEngineCollision>> ColTest;

			//유닛이 한마리라도 클릭중인지 체크			

				std::vector<std::shared_ptr<Unit>> Units = Unit::GetUnits();
				for (auto Start = Units.begin(); Start != Units.end(); Start++)
				{
					if (true == (*Start)->GetIsClick())
					{
						check = true;
						break;
					}
				}
				if (false == check)
				{
					DefenseFSM.ChangeState("Default");
				}
				else if (true == GameEngineInput::IsUp("EngineMouseLeft"))
				{
					std::vector<std::shared_ptr<Unit>> Units = Unit::GetUnits();
					for (auto Start = Units.begin(); Start != Units.end(); Start++)
					{
						if (true == (*Start)->IsClick && (*Start)->GetTransform()->GetLocalPosition().XYDistance(Collision->GetTransform()->GetLocalPosition()) < MinDistance)
						{
							MinDistance = (*Start)->GetTransform()->GetLocalPosition().XYDistance(Collision->GetTransform()->GetLocalPosition());
							CopyUnit = *Start;

						}
					}
					float4 TargetIndex = DefenseMapEditor::ConvertPosToTileXY(Collision->GetTransform()->GetLocalPosition());
					int IndexX = TargetIndex.ix() - CopyUnit->IndexX;
					int IndexY = TargetIndex.iy() - CopyUnit->IndexY;
					float TargetAngle = CopyUnit->CalAngle(CopyUnit->GetTransform()->GetLocalPosition(), Collision->GetTransform()->GetLocalPosition());
					for (auto Start = Units.begin(); Start != Units.end(); Start++)
					{
						if (true == (*Start)->GetIsClick())
						{
							float4 UnitIndex = DefenseMapEditor::ConvertPosToTileXY((*Start)->GetTransform()->GetLocalPosition());
							int IndexUX = UnitIndex.ix();
							int IndexUY = UnitIndex.iy();
							IndexUX += IndexX;
							IndexUY += IndexY;
							(*Start)->TargetPos = DefenseMapEditor::ConvertTileXYToPos(IndexUX, IndexUY);

						}
					}
					GetMoveMark(Collision->GetTransform()->GetLocalPosition());
					DefenseFSM.ChangeState("UnitsClick");
				}
				else if (true == GameEngineInput::IsUp("EngineMouseRight"))
				{
					DefenseFSM.ChangeState("UnitsClick");
				}
		}
		,
		.End = []()
		{

		}
		}
	);
	DefenseFSM.CreateState
	(
		{
			.Name = "UnitClickMove",
		.Start = [this]()
		{
			Render0->ChangeAnimation("Default");

		},
		.Update = [this](float _DeltaTime)
		{
			bool check = false;
			std::vector<std::shared_ptr<Unit>> Units = Unit::GetUnits();
				for (auto Start = Units.begin(); Start != Units.end(); Start++)
				{
					if (true == (*Start)->GetIsClick())
					{
						check = true;
						break;
					}
				}
				if (false == check)
				{
					DefenseFSM.ChangeState("Default");
				}
				else if (true == GameEngineInput::IsUp("EngineMouseLeft"))
				{
					DefenseFSM.ChangeState("UnitsClick");

				}
				else if (true == GameEngineInput::IsUp("EngineMouseRight"))
				{
					DefenseFSM.ChangeState("UnitsClick");

				}

		}
		,
		.End = []()
		{

		}
		}
	);
	DefenseFSM.CreateState
	(
		{
			.Name = "UnitClickPatrol",
		.Start = [this]()
		{
			Render0->ChangeAnimation("Patrol");

		},
		.Update = [this](float _DeltaTime)
		{
			bool check = false;
			std::vector<std::shared_ptr<Unit>> Units = Unit::GetUnits();
				for (auto Start = Units.begin(); Start != Units.end(); Start++)
				{
					if (true == (*Start)->GetIsClick())
					{
						check = true;
						break;
					}
				}
				if (false == check)
				{
					DefenseFSM.ChangeState("Default");
				}
				else if (true == GameEngineInput::IsUp("EngineMouseLeft"))
				{
					DefenseFSM.ChangeState("UnitsClick");

				}
				else if (true == GameEngineInput::IsUp("EngineMouseRight"))
				{
					DefenseFSM.ChangeState("UnitsClick");

				}

		}
		,
		.End = []()
		{


		}
		}
	);

	DefenseFSM.CreateState
	(
		{
			.Name = "BuildingClick",
		.Start = [this]()
		{
			NewDragBox->Area = 0;
			
			UIButton::MainUIButton->FSM.ChangeState("BuildingControl");
		},
		.Update = [this](float _DeltaTime)
		{
			if (nullptr != Collision->Collision(static_cast<int>(ColEnum::UIPannel), ColType::SPHERE2D, ColType::AABBBOX2D))
			{
				return;
			}
			std::vector<std::shared_ptr<GameEngineCollision>> ColTest;
			
			if (Collision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::AABBBOX2D), 0 != ColTest.size())
			{
				if (AnimationEnd == false)
				{
					Render0->ChangeAnimation("MyTeamCusor");
					AnimationEnd = true;
				}
				
				if (true == GameEngineInput::IsUp("EngineMouseLeft"))
				{			

					CopyBuilding->IsClick = true;
				}
			}
			//유닛이 없는데 클릭하면 디폴트상태로 변경
			else if (false == Collision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::AABBBOX2D) && GameEngineInput::IsUp("EngineMouseLeft"))
			{
				CopyBuilding->IsClick = false;
				DefenseFSM.ChangeState("Default");
			}
			else
			{
				Render0->ChangeAnimation("Default");
			}
			//드래그박스
			if (true == GameEngineInput::IsPress("EngineMouseLeft"))
			{
				if (false == NewDragBox->IsUpdate())
				{
					NewDragBox->On();
					NewDragBox->SetMousePos(Collision->GetTransform()->GetLocalPosition());
				}
				NewDragBox->SetMouseMovePos(Collision->GetTransform()->GetLocalPosition());
				if (120.f < NewDragBox->Area)
				{
					
					DefenseFSM.ChangeState("DragBoxOn");
				}
			}
			else
			{
				NewDragBox->Off();
			}
			
			
		}
		,
		.End = []()
			{

			}
		}
	);
	DefenseFSM.ChangeState("Default");
}