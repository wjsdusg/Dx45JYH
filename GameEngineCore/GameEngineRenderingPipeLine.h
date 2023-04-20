#pragma once
#include "GameEngineResource.h"

// ���� :
class GameEngineRenderingPipeLine : public GameEngineResource<GameEngineRenderingPipeLine>
{
public:
	// constrcuter destructer
	GameEngineRenderingPipeLine();
	~GameEngineRenderingPipeLine();

	// delete Function
	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _Other) = delete;
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _Other) noexcept = delete;
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _Other) = delete;
	GameEngineRenderingPipeLine& operator=(GameEngineRenderingPipeLine&& _Other) noexcept = delete;

	void InputAssembler1();
	void VertexShader();
	void InputAssembler2();
	// Lod��� ������ �ִµ�
	// ���� ���� �������̶�� �������� ���ؽ����� + �ε�������(�Ž�)�� �ܰ迡 ���� n�� �����
	// 5�� ������ٰ� ġ��
	// 100��
	// 1000��
	// 4000��
	// 8000��
	// 10000��
	// ĳ���Ͱ� �ָ� �־ �ڼ��� �M
	// void HullShader(); ���ؽ��� �ɰ��� ���� ǥ�ø� �����
	// void Tessellator(); �ɰ���.
	// 
	// 
	// void DomainShader(); ����ó��
	// void GeometryShaeder(); ���ؽ� ����.
	//                         �ν��Ͻ�

	// �̰� ��¥ ��ģ���� �߿��մϴ�.
	void Rasterizer();
	void PixelShader();
	void OutputMerger();

	void SetVertexBuffer(const std::string_view& _Value);

protected:

private:
	std::shared_ptr<class GameEngineVertexBuffer> VertexBuffer;

};

