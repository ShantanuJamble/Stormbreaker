#version 460 core

layout(location=0) in vec3 position;

out vec4 vCol;

uniform mat4 u_Model;
uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
	gl_Position =  u_Projection * u_View * u_Model * vec4(position,1.0f);
	vCol = vec4(clamp(position , 0.0f,1.0f),1.0f);
};