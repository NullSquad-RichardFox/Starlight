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

float screenPxRange() {
    vec2 unitRange = vec2(2.0)/vec2(textureSize(uTextures[int(vTexID)], 0));
    vec2 screenTexSize = vec2(1.0)/fwidth(vTexCoord);
    return max(0.5*dot(unitRange, screenTexSize), 1.0);
}

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

void main()
{    
    vec3 msd = texture(uTextures[int(vTexID)], vTexCoord).rgb;
    float sd = median(msd.x, msd.y, msd.z);
    float screenPxDistance = screenPxRange()*(sd - 0.5);
    float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);
    albedo = vec4(vColor.rgb, opacity * vColor.w);
}  
)"