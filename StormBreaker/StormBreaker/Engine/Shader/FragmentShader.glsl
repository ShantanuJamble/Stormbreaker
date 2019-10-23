#version 460 core

layout(location=0) out vec4 color;

struct Light
{
	vec3  direction;		//12
	int   type;				//16
	vec3  position;			//28
	float ambientintensity; //32
	vec3  color;			//44
	int padding;			//48
};

layout (std140, binding = 0) uniform Lights
{
	Light light;
};


in vec4 vCol;
in vec2 v_texcoord;

uniform sampler2D u_Texture;



vec4 Diffuse()
{
	return vec4(light.color,1.0)*light.ambientintensity;
}


void main()
{
	color = texture(u_Texture, v_texcoord)* vec4(light.color,1.0);
};