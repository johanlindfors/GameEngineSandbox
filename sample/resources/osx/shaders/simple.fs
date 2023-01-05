#version 330 core
in vec2 fragUV;

uniform sampler2D uTexture;

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0,0.0,0.0,1.0);//texture(uTexture, fragUV);
}
