#include "PrecompileHeader.h"
#include "Unit.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineTileMapRenderer.h>
#include "ContentsEnum.h"
#include "MapOverlay.h"
#include "Minion.h"
#include "Mouse.h"
#include "GlobalValue.h"
#include "DefenseMapEditor.h"
#include "Building.h"

extern float CalAngle1To2(float4 _Pos1, float4 _Pos2);
extern float4 MainMouse;
extern float4 IsoTileScale;
extern float4 MapUpP;
extern float4 TileScale;



void Unit::DefenseMapStateInit()
{
	DefenseMapFSM.CreateState(
		{ .Name = "Stay",
		.Start = [this]()
		{
			IsHold = true;
			if (Angle < 10 || Angle >= 350)
			{
				Render0->ChangeAnimation("LStay");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}
			else if (Angle < 80 && Angle >= 10)
			{
				Render0->ChangeAnimation("LUp45Stay");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}

			else if (Angle < 100 && Angle >= 80)
			{
				Render0->ChangeAnimation("UpStay");
			}
			else if (Angle < 170 && Angle >= 100)
			{
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
				Render0->ChangeAnimation("LUp45Stay");
			}
			else if (Angle < 190 && Angle >= 170)
			{
				Render0->ChangeAnimation("LStay");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			else if (Angle < 260 && Angle >= 190)
			{
				Render0->ChangeAnimation("LDown45Stay");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			else if (Angle < 280 && Angle >= 260)
			{
				Render0->ChangeAnimation("DownStay");

			}
			else if (Angle < 350 && Angle >= 280)
			{
				Render0->ChangeAnimation("LDown45Stay");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}
			float4 _Pos = DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
			IndexX = _Pos.ix();
			IndexY = _Pos.iy();
			float4 _Pos2 = DefenseMapEditor::ConvertTileXYToPos(IndexX, IndexY);
			GetTransform()->SetLocalPosition(_Pos2);
			DefenseGlobalValue::Collision->SetAt(IndexX, IndexY);
		},
		.Update = [this](float _DeltaTime)
		{
			if (0 >= CurHp)
			{
				DefenseMapFSM.ChangeState("Die");
				return;
			}
			float4 _Pos = DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
			if (IndexX != _Pos.x || IndexY != _Pos.y)
			{
				DefenseGlobalValue::Collision->ClrAt(IndexX, IndexY);
				IndexX = _Pos.ix();
				IndexY = _Pos.iy();
				float4 _Pos2 = DefenseMapEditor::ConvertTileXYToPos(IndexX, IndexY);
				GetTransform()->SetLocalPosition(_Pos2);
				DefenseGlobalValue::Collision->SetAt(IndexX, IndexY);
			}
			//유닛우선 쫒기
			std::vector<std::shared_ptr<GameEngineCollision>> ColTest;
			if (nullptr != FOVCollision
				&& FOVCollision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::AABBBOX2D)
				&& 1 < ColTest.size()
				&& false == IsHold)
			{
				for (std::shared_ptr<GameEngineCollision> Col : ColTest)
				{
					std::shared_ptr<Object> NewObject = Col->GetActor()->DynamicThis<Object>();
					if (nullptr == NewObject)
					{
						continue;
					}
					else if (NewObject == DynamicThis<Object>())
					{
						continue;
					}
					else if (MyTeam != NewObject->GetTeam())
					{
						CopyObject = NewObject;
						TargetPos = CopyObject->GetTransform()->GetLocalPosition();
						PrePos = GetTransform()->GetLocalPosition();
						DefenseMapPathCal();
						CopyIndexX = DefenseMapEditor::ConvertPosToTileXY(CopyObject->GetTransform()->GetLocalPosition()).ix();
						CopyIndexY = DefenseMapEditor::ConvertPosToTileXY(CopyObject->GetTransform()->GetLocalPosition()).iy();
						if (AttackType::Far == MyAttackType)
						{
							CalAngle(GetTransform()->GetLocalPosition(), CopyObject->GetTransform()->GetWorldPosition());
							DefenseMapFSM.ChangeState("Attack");
							return;
						}
						else
						{
							
							return;
						}

					}
				}
			}
			if (AttackType::Near == MyAttackType)
			{
				if (nullptr != Collision
					&& Collision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::AABBBOX2D, ColType::AABBBOX2D)
					&& 1 < ColTest.size()
					&& true == IsHold)
				{
					for (std::shared_ptr<GameEngineCollision> Col : ColTest)
					{
						std::shared_ptr<Object> NewObject = Col->GetActor()->DynamicThis<Object>();
						if (nullptr == NewObject)
						{
							continue;
						}
						else if (NewObject == DynamicThis<Object>())
						{
							continue;
						}
						else if (MyTeam != NewObject->GetTeam())
						{
							CopyObject = NewObject;
							DefenseMapFSM.ChangeState("HoldAttack");
							return;
						}
					}

				}
			}
			else if (AttackType::Far == MyAttackType)
			{
				if (nullptr != FOVCollision
					&& FOVCollision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::AABBBOX2D)
					&& 1 < ColTest.size()
					&& true == IsHold)
				{
					for (std::shared_ptr<GameEngineCollision> Col : ColTest)
					{
						std::shared_ptr<Object> NewObject = Col->GetActor()->DynamicThis<Object>();
						if (nullptr == NewObject)
						{
							continue;
						}
						else if (NewObject == DynamicThis<Object>())
						{
							continue;
						}
						else if (MyTeam != NewObject->GetTeam())
						{
							CopyObject = NewObject;
							DefenseMapFSM.ChangeState("HoldAttack");
							return;
						}
					}

				}
			}



		},
		.End = []() {}
		}
	);
	DefenseMapFSM.CreateState(
		{ .Name = "Move",
		.Start = [this]() {
			//경로계산

			if (0 != PathPos.size())
			{

				if (GetTransform()->GetLocalPosition() == PathPos.front())
				{
					float4 Pos2 = DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());

					PathPos.pop_front();

				}
				InterTargetPos = PathPos.front();

				PathPos.pop_front();

				//각도계산
				PreAngle = Angle;
				CalAngle(GetTransform()->GetLocalPosition(), InterTargetPos);
				//지금 내가 가는 방향에 장애물이 없다면 그타일을 미리선점하고 그쪽으로 움직인다.
				if (false == IsNextDefenseMapTileCollision())
				{

					//현재위치콜리전 삭제
					DefenseGlobalValue::Collision->ClrAt(IndexX, IndexY);
					if (DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition()) == DefenseMapEditor::ConvertPosToTileXY(InterTargetPos)/*&&180>abs(PreAngle-Angle)*/)
					{
						float4 _Pos = DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());

						IndexX = _Pos.ix();
						IndexY = _Pos.iy();
						DefenseGlobalValue::Collision->SetAt(IndexX, IndexY);

						ShortTargetPos = DefenseMapEditor::ConvertTileXYToPos(IndexX, IndexY);
					}
					else
					{
						//각도를 알기떄문에 그냥 쓰면된다
						float4 Pos = DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
						IndexX = Pos.ix();
						IndexY = Pos.iy();

						Pos = ReturnIndexPlusPos();
						IndexX = Pos.ix();
						IndexY = Pos.iy();

						DefenseGlobalValue::Collision->SetAt(IndexX, IndexY);

						ShortTargetPos = DefenseMapEditor::ConvertTileXYToPos(IndexX, IndexY);
					}

				}
				else if (true == IsNextDefenseMapTileCollision())
				{
					//경로계산
					DefenseMapPathCal();
					if (0 != PathPos.size())
					{
						if (DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition()) == DefenseMapEditor::ConvertPosToTileXY(PathPos.front()))
						{
							PathPos.pop_front();
						}
						InterTargetPos = PathPos.front();

						PathPos.pop_front();

						CalAngle(DefenseMapEditor::ConvertPosToTilePos(GetTransform()->GetLocalPosition()), InterTargetPos);

						//현재위치콜리전 삭제
						DefenseGlobalValue::Collision->ClrAt(IndexX, IndexY);
						//각도를 알기떄문에 그냥 쓰면된다
						if (DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition()) == DefenseMapEditor::ConvertPosToTileXY(InterTargetPos)/*&&180>abs(PreAngle-Angle)*/)
						{
							float4 _Pos = DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());

							IndexX = _Pos.ix();
							IndexY = _Pos.iy();
							DefenseGlobalValue::Collision->SetAt(IndexX, IndexY);

							ShortTargetPos = DefenseMapEditor::ConvertTileXYToPos(IndexX, IndexY);
						}
						else
						{
							//각도를 알기떄문에 그냥 쓰면된다
							float4 Pos = DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
							IndexX = Pos.ix();
							IndexY = Pos.iy();

							Pos = ReturnIndexPlusPos();
							IndexX = Pos.ix();
							IndexY = Pos.iy();

							DefenseGlobalValue::Collision->SetAt(IndexX, IndexY);

							ShortTargetPos = DefenseMapEditor::ConvertTileXYToPos(IndexX, IndexY);
						}
					}
				}
			}


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
				else if (Angle < 80 && Angle >= 10)
				{
					Render0->ChangeAnimation("LUp45Move");

					if (false == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = true;
					}
				}
				else if (Angle < 100 && Angle >= 80)
				{
					Render0->ChangeAnimation("UpMove");
				}
				else if (Angle < 170 && Angle >= 100)
				{
					if (true == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = false;
					}
					Render0->ChangeAnimation("LUp45Move");
				}
				else if (Angle < 190 && Angle >= 170)
				{
					Render0->ChangeAnimation("LMove");
					if (true == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = false;
					}
				}
				else if (Angle < 260 && Angle >= 190)
				{
					Render0->ChangeAnimation("LDown45Move");
					if (true == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = false;
					}
				}
				else if (Angle < 280 && Angle >= 260)
				{
					Render0->ChangeAnimation("DownMove");

				}
				else if (Angle < 350 && Angle >= 280)
				{
					Render0->ChangeAnimation("LDown45Move");
					if (false == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = true;
					}
				}
			}

			if (nullptr != CopyObject)
			{
				CopyObject = nullptr;
			}
		},
		.Update = [this](float _DeltaTime)
		{
			if (0 >= CurHp)
			{
				DefenseMapFSM.ChangeState("Die");
				return;
			}
			GetTransform()->AddLocalPosition(MovePointTowardsTarget(GetTransform()->GetLocalPosition(), InterTargetPos, Speed, _DeltaTime));
			if (ShortTargetPos == InterTargetPos && InterTargetPos.XYDistance(GetTransform()->GetLocalPosition()) <= 2.f)
			{
				GetTransform()->SetLocalPosition(InterTargetPos);
				if (0 == PathPos.size())
				{
					DefenseMapFSM.ChangeState("Stay");
				}
				else if (true == IsHold)
				{
					DefenseMapFSM.ChangeState("Stay");
				}
				else
				{
					DefenseMapFSM.ChangeState("Move");
				}
			}
			else
			{
				if (ShortTargetPos.XYDistance(GetTransform()->GetLocalPosition()) <= 2.f)
				{
					if (true == IsHold)
					{
						DefenseMapFSM.ChangeState("Stay");
					}
					else if (false == IsNextDefenseMapTileCollision())
					{

						DefenseGlobalValue::Collision->ClrAt(IndexX, IndexY);
						//각도를 알기떄문에 그냥 쓰면된다						
						float4 Pos = ReturnIndexPlusPos();
						IndexX = Pos.ix();
						IndexY = Pos.iy();
						DefenseGlobalValue::Collision->SetAt(IndexX, IndexY);
						ShortTargetPos = DefenseMapEditor::ConvertTileXYToPos(IndexX, IndexY);
					}
					else if (true == IsNextDefenseMapTileCollision())
					{
						DefenseMapPathCal();
						DefenseMapFSM.ChangeState("Move");
					}
				}
			}

		},
		.End = [this]()
		{

		}
		}
	);
	//쫒기전에 타겟콜을 미리 지정해줘야한다.
	DefenseMapFSM.CreateState(
		{ .Name = "Chase",
		.Start = [this]()
		{
			if (0 != PathPos.size())
			{

				if (GetTransform()->GetLocalPosition() == PathPos.front())
				{
					PathPos.pop_front();
				}
				InterTargetPos = PathPos.front();
				PathPos.pop_front();

				//각도계산				
				CalAngle(GetTransform()->GetLocalPosition(), InterTargetPos);
				//지금 내가 가는 방향에 장애물이 없다면 그타일을 미리선점하고 그쪽으로 움직인다.
				if (false == IsNextDefenseMapTileCollision())
				{
					//현재위치콜리전 삭제
					DefenseGlobalValue::Collision->ClrAt(IndexX, IndexY);
					if (DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition()) == DefenseMapEditor::ConvertPosToTileXY(InterTargetPos)/*&&180>abs(PreAngle-Angle)*/)
					{
						float4 _Pos = DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
						IndexX = _Pos.ix();
						IndexY = _Pos.iy();
						DefenseGlobalValue::Collision->SetAt(IndexX, IndexY);

						ShortTargetPos = DefenseMapEditor::ConvertTileXYToPos(IndexX, IndexY);
						InterTargetPos = ShortTargetPos;
					}
					else
					{
						float4 Pos = DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
						IndexX = Pos.ix();
						IndexY = Pos.iy();

						Pos = ReturnIndexPlusPos();
						IndexX = Pos.ix();
						IndexY = Pos.iy();

						DefenseGlobalValue::Collision->SetAt(IndexX, IndexY);
						ShortTargetPos = DefenseMapEditor::ConvertTileXYToPos(IndexX, IndexY);
						InterTargetPos = ShortTargetPos;
					}

				}
				else if (true == IsNextDefenseMapTileCollision())
				{
					//경로계산
					DefenseMapPathCal();
					if (0 != PathPos.size())
					{
						if (DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition()) == DefenseMapEditor::ConvertPosToTileXY(PathPos.front()))
						{
							PathPos.pop_front();
						}
						InterTargetPos = PathPos.front();

						PathPos.pop_front();

						CalAngle(DefenseMapEditor::ConvertPosToTilePos(GetTransform()->GetLocalPosition()), InterTargetPos);

						//현재위치콜리전 삭제
						DefenseGlobalValue::Collision->ClrAt(IndexX, IndexY);
						//각도를 알기떄문에 그냥 쓰면된다
						if (DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition()) == DefenseMapEditor::ConvertPosToTileXY(InterTargetPos)/*&&180>abs(PreAngle-Angle)*/)
						{
							float4 _Pos = DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());

							IndexX = _Pos.ix();
							IndexY = _Pos.iy();
							DefenseGlobalValue::Collision->SetAt(IndexX, IndexY);

							ShortTargetPos = DefenseMapEditor::ConvertTileXYToPos(IndexX, IndexY);
							InterTargetPos = ShortTargetPos;
						}
						else
						{
							//각도를 알기떄문에 그냥 쓰면된다
							float4 Pos = DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
							IndexX = Pos.ix();
							IndexY = Pos.iy();

							Pos = ReturnIndexPlusPos();
							IndexX = Pos.ix();
							IndexY = Pos.iy();

							DefenseGlobalValue::Collision->SetAt(IndexX, IndexY);

							ShortTargetPos = DefenseMapEditor::ConvertTileXYToPos(IndexX, IndexY);
							InterTargetPos = ShortTargetPos;
						}
					}
				}
			}


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
				else if (Angle < 80 && Angle >= 10)
				{
					Render0->ChangeAnimation("LUp45Move");

					if (false == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = true;
					}
				}
				else if (Angle < 100 && Angle >= 80)
				{
					Render0->ChangeAnimation("UpMove");
				}
				else if (Angle < 170 && Angle >= 100)
				{
					if (true == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = false;
					}
					Render0->ChangeAnimation("LUp45Move");
				}
				else if (Angle < 190 && Angle >= 170)
				{
					Render0->ChangeAnimation("LMove");
					if (true == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = false;
					}
				}
				else if (Angle < 260 && Angle >= 190)
				{
					Render0->ChangeAnimation("LDown45Move");
					if (true == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = false;
					}
				}
				else if (Angle < 280 && Angle >= 260)
				{
					Render0->ChangeAnimation("DownMove");

				}
				else if (Angle < 350 && Angle >= 280)
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
			if (true == IsClick)
			{
				int a = 0;
			}
			if (0 >= CurHp)
			{
				DefenseMapFSM.ChangeState("Die");
				return;
			}

			float Min = 10000.f;
			if (nullptr == FOVCollision)
			{
				return;
			}
			// 가장가까운대상에게 타겟팅된다.

			std::vector<std::shared_ptr<GameEngineCollision>> ColTest;
			//안에서 각도계산도해줌
			GetTransform()->AddLocalPosition(MovePointTowardsTarget(GetTransform()->GetLocalPosition(), InterTargetPos, Speed, _DeltaTime));
			if (ShortTargetPos == InterTargetPos && InterTargetPos.XYDistance(GetTransform()->GetLocalPosition()) <= 2.f)
			{
				GetTransform()->SetLocalPosition(InterTargetPos);
					if (true == IsHold)
					{
						DefenseMapFSM.ChangeState("Stay");
						return;
					}
					if (AttackType::Near == MyAttackType)
					{
						if (Collision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::AABBBOX2D, ColType::AABBBOX2D), 1 < ColTest.size())
						{
							for (std::shared_ptr<GameEngineCollision> Col : ColTest)
							{
								std::shared_ptr<Object> NewObject = Col->GetActor()->DynamicThis<Object>();
								if (nullptr == NewObject)
								{
									continue;
								}
								else if (NewObject == DynamicThis<Unit>())
								{
									continue;
								}
								else if (MyTeam != NewObject->GetTeam())
								{
									CopyObject = NewObject;
									if (1 < abs(CopyObject->IndexX - IndexX) || 1 < abs(CopyObject->IndexY - IndexY))
									{
										continue;
									}
									CalAngle(GetTransform()->GetLocalPosition(), CopyObject->GetTransform()->GetWorldPosition());
									DefenseMapFSM.ChangeState("Attack");
									return;

								}
							}
						}
					}
					else if (AttackType::Far == MyAttackType)
					{
						if (FOVCollision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::AABBBOX2D), 1 < ColTest.size())
						{
							for (std::shared_ptr<GameEngineCollision> Col : ColTest)
							{
								std::shared_ptr<Object> NewObject = Col->GetActor()->DynamicThis<Object>();
								if (nullptr == NewObject)
								{
									continue;
								}
								else if (NewObject == DynamicThis<Unit>())
								{
									continue;
								}
								else if (MyTeam != NewObject->GetTeam())
								{
									CopyObject = NewObject;
									CalAngle(GetTransform()->GetLocalPosition(), CopyObject->GetTransform()->GetWorldPosition());

									DefenseMapFSM.ChangeState("Attack");
									return;

								}
							}
						}
					}


					if (0 != PathPos.size())
					{
						DefenseMapFSM.ChangeState("Chase");
						return;
					}
					else if (0 == PathPos.size())
					{
						DefenseMapFSM.ChangeState("Stay");
						return;
					}

			}
			else
			{
				float sdads = ShortTargetPos.XYDistance(GetTransform()->GetLocalPosition());
				if (ShortTargetPos.XYDistance(GetTransform()->GetLocalPosition()) <= 2.f)
				{
					GetTransform()->SetLocalPosition(ShortTargetPos);
					if (true == IsHold)
					{
						DefenseMapFSM.ChangeState("Stay");
						return;
					}
					if (Collision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::AABBBOX2D, ColType::AABBBOX2D), 1 < ColTest.size())
					{
						for (std::shared_ptr<GameEngineCollision> Col : ColTest)
						{
							std::shared_ptr<Object> NewObject = Col->GetActor()->DynamicThis<Object>();
							if (nullptr == NewObject)
							{
								continue;
							}
							else if (NewObject == DynamicThis<Unit>())
							{
								continue;
							}
							else if (MyTeam != NewObject->GetTeam())
							{
								CopyObject = NewObject;
								if (1 < abs(CopyObject->IndexX - IndexX) || 1 < abs(CopyObject->IndexY - IndexY))
								{
									continue;
								}
								CalAngle(GetTransform()->GetLocalPosition(), CopyObject->GetTransform()->GetWorldPosition());
								DefenseMapFSM.ChangeState("Attack");
								return;
							}
						}
					}

					if (FOVCollision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::AABBBOX2D), 1 < ColTest.size())
					{
						Min = CopyObject->GetTransform()->GetLocalPosition().XYDistance(GetTransform()->GetLocalPosition());
						if (AttackType::Far == MyAttackType)
						{
							for (std::shared_ptr<GameEngineCollision> Col : ColTest)
							{
								std::shared_ptr<Object> NewObject = Col->GetActor()->DynamicThis<Object>();
								if (nullptr == NewObject)
								{
									continue;
								}
								else if (NewObject == DynamicThis<Object>())
								{
									continue;
								}
								else if (MyTeam != NewObject->GetTeam())
								{
									CopyObject = NewObject;
									CalAngle(GetTransform()->GetLocalPosition(), CopyObject->GetTransform()->GetWorldPosition());
									DefenseMapFSM.ChangeState("Attack");
									return;
								}
							}
						}
						else if (AttackType::Near == MyAttackType)
						{
							for (std::shared_ptr<GameEngineCollision> Col : ColTest)
							{
								std::shared_ptr<Object> NewObject = Col->GetActor()->DynamicThis<Object>();
								if (nullptr == NewObject)
								{
									continue;
								}
								else if (NewObject == DynamicThis<Object>())
								{
									continue;
								}
								else if (MyTeam != NewObject->GetTeam())
								{
									if (Min > NewObject->GetTransform()->GetLocalPosition().XYDistance(GetTransform()->GetLocalPosition()))
									{
										Min = NewObject->GetTransform()->GetLocalPosition().XYDistance(GetTransform()->GetLocalPosition());
										CopyObject = NewObject;
									}
								}
							}
						}


					}
					int _IndexX = CopyObject->IndexX;
					int _IndexY = CopyObject->IndexY;
					//타겟이사라지면대기상태로변경
					if (nullptr == CopyObject || true == CopyObject->IsDeath())
					{
						CopyObject = nullptr;
						DefenseMapFSM.ChangeState("Stay");
						return;
					}
					//시야 범위 벗어나면 기존자리 복귀			
					else if (abs(FOVCollision->GetTransform()->GetLocalScale().x)
						< GetTransform()->GetLocalPosition().XYDistance(CopyObject->GetTransform()->GetWorldPosition())
						)
					{
						CopyObject = nullptr;
						TargetPos = PrePos;
						DefenseMapPathCal();
						DefenseMapFSM.ChangeState("Move");
						return;
					}
					else if (_IndexX != CopyIndexX || _IndexY != CopyIndexY)
					{
						if (1 < abs(CopyObject->IndexX - IndexX) || 1 < abs(CopyObject->IndexY - IndexY))
						{
							TargetPos = DefenseMapEditor::ConvertTileXYToPos(_IndexX, _IndexY);
							DefenseMapPathCal();
							CopyIndexX = DefenseMapEditor::ConvertPosToTileXY(CopyObject->GetTransform()->GetLocalPosition()).ix();
							CopyIndexY = DefenseMapEditor::ConvertPosToTileXY(CopyObject->GetTransform()->GetLocalPosition()).iy();
							DefenseMapFSM.ChangeState("Chase");
							return;
						}
					}

					//이동관련
					if (false == IsNextDefenseMapTileCollision())
					{

						DefenseGlobalValue::Collision->ClrAt(IndexX, IndexY);
						//각도를 알기떄문에 그냥 쓰면된다						
						float4 Pos = ReturnIndexPlusPos();
						IndexX = Pos.ix();
						IndexY = Pos.iy();
						DefenseGlobalValue::Collision->SetAt(IndexX, IndexY);
						ShortTargetPos = DefenseMapEditor::ConvertTileXYToPos(IndexX, IndexY);
					}
					else if (true == IsNextDefenseMapTileCollision())
					{
						DefenseMapPathCal();
						CopyIndexX = DefenseMapEditor::ConvertPosToTileXY(CopyObject->GetTransform()->GetLocalPosition()).ix();
						CopyIndexY = DefenseMapEditor::ConvertPosToTileXY(CopyObject->GetTransform()->GetLocalPosition()).iy();
						DefenseMapFSM.ChangeState("Chase");
					}
				}
			}
		},
		.End = []() {}
		}
	);

	DefenseMapFSM.CreateState(
		{ .Name = "Attack",
		.Start = [this]()
		{
			if (AttackType::Far == MyAttackType && nullptr != MissileRender)
			{
				//float4 _Index = ReturnIndexPlusPos();
				//float4 _Pos = DefenseMapEditor::ConvertTileXYToPos(_Index.ix(), _Index.iy());

				MissileRender->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
				float _Angle = CalAngle(MissileRender->GetTransform()->GetWorldPosition(), CopyObject->GetTransform()->GetWorldPosition());
				MissileRender->GetTransform()->SetLocalRotation({ 0,0,_Angle });
				MissileRender->On();
			}
			PreAngle = Angle;
			if (Angle < 10 || Angle >= 350)
			{
				Render0->ChangeAnimation("LAttack");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}
			if (Angle < 80 && Angle >= 10)
			{
				Render0->ChangeAnimation("LUp45Attack");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}

			if (Angle < 100 && Angle >= 80)
			{
				Render0->ChangeAnimation("UpAttack");
			}
			if (Angle < 170 && Angle >= 100)
			{
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
				Render0->ChangeAnimation("LUp45Attack");
			}
			if (Angle < 190 && Angle >= 170)
			{
				Render0->ChangeAnimation("LAttack");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			if (Angle < 260 && Angle >= 190)
			{
				Render0->ChangeAnimation("LDown45Attack");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			if (Angle < 280 && Angle >= 260)
			{
				Render0->ChangeAnimation("DownAttack");

			}
			if (Angle < 350 && Angle >= 280)
			{
				Render0->ChangeAnimation("LDown45Attack");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}

		},
		.Update = [this](float _DeltaTime)
		{
			if (true == IsClick)
			{
				int a = 0;
			}

			std::vector<std::shared_ptr<GameEngineCollision>> ColTest;
			float InterDistance = CopyObject->GetTransform()->GetWorldPosition().XYDistance(GetTransform()->GetLocalPosition());
			CalAngle(GetTransform()->GetLocalPosition(), CopyObject->GetTransform()->GetWorldPosition());
			if (nullptr == CopyObject || true == CopyObject->IsDeath())
			{
				CopyObject = nullptr;
				DefenseMapFSM.ChangeState("Stay");
				return;
			}
			else if (AttackType::Far == MyAttackType)
			{
				MissileRender->GetTransform()->AddWorldPosition(MovePointTowardsTarget
				(
					MissileRender->GetTransform()->GetWorldPosition(),
					CopyObject->GetTransform()->GetWorldPosition(),
					MissileRender->GetTransform()->GetWorldPosition().XYDistance(DefenseMapEditor::ConvertPosToTilePos(CopyObject->GetTransform()->GetWorldPosition())) / AttackSpeed,
					_DeltaTime) * 3.f
				);
				if (3.f > MissileRender->GetTransform()->GetWorldPosition().XYDistance(DefenseMapEditor::ConvertPosToTilePos(CopyObject->GetTransform()->GetWorldPosition())))
				{
					MissileRender->Off();
				}
			}
			if (0 >= CurHp)
			{
				DefenseMapFSM.ChangeState("Die");
				return;
			}
			else if (Render0->IsAnimationEnd())
			{
				if (nullptr == CopyObject || true == CopyObject->IsDeath())
				{
					CopyObject = nullptr;
					DefenseMapFSM.ChangeState("Stay");
					return;
				}
				if (true == IsHold)
				{
					DefenseMapFSM.ChangeState("Stay");
					return;
				}
				if (AttackType::Near == MyAttackType)
				{
					if (1 < abs(CopyObject->IndexX - IndexX) || 1 < abs(CopyObject->IndexY - IndexY))
					{

						if (0 < CopyObject->CurHp)
						{
							CopyObject->CurHp -= (AddATK + ATK);
						}
						TargetPos = CopyObject->GetTransform()->GetLocalPosition();
						DefenseMapPathCal();
						CopyIndexX = DefenseMapEditor::ConvertPosToTileXY(CopyObject->GetTransform()->GetLocalPosition()).ix();
						CopyIndexY = DefenseMapEditor::ConvertPosToTileXY(CopyObject->GetTransform()->GetLocalPosition()).iy();
						DefenseMapFSM.ChangeState("Chase");
						return;
					}
					else if (abs(PreAngle - Angle) > 25.f)
					{
						if (0 < CopyObject->CurHp)
						{
							CopyObject->CurHp -= (AddATK + ATK);
						}
						CalAngle(GetTransform()->GetLocalPosition(), CopyObject->GetTransform()->GetWorldPosition());
						DefenseMapFSM.ChangeState("Attack");
						if (true == IsClick)
						{
							int a = 0;
						}
						return;
					}
					else
					{
						if (0 < CopyObject->CurHp)
						{
							CopyObject->CurHp -= (AddATK + ATK);

						}

					}
				}
				else if (AttackType::Far == MyAttackType)
				{
					if (0 < CopyObject->CurHp)
					{
						CopyObject->CurHp -= (AddATK + ATK);

					}
					DefenseMapFSM.ChangeState("Attack");
					return;

				}


			}


		},
		.End = [this]()
		 {
			 if (AttackType::Far == MyAttackType && nullptr != MissileRender)
			 {

				 MissileRender->Off();
			 }
		 }
		}
	);
	DefenseMapFSM.CreateState(
		{ .Name = "HoldAttack",
		.Start = [this]()
		{
			//각도계산용

			CalAngle(GetTransform()->GetLocalPosition(), CopyObject->GetTransform()->GetLocalPosition());
			if (Angle < 10 || Angle >= 350)
			{
				Render0->ChangeAnimation("LAttack");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}
			if (Angle < 80 && Angle >= 10)
			{
				Render0->ChangeAnimation("LUp45Attack");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}

			if (Angle < 100 && Angle >= 80)
			{
				Render0->ChangeAnimation("UpAttack");
			}
			if (Angle < 170 && Angle >= 100)
			{
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
				Render0->ChangeAnimation("LUp45Attack");
			}
			if (Angle < 190 && Angle >= 170)
			{
				Render0->ChangeAnimation("LAttack");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			if (Angle < 260 && Angle >= 190)
			{
				Render0->ChangeAnimation("LDown45Attack");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			if (Angle < 280 && Angle >= 260)
			{
				Render0->ChangeAnimation("DownAttack");

			}
			if (Angle < 350 && Angle >= 280)
			{
				Render0->ChangeAnimation("LDown45Attack");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}
			PreAngle = Angle;
		},
		.Update = [this](float _DeltaTime)
		{
			if (Render0->IsAnimationEnd())
			{

				if (nullptr == CopyObject || true == CopyObject->IsDeath())
				{
					CopyObject = nullptr;
					DefenseMapFSM.ChangeState("Stay");
					return;
				}
else
{
	if (0 < CopyObject->CurHp)
	{
		CopyObject->CurHp -= (AddATK + ATK);

	}
	DefenseMapFSM.ChangeState("Stay");
}

}
},
.End = []() {}
		}
	);
	DefenseMapFSM.CreateState(
		{ .Name = "Die",
		.Start = [this]()
		{
			
			if (CurHp > 10)
			{
				Render0->ChangeAnimation("ShomenDie");
			}
			else
			{
				Render0->ChangeAnimation("Die");
			}
			
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
				DefenseGlobalValue::Collision->ClrAt(IndexX, IndexY);
				Death();
			}
		},
		.End = [this]()
		{
			
		}
		}
	);

	DefenseMapFSM.CreateState(
		{ .Name = "MoveChase",
		.Start = [this]() {
			//경로계산
			IsA = false;
			if (0 != PathPos.size())
			{

				if (GetTransform()->GetLocalPosition() == PathPos.front())
				{
					float4 Pos2 = DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());

					PathPos.pop_front();

				}
				InterTargetPos = PathPos.front();

				PathPos.pop_front();

				//각도계산
				PreAngle = Angle;
				CalAngle(GetTransform()->GetLocalPosition(), InterTargetPos);
				//지금 내가 가는 방향에 장애물이 없다면 그타일을 미리선점하고 그쪽으로 움직인다.
				if (false == IsNextDefenseMapTileCollision())
				{

					//현재위치콜리전 삭제
					DefenseGlobalValue::Collision->ClrAt(IndexX, IndexY);
					if (DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition()) == DefenseMapEditor::ConvertPosToTileXY(InterTargetPos)/*&&180>abs(PreAngle-Angle)*/)
					{
						float4 _Pos = DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());

						IndexX = _Pos.ix();
						IndexY = _Pos.iy();
						DefenseGlobalValue::Collision->SetAt(IndexX, IndexY);

						ShortTargetPos = DefenseMapEditor::ConvertTileXYToPos(IndexX, IndexY);
					}
					else
					{
						//각도를 알기떄문에 그냥 쓰면된다
						float4 Pos = DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
						IndexX = Pos.ix();
						IndexY = Pos.iy();

						Pos = ReturnIndexPlusPos();
						IndexX = Pos.ix();
						IndexY = Pos.iy();

						DefenseGlobalValue::Collision->SetAt(IndexX, IndexY);

						ShortTargetPos = DefenseMapEditor::ConvertTileXYToPos(IndexX, IndexY);
					}

				}
				else if (true == IsNextDefenseMapTileCollision())
				{
					//경로계산
					DefenseMapPathCal();
					if (0 != PathPos.size())
					{
						if (DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition()) == DefenseMapEditor::ConvertPosToTileXY(PathPos.front()))
						{
							PathPos.pop_front();
						}
						InterTargetPos = PathPos.front();

						PathPos.pop_front();

						CalAngle(DefenseMapEditor::ConvertPosToTilePos(GetTransform()->GetLocalPosition()), InterTargetPos);

						//현재위치콜리전 삭제
						DefenseGlobalValue::Collision->ClrAt(IndexX, IndexY);
						//각도를 알기떄문에 그냥 쓰면된다
						if (DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition()) == DefenseMapEditor::ConvertPosToTileXY(InterTargetPos)/*&&180>abs(PreAngle-Angle)*/)
						{
							float4 _Pos = DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());

							IndexX = _Pos.ix();
							IndexY = _Pos.iy();
							DefenseGlobalValue::Collision->SetAt(IndexX, IndexY);

							ShortTargetPos = DefenseMapEditor::ConvertTileXYToPos(IndexX, IndexY);
						}
						else
						{
							//각도를 알기떄문에 그냥 쓰면된다
							float4 Pos = DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
							IndexX = Pos.ix();
							IndexY = Pos.iy();

							Pos = ReturnIndexPlusPos();
							IndexX = Pos.ix();
							IndexY = Pos.iy();

							DefenseGlobalValue::Collision->SetAt(IndexX, IndexY);

							ShortTargetPos = DefenseMapEditor::ConvertTileXYToPos(IndexX, IndexY);
						}
					}
				}
			}


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
				else if (Angle < 80 && Angle >= 10)
				{
					Render0->ChangeAnimation("LUp45Move");

					if (false == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = true;
					}
				}
				else if (Angle < 100 && Angle >= 80)
				{
					Render0->ChangeAnimation("UpMove");
				}
				else if (Angle < 170 && Angle >= 100)
				{
					if (true == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = false;
					}
					Render0->ChangeAnimation("LUp45Move");
				}
				else if (Angle < 190 && Angle >= 170)
				{
					Render0->ChangeAnimation("LMove");
					if (true == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = false;
					}
				}
				else if (Angle < 260 && Angle >= 190)
				{
					Render0->ChangeAnimation("LDown45Move");
					if (true == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = false;
					}
				}
				else if (Angle < 280 && Angle >= 260)
				{
					Render0->ChangeAnimation("DownMove");

				}
				else if (Angle < 350 && Angle >= 280)
				{
					Render0->ChangeAnimation("LDown45Move");
					if (false == IsFlip)
					{
						Render0->SetFlipX();
						IsFlip = true;
					}
				}
			}

			if (nullptr != CopyObject)
			{
				CopyObject = nullptr;
			}
		},
		.Update = [this](float _DeltaTime)
		{
			if (0 >= CurHp)
			{
				DefenseMapFSM.ChangeState("Die");
				return;
			}
			float4 sdsd = TargetPos;
			std::vector<std::shared_ptr<GameEngineCollision>> ColTest;
			GetTransform()->AddLocalPosition(MovePointTowardsTarget(GetTransform()->GetLocalPosition(), InterTargetPos, Speed, _DeltaTime));
			if (ShortTargetPos == InterTargetPos && InterTargetPos.XYDistance(GetTransform()->GetLocalPosition()) <= 2.f)
			{
				if (true == IsClick)
				{
					int a = 0;
				}
				GetTransform()->SetLocalPosition(InterTargetPos);
				if (nullptr != FOVCollision
					&& FOVCollision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::AABBBOX2D)
					&& 1 < ColTest.size()
					&& false == IsHold)
				{
					for (std::shared_ptr<GameEngineCollision> Col : ColTest)
					{
						std::shared_ptr<Object> NewObject = Col->GetActor()->DynamicThis<Object>();
						if (nullptr == NewObject)
						{
							continue;
						}
						else if (NewObject == DynamicThis<Object>())
						{
							continue;
						}
						else if (MyTeam != NewObject->GetTeam())
						{
							CopyObject = NewObject;
							TargetPos = CopyObject->GetTransform()->GetLocalPosition();
							PrePos = GetTransform()->GetLocalPosition();
							DefenseMapPathCal();
							CopyIndexX = DefenseMapEditor::ConvertPosToTileXY(CopyObject->GetTransform()->GetLocalPosition()).ix();
							CopyIndexY = DefenseMapEditor::ConvertPosToTileXY(CopyObject->GetTransform()->GetLocalPosition()).iy();
							DefenseMapFSM.ChangeState("Chase");
							return;
						}
					}
				}
				if (0 == PathPos.size())
				{
					DefenseMapFSM.ChangeState("Stay");
				}
				else if (true == IsHold)
				{
					DefenseMapFSM.ChangeState("Stay");
					return;
				}
				else
				{
					DefenseMapFSM.ChangeState("MoveChase");
				}
			}
			else
			{
				if (ShortTargetPos.XYDistance(GetTransform()->GetLocalPosition()) <= 2.f)
				{
					if (true == IsClick)
					{
						int a = 0;
					}
					if (nullptr != FOVCollision
						&& FOVCollision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::AABBBOX2D)
						&& 1 < ColTest.size()
						&& false == IsHold)
					{
						for (std::shared_ptr<GameEngineCollision> Col : ColTest)
						{
							std::shared_ptr<Object> NewObject = Col->GetActor()->DynamicThis<Object>();
							if (nullptr == NewObject)
							{
								continue;
							}
							else if (NewObject == DynamicThis<Object>())
							{
								continue;
							}
							else if (MyTeam != NewObject->GetTeam())
							{
								CopyObject = NewObject;
								TargetPos = CopyObject->GetTransform()->GetLocalPosition();
								PrePos = GetTransform()->GetLocalPosition();
								DefenseMapPathCal();
								CopyIndexX = DefenseMapEditor::ConvertPosToTileXY(CopyObject->GetTransform()->GetLocalPosition()).ix();
								CopyIndexY = DefenseMapEditor::ConvertPosToTileXY(CopyObject->GetTransform()->GetLocalPosition()).iy();
								if (AttackType::Far == MyAttackType)
								{
									CalAngle(GetTransform()->GetLocalPosition(), CopyObject->GetTransform()->GetWorldPosition());
									DefenseMapFSM.ChangeState("Attack");
									return;
								}
								else
								{
									DefenseMapFSM.ChangeState("Chase");
									return;
								}
							}
						}
					}
					if (true == IsHold)
					{
						DefenseMapFSM.ChangeState("Stay");
						return;
					}
					else if (false == IsNextDefenseMapTileCollision())
					{

						DefenseGlobalValue::Collision->ClrAt(IndexX, IndexY);
						//각도를 알기떄문에 그냥 쓰면된다						
						float4 Pos = ReturnIndexPlusPos();
						IndexX = Pos.ix();
						IndexY = Pos.iy();
						DefenseGlobalValue::Collision->SetAt(IndexX, IndexY);
						ShortTargetPos = DefenseMapEditor::ConvertTileXYToPos(IndexX, IndexY);
					}
					else if (true == IsNextDefenseMapTileCollision())
					{
						DefenseMapPathCal();
						DefenseMapFSM.ChangeState("MoveChase");
					}


				}
			}

		},
		.End = [this]()
		{

		}
		}
	);

	DefenseMapFSM.CreateState(
		{ .Name = "Summoning",
		.Start = [this]()
		{
			/*if (false == IsShamonAniEnd)
			{
				Render0->ChangeAnimation("Shomen");
			}
			else
			{*/
				if (Angle < 10 || Angle >= 350)
			{
				Render0->ChangeAnimation("LStay");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}
			else if (Angle < 80 && Angle >= 10)
			{
				Render0->ChangeAnimation("LUp45Stay");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}

			else if (Angle < 100 && Angle >= 80)
			{
				Render0->ChangeAnimation("UpStay");
			}
			else if (Angle < 170 && Angle >= 100)
			{
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
				Render0->ChangeAnimation("LUp45Stay");
			}
			else if (Angle < 190 && Angle >= 170)
			{
				Render0->ChangeAnimation("LStay");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			else if (Angle < 260 && Angle >= 190)
			{
				Render0->ChangeAnimation("LDown45Stay");
				if (true == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = false;
				}
			}
			else if (Angle < 280 && Angle >= 260)
			{
				Render0->ChangeAnimation("DownStay");

			}
			else if (Angle < 350 && Angle >= 280)
			{
				Render0->ChangeAnimation("LDown45Stay");
				if (false == IsFlip)
				{
					Render0->SetFlipX();
					IsFlip = true;
				}
			}
		//	}
			
			float4 _Pos = DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
			IndexX = _Pos.ix();
			IndexY = _Pos.iy();
			float4 _Pos2 = DefenseMapEditor::ConvertTileXYToPos(IndexX, IndexY);
			GetTransform()->SetLocalPosition(_Pos2);
			DefenseGlobalValue::Collision->SetAt(IndexX, IndexY);
		},
		.Update = [this](float _DeltaTime)
		{			
			float4 _Pos = DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetLocalPosition());
			if (IndexX != _Pos.x || IndexY != _Pos.y)
			{
				DefenseGlobalValue::Collision->ClrAt(IndexX, IndexY);
				IndexX = _Pos.ix();
				IndexY = _Pos.iy();
				float4 _Pos2 = DefenseMapEditor::ConvertTileXYToPos(IndexX, IndexY);
				GetTransform()->SetLocalPosition(_Pos2);
				DefenseGlobalValue::Collision->SetAt(IndexX, IndexY);
			}

		},
		.End = []() {}
		}
	);

	DefenseMapFSM.ChangeState("Summoning");
}

