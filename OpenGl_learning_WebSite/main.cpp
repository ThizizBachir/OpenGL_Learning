#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GUI.hpp"
#include <chrono>


//#include "filesystem.h"
#include "shader_m.h"
#include "camera.h"
#include "model.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
GLFWwindow* make_window(bool Fullsize);
unsigned int CubemapsTextureFromFile(const char* path, const std::string& directory, bool gamma);


// !settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
bool cursorDisabled = false;
bool ctrlPressed = false;
GUI_Variables var;

//!camera
Camera camera=Camera();
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// !timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//!lightning
glm::vec3 lightDirection = glm::vec3(-1.0, -1.0, -1.0);

int main()
{
    glfwInit();
    
    GLFWwindow* window = make_window(true);

    if (window == nullptr) {
        return -1;
    }
    // start timer with high_resolution_clock, 1st time point
    auto start = std::chrono::steady_clock::now();

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
   
    //@build and compile shaders
    // -------------------------
    Shader LoadingShader("shaders/model_loading.vert", "shaders/model_loading.frag");
    Shader GridShader("shaders/EndlessGrid.vert", "shaders/EndlessGrid.frag");
    Shader SkyboxShader("shaders/Skybox.vert", "shaders/Skybox.frag");

    //@load models
    // -----------
    Model ourModel("models/backpack/backpack.obj");


    //@initializing imgui

    ImGuiIO& io = Imgui_Initialize(window);
    SetImGuiStyle();


    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;

    unsigned int GridVAO;
    glGenVertexArrays(1, &GridVAO); 

    unsigned int SkyboxVAO;
    glGenVertexArrays(1, &SkyboxVAO);

    unsigned int skybox_texture = CubemapsTextureFromFile("img/CubeMap", "Sky2", false);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {

        //@starting time calculation
        //--------------------
        auto start = std::chrono::steady_clock::now();
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        int FPS = static_cast<int>(1 / deltaTime);


        // @input
        // -----
        processInput(window);
        camera.UpdateProjectionMatrix();//!!!!!!!!!!!!
        camera.UpdateViewMatrix();//!!!!!!!!!!!!!!! wa3lech ki enni7ihom ma3ach irander chyyy

        // @render
        // ------
        //!clearing screan
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        //!model matrix
        glm::mat4 model = glm::mat4(1.0f);

        //!Model Drawing
        LoadingShader.use();

        model = glm::mat4(1.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f));	// it's a bit too big for our scene, so scale it down

        LoadingShader.setMat4("projection", camera.projection);
        LoadingShader.setMat4("view", camera.view);
        LoadingShader.setVec3("lightDir", lightDirection);
        LoadingShader.setVec3("ViewPos", camera.Position);
        LoadingShader.setMat4("model", model);

        ourModel.Draw(LoadingShader); 


        //!drawing the skybox
       
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_FALSE);

        glBindVertexArray(SkyboxVAO);

        SkyboxShader.use();
        SkyboxShader.setMat4("projection", camera.projection);
        SkyboxShader.setMat4("view", glm::mat4(glm::mat3(camera.view)));
        SkyboxShader.setInt("skybox", 0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_texture);

        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);



         
        
        
        //!Drawing the Grid
        
        glBindVertexArray(GridVAO);

        GridShader.use();
        //camera.UpdateProjectionMatrix();
        //camera.UpdateViewMatrix();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f));
        GridShader.setVec3("CameraWorldPos", camera.Position);
        GridShader.setMat4("projection", camera.projection);
        GridShader.setMat4("view", camera.view);
        GridShader.setMat4("model", model);
        //GridShader.setInt("stretchmult", stretchmult);
        glDrawArrays(GL_TRIANGLES, 0, 12);
        glBindVertexArray(0);
        

        


        //!drawing IMGUI
        //DrawImgui(var);
        // Tell OpenGL a new frame is about to begin
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        //IMGUI window creation
        ImVec2 topLeftCorner(0.0f, 0.0f); // Position at (0, 0)
        ImGui::SetNextWindowPos(topLeftCorner, ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(200, 400));
        ImGui::Begin("GRID TEST", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

        auto end = std::chrono::steady_clock::now();
        float ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        ImGui::Text("frame periode: %f ms", ms);
        ms++;
        ImGui::Text("Frame Rate: %f fps", 1000/ms);
        ImGui::Text("camera.x: %f ", camera.Position.x);
        ImGui::Text("camera.y: %f ", camera.Position.y);
        ImGui::Text("camera.z: %f ", camera.Position.z);
        ImGui::SliderFloat("Light X", &lightDirection.x, -1.0f, 1.0f);
        ImGui::SliderFloat("Light Y", &lightDirection.y, -1.0f, 1.0f);
        ImGui::SliderFloat("Light Z", &lightDirection.z, -1.0f, 1.0f);
        //ImGui::SliderInt("Stretch mult", &stretchmult, 0, 5);
        //ImGui::Text(std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()).c_str());


        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
           

        //!swapping buffers
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();


    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    Imgui_Close();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && !ctrlPressed)
    {
        ctrlPressed = true;  // Mark that key was pressed once
        cursorDisabled = !cursorDisabled; // Toggle state
        glfwSetInputMode(window, GLFW_CURSOR, cursorDisabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }

    // Reset ctrlPressed when the key is released
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
    {
        ctrlPressed = false;
    }
        
        
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    if (cursorDisabled)
    {


        camera.ProcessMouseMovement(xoffset, yoffset);
    }

}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

