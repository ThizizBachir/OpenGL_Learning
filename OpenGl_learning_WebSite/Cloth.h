#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include <glm\glm.hpp>


class particle {
private:
	glm::vec3 postion;
	glm::vec3 prevposition;
	float masss;
	bool isPenned = false;
	bool isSelected = false;

 

};

class Spring {

private :

	float k;
	particle *p1, *p2;
	float origin_length;



};

class Cloth {
private:
	std::vector<particle> particles;

};