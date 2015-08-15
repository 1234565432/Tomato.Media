//
// Tomato Media
// Ĭ����Ƶ Shader ����
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-08-15
//

struct VertexInput
{
	float4 Position : POSITION;
	float4 Color : COLOR0;
	float2 TexCoord : TEXTCOORD;
};

struct PixelInput
{
	float4 Position : SV_Position;
	float4 Color : COLOR0;
};

struct PixelOutput
{
	float4 Color : SV_Target;
};