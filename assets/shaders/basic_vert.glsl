#version 450

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextureCoord;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;
uniform vec4 u_Color;
uniform vec3 u_Light_Pos;
uniform vec3 u_Camera_Pos;

out vec3 vert_color;
out vec2 texCoords;

out vec3 light_pos;
out vec3 camera_pos;
out vec3 world_pos;
out vec3 vert_normal;
void main()
{
	mat4 MVP = u_Projection * u_View * u_Model;

	gl_Position = MVP* vec4(a_Position,1.0);
	vert_color = u_Color.xyz * a_Position;
	texCoords = a_TextureCoord;

	vert_normal =  normalize(mat3(u_Model)*vec3(0,1,0));
    world_pos = vec4(u_Model *vec4(a_Position,1.0)).xyz;
    light_pos = world_pos+vec3(0,3,0);
	camera_pos = u_Camera_Pos;
};