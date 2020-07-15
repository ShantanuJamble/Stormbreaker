#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

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
	vec3 tangent;
	vec3 bitangent;
	mat3 TBN;
} vsOut;


void main()
{
	gl_Position =  u_Projection * u_View * u_Model * vec4(position,1.0f);
	vsOut.pos = vec3(u_Model * vec4(position, 1.0));
	vsOut.vCol = vec4(clamp(position , 0.0f,1.0f),1.0f);
	vsOut.v_texcoord = texcoord;

	vec4 tmp = vec4(normal, 1.0f) * u_Model;
	vsOut.normal = mat3(transpose(inverse(u_Model))) * normal;// normalize(vec3(tmp));
	
	
	vec4 tmpTangent =  vec4(tangent,1.0f) * u_Model;//vec3(tangent * vec4(position, 1.0));
	vsOut.tangent = mat3(transpose(inverse(u_Model))) * tangent;


	mat3 normalMatrix = transpose(inverse(mat3(u_Model)));
	vec3 T = normalize(normalMatrix * tangent);
	vec3 N = normalize(normalMatrix * normal);
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N, T);

	mat3 TBN = transpose(mat3(T, B, N));
	vsOut.TBN = TBN;
};