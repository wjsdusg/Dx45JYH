#include "PrecompileHeader.h"
#include "DragBox.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include "Unit.h"

DragBox::DragBox()
{

}

DragBox::~DragBox()
{
}


void DragBox::Update(float _DeltaTime)
{
	float4 Pos;
	Pos.x = (MousePos.x + MouseMovePos.x) / 2.f;
	Pos.y = (MousePos.y + MouseMovePos.y) / 2.f;
	Render0->GetTransform()->SetLocalPosition(Pos);
	Collision->GetTransform()->SetLocalPosition(Pos);
	float4 Scale;
	Scale.x = abs(MousePos.x - MouseMovePos.x);
	Scale.y = abs(MousePos.y - MouseMovePos.y);
	Scale.z = 1;
	Render0->GetTransform()->SetLocalScale(Scale);
	Collision->GetTransform()->SetLocalScale(Scale);
	Area = Scale.x * Scale.y;
	GameEngineDebug::DrawBox(GetLevel()->GetMainCamera().get(), Collision->GetTransform());
}

void DragBox::Start()
{
	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	Render0->SetTexture("DragBox.png");
	Render0->ColorOptionValue.MulColor.a = 0.4f;
	Collision = CreateComponent<GameEngineCollision>();
}

bool DragBox::AllCollision()
{
	std::vector<std::shared_ptr<GameEngineCollision>> ColTest;
	check = false;
	if (Collision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::AABBBOX2D, ColType::AABBBOX2D), 0 != ColTest.size())
	{
		for (std::shared_ptr<GameEngineCollision> Col : ColTest)
		{
			std::shared_ptr<Unit> NewUnit = Col->GetActor()->DynamicThis<Unit>();

			if (nullptr != NewUnit &&Team::Mine== NewUnit->MyTeam &&120.f < Area)
			{
				if (false == check)
				{
					for (int i = 0; i < Unit::Units.size(); i++)
					{
						Unit::Units[i]->IsClick = false;
					}
					check = true;
				}
				NewUnit->IsClick = true;
			}
		}
	}
	//float4 pos = Collision->GetTransform()->GetLocalScale();
	return check;
}

void DragBox::Render(float _DeltaTime)
{

}