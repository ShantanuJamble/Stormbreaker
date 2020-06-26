#ifndef LIGHT_H
#define LIGHT_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


// Light types
// Must match definitions in shader
#define LIGHT_TYPE_DIRECTIONAL  0
#define LIGHT_TYPE_POINT		1
#define LIGHT_TYPE_SPOT			2


struct Light
{
	glm::vec3	Direction;				//12
	int			Type;					//4
	glm::vec3	Position;				//12
	float		AmbientIntensity;		//4
	glm::vec3   Color;					//12
	float		padding;		        //4
	
};

#endif