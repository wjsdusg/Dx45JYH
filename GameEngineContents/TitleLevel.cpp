#include "PrecompileHeader.h"
#include "TitleLevel.h"
#include <GameEngineBase\GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}


void TitleLevel::Start()
{
	if (false == GameEngineInput::IsKey("LevelChangeKey"))
	{
		GameEngineInput::CreateKey("LevelChangeKey", 'I');
	}

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });


	// TimeEvent.AddEvent(5.0f, std::bind(&TitleLevel::TestMsg, this), true);

	//std::function<void(GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)> Test0 =
	//	[](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
	//{
	//	MsgTextBox("����");
	//};

	//// ���� ����
	//// �̸��� ���� �Լ��� ������ ����.
	//std::function<void(GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)> Test = 
	//	[=](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
	//{
	//	MsgTextBox("����");

	//	_Manager->AddEvent(3.0f, Test0, false);
	//};

	// TimeEvent.AddEvent(3.0f, Test, false);
}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("LevelChangeKey"))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}