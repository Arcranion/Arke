#version 460 core

layout(location = 0) in vec2 vTexCoords;

layout(location = 0) out vec4 fragColor;

uniform sampler2D uTexture;
layout(location = 0) uniform vec4 uColor;

void main() {
    fragColor = uColor * texture(uTexture, vTexCoords);
}