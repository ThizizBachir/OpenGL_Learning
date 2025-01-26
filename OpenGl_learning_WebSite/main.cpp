#include <iostream>
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "Shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

float x=0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


int main() {
    //glm::mat4 trans = glm::mat4(1.0f);
    //trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    //trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);


    //making verticies buffer Object "VBO"

    /* float vertices[] = {
        // positions         // colors          //textures
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,      // top right
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,      // bottom right
       - 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,      // bottom left 
       - 0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f       // top   left
    };*/
    float vertices[] = {
        // positions         // colors          //textures
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,    1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,    0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,    1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,    0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,    0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,    0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,    1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,    0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,    0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,    1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,    0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,    1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,    1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,    0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,    1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,    1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    0.0f, 1.0f
    };
    /*unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,// first triangle
        0,2,3

    };*/

    unsigned int VAO,VBO,EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //drawing mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    
    //generating textures
    unsigned int texture_1,texture_2;
    glGenTextures(1, &texture_1);
    glBindTexture(GL_TEXTURE_2D, texture_1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //texture loading
    int width, height, nrchannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrchannels, 0);
    //std::cout << "widhth=" << width << " height=" << height << "\n";
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else { std::cout << "ERROR::Texture::Failed to load texture"; } 

    stbi_image_free(data);
    
    glGenTextures(1, &texture_2);
    glBindTexture(GL_TEXTURE_2D, texture_2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //texture loading
    unsigned char* data_2 = stbi_load("ragoubi2.png", &width, &height, &nrchannels, 0);
    //std::cout << "widhth=" << width << " height=" << height << "\n";
    if (data_2) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data_2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else { std::cout << "ERROR::Texture::Failed to load texture"; }


    stbi_image_free(data_2);

    // making the shader program

    Shader sh("vertexShader.vert", "fragmentShader.frag");

    
    glm::mat4 trans = glm::mat4(1.0f);

    glEnable(GL_DEPTH_TEST);

    glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };


    // @RENDRING_Engine
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        // clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate the shader
        sh.use();
        sh.setInt("Texture_1", 0); 
        sh.setInt("Texture_2", 1);

        //simple dynamic transform matrix
        /*unsigned int transformloc = glGetUniformLocation(sh.ID, "transform");
        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, 10 * (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(1/ (float)glfwGetTime(), 1 / (float)glfwGetTime(), 1 / (float)glfwGetTime()));
        glUniformMatrix4fv(transformloc, 1, GL_FALSE, glm::value_ptr(trans));*/
        for (int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            float angle = 20.0f * i;
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f+(float)i, (float)i*0.3f, 0.5f) - (float)i);
            unsigned int modelloc = glGetUniformLocation(sh.ID, "model");
            glUniformMatrix4fv(modelloc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        unsigned int viewloc = glGetUniformLocation(sh.ID, "view");
        glUniformMatrix4fv(viewloc, 1, GL_FALSE, glm::value_ptr(view));
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        unsigned int projectionloc = glGetUniformLocation(sh.ID, "projection");
        glUniformMatrix4fv(projectionloc, 1, GL_FALSE, glm::value_ptr(projection));
                

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture_2);
        // now render the triangle
        glBindVertexArray(VAO);
        
       // glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,0);

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
        x += 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {/*definesomething to do when pressing Y*/
        x = 0.0f;
    }
}