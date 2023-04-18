#pragma once
#include <list>
#include <memory>
#include <string_view>

// ���� :
class GameEngineObjectBase
{
public:
	// constrcuter destructer
	GameEngineObjectBase();
	~GameEngineObjectBase();

	// delete Function
	GameEngineObjectBase(const GameEngineObjectBase& _Other) = delete;
	GameEngineObjectBase(GameEngineObjectBase&& _Other) noexcept = delete;
	GameEngineObjectBase& operator=(const GameEngineObjectBase& _Other) = delete;
	GameEngineObjectBase& operator=(GameEngineObjectBase&& _Other) noexcept = delete;


	int GetOrder()
	{
		return Order;
	}

	void SetOrder(int _Order)
	{
		Order = _Order;
	}

	void On()
	{
		ActiveValue = true;
	}

	void Off()
	{
		ActiveValue = false;
	}

	void Death()
	{
		DeathValue = true;
	}

	//                 "�巡��"
	// �����Ҵ� 1���� ���̷���.
	void SetName(const std::string_view& _Name)
	{
		Name = _Name;
	}

	void DebugOn()
	{
		DebugValue = true;
	}

	bool IsDebug()
	{
		return DebugValue;
	}

protected:

private:
	std::string Name = "";
	bool ActiveValue = true; // ������ ������
	bool DeathValue = false; // �׾��� ��Ҵ�
	bool DebugValue = false;
	int Order = 0;
	////////////////////////////////////////////////////////////// Transform ���ϱ���
};

