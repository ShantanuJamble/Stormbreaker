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


//in vec4 vCol;
//in vec2 v_texcoord;


in V_OUT {
	vec3 pos;
	vec4 vCol;
	vec2 v_texcoord;
} fsIn;

uniform sampler2D u_Texture;
uniform sampler2D u_NormalMap;


vec4 Diffuse()
{
	return vec4(light.color,1.0)*light.ambientintensity;
}


void main()
{

	vec3 objectColor = vec3(texture(u_Texture, fsIn.v_texcoord));

	//Ambient lighting
    vec3 ambientLight = light.ambientintensity * light.color;
	vec3 ambient = ambientLight * objectColor;

	//Diffuse lighting
	//vec3 norm = normalize(vec3(texture(u_NormalMap, fsIn.v_texcoord)));
	//vec3 lightDir = normalize(light.position - fsIn.vPos);  
	//float diff = max(dot(norm, light.direction), 0.0);
	//vec3 diffuse = diff * light.color;

	vec3 diffuse = vec3(1.0,1.0,1.0);
	
	vec3 result = (ambient + diffuse) * objectColor;


	//Final Color
	color = vec4(result, 1.0);
};