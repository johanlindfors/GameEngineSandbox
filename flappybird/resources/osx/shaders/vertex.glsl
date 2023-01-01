attribute vec4 vertex;
attribute vec2 a_uv;

uniform mat4 world;
uniform mat4 projection;

varying vec2 TexCoords;

void main()
{
    TexCoords = a_uv;
    gl_Position = projection * world * vertex;
}