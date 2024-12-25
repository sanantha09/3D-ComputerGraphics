/*cbuffer ConstantBuffer
{
    matrix worldViewProjection;
    float4 ambientLightColour;
};

Texture2D Texture;
SamplerState ss;

struct VertexIn
{
    float3 InputPosition : POSITION;
    float2 TexCoord : TEXCOORD;
};

struct VertexOut
{
    float4 OutputPosition : SV_POSITION;
    float4 Colour : COLOR;
    float2 TexCoord : TEXCOORD;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
	
	// Transform to homogeneous clip space.
    vout.OutputPosition = mul(worldViewProjection, float4(vin.InputPosition, 1.0f));
    vout.Colour = ambientLightColour;
    vout.TexCoord = vin.TexCoord;
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    return pin.Colour * Texture.Sample(ss, pin.TexCoord);
}
*/

cbuffer ConstantBuffer2
{
    matrix worldViewProjection;
    matrix world;
    float4 materialColour;
    float4 ambientLightColour;
    float4 DirectionalLightColour;
    float4 DirectionalLightVector;
};

Texture2D Texture;
SamplerState ss;

struct VertexIn
{
    float3 InputPosition : POSITION;
    float3 Normal : NORMAL;
    float2 TexCoord : TEXCOORD;
};

struct VertexOut
{
    float4 OutputPosition : SV_POSITION;
    float4 Colour : COLOR;
    float2 TexCoord : TEXCOORD;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
	
	// Transform to homogeneous clip space.
    vout.OutputPosition = mul(worldViewProjection, float4(vin.InputPosition, 1.0f));

    // Transform normal to world space using the world matrix
    float3 worldNormal = normalize(mul((float3x3) world, vin.Normal));

    // Calculate diffuse lighting
    float diffuseFactor = max(dot(worldNormal, -normalize(DirectionalLightVector.xyz)), 0.0);
    diffuseFactor = saturate(diffuseFactor); // Ensure the value is between 0 and 1

    // Calculate the total light on the vertex
    float4 totalLight = saturate(ambientLightColour + diffuseFactor * DirectionalLightColour);

    // Multiply by the material colour
    vout.Colour = saturate(totalLight * materialColour);
    vout.TexCoord = vin.TexCoord;
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    return pin.Colour * Texture.Sample(ss, pin.TexCoord);
}