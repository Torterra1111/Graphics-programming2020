#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
class Lighting
{
public:
	Lighting();
	~Lighting();

	void MakeLighting();

	unsigned int LightVAO;
};

