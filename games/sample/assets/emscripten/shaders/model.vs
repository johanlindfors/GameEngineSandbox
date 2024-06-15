attribute vec3 aPos;
attribute vec3 aNormal;
attribute vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 normalRotation;

varying vec3 FragPos;
varying vec3 Normal;

void main() {
    //FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = (normalRotation * vec4(aNormal, 1.0)).xyz;
    
    gl_Position = projection * view * model * vec4(aPos, 1.0);//vec4(FragPos, 1.0);
    FragPos = vec3(aTexCoord, 1.0);
}
