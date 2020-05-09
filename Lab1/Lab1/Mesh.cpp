#include "Mesh.h"

Mesh::Mesh()
{
	drawNum = NULL;
}

void Mesh::Create(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)//init
{
	for (unsigned int i = 0; i < numVertices; i++) //For each vertice
	{
		model.positions.push_back(*vertices[i].Getpos()); //Put the data to the back for Position
		model.texCoords.push_back(*vertices[i].GettexCoord()); //Put the data to the back for Texture co-ordinates
		model.normals.push_back(*vertices[i].Getnormal()); //Put the data to the back for normal
	}
	for (unsigned int i = 0; i < numIndices; i++)
	{
		model.indices.push_back(indices[i]); //Put the data to the back for the indices
	}

	MakeModel(model); //Create model
	
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject); //bye bye arrays
}


void Mesh::MakeModel(const IndexedModel& model)
{
	drawNum = model.indices.size(); //For each draw numnber, make more room


	glGenVertexArrays(1, &vertexArrayObject); //generate a vertex array and store it in the VAO
	glBindVertexArray(vertexArrayObject); //bind the VAO (any operation that works on a VAO will work on our bound VAO - binding)

	glGenBuffers(NUM_BUFFS, vertexArrayBuff); //generate our buffers based of our array of data/buffers - GLuint vertexArrayBuffers[NUM_BUFFERS];

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuff[POSITION_VERTEXBUFFS]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU (determined by type)
	glEnableVertexAttribArray(0); //Using the array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0,0); //Telling the CPU how to use passing index to use,Size of array,Type of array,tpe of data, To compress value
	//6* sizeof( GLfloat), ( GLvoid *) (3* sizeof( GLfloat))
	//strides
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuff[TEXCOORD_VB]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0,0);//Telling the CPU how to use passing index to use,Size of array,Type of array,tpe of data, To compress value

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuff[NORMAL_VB]); //tell opengl what type of data the buffer is (GL_ARRAY-BUFFER) and pass the datat
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0,0); //Telling the CPU how to use passing index to use,Size of array,Type of array,tpe of data, To compress value

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuff[INDEX_VB]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU

	glBindVertexArray(0); // unbind our Vertex array object

}
void Mesh::LoadModel(const std::string& filename)
{
	model = OBJModel(filename).ToIndexedModel(); //Take the file name
	MakeModel(model);
	CloudSphere MeshCloudsphere();
	
}

void Mesh::Draw()
{
	glBindVertexArray(vertexArrayObject); //Bind the object
	glDrawElements(GL_TRIANGLES, drawNum, GL_UNSIGNED_INT, 0); //Draw the thing
	glBindVertexArray(0); //unbind it

}

void Mesh::UpdatePos(glm::vec3 pos, float rad)  //Updating the position of the hitbox around the objects
{
	MeshCloudsphere.SetPos(pos); //Position
	MeshCloudsphere.SetRadius(rad);//Radius of the sphere
}


