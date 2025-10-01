#type vertex
#version 450 core

struct MatData
{
	vec3 Position;
	vec3 Normal;
	vec3 LightPos;
	float LightIntensity;
	vec4 Color;
	vec2 TexCoord;
	float TexID;
};

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec4 aColor;
layout(location = 4) in float aTexID;	

uniform mat4 uViewProjMat;
uniform vec4 uLightPos;

out MatData vMaterialData;

void main()
{
	vMaterialData.Position = aPosition;
	vMaterialData.Normal = aNormal;
	vMaterialData.LightPos = uLightPos.xyz;
	vMaterialData.LightIntensity = uLightPos.w;
	vMaterialData.Color = aColor;
	vMaterialData.TexCoord = aTexCoord;
	vMaterialData.TexID = aTexID;

	gl_Position = uViewProjMat * vec4(aPosition, 1.0);
}			

#type fragment
#version 450 core

struct MatData
{
	vec3 Position;
	vec3 Normal;
	vec3 LightPos;
	float LightIntensity;
	vec4 Color;
	vec2 TexCoord;
	float TexID;
};

out vec4 albedo;

layout (binding = 0) uniform sampler2D uTextures[32];
layout (location = 0) in MatData vMaterialData;

void main()
{
	vec3 lightDir = vMaterialData.LightPos - vMaterialData.Position;
	float lightDist = length(lightDir);
	float lightMagnitude = vMaterialData.LightIntensity * dot(normalize(vMaterialData.Normal), normalize(lightDir)) / lightDist;

	switch(int(vMaterialData.TexID))
	{
		case -1: albedo = vec4(vMaterialData.Color.rgb * lightMagnitude, vMaterialData.Color.w); break;
		default: albedo = texture(uTextures[int(vMaterialData.TexID)], vMaterialData.TexCoord); break;
	}
}