#version 460 core
out vec4 FragColor;
in vec3 WorldPos;

uniform float GridMinPixelBetween=2.0;
uniform float GridCellSize=0.025;
uniform vec4 GridColorThick=vec4(0.0,0.0,0.0,1.0);
uniform vec4 GridColorThin=vec4(0.5,0.5,0.5,1.0);
uniform float gGridSize = 100.0;



float log10(float x)
{
    float f = log(x) / log(10.0);
    return f;
}


float satf(float x)
{
    float f = clamp(x, 0.0, 1.0);
    return f;
}


vec2 satv(vec2 x)
{
    vec2 v = clamp(x, vec2(0.0), vec2(1.0));
    return v;
}


float max2(vec2 v)
{
    float f = max(v.x, v.y);
    return f;
}



void main()
{

    vec2 dvx=vec2(dFdx(WorldPos.x),dFdy(WorldPos.x));
    vec2 dvy=vec2(dFdx(WorldPos.z),dFdy(WorldPos.z));

    float lx=length(dvx);
    float ly=length(dvy);

    vec2 dudv=vec2(lx,ly);

    float l =length(dudv);
    float LOD=max(0.0,log10(l*GridMinPixelBetween/GridCellSize)+1.0);

    float GridCellSizelod0 = GridCellSize*pow(10,floor(LOD));
    float GridCellSizelod1 = GridCellSizelod0 * 10.0;
    float GridCellSizelod2 = GridCellSizelod1 * 10.0;

    dudv*=4.0;

    vec2 mod_div_dudv = mod(WorldPos.xz,GridCellSizelod0)/dudv;
    float lod0a=max2(vec2(1.0)-abs(satv(mod_div_dudv) * 2.0 - vec2(1.0)));

    mod_div_dudv = mod(WorldPos.xz,GridCellSizelod1)/dudv;
    float lod1a=max2(vec2(1.0)-abs(satv(mod_div_dudv) * 2.0 - vec2(1.0)));

    mod_div_dudv = mod(WorldPos.xz,GridCellSizelod2)/dudv;
    float lod2a=max2(vec2(1.0)-abs(satv(mod_div_dudv) * 2.0 - vec2(1.0)));
    //float lod0a=max(1.0-mod(WorldPos.x,GridCellSizelod0)/ dudv.x,1.0-mod(WorldPos.z,GridCellSizelod0)/ dudv.y) ;
    //float lod1a=max(1.0-mod(WorldPos.x,GridCellSizelod1)/ dudv.x,1.0-mod(WorldPos.z,GridCellSizelod1)/ dudv.y) ;
    //float lod2a=max(1.0-mod(WorldPos.x,GridCellSizelod2)/ dudv.x,1.0-mod(WorldPos.z,GridCellSizelod2)/ dudv.y) ;

    float LOD_fade=fract(LOD);

    vec4 color;

    if (lod2a >0.0){
        color=GridColorThick;
        color.a*=lod2a;
    } else {
        if (lod1a>0.0) {
            color= mix(GridColorThick,GridColorThin,LOD_fade);
            color.a*=lod1a;
      } else {
            color=GridColorThin;
            color.a*=(lod0a* (1.0-LOD_fade));
        }
    }
    vec3 POS=WorldPos;
    if(abs(POS.x)<=0.03){color.x=1.0;color.y=0.0;color.z=0.0;}
    if(abs(POS.z)<=0.03){color.x=0.0;color.y=1.0;color.z=0.0;}

    float opacity_Fall_OFF=(1.0 -satf(length(WorldPos.xz)/gGridSize));
    color.a *= opacity_Fall_OFF;
    
    FragColor = color;
}