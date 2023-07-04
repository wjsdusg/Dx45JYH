#include "PrecompileHeader.h"
#include "UIButton.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTileMapRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "ContentsEnum.h"


UIButton::UIButton()
{

}

UIButton::~UIButton()
{
}


void UIButton::Update(float _DeltaTime)
{
	
}

void UIButton::Start()
{
	if (nullptr == GameEngineSprite::Find("button.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Button");
		GameEngineSprite::LoadSheet(NewDir.GetPlusFileName("button.png").GetFullPath(), 17, 17);
	}
	//Render0 = CreateComponent<GameEngineSpriteRenderer>();
	//Collision = CreateComponent<GameEngineCollision>();
	//Render0->GetTransform()->SetLocalScale({ 50.f,50.f });

	/*TileMap = CreateComponent<GameEngineTileMapRenderer>();
	TileMap->CreateTileMap(3,3,-1.f,{46.f,37.f});
	int num = 0;
	for (int y = TileMap->GetCount().y - 1; y >= 0; y--)
	{
		for (size_t x = 0; x < TileMap->GetCount().x; x++)
		{
			TileMap->SetTile(x, static_cast<size_t>(y), "button.png", num);
			num++;
		}
	}*/
	// Render0->CreateAnimation({ "LDown45Stay", "archerk.png",0,7 });

	 Render0 = CreateComponent<GameEngineUIRenderer>();
	 Render0->CreateAnimation({ "Stop", "button.png", 39, 39 });
	 Render0->ChangeAnimation("Stop");
	 Render0->GetTransform()->SetLocalScale({ 50.f,42.f,1.f });
	 Render0->GetTransform()->AddLocalPosition({ 408.f,34.f });
	 //Render0->GetTransform()->SetWorldPosition(Render0->GetTransform()->GetWorldPosition());
	
	 Render1 = CreateComponent<GameEngineUIRenderer>(); 	 
	 Render1->CreateAnimation({ "Move", "button.png", 6, 6 });
	 Render1->ChangeAnimation("Move");
	 Render1->GetTransform()->SetLocalScale({ 50.f,42.f,1.f });
	 Render1->GetTransform()->AddLocalPosition({ 408.f+x,34.f });
	 
	 Render2 = CreateComponent<GameEngineUIRenderer>();
	 Render2->CreateAnimation({ "Attack", "button.png", 4, 4 });
	 Render2->ChangeAnimation("Attack");
	 Render2->GetTransform()->SetLocalScale({ 50.f,42.f,1.f });
	 Render2->GetTransform()->AddLocalPosition({ 405.f + x*2,34.f });

	 Render3 = CreateComponent<GameEngineUIRenderer>();
	 Render3->CreateAnimation({ "Patrol", "button.png", 10, 10 });
	 Render3->ChangeAnimation("Patrol");
	 Render3->GetTransform()->SetLocalScale({ 50.f,42.f,1.f });
	 Render3->GetTransform()->AddLocalPosition({ 405.f + x * 3,34.f });

	 Render4 = CreateComponent<GameEngineUIRenderer>();
	 Render4->CreateAnimation({ "Hold", "button.png", 35, 35 });
	 Render4->ChangeAnimation("Hold");
	 Render4->GetTransform()->SetLocalScale({ 50.f,42.f,1.f });
	 Render4->GetTransform()->AddLocalPosition({ 408.f,34.f-y });

}


void UIButton::Render(float _DeltaTime)
{

}