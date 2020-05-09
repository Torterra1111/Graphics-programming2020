#include "Shader.h"

Shader::Shader()
{
}
//"..\\res\\shader.frag"
//"..\\res\\shader.vert"

void Shader::Create(const std::string& vertFile, const std::string& fragFile, bool shad2)
{
	program = glCreateProgram(); //Setting program to an empty object to attach shaders to
	shaders[0] = makeShader(LoadShader(vertFile), GL_VERTEX_SHADER); //Loading the Vertex shader
	shaders[1] = makeShader(LoadShader(fragFile), GL_FRAGMENT_SHADER); //Loading the Fragment shader
	if(shad2)
	{
		shaders[2] = makeShader(LoadShader("..\\res\\shaderGeoText.geom"), GL_GEOMETRY_SHADER); // create fragment shader
	}
	for (int i = 0; i < NUM_SHADS; i++)
	{
		glAttachShader(program, shaders[i]);
	}
	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "texCoord");
	glBindAttribLocation(program, 2, "Normal");
	
	glLinkProgram(program); //create executables that will run on the GPU shaders
	CheckShaderError(program, GL_LINK_STATUS, true, "Error: Shader program linking failed"); // cheack for error

	glValidateProgram(program); //check the entire program is valid
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform"); // associate with the location of uniform variable within a program
}



void Shader::Bind()
{
	glUseProgram(program);
}

Shader::~Shader()
{
	for (int i = 0; i < NUM_SHADS; i++)
	{
		glDetachShader(program, shaders[i]); //detach shader from program
		glDeleteShader(shaders[i]); //delete the shaders
	}
	glDeleteProgram(program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);
}



std::string Shader::LoadShader(const std::string& fileName) //Loading the shader from  file.
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) //Checking if the shader loaded corretly
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

GLuint Shader::makeShader(const std::string& text, unsigned int type) 
{
	GLuint shader = glCreateShader(type); //create shader based on specified type

	if (shader == 0) //if == 0 shader no created
		std::cerr << "Error type creation failed " << type << std::endl;

	const GLchar* stringSource[1]; //convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, stringSource, lengths); //send source code to opengl
	glCompileShader(shader); //get open gl to compile shader code

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

	return shader;
}