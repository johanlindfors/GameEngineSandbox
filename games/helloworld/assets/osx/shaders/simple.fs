#version 330 core
precision mediump float;
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D tex;

void main() {
	FragColor = texture(tex, TexCoord);
}