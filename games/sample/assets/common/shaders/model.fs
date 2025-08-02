#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  

uniform bool useTexture;
uniform sampler2D tex;

uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
            
    vec3 result = (diffuse) * objectColor;
    if(useTexture) {
        FragColor = texture(tex, FragPos.xy) + vec4(result, 1.0);
    } else {
        FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
}
