#pragma once
#include <iostream>          
#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>  
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>
#include <vector>

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    Material(glm::vec3 _ambient ,glm::vec3 _diffuse ,glm::vec3 _specular)
    {
        ambient = _ambient;
        diffuse = _diffuse;
        specular = _specular;
    }

};

struct Cube {
    glm::vec3 object_color = glm::vec3(1.0f, 0.5f, 0.31f);
    bool object_Isturning = false;
    float object_Isturning_speed = 0.0f;
    glm::vec3 object_Isturning_axe = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 object_position = glm::vec3(0.0f, 0.0f, 0.0f);
    Material object_material = Material(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f));;

    int object_shininess = 4;

};

struct GUI_Variables {

    //!light properties

    glm::vec3 light_color= glm::vec3(1.0f, 1.0f, 1.0f);
    bool light_Isturning = true;

    float light_Isturning_radius=0.0f;
    float light_Isturning_speed=0.0f;
    glm::vec3 light_position = glm::vec3(1.0f, 1.0f, 1.0f);
    Material light_material=Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));

    //!Cubes
    unsigned int CubeNr=0;
    Cube Cubes[10];

    int cubeIndex = -1;

};
void Imgui_Close();
ImGuiIO& Imgui_Initialize(GLFWwindow* window);
void SetImGuiStyle();
void DrawImgui(GUI_Variables& variables);

