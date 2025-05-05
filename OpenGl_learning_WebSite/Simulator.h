#pragma once
#include "Component.h"
#include <memory>
#include "glm\glm.hpp"
#include "EventSys.h"

class Particle {
public :
	glm::vec3 Postion;
	glm::vec3 OldPosition;
	glm::vec3 Acceleration;
	bool fixed;
};

struct Constraint {
	Particle* p1;
	Particle* p2;
	float restDistance; 
};


class Engine;
class Simulator :public Component<Engine> {
private :
	inline static std::unique_ptr<Simulator> instance = nullptr;
	Simulator() {};

	friend std::unique_ptr<Simulator> std::make_unique<Simulator>();

public:
	~Simulator() {};
	static Simulator* getInstance() {
		if (!instance) {
			instance = std::make_unique<Simulator>();
		}
		return instance.get();
	}
	void Init(EventDispatcher * eventsys) {

	}

	void Update(float deltaTime) {

	}

private:
	EventDispatcher* EvenSys;

	
};
