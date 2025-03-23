#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Fragpos;
in mat3 TBN;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

uniform vec3 lightColor=vec3(1.0,1.0,1.0);
uniform vec3 lightDir=vec3(-1.0,-1.0,-1.0);
uniform vec3 ViewPos;

float near = 0.1; 
float far  = 100.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{             
    float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
    //FragColor = vec4(1.0-depth,0.0,0.0, 1.0);

    //diffuse color
    vec3 diffuseColor= texture(texture_diffuse1,TexCoords).rgb;

    //calculating normal
    vec3 normal = texture(texture_normal1,TexCoords).rgb;
    normal = normal*2 -1.0;
    normal = normalize(TBN * normal);

    //calculating Spec
    float specStrenght = texture(texture_specular1,TexCoords).r;

    //lightning calculation
    vec3 LightDirection = normalize(-lightDir);
    vec3 viewDir = normalize(ViewPos-Fragpos);

    //diffuse calculation
    float diff = max(0.0,dot(normal,LightDirection));
    vec3 diffuse = diff * diffuseColor * lightColor;

    //specular lightning 
    vec3 halfwayDir = normalize(viewDir+LightDirection);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = spec * specStrenght * lightColor;

    FragColor=vec4(diffuse+specular,1.0);




    //FragColor += texture(texture_diffuse1,TexCoords);
    //FragColor += texture(texture_specular1,TexCoords);
    //FragColor += texture(texture_normal1,TexCoords) ;
    
}