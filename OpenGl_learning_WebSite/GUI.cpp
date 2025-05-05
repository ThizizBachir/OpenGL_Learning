#include "GUI.hpp"


ImGuiIO& Imgui_Initialize(GLFWwindow* window) {
    //IMGUI intialisation
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
    return io;
}

void Imgui_Close() {

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void SetImGuiStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Corners
    style.WindowRounding = 8.0f;
    style.ChildRounding = 8.0f;
    style.FrameRounding = 6.0f;
    style.PopupRounding = 6.0f;
    style.ScrollbarRounding = 6.0f;
    style.GrabRounding = 6.0f;
    style.TabRounding = 6.0f;
    style.TabRounding = 5.0f;

    // Colors
    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.43f, 0.50f, 0.56f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.50f, 0.56f, 0.50f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    ImGui::StyleColorsDark(); // Start with the default dark style

    // Modify the alpha channel of the window background color
    ImVec4 windowBgColor = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);
    windowBgColor.w = 0.5f; // Set alpha to 0.5 (50% transparency)
    ImGui::PushStyleColor(ImGuiCol_WindowBg, windowBgColor);

    // Optionally, make other elements semi-transparent
    ImVec4 childBgColor = ImGui::GetStyleColorVec4(ImGuiCol_ChildBg);
    childBgColor.w = 0.5f; // Set alpha to 0.5 (50% transparency)
    ImGui::PushStyleColor(ImGuiCol_ChildBg, childBgColor);

    ImVec4 popupBgColor = ImGui::GetStyleColorVec4(ImGuiCol_PopupBg);
    popupBgColor.w = 0.5f; // Set alpha to 0.5 (50% transparency)
    ImGui::PushStyleColor(ImGuiCol_PopupBg, popupBgColor);
}

void DrawImgui(GUI_Variables& variables) {
    // Tell OpenGL a new frame is about to begin
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //IMGUI window creation
    ImVec2 topLeftCorner(0.0f, 0.0f); // Position at (0, 0)
    ImGui::SetNextWindowPos(topLeftCorner, ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(500, 900));
    ImGui::Begin("Cloth Simulation Control Panel", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::Text("Light");

    ImGui::Text("Light Position");
    ImGui::Checkbox("light_Isturning", &variables.light_Isturning);
    if (variables.light_Isturning) {


        ImGui::SliderFloat("light_Speed", &variables.light_Isturning_speed, -5.0f, 5.0f);
        ImGui::SliderFloat("radius", &variables.light_Isturning_radius, 0.0f, 20.0f);
        ImGui::SliderFloat("height", &variables.light_position.y, -20.0f, 20.0f);
    }
    else {
        ImGui::SliderFloat("light x", &variables.light_position.x, -20.0f, 20.0f);
        ImGui::SliderFloat("light y ", &variables.light_position.y, -20.0f, 20.0f);
        ImGui::SliderFloat("light z", &variables.light_position.z, -20.0f, 20.0f);
    }
    ImGui::Text("Light color");
    ImGui::ColorEdit3("light_Color", (float*)&variables.light_color, ImGuiColorEditFlags_NoLabel);
    ImGui::ColorEdit3("light ambient", (float*)&variables.light_material.ambient, ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoLabel);
    ImGui::ColorEdit3("light diffusion", (float*)&variables.light_material.diffuse, ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoLabel);
    ImGui::ColorEdit3("light specular", (float*)&variables.light_material.specular, ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoLabel);

    if (ImGui::Button("Add Cube") && variables.CubeNr < 10) {
        variables.CubeNr++;


    }
    ImGui::SameLine();
    ImGui::Text("Total Cubes: %d", variables.CubeNr);

    if (variables.CubeNr) {
        static std::vector<std::string> cubeNameStrings;  // Stores actual strings
        static std::vector<const char*> cubeNames;  // Stores pointers to those strings

        cubeNameStrings.clear();
        cubeNames.clear();

        for (int i = 0; i < variables.CubeNr; i++) {
            cubeNameStrings.push_back("Cube " + std::to_string(i));  // Store full strings
        }

        for (const auto& name : cubeNameStrings) {
            cubeNames.push_back(name.c_str());  // Store pointers to valid strings
        }

        ImGui::Combo("Select Cube", &variables.cubeIndex, cubeNames.data(), cubeNames.size());
    }

    if (variables.CubeNr > 0 && variables.cubeIndex != -1) {
        ImGui::Text("Object");

        ImGui::Text("Object Position");
        ImGui::SliderFloat("Object X ", &variables.Cubes[variables.cubeIndex].object_position.x, -20.0f, 20.0f);
        ImGui::SliderFloat("Object Y ", &variables.Cubes[variables.cubeIndex].object_position.y, -20.0f, 20.0f);
        ImGui::SliderFloat("Object Z ", &variables.Cubes[variables.cubeIndex].object_position.z, -20.0f, 20.0f);
        ImGui::Checkbox("Object_Isturning", &variables.Cubes[variables.cubeIndex].object_Isturning);
        if (variables.Cubes[variables.cubeIndex].object_Isturning) {

            ImGui::SliderFloat("object_Speed", &variables.Cubes[variables.cubeIndex].object_Isturning_speed, -10.0f, 10.0f);
            ImGui::SliderFloat("x", &variables.Cubes[variables.cubeIndex].object_Isturning_axe.x, -1.0f, 1.0f);
            ImGui::SliderFloat("y", &variables.Cubes[variables.cubeIndex].object_Isturning_axe.y, -1.0f, 1.0f);
            ImGui::SliderFloat("z", &variables.Cubes[variables.cubeIndex].object_Isturning_axe.z, -1.0f, 1.0f);

        }

        ImGui::Text("Object color");
        ImGui::ColorEdit3("object_Color", (float*)&variables.Cubes[variables.cubeIndex].object_color, ImGuiColorEditFlags_NoLabel);
        ImGui::ColorEdit3("Object ambient", (float*)&variables.Cubes[variables.cubeIndex].object_material.ambient, ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoLabel);
        ImGui::ColorEdit3("Object diffusion", (float*)&variables.Cubes[variables.cubeIndex].object_material.diffuse, ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoLabel);
        ImGui::ColorEdit3("Object specular", (float*)&variables.Cubes[variables.cubeIndex].object_material.specular, ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoLabel);
        ImGui::SliderInt("Object Shininess", &variables.Cubes[variables.cubeIndex].object_shininess, 1, 10);

    }
    ImGui::End();


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}