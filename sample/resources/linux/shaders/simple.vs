#version 300 es

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inUV;

out vec2 fragUV;

uniform mat4 uMVP;

void main() {
    fragUV = inUV;
    gl_Position = uMVP * vec4(inPosition, 1.0);
}
