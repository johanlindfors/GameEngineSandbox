attribute vec3 inPosition;
attribute vec2 inUV;

varying vec2 fragUV;

uniform mat4 uMVP;

void main() {
    fragUV = inUV;
    gl_Position = uMVP * vec4(inPosition, 1.0);
}