precision mediump float;

varying vec2 TexCoord;
uniform sampler2D screenTexture;

void main()
{
    gl_FragColor = texture2D(screenTexture, TexCoord);
}