#pragma once
#include <chrono>
#include "Component.h"
#include "Renderer.h"
#include "Simulator.h"
#include "EventSys.h"

class Engine
{

private:
	inline static std::unique_ptr<Engine> instance=nullptr;
	Engine() {};// singleton constructor
	friend std::unique_ptr<Engine> std::make_unique<Engine>();
public:
	~Engine() {};

	static Engine* getInstance() {
		if (!instance) {
			instance = std::make_unique<Engine>();
		}
		return instance.get();
	}



	void Init()
	{
		//auto start = std::chrono::steady_clock::now();
		auto start = std::chrono::high_resolution_clock::now();
		this->deltaTime = 0;
		Engine_Entities[EntitiesID::simulator] = Simulator::getInstance();
		Engine_Entities[EntitiesID::Renderer] = Renderer::getInstance();
		Engine_Entities[EntitiesID::EventSys] = EventDispatcher::getInstance();
		getEventsys()->Init();
		getSimulator()->Init(getEventsys());			 
		getRenderer()->Init(getEventsys());

		//auto end = std::chrono::steady_clock::now();
		auto end = std::chrono::high_resolution_clock::now();
		//auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << "Time taken for Initialisation: " << duration.count() << " milliseconds" << std::endl;

	}

	void loop()
	{
		auto start = std::chrono::steady_clock::now();
		float glfwStart = (float)glfwGetTime();

		Input();
		Update(deltaTime);
		Render();
		Plot();

		auto end = std::chrono::steady_clock::now();
		float glfwEnd = (float)glfwGetTime();

		//deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		deltaTime = glfwEnd - glfwStart;
		
		
	}

	void Shutdown() {

		getRenderer()->Shutdown();
		getEventsys()->Shutdown();
		getSimulator()->Shutdown();
		

	}
	
	bool Closed(){

		return getRenderer()->Closed();
	};

private:
	float deltaTime = 0.0f;

	enum class EntitiesID {
		Renderer,
		EventSys,
		simulator
	};

	
	 std::unordered_map<EntitiesID ,Component<Engine>*> Engine_Entities;

	Renderer * getRenderer(){

		return static_cast<Renderer*>(Engine_Entities[EntitiesID::Renderer]);
		
	}

	EventDispatcher * getEventsys() {
		return static_cast<EventDispatcher*>(Engine_Entities[EntitiesID::EventSys]);
	}

	Simulator * getSimulator() {
		return static_cast<Simulator*>(Engine_Entities[EntitiesID::simulator]);
	}

private:

	void Input() {	   
		getRenderer()->Input();
		/*eventSys.pollEvents();*/    //!9alli 3liha chta ama ena 3amelha dynamic m3a el Input 
		
	};

	void Update(float deltaTime) {
		getSimulator()->Update(deltaTime);
		getRenderer()->Update(deltaTime);
	};

	void Render() {
		getRenderer()->Draw();
	};

	void Plot() {
		getRenderer()->Plot();
	}


};
