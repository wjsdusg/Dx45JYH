#include "PrecompileHeader.h"
#include "Map.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineVideo.h>
#include <GameEngineCore/GameEngineSprite.h>
#include "TestObject.h"

Map::Map()
{
}

Map::~Map()
{
}


void Map::Update(float _DeltaTime)
{


	std::vector<std::shared_ptr<GameEngineCollision>> ColTest;

	

}

void Map::Start()
{
	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	Render0->SetScaleRatio(10.0f);
	//Render0->SetScaleToTexture("background.png");
	
	Render0->SetTexture("background.png");
	Render0->GetTransform()->SetLocalScale({ (GameEngineWindow::GetScreenSize().x * 4), (GameEngineWindow::GetScreenSize().y * 4), 0.f, 1.f });
	
	
	//Render0->GetTransform()->SetLocalScale({ (GameEngineWindow::GetScreenSize().x ), (GameEngineWindow::GetScreenSize().y ), 0.f, 0.f });


}

// 이건 디버깅용도나 
void Map::Render(float _Delta)
{

};
