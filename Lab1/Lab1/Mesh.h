#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"


class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2&texCoord) //Getting positions for movement, making it a Vec3
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}
	glm::vec3* Getpos() { return &pos;} //getter for the pos
	glm::vec2* GettexCoord() { return &texCoord;} //Getter for the texure co-ordinate
	glm::vec3* Getnormal() { return &normal;} //Getter for the normal
private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;

};

struct CloudSphere //This is the Spherical hitbox that can be called for any object
{
public:
	CloudSphere() {} //defult constructor

	//Getters
	float GetRadius() const { return radius; } 
	glm::vec3 GetPos() const { return Position; }

	//Setters
	void SetRadius(float changeto) { this->radius = changeto; }
	void SetPos(glm::vec3 changeto) { this->Position = changeto; }

private:
	glm::vec3 Position;
	float radius;

};

class Mesh //Loading models and being able to move them
{
public:
	Mesh(); //Constructor
	~Mesh(); //Destructor
	void Draw(); //Draw models
	void Create(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices); //Get the varibles needed to store the model
	void LoadModel(const std::string& filename); //Loading the model from file and creating it
	void MakeModel(const IndexedModel& model); //Creating the model to be loaded
	void UpdatePos(glm::vec3 pos,float rad); //Updtaing the position
	
	float ReturnRad() { return MeshCloudsphere.GetRadius(); } //Getter for pos
	glm::vec3 ReturnPos() { return MeshCloudsphere.GetPos(); } //Getter for pos
	
private:

	enum
	{
		POSITION_VERTEXBUFFS,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		
		NUM_BUFFS
	};

	IndexedModel model; //Storing the model
	CloudSphere MeshCloudsphere; //storaging the hitbox
	GLuint vertexArrayObject; //Array
	GLuint vertexArrayBuff[NUM_BUFFS]; // create our array of buffers
	unsigned int drawNum; //how much of the vertexArrayObject do we want to draw
	

};