void Unit::DefenseMapPathCal()
{

	float4 MPos = DefenseMapEditor::ConvertPosToTileXY(TargetPos);
	float4 UPos = DefenseMapEditor::ConvertPosToTileXY(GetTransform()->GetWorldPosition());

	PathPos.clear();

	//Angle계산	
	CalAngle(GetTransform()->GetLocalPosition(), TargetPos);
	DefenseGlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), MPos.ix(), MPos.iy(), JPSPathResult);

	if (JPSPathResult.size() == 0)
	{
		if (Angle < 45 || Angle >= 315)
		{
			//오른쪽
			int CloseXRight = DefenseGlobalValue::Collision->GetOpenValue(MPos.ix(), MPos.iy(), true, true);
			int CloseXLeft = DefenseGlobalValue::Collision->GetOpenValue(MPos.ix(), MPos.iy(), true, false);
			if (CloseXRight == MPos.ix())
			{
				int _Y = MPos.iy();
				while (JPSPathResult.size() == 0)
				{
					CloseXRight--;
					_Y++;
					DefenseGlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), CloseXRight, _Y, JPSPathResult);
					if (DefenseGlobalValue::Collision->IsOutBound(CloseXRight, _Y))
					{
						break;
					}
				}
			}
			else
			{
				if (abs(MPos.ix() - CloseXRight) <= abs(MPos.ix() - CloseXLeft))
				{
					DefenseGlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), CloseXRight, MPos.iy(), JPSPathResult);
				}
				else
				{
					DefenseGlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), CloseXLeft, MPos.iy(), JPSPathResult);
				}

			}
		}
		else if (Angle >= 45 && Angle < 135)
		{
			//위
			int CloseYUp = DefenseGlobalValue::Collision->GetOpenValue(MPos.ix(), MPos.iy(), false, false);
			int CloseYDown = DefenseGlobalValue::Collision->GetOpenValue(MPos.ix(), MPos.iy(), false, true);
			if (CloseYUp == MPos.iy())
			{
				int _X = MPos.ix();
				while (JPSPathResult.size() == 0)
				{
					CloseYUp++;
					_X++;
					DefenseGlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), _X, CloseYUp, JPSPathResult);

					if (DefenseGlobalValue::Collision->IsOutBound(_X, CloseYUp))
					{
						break;
					}
				}
			}
			else
			{
				if (abs(MPos.iy() - CloseYUp) <= abs(MPos.iy() - CloseYDown))
				{
					DefenseGlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), MPos.ix(), CloseYUp, JPSPathResult);
				}
				else
				{
					DefenseGlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), MPos.ix(), CloseYDown, JPSPathResult);
				}
			}
		}
		else if (Angle >= 135 && Angle < 225)
		{
			//왼
			int CloseXRight = DefenseGlobalValue::Collision->GetOpenValue(MPos.ix(), MPos.iy(), true, true);
			int CloseXLeft = DefenseGlobalValue::Collision->GetOpenValue(MPos.ix(), MPos.iy(), true, false);
			if (CloseXLeft == MPos.ix())
			{
				int _Y = MPos.iy();
				while (JPSPathResult.size() == 0)
				{
					CloseXLeft++;
					_Y--;
					DefenseGlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), CloseXLeft, _Y, JPSPathResult);

					if (DefenseGlobalValue::Collision->IsOutBound(CloseXLeft, _Y))
					{
						break;
					}
				}
			}
			else
			{
				if (abs(MPos.ix() - CloseXRight) >= abs(MPos.ix() - CloseXLeft))
				{
					DefenseGlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), CloseXLeft, MPos.iy(), JPSPathResult);
				}
				else
				{
					DefenseGlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), CloseXRight, MPos.iy(), JPSPathResult);
				}

			}
		}
		else if (Angle >= 225 && Angle < 315)
		{
			//밑
			int CloseYUp = DefenseGlobalValue::Collision->GetOpenValue(MPos.ix(), MPos.iy(), false, false);
			int CloseYDown = DefenseGlobalValue::Collision->GetOpenValue(MPos.ix(), MPos.iy(), false, true);
			if (CloseYUp == MPos.iy())
			{
				int _X = MPos.ix();
				while (JPSPathResult.size() == 0)
				{
					CloseYDown--;
					_X--;
					DefenseGlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), _X, CloseYDown, JPSPathResult);

					if (DefenseGlobalValue::Collision->IsOutBound(_X, CloseYDown))
					{
						break;
					}
				}
			}
			else
			{
				if (abs(MPos.iy() - CloseYUp) >= abs(MPos.iy() - CloseYDown))
				{
					DefenseGlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), MPos.ix(), CloseYDown, JPSPathResult);
				}
				else
				{
					DefenseGlobalValue::JpsP.Search(UPos.ix(), UPos.iy(), MPos.ix(), CloseYUp, JPSPathResult);
				}
			}
		}
	}

	for (const JPSCoord& Point : JPSPathResult)
	{
		float4 ConvertPos = DefenseMapEditor::ConvertTileXYToPos(Point.m_x, Point.m_y);

		PathPos.push_back(ConvertPos);

	}
}

