#version 460 core

layout(location=0) in vec3 position;

out vec4 vCol;


void main()
{
	gl_Position  = position;
};