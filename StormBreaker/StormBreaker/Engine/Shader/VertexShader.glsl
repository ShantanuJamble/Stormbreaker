#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout(location = 1) in vec3 normal;

//out vec4 vCol;
//out vec2 v_texcoord;
uniform mat4 u_Model;
uniform mat4 u_Projection;
uniform mat4 u_View;


out V_OUT {
	vec3 pos;
	vec4 vCol;
	vec2 v_texcoord;
	vec3 normal;
} vsOut;


void main()
{
	gl_Position =  u_Projection * u_View * u_Model * vec4(position,1.0f);
	vsOut.pos = vec3(u_Model * vec4(position, 1.0));
	vsOut.vCol = vec4(clamp(position , 0.0f,1.0f),1.0f);
	vsOut.v_texcoord = texcoord;
	vsOut.normal = normal;
};