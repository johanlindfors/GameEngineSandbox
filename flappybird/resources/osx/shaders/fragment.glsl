varying vec2 TexCoords;

uniform sampler2D tex;

void main()
{
    gl_FragColor = texture2D(tex, TexCoords);
}