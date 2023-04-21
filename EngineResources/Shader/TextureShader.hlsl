// ���̴��� ¥�ԵǸ� ������ ��Ģ�� ���Ѿ� �Ѵ�.

// � ������ ������ ����ü�� ������ �մϴ�.
// ��� �������̰� ��� ���̰�
// �̸� �������
struct Input
{
    // �ø�ƽ      ������� �������� 
    float4 Pos   : POSITION;
    float4 Color : COLOR;
};

struct OutPut
{
    // �����Ͷ������� �� ��������
    // w���� ����  ����Ʈ ���ϰ� �ȼ� �������� �������� ������ ���� �����ž�.
    float4 Pos : SV_Position;
    float4 Color : COLOR;
};

OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut)0;

    OutPutValue.Pos = _Value.Pos;
    OutPutValue.Color = _Value.Color;

    // �����ܰ迡�� ����� ������.
    // _Value.Pos *= �������������;

    return OutPutValue;
}

struct OutColor
{
    // ��Ƴ��� ��ȭ���� 0��° ��ȭ���� ����ض�.
    float4 Color : SV_Target0;
};

OutColor Texture_PS(OutPut _Value)
{
    OutColor ReturnColor = (OutColor)0;
    ReturnColor.Color = _Value.Color;
    return ReturnColor;
}