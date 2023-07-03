#include "PrecompileHeader.h"
#include "UIButton.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTileMapRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
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
	Render0 = CreateComponent<GameEngineSpriteRenderer>();
	//Collision = CreateComponent<GameEngineCollision>();
	Render0->GetTransform()->SetLocalScale({ 50.f,50.f });
	TileMap = CreateComponent<GameEngineTileMapRenderer>(1);
	TileMap->CreateTileMap(3,3,{46.f,37.f});
	int num = 0;
	for (int y = TileMap->GetCount().y - 1; y >= 0; y--)
	{
		for (size_t x = 0; x < TileMap->GetCount().x; x++)
		{
			TileMap->SetTile(x, static_cast<size_t>(y), "button.png", num);
			num++;
		}
	}
}


void UIButton::Render(float _DeltaTime)
{

}