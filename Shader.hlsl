Texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 color : COLOR0;
};

cbuffer ShaderInput : register(b1)
{
	float2 g_resolution;
	float  g_time;
	float  g_frame;
	float2 g_mouse;
	float  g_leftPressed;
	float  g_rightPressed;
	float2 g_textureResolution;
};

float4 PS(float4 position : SV_POSITION, float2 uv : TEXCOORD0) : SV_Target
{
	float d = 1.0 - distance(position.xy, g_mouse) / 200;
	
	if (g_leftPressed)
	{
		d = (d > 0.0);
	}

	return float4(d, d, d, 1) * texture0.Sample(sampler0, uv);
}
