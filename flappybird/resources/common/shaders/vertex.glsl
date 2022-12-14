attribute vec4 vertex; // <vec2 position, vec2 texCoords>
attribute vec2 a_uv;

uniform mat4 world;
uniform mat4 projection;

varying vec2 TexCoords;

void main()
{
    TexCoords = a_uv;
    gl_Position = projection * world * vertex;
}
