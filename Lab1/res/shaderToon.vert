#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 VertexTexCoord;
layout (location = 2) in vec3 VertexNormal;

varying vec3 normal;

uniform mat4 transform;

//textures in an arraw going out
out VS_OUT {
    vec2 texCoords;
} vs_out;

void main()
{
	normal = VertexNormal;
	gl_Position = transform * vec4(VertexPosition, 1.0);

    vs_out.texCoords = VertexTexCoord;
}