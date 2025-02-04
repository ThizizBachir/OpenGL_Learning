#version 460 core
out vec4 FragColor;

in vec3 normal;  
in vec3 fragPos;  

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct Light{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 position;
};

uniform Material material;
uniform Light light;

uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;

in vec2 TexCoords;

void main()
{
    // ambient
    vec3 ambient =  light.ambient * vec3(texture(material.diffuse, TexCoords));
    //float ambientStrength = 0.1;
    //vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCoords)) ;
    
    // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = vec3(texture(material.specular,TexCoords)) * spec * light.specular; 
    
    //emission 
    vec3 emiss=vec3(texture(material.emission,TexCoords));
        
    vec3 result = (ambient + diffuse + specular + emiss);
    FragColor = vec4(result, 1.0);
} 