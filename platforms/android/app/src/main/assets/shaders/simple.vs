precision mediump float;
//layout (location = 0) in vec4 vertex;
attribute vec4 vertex;

uniform mat4 world;
uniform mat4 projection;
uniform vec4 offset;

varying vec2 TexCoord;

void main() {
	gl_Position = projection * world * vec4(vertex.xy, 0.0, 1.0);
	TexCoord =
	    //offset.xy +
	    vec2(offset.x, offset.y) +
	    vec2(vertex.z, vertex.w) *
	    //offset.zw;
	    vec2(offset.z, offset.w);
}