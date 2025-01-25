#include <iostream>
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "Shader.h"
#include "stb_image.h"

float x=0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//static unsigned int compileShader(GLuint type, const std::string& source) {
//    unsigned int id;
//    id = glCreateShader(type);
//    const char* src = source.c_str();
//    glShaderSource(id, 1, &src, NULL);
//    glCompileShader(id);
//
//    int success;
//    char infolog[512];
//
//    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        glGetShaderInfoLog(id, 512, NULL, infolog);
//        std::cout << "ERROR::SHADER::" << (type == GL_VERTEX_SHADER ? "Vertex": "Fragment") << "::COMPILATION_FAILED\n" << infolog << std::endl;
//    }
//    return id;
//
//}
//
//static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
//{
//    unsigned int vs = compileShader(GL_VERTEX_SHADER,vertexShader); 
//    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
//    unsigned int program=glCreateProgram();
//    glAttachShader(program, vs);
//    glAttachShader(program, fs);
//    glLinkProgram(program);
//
//    int success;
//    char infolog[512];
//    glGetProgramiv(program, GL_LINK_STATUS, &success);
//
//    if (!success) {
//        glGetProgramInfoLog(program, 512, NULL, infolog);
//        std::cout << "ERROR::shaderProgram::Linking\n" << infolog << std::endl;
//    }
//
//    glDeleteShader(vs);
//    glDeleteShader(fs);
//
//    return program;
//
//
//}
//
//
//const char* vertexShaderSource = "#version 460 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"layout (location = 1) in vec3 aColor;\n"
//"out vec3 vertexColor;\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"   vertexColor = aColor;\n"
//"}\0";
//
//
//const char* fragmentShaderSource = "#version 460 core\n"
//"out vec4 FragColor;\n"
//"in vec3 vertexColor;\n"
//"uniform vec4 Color;\n"
//"void main()\n"
//"{\n"
//"   FragColor = vec4(vertexColor,1.0f);\n"
//"}\0";

int main() {


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

    float vertices[] = {
        // positions         // colors          //textures
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,      // top right
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,      // bottom right
       - 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,      // bottom left 
       - 0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f       // top   left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,// first triangle
        0,2,3

    };

    unsigned int VAO,VBO,EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    //texture loading
    int width, height, nrchannels;
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrchannels, 0);
    std::cout << "widhth=" << width << " height=" << height << "\n";
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else { std::cout << "ERROR::Texture::Failed to load texture"; } 
    // set the texture wrapping/filtering options (on the currently bound texture object)

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    //texture loading
    unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrchannels, 0);
    std::cout << "widhth=" << width << " height=" << height << "\n";
    if (data2) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else { std::cout << "ERROR::Texture::Failed to load texture"; }


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(data);
    stbi_image_free(data2);

    
    
   

    // making the shader program

    //unsigned int sh = createShader(vertexShaderSource, fragmentShaderSource);
    Shader sh("vertexShader.vs", "fragmentShader.frag");

    // @RENDRING_Engine

    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        // clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // be sure to activate the shader
        sh.use();
        glUniform1i(glGetUniformLocation(sh.ID, "Texture_1"), 0); // set it manually
        sh.setInt("Texture_2", 1);
        //glUseProgram(sh);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // now render the triangle
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,0);

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
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {/*definesomrthing to do when pressing X*/
        x += 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {/*definesomrthing to do when pressing Y*/
        x = 0.0f;
    }
}