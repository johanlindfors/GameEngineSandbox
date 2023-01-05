#version 320 es
in vec2 fragUV;

uniform sampler2D uTexture;

out vec4 FragColor;

void main() {
    FragColor = texture(uTexture, fragUV);
}
