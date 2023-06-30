#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 normalRotation;

out vec3 FragPos;
out vec3 Normal;

void main() {
    //FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = (normalRotation * vec4(aNormal, 1.0)).xyz;
    
    gl_Position = projection * view * model * vec4(aPos, 1.0);//vec4(FragPos, 1.0);
    FragPos = vec3(aTexCoord, 1.0);
}
