#version 460 core

/**
 Don't know what combining two attributes in one actually increase speed
*/
layout(location = 0) in vec4 aVertex;

layout(location = 0) out vec2 vTexCoords;

void main() {
    gl_Position = vec4(aVertex.xy, 0.0, 1.0);
    vTexCoords = aVertex.zw;
}