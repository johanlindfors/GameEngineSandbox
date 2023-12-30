precision mediump float;
attribute vec4 vertex;

uniform mat4 world;
uniform mat4 projection;
uniform vec4 offset;

varying vec2 TexCoord;

void main() {
	gl_Position = projection * world * vec4(vertex.xy, 0.0, 1.0);
	TexCoord = vec2(offset.x, 1.0 - offset.y - offset.w) +
	           vec2(vertex.z, 1.0 - vertex.w) *
	           vec2(offset.z, offset.w);
}
