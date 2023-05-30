#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>
#include "PlayLevel.h"
#include "TitleLevel.h"
#include <GameEngineCore/GameEngineCoreWindow.h>



ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}


void ContentsCore::GameStart()
{


	new int();

	GameEngineGUI::GUIWindowCreate<GameEngineCoreWindow>("CoreWindow");


	ContentsResourcesCreate();

	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<PlayLevel>();
	GameEngineCore::ChangeLevel("PlayLevel");
}

void ContentsCore::GameEnd()
{

}