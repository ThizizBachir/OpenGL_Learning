#version 460 core
out vec4 FragColor;

in vec3 fragPos;  
in vec3 normal;  
in vec2 TexCoords;

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct DirLight{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight{
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NR_POINTS_LIGHTS 1


uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINTS_LIGHTS];
uniform SpotLight spotLight;
uniform Material material;

uniform vec3 viewPos; 

vec3 CalcDirLight(DirLight light,vec3 normal,vec3 viewDir);
vec3 CalcPointLight(PointLight light,vec3 normal ,vec3 viewDir);
vec3 CalcSpotLight(SpotLight light , vec3 normal ,vec3 viewDir);

void main()
{
    
    // properties 
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);
    //@emission 
    //vec3 emiss=vec3(texture(material.emission,TexCoords));
    vec3 result=vec3(0.0,0.0,0.0);
    //result+=CalcDirLight(dirLight,norm,viewDir);

    for (int i=0;i<NR_POINTS_LIGHTS;i++){
        result+=CalcPointLight(pointLights[i],norm,viewDir);
    }

    //result += CalcSpotLight(spotLight,normal,viewDir);

    FragColor = vec4(result, 1.0);
} 

vec3 CalcDirLight(DirLight light,vec3 normal,vec3 viewDir){
    vec3 lightDir=normalize(-light.direction);
    // diffuse shading 
    float diff=max(dot(normal,lightDir),0.0);
    // specular shading 
    vec3 reflectDir=reflect(-lightDir,normal);
    float spec =pow(max(dot(reflectDir,lightDir),0.0),material.shininess);
    //combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoords));
    return (ambient + diffuse + specular);
    }

vec3 CalcPointLight(PointLight light,vec3 normal ,vec3 viewDir){
    vec3 lightDir=normalize(light.position-fragPos);
    //diffuse shading 
    float diff=max(dot(normal,lightDir),0.0);
    //specular shading
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(reflectDir,viewDir),0.0),material.shininess);
    // attenuation
    float dist = distance(light.position,fragPos);
    float attenuation = 1.0/(light.constant+light.linear*dist + light.quadratic * dist * dist);
    //combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords)) * attenuation;
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCoords)) * attenuation;
    vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoords)) * attenuation;
    
    return (ambient + diffuse + specular);

}

vec3 CalcSpotLight(SpotLight light, vec3 normal,vec3 viewDir){
    vec3 lightDir=normalize(light.position-fragPos);
    //diffuse shading
    vec3 norm=normalize(normal);
    float diff= max(dot(lightDir,norm),0.0);
    //specular shading
    vec3 reflectDir=reflect(-lightDir,normal);
    float spec= pow(max(dot(reflectDir,viewDir),0.0),material.shininess);
     // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 
    //spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}