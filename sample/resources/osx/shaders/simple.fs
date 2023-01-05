varying vec2 fragUV;

uniform sampler2D uTexture;

varying vec4 FragColor;

void main() {
    gl_FragColor = texture2D(uTexture, fragUV);
}
