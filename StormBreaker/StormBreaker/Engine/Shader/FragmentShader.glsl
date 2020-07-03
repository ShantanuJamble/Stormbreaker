#version 460 core

layout(location=0) out vec4 color;

in V_OUT {
	vec3 pos;
	vec4 vCol;
	vec2 v_texcoord;
	vec3 normal;
	vec3 tangent;
	vec3 bitangent;
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

	// ambient
	vec3 ambient = light.ambientintensity * light.color * objectColor;

	// diffuse 
	vec3 norm = normalize(fsIn.normal);
	// vec3 lightDir = normalize(light.position - FragPos);
	//vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.color * diff * objectColor;

	// specular
	vec3 viewDir = normalize(viewPos - fsIn.pos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 21);
	vec3 specular = light.color * spec * objectColor;

	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0);

	//// Create the matrix that will allow us to go from tangent space to world space
	//vec3 N = normalize(fsIn.normal);
	//vec3 tmpTan = normalize(fsIn.tangent);
	//vec3 T = normalize(tmpTan - N * dot(tmpTan, N));
	//vec3 B = cross(T, N);
	//mat3 TBN = mat3(T, B, N);

	//// Overwrite the initial normal with the version from the
	//// normal map, after we've converted to world space
	//vec3 newNormal = normalize( normalFromMap* TBN);


	////Ambient lighting
 //   vec3 ambientLight = light.ambientintensity * light.color;
	//vec3 ambient = ambientLight * objectColor;

	//	// DIRECTIONAL LIGHT ////////////////////////////

	//// N dot L (Lambert / Diffuse) lighting
	//// Note: We need the direction TO the light
	//
	//float dirNdotL = dot(newNormal, lightDir);
	//dirNdotL = clamp(dirNdotL,0.0,1.0); // Remember to CLAMP between 0 and 1

	//// Specular calc for reflections (Phong)

	//vec3 dirRefl = reflect(-lightDir, newNormal);
	//vec3 viewDir = normalize(viewPos - fsIn.pos);
	//
	//vec3 halfwayDir = normalize(lightDir + viewDir);
	//float dirSpec = pow(max(dot(dirRefl, halfwayDir),0.0), 32.0);
	////dirSpec = 0.3 * dirSpec; // assuming bright white light color
	//
	//
	//
	//
	//// Combine the surface and lighting
	//vec3 finalDirLight = objectColor * (light.color * dirNdotL)
	//	+ objectColor *dirSpec.rrr;
	////finalDirLight = clamp(finalDirLight,0.0,1.0);
	//
	//
	////Final Color
	//color = vec4(finalDirLight + ambient, 1.0);
	//
	////color = vec4(lightDir,1.0);



	
};

