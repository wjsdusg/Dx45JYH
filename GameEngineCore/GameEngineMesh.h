#pragma once
#include "GameEngineResource.h"
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"

// ���� :
class GameEngineMesh : public GameEngineResource<GameEngineMesh>
{
	friend class GameEngineRenderUnit;

public:
	static void Create(const std::string_view& _Name)
	{
		Create(_Name, _Name, _Name);
	}

	static void Create(const std::string_view& _Name, const std::string_view& _VtxName, const std::string_view& _IdxName)
	{
		std::shared_ptr<GameEngineMesh> Res = GameEngineResource::Create(_Name);
		Res->VertexBufferPtr = GameEngineVertexBuffer::Find(_VtxName);
		Res->IndexBufferPtr = GameEngineIndexBuffer::Find(_IdxName);

		if ((nullptr == Res->VertexBufferPtr) || (nullptr == Res->IndexBufferPtr))
		{
			MsgAssert("�Ž��� ����µ� �����߽��ϴ�.");
		}
	}

	std::shared_ptr<GameEngineVertexBuffer> GetVertexBuffer()
	{
		return VertexBufferPtr;
	}

	// constrcuter destructer
	GameEngineMesh();
	~GameEngineMesh();

	// delete Function
	GameEngineMesh(const GameEngineMesh& _Other) = delete;
	GameEngineMesh(GameEngineMesh&& _Other) noexcept = delete;
	GameEngineMesh& operator=(const GameEngineMesh& _Other) = delete;
	GameEngineMesh& operator=(GameEngineMesh&& _Other) noexcept = delete;

protected:
	void Setting() override;

	void InputAssembler1();
	void InputAssembler2();

private:
	D3D11_PRIMITIVE_TOPOLOGY TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	std::shared_ptr<GameEngineVertexBuffer> VertexBufferPtr;
	std::shared_ptr<GameEngineIndexBuffer> IndexBufferPtr;
};

