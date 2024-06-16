attribute vec4 vertex;
uniform mat4 world;
uniform mat4 projection;
uniform vec4 offset;

varying vec2 TexCoord;

void main() {
	gl_Position = projection * world * vec4(vertex.xy, 0.0, 1.0);
	TexCoord = offset.xy + vertex.zw * offset.zw;
}