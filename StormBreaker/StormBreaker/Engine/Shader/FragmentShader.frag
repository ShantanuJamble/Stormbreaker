#version 460 core

layout(location=0) out vec4 color;

in vec4 vCol;
in vec2 v_texcoord;

uniform sampler2D u_Texture;

void main()
{
	//color = vCol;
	color = texture(u_Texture, v_texcoord);
};