precision mediump float;
attribute vec2 aPos;
attribute vec2 aTexCoords;

varying vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
    TexCoord = aTexCoords;
}