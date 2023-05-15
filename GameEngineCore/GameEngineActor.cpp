#include "PrecompileHeader.h"
#include "GameEngineActor.h"
#include "GameEngineComponent.h"

GameEngineActor::GameEngineActor()
{
}

GameEngineActor::~GameEngineActor()
{
}

void GameEngineActor::ComponentInit(std::shared_ptr<class GameEngineComponent> _Component)
{
	_Component->Actor = this;
	_Component->Level = GetLevel();
	_Component->GetTransform()->SetParent(GetTransform());
	_Component->Start();

	// PushChild(_Component); << SetParent 문제로 child가 두 번 들어가서 뺌
}

