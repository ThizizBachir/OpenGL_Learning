#version 460 core

out vec3 TexCoords;

//uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

const vec3 POS[8]=vec3[8](
	//   Coordinates
	vec3(-1.0f, -1.0f,  1.0f),//        7--------6
	vec3( 1.0f, -1.0f,  1.0f),//       /|       /|
	vec3( 1.0f, -1.0f, -1.0f),//      4--------5 |
	vec3(-1.0f, -1.0f, -1.0f),//      | |      | |
	vec3(-1.0f,  1.0f,  1.0f),//      | 3------|-2
	vec3( 1.0f,  1.0f,  1.0f),//      |/       |/
	vec3( 1.0f,  1.0f, -1.0f),//      0--------1
	vec3(-1.0f,  1.0f, -1.0f)
);

const int indices[36]=int[36](
    // Right
	1, 2, 6,
	6, 5, 1,
	// Left
	0, 4, 7,
	7, 3, 0,
	// Top
	4, 5, 6,
	6, 7, 4,
	// Bottom
	0, 3, 2,
	2, 1, 0,
	// Back
	0, 1, 5,
	5, 4, 0,
	// Front
	3, 7, 6,
	6, 2, 3
);

void main(){

	int index= indices[gl_VertexID];
	vec3 cube_pos=POS[index];
	vec4 pos= projection * view * vec4(cube_pos,1.0);

	gl_Position=pos.xyww;
	TexCoords=cube_pos;

}

