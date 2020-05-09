#version 330 core

layout (location = 0) in vec3 VertexPosition;
layout (location = 2) in vec3 VertexNormal;

out vec3 Normal;
out vec3 Position;
uniform mat4 transform;

uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;

void main()
{
    Normal = mat3(transpose(inverse(model))) * VertexNormal;
    Position = vec3(model * vec4(VertexPosition, 1.0));
    gl_Position = transform * vec4(VertexPosition, 1.0);
}  