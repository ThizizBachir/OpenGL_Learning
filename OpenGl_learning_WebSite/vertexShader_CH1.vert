#version 460 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;// the color variable has attribute position 1
  
out vec3  Color; // output a color to the fragment shader
out vec2  Tex; 
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection*view*model*vec4(aPos, 1.0);
    Color = aColor; // set ourColor to the input color we got from the vertex data
    Tex=aTex;
}   