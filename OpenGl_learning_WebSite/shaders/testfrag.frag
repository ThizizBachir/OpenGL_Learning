#version 460 core
out vec4 FragColor;
in vec3 WorldPos;

uniform float GridMinPixelBetween=2.0;
uniform float GridCellSize=0.025;
uniform vec4 GridColorThick=vec4(0.0,0.0,0.0,1.0);
uniform vec4 GridColorThin=vec4(0.5,0.5,0.5,1.0);
uniform float gGridSize = 100.0;

void main(){
FragColor=vec4(1.0,0.0,0.0,1.0);
}