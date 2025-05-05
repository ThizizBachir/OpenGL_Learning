

#version 460 core

out vec3 WorldPos;
out vec3 RelativetoCameraPos;

uniform mat4 view;
uniform mat4 projection;
uniform vec3 CameraWorldPos;
uniform float gGridSize = 100.0;

const vec3 Pos[8] = vec3[8](
    vec3(-1.0, 0.0, -1.0),  //             
    vec3( 1.0, 0.0, -1.0),  //    7---------6                           
    vec3( 1.0, 0.0,  1.0),  //    |3--------|2      
    vec3(-1.0, 0.0,  1.0),  //    /         /      
    vec3(-1.0, -1.0, 0.0),  //   0|--------1|      
    vec3( 1.0, -1.0, 0.0),  //    |         |   
    vec3( 1.0,  1.0, 0.0),  //    4---------5   
    vec3(-1.0,  1.0, 0.0)   //      
);                          //      

const int Indices[12] = int[12](0, 2, 1, 2, 0, 3, 4, 6, 5, 6, 4, 7);


void main()
{
    int Index = Indices[gl_VertexID];
    vec3 vPos3 = Pos[Index] * gGridSize;

    RelativetoCameraPos=vPos3;
    if (gl_VertexID<6)
    {
        vPos3.x += CameraWorldPos.x;
        vPos3.z += CameraWorldPos.z;
    }

    vec4 vPos4 = vec4(vPos3, 1.0);

    gl_Position = projection * view * vPos4;

    WorldPos = vPos3;
}