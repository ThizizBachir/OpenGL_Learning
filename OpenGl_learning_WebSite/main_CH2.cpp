#include <iostream>           
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "Shader.hpp"
#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>  
#include "Camera.hpp"
#include <assimp\Vertex.h>

float deltaTime = 0.0f;
float lastX = 400, lastY = 300;  
float currentFrame;
float lastFrame = 0.0f;
camera cam;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
GLFWwindow* makewindow();


int main() {
   
    GLFWwindow* window = makewindow();

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);




    //making verticies buffer Object "VBO"

    float vertices[] = {
          // positions                // normals         // texture coords
        -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,      0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,      1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,      1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,      1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,      0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,      0.0f, 0.0f,
                                                        
        -0.5f, -0.5f,  0.5f,     0.0f,  0.0f, 1.0f,       0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,     0.0f,  0.0f, 1.0f,       1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,     0.0f,  0.0f, 1.0f,       1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,     0.0f,  0.0f, 1.0f,       1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,     0.0f,  0.0f, 1.0f,       0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,     0.0f,  0.0f, 1.0f,       0.0f, 0.0f,
                                                        
        -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,      1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,      1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,      0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,      0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,      0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,      1.0f, 0.0f,
                                                        
         0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,      1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,      1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,      0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,      0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,      0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,      1.0f, 0.0f,
                                                        
        -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,      0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,      1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,      1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,      1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,      0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,      0.0f, 1.0f,
                                                        
        -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,      0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,      1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,      1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,      1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,      0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,      0.0f, 1.0f
    };



    unsigned int cubeVAO,VBO;
    glGenVertexArrays(1, &cubeVAO);

    glGenBuffers(1, &VBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

     //!SETTING TEXTURE
    unsigned int diffuse_texture = TextureFromFile("img/container2.png");
    unsigned int specular_texture =TextureFromFile("img/container2_specular.png");
    unsigned int emission_texture =TextureFromFile("img/woodstrip.png");

    // making the shader program

    Shader cubesh("vertexShader_CH2.vert", "fragmentShader_CH2.frag");
    Shader lightsh("vertexShader_CH2.vert", "fragmentShader_CH2_light.frag");

    glm::vec3 lightpos = glm::vec3(0.0f,2.0f,0.0f);

    // @RENDRING_Engine
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        // clear the colorbuffer
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //calculating Time
        currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //!setting gloal view and prespective matrix
        cam.make_view_projection();


        //!setting model matrix for the cube
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(1.0f));
        model = glm::translate(model, glm::vec3(0.0f,0.0f,0.0f));
        //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));


        cubesh.use();
        //setting light variable
        cubesh.setVec3("light.position", lightpos);
        cubesh.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        cubesh.setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
        cubesh.setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // darken diffuse light a bit
        cubesh.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        //setting ,model,view,projection matrices
        cubesh.setMat4("model", model);
        cubesh.setMat4("view", cam.view);
        cubesh.setMat4("projection", cam.projection);
        //setting view pos and materials
        cubesh.setVec3("viewPos", cam.cameraPos);
        cubesh.setInt("material.diffuse", 0);
        cubesh.setInt("material.specular", 1);
        cubesh.setInt("material.emission", 2);
        cubesh.setFloat("material.shininess", 32.0f);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuse_texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specular_texture);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, emission_texture);
        // now render the triangle
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);



        float r = 2.0;
        float spead = 3;
        lightpos.x = sin(glfwGetTime()* spead) * r;
        lightpos.z = cos(glfwGetTime()* spead) * r;

        model = glm::mat4(1.0f);
        //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, lightpos);
        model = glm::scale(model, glm::vec3(0.2f));

        // be sure to activate the shader
        lightsh.use();
        lightsh.setMat4("model", model);
        lightsh.setMat4("view", cam.view);
        lightsh.setMat4("projection", cam.projection);

       
        // now render the triangle
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
         

        // swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

    return 0;
}   

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {/*definesomething to do when pressing X*/

    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {/*definesomething to do when pressing Y*/

    }
    const float cameraSpeed = 0.5f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.Update_Position(GLFW_KEY_W);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.Update_Position(GLFW_KEY_S);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.Update_Position(GLFW_KEY_A);;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.Update_Position(GLFW_KEY_D);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cam.Update_Position(GLFW_KEY_Q);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cam.Update_Position(GLFW_KEY_E);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        cam.scroll_speed += 0.1f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        cam.scroll_speed -= 0.1f;
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    cam.Update_direction(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

    cam.Update_Zoom(yoffset);
};
GLFWwindow* makewindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
    GLFWwindow* window = glfwCreateWindow(videoMode->width, videoMode->height, "LearnOpenGL", primaryMonitor, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }
        
    glEnable(GL_DEPTH_TEST);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    return window;
}
