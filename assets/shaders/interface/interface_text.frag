#version 460

layout (location = 0) in vec2 vTexCoords;
layout (location = 0) out vec4 fragColor;

layout(location = 0) uniform sampler2D uText;
layout(location = 1) uniform vec3 uColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(uText, vTexCoords).r);
    fragColor = vec4(uColor, 1.0) * sampled;
}