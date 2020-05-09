#version 400
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 VertexTexCoord;
layout (location = 2) in vec3 VertexNormal;

uniform mat4 transform;
uniform mat4 model;

out vec3 Position;
out vec3 Normal;

void main()
{
	Position = vec3(model * vec4(VertexPosition, 1.0));
	Normal = VertexNormal;
	gl_Position = transform * vec4(VertexPosition, 1.0); //MVP * Models tranform
}