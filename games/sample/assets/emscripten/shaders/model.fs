precision mediump float;

varying vec3 Normal;  
varying vec3 FragPos;  

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
            
    vec3 result = (ambient + diffuse) * objectColor;
    gl_FragColor = texture2D(tex, FragPos.xy) + vec4(result, 1.0);
}
