#include "PrecompileHeader.h"
#include "GameEngineVertex.h"


void GameEngineInputLayOut::AddInputLayOut(
	LPCSTR SemanticName, // ���� �������̴� ���� �÷���.
	DXGI_FORMAT Format, // ���� n����Ʈ ¥�� ������ �ڷ���
	D3D11_INPUT_CLASSIFICATION InputSlotClass, //= D3D11_INPUT_PER_VERTEX_DATA, // ���ؽ� �����Ͱ� �ν��Ͻ� �����ʹ� ��°� ǥ��
	UINT InstanceDataStepRate, // = 0, // ���߿� ���߿� �ν��Ͻ��̶�� ������ ��ﶧ ������ �������̴�.
	UINT AlignedByteOffset, // = -1, // 0��° ����Ʈ���� 
	UINT InputSlot, // = 0, // n���� ���ؽ� ���۸� �����Ҷ� n��° ���ؽ� ������ ��ǲ ���̾ƿ��̴� ��°� ǥ���ϴ°�
	UINT SemanticIndex // = 0
)
{
	D3D11_INPUT_ELEMENT_DESC Data;

	// POSITION
	Data.SemanticName = SemanticName;

	Descs.push_back(Data);
}

GameEngineInputLayOut GameEngineVertex::LayOut;