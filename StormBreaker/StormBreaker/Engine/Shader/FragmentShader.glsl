#version 460 core

layout(location=0) out vec4 color;

in V_OUT {
	vec3 pos;
	vec4 vCol;
	vec2 v_texcoord;
	vec3 normal;
	vec3 tangent;
	vec3 bitangent;
	mat3 TBN;
} fsIn;

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
	Light lights [];
};

//Camera position
uniform vec3 viewPos;

uniform sampler2D u_Texture;
uniform sampler2D u_NormalMap;


/*vec4 Diffuse()
{
	return vec4(light.color,1.0)*light.ambientintensity;
}*/


void main()
{
	Light light = lights[0];
	vec3 objectColor = texture(u_Texture, fsIn.v_texcoord).rgb;
	vec3 normalFromMap = normalize(vec3(texture(u_NormalMap, fsIn.v_texcoord)));
	vec3 lightDir = normalize(-light.direction);
	
	//Light position, camera position in tangent space
	
	vec3 lightPosInTangentSpace = fsIn.TBN * light.position;
	vec3 camPosInTangentSpace   = fsIn.TBN * viewPos;
	vec3 pixelPosInTangentSpace = fsIn.TBN * fsIn.pos;
	vec3 normalInTangentSpace    = fsIn.TBN * normalFromMap;

	lightDir = normalize(lightPosInTangentSpace - pixelPosInTangentSpace);

	// ambient
	vec3 ambient = light.ambientintensity * light.color * objectColor;

	// diffuse 
	vec3 norm = normalize(fsIn.normal);
	norm = normalInTangentSpace;
	// vec3 lightDir = normalize(light.position - FragPos);
	//vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.color * diff * objectColor;

	// specular
	vec3 viewDir = normalize(camPosInTangentSpace - pixelPosInTangentSpace);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 21);
	vec3 specular = light.color * spec * objectColor;

	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0);
};



































