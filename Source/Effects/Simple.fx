

// ----------------------------------------------------------------------------
// STRUCT DEFINITIONS
// ----------------------------------------------------------------------------
struct VS_IN
{
	float3 pos : POSITION;
	float4 col : COLOR;
};

struct PS_IN
{
	float4 pos : SV_POSITION;
	float4 col : COLOR;
};

// ----------------------------------------------------------------------------
// CONSTANT BUFFERS
// ----------------------------------------------------------------------------
cbuffer cbPerObject
{
	float4x4 gWVP;
};

// ----------------------------------------------------------------------------
// VERTEX SHADERS
// ----------------------------------------------------------------------------
PS_IN VS(VS_IN vIn)
{
	PS_IN vOut;

	vOut.pos = mul(float4(vIn.pos, 1.0f), gWVP);
	vOut.col = vIn.col;

	return vOut;
}

// ----------------------------------------------------------------------------
// PIXEL SHADERS
// ----------------------------------------------------------------------------
float4 PS(PS_IN pIn) : SV_Target
{
    return pIn.col;
}

// ----------------------------------------------------------------------------
// STATES
// ----------------------------------------------------------------------------
DepthStencilState NoDepth
{
	DepthEnable = false;
};

// ----------------------------------------------------------------------------
// TECHNIQUES
// ----------------------------------------------------------------------------
technique10 Simple
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );

		SetDepthStencilState(NoDepth, 0);
    }
}