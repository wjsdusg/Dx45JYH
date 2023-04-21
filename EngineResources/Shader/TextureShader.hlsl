// ���̴��� ¥�ԵǸ� ������ ��Ģ�� ���Ѿ� �Ѵ�.

// 0~ 16�� ���� 
// ������ ���ٰ� ���°� �ƴϿ���.
cbuffer TransformData : register(b0)
{
    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalQuaternion;
    float4 LocalPosition;
    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuaternion;
    float4 WorldPosition;
    float4x4 LocalScaleMatrix;
    float4x4 LocalRotationMatrix;
    float4x4 LocalPositionMatrix;
    float4x4 LocalWorldMatrix;
    float4x4 WorldMatrix;
    float4x4 View;
    float4x4 Projection;
    float4x4 ViewPort;
    float4x4 WorldViewProjectionMatrix;
}

// � ������ ������ ����ü�� ������ �մϴ�.
// ��� �������̰� ��� ���̰�
// �̸� �������
struct Input
{
	// �ø�ƽ      ������� �������� 
    // ���ؽ� ���̴����ٰ� ������ ��� �س��� ��� �װ� ����� �����.
    // �߿��Ѱ� ���ؽ� ���۰� 
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct OutPut
{
    // �����Ͷ������� �� ��������
    // w���� ����  ����Ʈ ���ϰ� �ȼ� �������� �������� ������ ���� �����ž�.
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};


// �������������

OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    // OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;
	
	// �����ܰ迡�� ����� ������.
    // OutPutValue.Pos *= �������������;

    return OutPutValue;
}

cbuffer OutPixelColor : register(b0)
{
    float4 OutColor;
}

Texture2D DiffuseTex : register(t0);
SamplerState CLAMPSAMPLER : register(s0);

float4 Texture_PS(OutPut _Value) : SV_Target0
{
    // ������ ǥ�����̶�� �ؼ�
    // float4
    // float4.xy == float2
    float4 Color = DiffuseTex.Sample(CLAMPSAMPLER, _Value.UV.xy);
    
    //if (0.5 < _Value.Color.x)
    //{
    //    clip(-1);
    //}
    
    return Color;
}