precision mediump float;
//out vec4 FragColor;

varying vec2 TexCoord;
uniform sampler2D tex;

void main() {
	gl_FragColor = texture2D(tex, TexCoord);
}