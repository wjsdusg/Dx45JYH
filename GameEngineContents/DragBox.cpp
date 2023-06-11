#include "PrecompileHeader.h"
#include "DragBox.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include "Unit.h"
extern float4 TIleScale;
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
	Pos.y = (MousePos.y + MouseMovePos.y)/2.f;
	Render0->GetTransform()->SetLocalPosition(Pos);
	Collision->GetTransform()->SetLocalPosition(Pos);
	float4 Scale;
	Scale.x = abs(MousePos.x - MouseMovePos.x);
	Scale.y = abs(MousePos.y - MouseMovePos.y);
	Render0->GetTransform()->SetLocalScale(Scale);
	Collision->GetTransform()->SetLocalScale(Scale);
}

void DragBox::Start()
{
	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	Collision = CreateComponent<GameEngineCollision>();
}

void DragBox::AllCollision()
{
	std::vector<std::shared_ptr<GameEngineCollision>> ColTest;

	if (Collision->CollisionAll(static_cast<int>(ColEnum::Unit), ColTest, ColType::SPHERE2D, ColType::SPHERE2D), 0 != ColTest.size())
	{
		for (std::shared_ptr<GameEngineCollision> Col : ColTest)
		{
			std::shared_ptr<Unit> NewUnit = Col->GetActor()->DynamicThis<Unit>();
			if (nullptr != NewUnit&&TIleScale.x* TIleScale.y<GetTransform()->GetLocalScale().x* GetTransform()->GetLocalScale().y)
			{
				NewUnit->IsClick = true;
			}
		}
	}
}

void DragBox::Render(float _DeltaTime)
{

}