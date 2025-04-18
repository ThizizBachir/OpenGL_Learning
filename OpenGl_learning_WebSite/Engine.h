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

	Engine();// singleton constructor

	~Engine() {};


public:

	static Engine* getInstance() {
		if (!instance) {
			instance = std::make_unique<Engine>();
		}
		return instance.get();
	}



	void Init()
	{
		auto start = std::chrono::steady_clock::now();

		//Engine_Entities["Simulator"] = Simulator.getInstance();
		Engine_Entities[EngineEntitiesID::Renderer] = Renderer::getInstance();
		Engine_Entities[EngineEntitiesID::EventSys] = EventDispatcher::getInstance();
		//Simulator.Init();			 
		getEventsys()->Init();
		getRenderer()->Init(getEventsys());

		auto end = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
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
		

	}
	
	bool Closed(){

		return getRenderer()->Closed();
	};

private:
	float deltaTime = 0.0f;

	enum class EngineEntitiesID {
		Renderer,
		EventSys,
		simulator
	};

	
	 std::unordered_map<EngineEntitiesID ,Component<Engine>*> Engine_Entities;

	Renderer * getRenderer(){

		return static_cast<Renderer*>(Engine_Entities[EngineEntitiesID::Renderer]);
		
	}

	EventDispatcher * getEventsys() {
		return static_cast<EventDispatcher*>(Engine_Entities[EngineEntitiesID::EventSys]);
	}

	/*Simulator& getEventsys() {
		return *static_cast<Simulator*>(Engine_Entities["Simulator"]);
	}*/

private:

	void Input() {	   
		getRenderer()->Input();
		/*eventSys.pollEvents();*/    //!9alli 3liha chta ama ena 3amelha dynamic m3a el Input 
		
	};

	void Update(float deltaTime) {
		//getSimulator().Update(deltaTime);
		getRenderer()->Update(deltaTime);
	};

	void Render() {
		getRenderer()->Draw();
	};

	void Plot() {
		getRenderer()->Plot();
	}


};
