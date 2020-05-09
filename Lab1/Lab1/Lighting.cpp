#include "Lighting.h"
Lighting::Lighting()
{
}


Lighting::~Lighting()
{
}

void Lighting::MakeLighting()
{
	glGenVertexArrays(1, &LightVAO);
	glBindVertexArray(LightVAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}