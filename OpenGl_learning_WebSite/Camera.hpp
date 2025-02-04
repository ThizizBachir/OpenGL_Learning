#pragma once        
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>  


class camera {
public:
	float mov_speed, fov;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	float pitch, yaw, roll;
	float zoom;
public:
	glm::mat4 view, projection;
	float scroll_speed;
	camera()
		:mov_speed(0.5f), fov(45.0f), scroll_speed(1.0f),
		cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)), cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)), cameraFront(glm::vec3(0.0f, 0.0f, 0.0f)),
		pitch(0.0f), yaw(-90), roll(0.0f),
		view(glm::mat4(1.0f)),projection(glm::mat4(1.0f))
		{
		
	}
public:
	void Update_direction(const float xoffset,const float yoffset);
	void Update_Zoom(double yoffset);
	void Update_Position(const int key);
	void make_view_projection();
};				   
