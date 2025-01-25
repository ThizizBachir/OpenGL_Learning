//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include <cmath>
//#include <vector>
//
//// Shader compilation function
//static unsigned int CompileShader(unsigned int type, const std::string& source)
//{
//    unsigned int id = glCreateShader(type);
//    const char* src = source.c_str();
//    glShaderSource(id, 1, &src, nullptr);
//    glCompileShader(id);
//
//    int result;
//    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
//    if (result == GL_FALSE)
//    {
//        int length;
//        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
//        char* message = (char*)alloca(length * sizeof(char));
//        glGetShaderInfoLog(id, length, &length, message);
//        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex " : "fragment ") << "shader" << std::endl;
//        std::cout << message << std::endl;
//        glDeleteShader(id);
//        return 0;
//    }
//
//    return id;
//}
//
//// Shader program creation
//static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
//{
//    unsigned int program = glCreateProgram();
//    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
//    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//    glAttachShader(program, vs);
//    glAttachShader(program, fs);
//    glLinkProgram(program);
//    glValidateProgram(program);
//
//    glDeleteShader(vs);
//    glDeleteShader(fs);
//
//    return program;
//}
//
//int main(void)
//{
//    GLFWwindow* window;
//
//    if (!glfwInit())
//        return -1;
//
//    window = glfwCreateWindow(800, 600, "Dynamic Jumping and Moving Squares", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwMakeContextCurrent(window);
//
//    if (glewInit() != GLEW_OK)
//    {
//        std::cout << "Error initializing GLEW" << std::endl;
//        return -1;
//    }
//
//    std::cout << glGetString(GL_VERSION) << std::endl;
//
//    // Define vertices for a square
//    float squareVertices[] = {
//        -0.1f, -0.1f,  // Bottom left
//         0.1f, -0.1f,  // Bottom right
//         0.1f,  0.1f,  // Top right
//        -0.1f,  0.1f   // Top left
//    };
//
//    unsigned int indices[] = {
//        0, 1, 2,  // First triangle
//        2, 3, 0   // Second triangle
//    };
//
//    unsigned int vao, vbo, ibo;
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//
//    glGenBuffers(1, &vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
//
//    glGenBuffers(1, &ibo);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    // Vertex Shader
//    std::string vertexShader = R"(
//        #version 330 core
//        layout(location = 0) in vec2 position;
//
//        uniform float time;
//        uniform vec2 baseOffset;
//        uniform float scale;
//        uniform float rotationSpeed;
//
//        void main()
//        {
//            // Calculate horizontal and vertical movement (sway and jumping)
//            float horizontalMove = 0.3 * sin(time + baseOffset.x);
//            float verticalJump = 0.5 * abs(sin(time * 2.0 + baseOffset.y));
//
//            // Combine offset with dynamic movement
//            vec2 dynamicOffset = baseOffset + vec2(horizontalMove, verticalJump);
//
//            // Rotation matrix
//            float angle = rotationSpeed * time;
//            mat2 rotation = mat2(cos(angle), -sin(angle),
//                                 sin(angle),  cos(angle));
//
//            vec2 rotatedPosition = rotation * (position * scale);
//            vec2 finalPosition = rotatedPosition + dynamicOffset;
//
//            gl_Position = vec4(finalPosition, 0.0, 1.0);
//        }
//    )";
//
//    // Fragment Shader
//    std::string fragmentShader = R"(
//        #version 330 core
//        layout(location = 0) out vec4 color;
//
//        uniform float time;
//        uniform vec3 baseColor;
//
//        void main()
//        {
//            float intensity = 0.5 + 0.5 * sin(time);
//            color = vec4(baseColor * intensity, 1.0);
//        }
//    )";
//
//    unsigned int shader = CreateShader(vertexShader, fragmentShader);
//    glUseProgram(shader);
//
//    // Uniform locations
//    int timeLocation = glGetUniformLocation(shader, "time");
//    int baseOffsetLocation = glGetUniformLocation(shader, "baseOffset");
//    int scaleLocation = glGetUniformLocation(shader, "scale");
//    int rotationSpeedLocation = glGetUniformLocation(shader, "rotationSpeed");
//    int baseColorLocation = glGetUniformLocation(shader, "baseColor");
//
//    // Define parameters for multiple squares
//    struct Square {
//        float offsetX, offsetY;
//        float scale;
//        float rotationSpeed;
//        float r, g, b; // Base color
//    };
//
//    std::vector<Square> squares = {
//        {-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f}, // Red square
//        { 0.5f, -0.5f, 0.4f, 1.5f, 0.0f, 1.0f, 0.0f}, // Green square
//        {-0.5f,  0.5f, 0.3f, 2.0f, 0.0f, 0.0f, 1.0f}, // Blue square
//        { 0.5f,  0.5f, 0.2f, 3.0f, 1.0f, 1.0f, 0.0f}, // Yellow square
//        { 0.0f,  0.0f, 0.6f, 0.7f, 1.0f, 0.0f, 1.0f}  // Purple square
//    };
//
//    while (!glfwWindowShouldClose(window))
//    {
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        float time = (float)glfwGetTime();
//
//        for (const auto& square : squares)
//        {
//            // Update uniforms for each square
//            glUniform1f(timeLocation, time);
//            glUniform2f(baseOffsetLocation, square.offsetX, square.offsetY);
//            glUniform1f(scaleLocation, square.scale);
//            glUniform1f(rotationSpeedLocation, square.rotationSpeed);
//            glUniform3f(baseColorLocation, square.r, square.g, square.b);
//
//            glBindVertexArray(vao);
//            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
//        }
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glDeleteVertexArrays(1, &vao);
//    glDeleteBuffers(1, &vbo);
//    glDeleteBuffers(1, &ibo);
//    glDeleteProgram(shader);
//
//    glfwTerminate();
//    return 0;
//}
