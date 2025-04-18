#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "EventSys.h"
#include "Component.h"


class EventDispatcher;
class Renderer;
class Window : public Component<Renderer> {

private: 
    inline static std::unique_ptr<Window> instance = nullptr;

    Window();

    ~Window() {};

public:

    static Window* getInstance() {
        if (!instance) {
            instance = std::make_unique<Window>();
        }
        return instance.get();
    };

    //void init(std::unordered_map <std::string, Component<Renderer>*> Renderer_Entities)
    void Init(EventDispatcher * eventSys)
    {
        //this->Renderer_Entities = Renderer_Entities;
        this->eventSys = eventSys;
         
        glfwInit();

        glfwWindow = Window::make_window(true);

        if (glfwWindow == nullptr) {
            std::cout << "ERROOR::WINDOW::rendering window can't be made" << std::endl;
            return (void)nullptr;
        }


        glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);
        glfwSetCursorPosCallback(glfwWindow, mouse_callback);
        glfwSetScrollCallback(glfwWindow, scroll_callback);

        EventDispatcher::getInstance()->subscribe(Event_WindowResize_STR,
                                                  [](std::shared_ptr<EventBase> event){
            
                 auto Resizeevent = std::static_pointer_cast<Event_WindowResize>(event);
                 glViewport(0, 0, Resizeevent->width, Resizeevent->height);

                                                    });

        EventDispatcher::getInstance()->subscribe(Event_UI_Complete_Frame_STR,
                                                  [this](std::shared_ptr<EventBase> event) {
                glfwSwapBuffers(glfwWindow);
                glfwPollEvents();
                                                    });
    

	}

    void Shutdown() 
    {
        glfwTerminate();
    }

    void Input() {
        process_input(glfwWindow);
    }

    void Plot() {
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    bool Closed() {
        return glfwWindowShouldClose(glfwWindow);
    }

    GLFWwindow* getGLFWWindow() {
        return glfwWindow;
    }

	


private:
	
	GLFWwindow* glfwWindow;
    EventDispatcher * eventSys;

   inline static  int Width = 800;
   inline static int Height = 600;

    inline static double LastXpos = Width / 2;
    inline static double LastYpos = Height / 2;


     GLFWwindow* make_window(bool Fullsize) {

        // glfw: initialize and configure
        // ------------------------------
        //glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);  // Remove borders and title bar
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);  // Prevent resizing
        // glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE); // Start maximized

        #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif

        //int width = 800, height = 600;

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
            Width = videoMode->width;
            Height = videoMode->height;

             LastXpos = Width / 2;
             LastYpos = Height / 2;

            monitor = primaryMonitor;
        }

        // glfw window creation
        // --------------------
        GLFWwindow* window = glfwCreateWindow(Width, Height, "LearnOpenGL", monitor, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return nullptr;
        }

        // Center the window on the screen
        //if (Fullsize)
        //{
        //    int xpos = width / 2;
        //    int ypos = height / 2;
        //    glfwSetWindowPos(window, xpos, ypos);
        //}

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
        //stbi_set_flip_vertically_on_load(true);

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
     static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        EventDispatcher::getInstance()->Dispatch(std::make_shared<Event_WindowResize>(width, height));
    }


     static void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

         double xoffset = LastXpos - xpos;
         double yoffset = LastYpos - ypos;

         LastXpos = xpos;
         LastYpos = ypos;

        EventDispatcher::getInstance()->Dispatch(std::make_shared<Event_MouseMov>(xpos, ypos,xoffset,yoffset));

    }

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

        EventDispatcher::getInstance()->Dispatch(std::make_shared<Event_Scroll>(xoffset, yoffset));

    }
     //int keys[126]= {
     //   0, 1, 2, 3, 4, 5, 6, 7, 32, 39, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 59, 61,
     //   65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88,
     //   89, 90, 91, 92, 93, 96, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269,
     //   280, 281, 282, 283, 284, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303,
     //   304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 320, 321, 322, 323, 324, 325, 326, 327,
     //   328, 329, 330, 331, 332, 333, 334, 335, 336, 340, 341, 342, 343, 344, 345, 346, 347, 348
     //};

     int keys[126]{

        KEY_SPACE, KEY_APOSTROPHE, KEY_COMMA, KEY_MINUS, KEY_PERIOD, KEY_SLASH, KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_SEMICOLON, KEY_EQUAL, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M,KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_LEFT_BRACKET, KEY_BACKSLASH, KEY_RIGHT_BRACKET, KEY_GRAVE_ACCENT, KEY_ESCAPE, KEY_ENTER, KEY_TAB, KEY_BACKSPACE, KEY_INSERT, KEY_DELETE, KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP, KEY_PAGE_UP, KEY_PAGE_DOWN, KEY_HOME, KEY_END, KEY_CAPS_LOCK, KEY_SCROLL_LOCK, KEY_NUM_LOCK, KEY_PRINT_SCREEN, KEY_PAUSE, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_F13, KEY_F14, KEY_F15, KEY_F16, KEY_F17, KEY_F18, KEY_F19, KEY_F20, KEY_F21, KEY_F22, KEY_F23, KEY_F24, KEY_F25, KEY_KP_0, KEY_KP_1, KEY_KP_2, KEY_KP_3, KEY_KP_4, KEY_KP_5, KEY_KP_6, KEY_KP_7, KEY_KP_8, KEY_KP_9, KEY_KP_DECIMAL, KEY_KP_DIVIDE, KEY_KP_MULTIPLY, KEY_KP_SUBTRACT, KEY_KP_ADD, KEY_KP_ENTER, KEY_KP_EQUAL, KEY_LEFT_SHIFT, KEY_LEFT_CONTROL, KEY_LEFT_ALT, KEY_LEFT_SUPER, KEY_RIGHT_SHIFT, KEY_RIGHT_CONTROL, KEY_RIGHT_ALT, KEY_RIGHT_SUPER, KEY_MENU, MOUSE_BUTTON_1, MOUSE_BUTTON_2, MOUSE_BUTTON_3, MOUSE_BUTTON_4, MOUSE_BUTTON_5, MOUSE_BUTTON_6, MOUSE_BUTTON_7, MOUSE_BUTTON_8   
                   
     };

    static void process_input(GLFWwindow* window) {

        for (int i = 0; i < sizeof(keys) / sizeof(int); i++) {

            if (glfwGetKey(window, i) == KEY_RELEASE) {

                EventDispatcher::getInstance()->Dispatch(std::make_shared<Event_Keyboard>(i, KEY_RELEASE));
            }

            else if (glfwGetKey(window, i) == KEY_PRESS) {

                EventDispatcher::getInstance()->Dispatch(std::make_shared<Event_Keyboard>(i, KEY_PRESS));
            }

        }
    }

    std::unordered_map <std::string, Component<Renderer>*> Renderer_Entities;

};
