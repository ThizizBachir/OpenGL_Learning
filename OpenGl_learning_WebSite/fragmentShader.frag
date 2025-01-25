#version 330 core
out vec4 FragColor;
in vec3 Color;
in vec2 Tex;
uniform sampler2D Texture_1;
uniform sampler2D Texture_2;
void main()
{
    //FragColor =texture(Texture_1,Tex);
    FragColor = mix(texture(Texture_1,Tex),texture(Texture_2,Tex),0.2);
}