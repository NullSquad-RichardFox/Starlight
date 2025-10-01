R"(
#type vertex
#version 450 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec4 aColor;
layout(location = 3) in float aTexID;

uniform mat4 uViewProjMat;

out vec2 vTexCoord;
out vec4 vColor;
out float vTexID;

void main()
{
    vTexCoord = aTexCoord;
    vColor = aColor;
    vTexID = aTexID;

    gl_Position = uViewProjMat * vec4(aPosition, 1.0);
}  	

#type fragment
#version 450 core

out vec4 albedo;

layout (binding = 0) uniform sampler2D uTextures[32];
layout (location = 0) in vec2 vTexCoord;
layout (location = 1) in vec4 vColor;
layout (location = 2) in float vTexID;

void main()
{    
    if (vTexID == -1.0f)
    {
        albedo = vColor;
    }
    else
    {
        vec4 tex = texture(uTextures[int(vTexID)], vTexCoord);
        albedo = vec4(tex.rgb, tex.w * vColor.w);
    }
}  
)"