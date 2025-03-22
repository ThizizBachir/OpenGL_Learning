#include "imgui.h"
#include "glm\glm.hpp"

class SimulationSettings {
public:
    // ImGui variables
    bool drawBox = true;
    float DPI = 1.0f;
    float camera_speed = 1;
    bool Block_Camera = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    bool Rotate_Box = false;
    //!only if rotate box = true
    glm::vec3 axe = glm::vec3(0.0f, 0.0f, 1.0f);
    float rotaion_speed = 1.0f;

    enum available_textures
    {
        box_default, smile,ragoubi , ragoubi2
    };

   // available_textures texture1 = 0;

    available_textures texture1 = smile;

    //@if texture1!=texture2  nzido slider

    float textureRation = 0.0;


    // Singleton Instance Access
    static SimulationSettings& getInstance() {
        static SimulationSettings instance;
        return instance;
    }

private:
    SimulationSettings() = default; // Private constructor for Singleton
};
