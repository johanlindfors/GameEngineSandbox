#version 330 core
in vec3 inPosition;
in vec2 inUV;

out vec2 fragUV;

uniform mat4 uMVP;

void main() {
    fragUV = inUV;
    gl_Position = uMVP * vec4(inPosition, 1.0);
}