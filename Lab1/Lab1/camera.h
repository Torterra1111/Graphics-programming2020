#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>



struct  Camera
{
	Camera()
	{
	}
	void makeCamera(const glm::vec3& pos, float fov, float aspect, float nrClip, float frClip) //Creating the VP
	{
		this->pos = pos; //Create position
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f); //create Forward position
		this->up = glm::vec3(0.0f, 1.0f, 0.0f); //create where "up" is in relation to the camera
		this->projection = glm::perspective(fov, aspect, nrClip, frClip); //Create viewing frustrum
	}
	inline glm::mat4 GetViewProjection() const //Creating the MVP
	{
		return projection * glm::lookAt(pos, pos + forward, up); //Create MVP
	}
	glm::vec3 getPos()
	{
		return this->pos;
	}

	inline glm::mat4 GetProjection() const
	{
		return projection;
	}

	inline glm::mat4 GetView() const
	{
		return glm::lookAt(pos, pos + forward, up);
	}
	inline glm::vec3 GetForward() const
	{
		return forward;
	}


private:
	//Varibles
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;


};