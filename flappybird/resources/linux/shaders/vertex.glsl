#version 330 core
layout (location = 0) in vec4 vertex;
layout (location = 1) in vec2 a_uv;

uniform mat4 world;
uniform mat4 projection;

out vec2 TexCoords;

void main()
{
    TexCoords = a_uv;
    gl_Position = projection * world * vertex;
}
