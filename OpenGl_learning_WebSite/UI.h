#pragma once
#include <memory>
#include "EventSys.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GUI.hpp"
#include "component.h"

class Renderer;
//class EventDispatcher;

class UI : public Component<Renderer>  {//renderer component

private:
	inline static std::unique_ptr<UI> instance = nullptr;
    UI() {};
    friend std::unique_ptr<UI> std::make_unique<UI>();

public:
	~UI(){};

	static UI* getInstance(){
		if (!instance) {
			instance = std::make_unique<UI>();
		}

		return instance.get();
	}

	void Init(EventDispatcher * eventSys,GLFWwindow * glfwwindow) {

        this->eventSys = eventSys;
		ImGuiIO& io = Imgui_Initialize(glfwwindow);//lezemmne5o access el window
		SetImGuiStyle();

	}

	void Draw() {


        StartFrame();

        ////IMGUI window creation
        //ImVec2 topLeftCorner(0.0f, 0.0f); // Position at (0, 0)
        //ImGui::SetNextWindowPos(topLeftCorner, ImGuiCond_Always);
        //ImGui::SetNextWindowSize(ImVec2(200, 400));
        //ImGui::Begin("GRID TEST", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

        //ImGui::Text("frame periode: %f ms", ms);
        //ms++;
        //ImGui::Text("Frame Rate: %f fps", 1000 / ms);
        //ImGui::Text("camera.x: %f ", camera.Position.x);
        //ImGui::Text("camera.y: %f ", camera.Position.y);
        //ImGui::Text("camera.z: %f ", camera.Position.z);
        //ImGui::SliderFloat("Light X", &lightDirection.x, -1.0f, 1.0f);
        //ImGui::SliderFloat("Light Y", &lightDirection.y, -1.0f, 1.0f);
        //ImGui::SliderFloat("Light Z", &lightDirection.z, -1.0f, 1.0f);

        CompleteFrame();



	}

    void ShutDown() {
        Imgui_Close();
    }

private:


    void StartFrame() {
        //!drawing IMGUI
        //DrawImgui(var);
        // Tell OpenGL a new frame is about to begin
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

    }

    void CompleteFrame() {

        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        EventDispatcher::getInstance()->Dispatch(std::make_shared< Event_UI_Complete_Frame>());

    }

    EventDispatcher * eventSys;

    std::unordered_map <std::string, Component<Renderer>*> Renderer_Entities;
};