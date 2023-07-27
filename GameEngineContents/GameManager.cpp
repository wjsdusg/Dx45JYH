#include "PrecompileHeader.h"
#include "GameManager.h"
#include "Building.h"
#include <GameEngineCore/GameEngineTileMapRenderer.h>
#include "MapOverlay.h"
#include "Unit.h"
#include "Object.h"
#include "Minion.h"
#include "MiniMap.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineFontUIRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "Monster_01.h"
#include "Frog.h"
#include "Gangsi.h"
#include "Gatpha.h"
#include "HungryDemon.h"
#include "Onghwa.h"
#include "Raccoondog.h"
#include "Snowdemon.h"
#include "Snowwoman.h"

#include "Tiger.h"
#include "WeirdPlant.h"
#include "SwordPirate.h"


GameManager::GameManager()
{

}

GameManager::~GameManager()
{
}




void GameManager::Update(float _DeltaTime)
{
	FSM.Update(_DeltaTime);
	if (num == 15)
	{
		FSM.ChangeState("CreateMOnster");
		num = 0;
		Round++;
	}

	{
		std::string str3 = std::to_string(Object::Money);
		FontRender0->SetText(str3);
	}
	{
		std::string str3 = std::to_string(Minion::MinionNum);
		FontRender1->SetText(str3);
	}
	{
		std::string str3 = "Round : ";
		std::string str4 = std::to_string(Round);
		str3 += str4;
		FontRender2->SetText(str3);
	}
	/*std::string str4 = std::to_string(Object::Money);
	str3 += str4;
	str3 += "/";
	str4 = std::to_string(HP);
	str3 += str4;*/

}

void GameManager::Start()
{
	StateInit();
	MoneyRender = CreateComponent<GameEngineUIRenderer>();
	MoneyRender->SetTexture("Money.png");	
	MoneyRender->GetTransform()->SetLocalScale({ 20,20,1.f });	
	MoneyRender->GetTransform()->SetLocalPosition({ -450.f,420.f });
	
	MonsterRender = CreateComponent<GameEngineUIRenderer>();
	MonsterRender->SetTexture("MonsterMark.png");
	MonsterRender->GetTransform()->SetLocalScale({ 20.f,20.f,1.f });
	MonsterRender->GetTransform()->SetLocalPosition({ -300.f,420.f });

	FontRender0 = CreateComponent<GameEngineFontUIRenderer>();
	FontRender0->SetFont("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");
	FontRender0->SetScale({ 20.f });
	FontRender0->SetColor({ 1.f,1.f,1.f });
	FontRender0->GetTransform()->SetLocalPosition({ -500.f,435.f });

	FontRender1 = CreateComponent<GameEngineFontUIRenderer>();
	FontRender1->SetFont("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");
	FontRender1->SetScale({ 20.f });
	FontRender1->SetColor({ 1.f,1.f,1.f });
	FontRender1->GetTransform()->SetLocalPosition({ -350,435.f });

	FontRender2 = CreateComponent<GameEngineFontUIRenderer>();
	FontRender2->SetFont("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");
	FontRender2->SetScale({ 30.f });
	FontRender2->SetColor({ 1.f,1.f,1.f });
	FontRender2->GetTransform()->SetLocalPosition({ -200.f,435.f });
}

void GameManager::StateInit()
{
	FSM.CreateState(
		{ .Name = "CreateMOnster",
		.Start = [this]()
		{
			RandomNum = GameEngineRandom::MainRandom.RandomInt(0,11);
		},
		.Update = [this](float _DeltaTime)
		{
			
			if (2 <= GetLiveTime())
			{
				switch (RandomNum)
				{
				case 0:
					GetLevel()->CreateActor<Monster_01>();
					break;
				case 1:
					GetLevel()->CreateActor<Frog>();
					break;
				case 2:
					GetLevel()->CreateActor<Gangsi>();
					break;
				case 3:
					GetLevel()->CreateActor<Gatpha>();
					break;
				case 4:
					GetLevel()->CreateActor<HungryDemon>();
					break;
				case 5:
					GetLevel()->CreateActor<Onghwa>();
					break;
				case 6:
					GetLevel()->CreateActor<Raccoondog>();
					break;
				case 7:
					GetLevel()->CreateActor<Snowdemon>();
					break;
				case 8:
					GetLevel()->CreateActor<Snowwoman>();
					break;
				case 9:
					GetLevel()->CreateActor<Tiger>();
					break;
				case 10:
					GetLevel()->CreateActor<WeirdPlant>();
					break;
				case 11:
					GetLevel()->CreateActor<SwordPirate>();
					break;

					break;
				}
				ResetLiveTime();
				num++;
			}
			
		},
		.End = []() {}
		}
	);

	FSM.ChangeState("CreateMOnster");
}

