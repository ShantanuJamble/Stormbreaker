#version 460 core

layout(location=0) out vec4 color;

in V_OUT {
	vec3 pos;
	vec4 vCol;
	vec2 v_texcoord;
	vec3 normal;
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
	vec3 objectColor = vec3(texture(u_Texture, fsIn.v_texcoord));

	
	//Ambient lighting
    vec3 ambientLight = light.ambientintensity * light.color;
	vec3 ambient = ambientLight * objectColor;
	ambient = clamp(ambient,0.0,1.0);

		// DIRECTIONAL LIGHT ////////////////////////////

	// N dot L (Lambert / Diffuse) lighting
	// Note: We need the direction TO the light
	vec3 norm = normalize(vec3(texture(u_NormalMap, fsIn.v_texcoord)));
	float dirNdotL = dot(norm, -light.direction);
	dirNdotL = clamp(dirNdotL,0.0,1.0); // Remember to CLAMP between 0 and 1

	// Specular calc for reflections (Phong)

	vec3 dirRefl = reflect(light.direction, norm);
	vec3 viewDir = normalize(viewPos - fsIn.pos);
	
	vec3 halfwayDir = normalize(light.direction + viewDir);
	float dirSpec = pow(clamp(dot(dirRefl, halfwayDir),0.0,1.0), 32.0);
	dirSpec = 0.3 * dirSpec; // assuming bright white light color
	// Combine the surface and lighting
	vec3 finalDirLight = objectColor * (light.color * dirNdotL)
		+ objectColor *dirSpec.rrr;
	finalDirLight = clamp(finalDirLight,0.0,1.0);
		//Final Color
	color = vec4(finalDirLight + ambient, 1.0);
};

