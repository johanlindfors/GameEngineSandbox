precision mediump float;
attribute vec2 aPos;
attribute vec2 aTexCoords;

out vec2 TexCoords;

void main() 
{
	gl_Position = vec4(aPos.xy, 0.0, 1.0);
	TexCoords = aTexCoords;
}
