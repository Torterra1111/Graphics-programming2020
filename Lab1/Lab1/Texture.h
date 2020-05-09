#pragma once
#include <string>
#include <GL\glew.h>
#include <cassert>
#include <iostream>
#include <vector>

class Texture
{
public:
	Texture();
	
	void Create(const std::string& fileName); //Creating the texure
	void Bind(unsigned int unit); // bind upto 32 textures

	~Texture(); //deconstructor
	GLuint loadCubemap(std::vector<std::string> faces);
	GLint getTexHandler() { return textureHolder; }

protected:
private:


	GLuint textureHolder; //Storage of texture
};
