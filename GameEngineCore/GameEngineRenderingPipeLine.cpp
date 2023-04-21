#include "PrecompileHeader.h"
#include "GameEngineRenderingPipeLine.h"
#include <GameEngineCore/GameEngineDevice.h>
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineVertexShader.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine()
{
}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine()
{
}

// �Ž� + ��Ƽ����

// ���� ���� ������ �غ��ϰ�
void GameEngineRenderingPipeLine::InputAssembler1()
{
	if (nullptr == VertexBufferPtr)
	{
		MsgAssert("���ؽ� ���۰� �������� �ʾƼ� ��ǲ�����1 ������ ������ �� �����ϴ�.");
		return;
	}

	VertexBufferPtr->Setting();
	// GameEngineDevice::GetContext()->IASetVertexBuffers()
}
// ���ÿ� �����ϴ� ���� �츮�� ���� ����� ���ؼ� ��ȯ�ϰ�.
void GameEngineRenderingPipeLine::VertexShader()
{
	if (nullptr == VertexShaderPtr)
	{
		MsgAssert("���ؽ� ���̴��� �������� �ʾƼ� ���ؽ� ���̴� ������ ������ �� �����ϴ�.");
		return;
	}

	VertexShaderPtr->Setting();
	// GameEngineDevice::GetContext()->VSSetShader
}

// ���� ������ ���� � ������ �׸��� ���ϰ�
void GameEngineRenderingPipeLine::InputAssembler2()
{
	if (nullptr == IndexBufferPtr)
	{
		MsgAssert("�ε��� ���۰� �������� �ʾƼ� ��ǲ �����2 ������ ������ �� �����ϴ�.");
		return;
	}

	IndexBufferPtr->Setting();
}

// ���⼭����
void GameEngineRenderingPipeLine::HullShader()
{

}
void GameEngineRenderingPipeLine::Tessellator()
{

}
void GameEngineRenderingPipeLine::DomainShader()
{

}
void GameEngineRenderingPipeLine::GeometryShaeder()
{

}
// ��������� ȭ����� ���

// w�����⸦ ���ݴϴ�. 
// ����Ʈ�� �����ݴϴ�.
// ȭ�� �ø� 
// �ȼ� ������
void GameEngineRenderingPipeLine::Rasterizer()
{
	// GameEngineDevice::GetContext()->RSSetState
}


void GameEngineRenderingPipeLine::PixelShader()
{
	// GameEngineDevice::GetContext()->PSSetShader
}
void GameEngineRenderingPipeLine::OutputMerger()
{
	// GameEngineDevice::GetContext()->OMSetRenderTargets
}


void GameEngineRenderingPipeLine::SetVertexBuffer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexBufferPtr = GameEngineVertexBuffer::Find(UpperName);

	if (nullptr == VertexBufferPtr)
	{
		MsgAssert("�������� �ʴ� ���ؽ� ���۸� ����Ϸ��� �߽��ϴ�.");
	}
}


void GameEngineRenderingPipeLine::SetIndexBuffer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	IndexBufferPtr = GameEngineIndexBuffer::Find(UpperName);

	if (nullptr == IndexBufferPtr)
	{
		MsgAssert("�������� �ʴ� ���ؽ� ���۸� ����Ϸ��� �߽��ϴ�.");
	}
}


void GameEngineRenderingPipeLine::SetVertexShader(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexShaderPtr = GameEngineVertexShader::Find(UpperName);

	if (nullptr == VertexShaderPtr)
	{
		MsgAssert("�������� �ʴ� ���ؽ� ���̴��� ����Ϸ��� �߽��ϴ�.");
	}
}

// �Ž� + ��Ƽ����
void GameEngineRenderingPipeLine::Render()
{
	// ������� �ϴ� �κ��� ������ ������������ �ѹٲ� ������ ��.
	InputAssembler1();
	VertexShader();
	InputAssembler2();
	HullShader();
	Tessellator();
	DomainShader();
	GeometryShaeder();
	Rasterizer();
	PixelShader();
	OutputMerger();

	// �޽� <= ������ ��� ���ϰ��ΰ�.
	//         �ȼ����������� ������ �����ϴ� Rasterizer
	//         w�����⸦ �ϰ� ����Ʈ�� ���ؼ�

	// ��Ƽ���� <= ������ ��� ���ð��ΰ�?
	//             �����Ͷ����� + �ȼ����̴� + ���ؽ� ���̴�
}