GLFWwindow* make_window(bool Fullsize) {
    
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);        
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);  // Remove borders and title bar
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);  // Prevent resizing
   // glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE); // Start maximized

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    int width = 800, height = 600;

    GLFWmonitor* monitor = NULL;
   
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    if (!primaryMonitor) {
        std::cerr << "Failed to get primary monitor" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
    if (!videoMode) {
        std::cerr << "Failed to get video mode" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    if (Fullsize)
    {
        width = videoMode->width;
        height = videoMode->height;
        monitor = primaryMonitor;
    }

   // glfw window creation
   // --------------------
   GLFWwindow* window = glfwCreateWindow(width,height, "LearnOpenGL", NULL, NULL);
   if (window == NULL)
   {
       std::cout << "Failed to create GLFW window" << std::endl;
       glfwTerminate();
       return nullptr;
   }
   // Center the window on the screen
   if (Fullsize)
   {
       int xpos = width  / 2;
       int ypos = height / 2;
       //glfwSetWindowPos(window, xpos, ypos);
   }
   glfwMakeContextCurrent(window);
   

   // tell GLFW to capture our mouse
   //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   // glad: load all OpenGL function pointers
   // ---------------------------------------
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
       std::cout << "Failed to initialize GLAD" << std::endl;
       return nullptr;
   }

   //tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
   stbi_set_flip_vertically_on_load(true);

   // configure global opengl state
   // -----------------------------
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);
   glEnable(GL_STENCIL_TEST);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   // draw in wireframe
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);// GL_LINE for wireframe mode and GL_FILL for normal mode
   

   return window;


}
unsigned int CubemapsTextureFromFile(const char* path, const std::string& directory, bool gamma) {

    std::string directoryname = string(path) + "/" + directory ;

    std::string faces[6] = { "px","nx","py","ny","pz","nz"};

    unsigned int ID;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    stbi_set_flip_vertically_on_load(false);
    for (unsigned int i = 0; i < 6; i++) {
        int width, height, nrComponents;
        std::string filename = directoryname+'/' + faces[i] + ".png";
        unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents,0);
        if (data) {

            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        }
        else
        {
                std::cout << "Texture failed to load at path: " << filename << std::endl;
                stbi_image_free(data);
        }

        
    }

    return ID;
}