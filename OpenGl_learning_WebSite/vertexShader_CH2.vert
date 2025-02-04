#version 460 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aNorm;   // the position variable has attribute position 0
layout (location = 2) in vec2 aTexCoords;   // the position variable has attribute position 0
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 normal;
out vec3 fragPos;
out vec2 TexCoords;
void main()
{
    gl_Position = projection*view*model*vec4(aPos, 1.0);
    fragPos= vec3(model* vec4(aPos,1.0f));
    normal = mat3(transpose(inverse(model)))*aNorm;
    TexCoords=aTexCoords;
}   