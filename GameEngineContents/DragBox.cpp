#include "PrecompileHeader.h"
#include "DragBox.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

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
	float4 Scale;
	Scale.x = abs(MousePos.x - MouseMovePos.x);
	Scale.y = abs(MousePos.y - MouseMovePos.y);
	Render0->GetTransform()->SetLocalScale(Scale);

}

void DragBox::Start()
{
	Render0 = CreateComponent<GameEngineSpriteRenderer>();
}

void DragBox::Render(float _DeltaTime)
{

}