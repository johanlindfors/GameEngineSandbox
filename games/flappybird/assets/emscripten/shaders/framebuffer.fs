uniform sampler2D screenTexture;
varying mediump vec2 TexCoords;

void main(void)
{ 
    gl_FragColor = texture2D(screenTexture, TexCoords);
}