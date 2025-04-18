#pragma once

#include <glad/glad.h>
#include <memory>
#include "component.h"
#include "shader.h"
#include "model.h"

class EventDispatcher;

class Renderer;

class Shader_Manager : public Component <Renderer> {

private:
	inline static std::unique_ptr<Shader_Manager> instance = nullptr;
	Shader_Manager();
	~Shader_Manager() {};
public :

	 static Shader_Manager* getInstance() {
		 if (!instance) {
			 instance = std::make_unique<Shader_Manager>();
		}
		return instance.get();
	}


	 void Init(EventDispatcher* eventSys) {

		 this->eventSys = eventSys;
		 //@build and compile shaders
		 // -------------------------
		 Shader LoadingShader("shaders/model_loading.vert", "shaders/model_loading.frag");
		 Shader GridShader("shaders/EndlessGrid.vert", "shaders/EndlessGrid.frag");
		 Shader SkyboxShader("shaders/Skybox.vert", "shaders/Skybox.frag");
		 Shaders[ShaderID::LoadingModel] = LoadingShader;
		 Shaders[ShaderID::Grid] = GridShader;
		 Shaders[ShaderID::SkyBox] = SkyboxShader;


		 //@load models
		 // -----------
		 Model Backpack("models/backpack/backpack.obj");


		 glGenVertexArrays(1, &GridVAO);

		 glGenVertexArrays(1, &SkyboxVAO);

	 }

	 void Update(float deltaTime,glm::mat4 ViewMatrix,glm::mat4 ProjectionMatrix,glm::vec3 cameraPosition) {

		 this->deltaTime = deltaTime;
		 this->ViewMatrix = ViewMatrix;
		 this->ProjectionMatrix = ProjectionMatrix;
		 this->CamPosition = cameraPosition;

	 }

	 void Draw() {
		 // @render
		 // ------
		 //!clearing screan
		 glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
		 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		 for (Model * m: Models)
		 {
			 Draw_Model(Shaders[ShaderID::LoadingModel], m);
		 }

		 int skybox_texture = 1;
		 Draw_Skybox(Shaders[ShaderID::SkyBox], SkyboxVAO, skybox_texture);

		 Draw_Grid(Shaders[ShaderID::Grid],GridVAO);


	 };

	 void Shutdown() {};


private: 

	enum class ShaderID {

		LoadingModel,
		SkyBox,
		Grid

	};
	
	std::unordered_map<ShaderID, Shader> Shaders;
	EventDispatcher * eventSys;
	std::vector<Model*> Models;

	unsigned int GridVAO;
	unsigned int SkyboxVAO;
	
	float deltaTime;
	glm::mat4 ViewMatrix = glm::mat4(0.0f);
	glm::mat4 ProjectionMatrix = glm::mat4(0.0f);
	glm::vec3 CamPosition = glm::vec3(0.0f);

private:

	void Draw_Skybox(Shader SkyboxShader,unsigned int SkyboxVAO, unsigned int skybox_texture) {

		//!drawing the skybox

		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_FALSE);

		glBindVertexArray(SkyboxVAO);

		SkyboxShader.use();
		SkyboxShader.setMat4("projection", ProjectionMatrix);
		SkyboxShader.setMat4("view", glm::mat4(glm::mat3(ViewMatrix)));
		SkyboxShader.setInt("skybox", 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_texture);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
	}

	void Draw_Grid(Shader GridShader,unsigned int GridVAO) {

		
		glBindVertexArray(GridVAO);

		GridShader.use();
		GridShader.setVec3("CameraWorldPos", CamPosition);
		GridShader.setMat4("projection", ProjectionMatrix);
		GridShader.setMat4("view", ViewMatrix);
		//GridShader.setInt("stretchmult", stretchmult);
		glDrawArrays(GL_TRIANGLES, 0, 12);
		glBindVertexArray(0);
	}

	void Draw_Model(Shader LoadingShader,Model * model) {
		//!model matrix
		glm::mat4 modelMatrix = glm::mat4(1.0f);

		//!Model Drawing
		LoadingShader.use();

		modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f));	// it's a bit too big for our scene, so scale it down

		LoadingShader.setMat4("projection", ProjectionMatrix);
		LoadingShader.setMat4("view", ViewMatrix);
		//LoadingShader.setVec3("lightDir", lightDirection);
		LoadingShader.setVec3("ViewPos", CamPosition);
		LoadingShader.setMat4("model", modelMatrix);

		model->Draw(LoadingShader);
	}

};