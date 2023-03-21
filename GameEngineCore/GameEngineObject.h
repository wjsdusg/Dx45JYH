#pragma once
#include <list>
#include <memory>
#include <string_view>
// ���� :
class GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineObject();
	~GameEngineObject();

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	void On()
	{
		IsActive = true;
	}

	void Off()
	{
		IsActive = false;
	}

	//                 "�巡��"
	// �����Ҵ� 1���� ���̷���.
	void SetName(const std::string_view& _Name)
	{
		Name = _Name;
	}

protected:

private:
	std::string Name = "";
	bool IsActive = true; // ������ ������
	bool IsDeath = false; // �׾��� ��Ҵ�.

	GameEngineObject* Parent;

	std::list<std::shared_ptr<GameEngineObject>> Childs;
};