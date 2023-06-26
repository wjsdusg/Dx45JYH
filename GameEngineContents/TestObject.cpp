#include "PrecompileHeader.h"
#include "TestObject.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>

TestObject::TestObject()
{
}

TestObject::~TestObject()
{
}


void TestObject::Update(float _DeltaTime)
{

}

void TestObject::Start()
{
	Render = CreateComponent<GameEngineSpriteRenderer>();
	Render->SetTexture("generalja0.png");
	Render->GetTransform()->SetLocalScale({ 100,100,1 });
}