#pragma once

// ���� :
class GameEngineShader
{
public:
	// constrcuter destructer
	GameEngineShader();
	~GameEngineShader();

	// delete Function
	GameEngineShader(const GameEngineShader& _Other) = delete;
	GameEngineShader(GameEngineShader&& _Other) noexcept = delete;
	GameEngineShader& operator=(const GameEngineShader& _Other) = delete;
	GameEngineShader& operator=(GameEngineShader&& _Other) noexcept = delete;

protected:

private:
	// Hlsl ������� ���� �ƿ� �ϰ���

	// ���̴� �ڵ带 2�������ͷ� ���������� �װ� �׷���ī�尡 ���ο� �����
	// �츮���Դ� 
	ID3DBlob* BinaryCode;
	std::string Version;

};

