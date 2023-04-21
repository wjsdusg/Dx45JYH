#pragma once
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"

// ��� �ؽ�ó�� ������۰� 
class GameEngineShaderResources
{
public:
	std::string Name;
	class GameEngineShader* ParentShader;
	int BindPoint = -1; // b0 t0 ���� ���° ���Կ� ���õǾ�� �ϴ����� ���� ����.
};

class GameEngineConstantBufferSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineConstantBuffer> Res;
};

class GameEngineTextureSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineTexture> Res;
};

class GameEngineShaderResHelper
{
private:
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBuffer;

public:
	void CreateConstantBufferSetter(const GameEngineConstantBufferSetter& _Buffer)
	{
		ConstantBuffer.insert(std::make_pair(_Buffer.Name, _Buffer));
	}

	void Copy(const GameEngineShaderResHelper& _ResHelper);
};