bool Unit::IsNextDefenseMapTileCollision()
{
	int _IndexX = -1;
	int _IndexY = -1;


	if (Angle < 10 || Angle >= 350)
	{
		_IndexX = IndexX + 1;
		_IndexY = IndexY - 1;
		return DefenseGlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
	if (Angle < 80 && Angle >= 10)
	{
		_IndexX = IndexX;
		_IndexY = IndexY - 1;
		return DefenseGlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}

	if (Angle < 100 && Angle >= 80)
	{
		_IndexX = IndexX - 1;
		_IndexY = IndexY - 1;
		return DefenseGlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
	if (Angle < 170 && Angle >= 100)
	{
		_IndexX = IndexX - 1;
		_IndexY = IndexY;
		return DefenseGlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
	if (Angle < 190 && Angle >= 170)
	{
		_IndexX = IndexX - 1;
		_IndexY = IndexY + 1;
		return DefenseGlobalValue::Collision->IsCollision(_IndexX, _IndexY);

	}
	if (Angle < 260 && Angle >= 190)
	{
		_IndexX = IndexX;
		_IndexY = IndexY + 1;
		return DefenseGlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
	if (Angle < 280 && Angle >= 260)
	{
		_IndexX = IndexX + 1;
		_IndexY = IndexY + 1;
		return DefenseGlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
	if (Angle < 350 && Angle >= 280)
	{
		_IndexX = IndexX + 1;
		_IndexY = IndexY;
		return DefenseGlobalValue::Collision->IsCollision(_IndexX, _IndexY);
	}
	else
	{
		return false;
	}
}



