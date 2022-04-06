Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

cbuffer cbuff0 : register(b0)
{
	float4 color;
	matrix mat;
};

struct VSOutput
{
	float4 svpos : SV_POSITION;	//���_���W
	float2 uv    : TEXCOORD;	//UV���W
	
    matrix ins_matrix : INSTANCE_WORLD_MAT;	//�C���X�^���V���O�p�ϊ��s��
};

struct GSOutput
{
    float4 pos : SV_POSITION;
	
};