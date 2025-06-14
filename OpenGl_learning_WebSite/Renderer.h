#pragma once
#include "component.h"
#include "Window.h"
#include "UI.h"
#include "Shader_Manager.h"
#include "Cam.h"

class Engine;
class EventDispatcher;

class Renderer : public Component<Engine>
{
private:

	inline static std::unique_ptr<Renderer> instance = nullptr;
	Renderer() {};
	friend std::unique_ptr<Renderer> std::make_unique<Renderer>();

public:
	~Renderer() {};

	static Renderer* getInstance() {
		if (!instance) {
			instance = std::make_unique<Renderer>();
		}
		return instance.get();
	}

	//void Init(std::unordered_map<std::string, Component<Engine>*> Engine_entities) {
	void Init(EventDispatcher * EvenSys) {
		//this->Engine_Entities = Engine_entities;
		this->EvenSys = EvenSys;
		Renderer_Entities[EntitiesID::Window]         = Window::getInstance();										
		Renderer_Entities[EntitiesID::UI]             = UI::getInstance();
		Renderer_Entities[EntitiesID::Shader_Manager] = Shader_Manager::getInstance();
		Renderer_Entities[EntitiesID::Camera]         = Camera::getInstance();

		getWindow()->Init(EvenSys);
		getUI()->Init(EvenSys, getWindow()->getGLFWWindow());
		getCamera()->Init(EvenSys);
		getShader_M()->Init(EvenSys);

	}
	

	void Shutdown() {
		getWindow()   ->Shutdown();
		getUI()       ->Shutdown();
		getShader_M() ->Shutdown();
	
	};

	bool Closed(){
		return getWindow()->Closed();//=== glfw->shouldclose(window)
	}

	void Input() {
		getWindow()->Input();
	}

	void Update(float deltaTime) {
		getCamera()->Update(deltaTime);
		getShader_M()->Update(deltaTime,getCamera()->GetViewMatrix(), getCamera()->GetProjectionMatrix(),getCamera()->GetPosition());
	}

	void Draw() {
		getShader_M()->Draw();
		getUI()->Draw();

	}

	void Plot() {
		getWindow()->Plot();
	}

	 


private:

	enum class EntitiesID {
		Window,
		UI,
		Shader_Manager,
		Camera
	};

	std::unordered_map<EntitiesID, Component<Renderer>*> Renderer_Entities;
	EventDispatcher * EvenSys;

	Window* getWindow() {
		return static_cast<Window*>(Renderer_Entities[EntitiesID::Window]);
	}

	UI* getUI() {
		return static_cast<UI*>(Renderer_Entities[EntitiesID::UI]);
	}
	Shader_Manager* getShader_M(){
		return static_cast<Shader_Manager*>(Renderer_Entities[EntitiesID::Shader_Manager]);
	}

	Camera * getCamera() {
		return static_cast<Camera*>(Renderer_Entities[EntitiesID::Camera]);
	}

	std::unordered_map<std::string, Component<Engine>*> Engine_Entities;
	

};

