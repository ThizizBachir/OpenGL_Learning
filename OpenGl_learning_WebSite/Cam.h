#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.h"
#include "Component.h"
#include "EventSys.h"





// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera :public  Component<Renderer> { 

private:

    inline static std::unique_ptr<Camera> instance = nullptr;

public:

    Camera(glm::vec3 Position = glm::vec3(7.35, 4.95, 6.925), glm::vec3 LookingAt = glm::vec3(0.0))
    {
        this->Position = Position;
        this->LookingAt = LookingAt;

        Front = glm::normalize(LookingAt - Position);

        Update_Camera_Angles_From_Front(Front);

        update_Camera_Vectors_From_Front(Front);

        UpdateViewMatrix();
        //!de preference na9ra les valeur el 7a99aniyin mta3 el window ba3d nrakka7 el projection matrix !! taw nsala7ha mba3d
        UpdateProjectionMatrix();

    }

    friend std::unique_ptr<Camera> std::make_unique<Camera>();


    ~Camera() {};
    static Camera* getInstance() {
        if (!instance) {
            instance = std::make_unique<Camera>();
        }
        return instance.get();
    }

    void Init(EventDispatcher * eventSys) {

        instance->eventSys = eventSys;


        EventDispatcher::getInstance()->subscribe(Event_WindowResize_STR,
                                                   [this](std::shared_ptr<EventBase> event) {

                auto resizeEvent = std::static_pointer_cast<Event_WindowResize>(event);
                Screen_Width = resizeEvent->width;
                Screen_Height = resizeEvent->height;
                UpdateProjectionMatrix();
                                                                                         });


        EventDispatcher::getInstance()->subscribe(Event_MouseMov_STR,
                                                [this](std::shared_ptr<EventBase> event) {
                auto mouseEvent = std::static_pointer_cast<Event_MouseMov>(event);
                float xoffset = static_cast<float>(mouseEvent->xoffset);
                float yoffset = static_cast<float>(mouseEvent->yoffset);
                if (!MouseLocked)
                {
                    
                    xoffset *= -Sensitivity;
                    yoffset *= Sensitivity;

                    Yaw += xoffset;
                    Pitch += yoffset;

                    // make sure that when pitch is out of bounds, screen doesn't get flipped
                    if (constrainPitch)
                    {
                        if (Pitch > 89.0f)
                            Pitch = 89.0f;
                        if (Pitch < -89.0f)
                            Pitch = -89.0f;
                    }

                    // update Front, Right and Up Vectors using the updated Euler angles
                    update_Camera_Vectors_From_Angles();

                    UpdateViewMatrix();

                }
                                                 });

        EventDispatcher::getInstance()->subscribe(Event_Keyboard_STR,
                                                 [this](std::shared_ptr<EventBase>(event)) {

            auto keyboardEvent = static_pointer_cast<Event_Keyboard>(event);
            int key = keyboardEvent->Key;
            int action = keyboardEvent->Action;

            float velocity = MovementSpeed * deltaTime;
            if (action)
            {
                switch (key)
                {
                case Forward_Key:
                    Position += Front * velocity;
                    break;
                case Backward_Key:
                    Position -= Front * velocity;
                    break;
                case Right_Key:
                    Position += Right * velocity;
                    break;
                case Left_Key:
                    Position -= Right * velocity;
                    break;
                case Up_Key:
                    Position += Up * velocity;
                    break;
                case Down_Key:
                    Position -= Up * velocity;
                    break;
                case Sensitivity_add_Key:
                    Sensitivity += Sensitivity_Sensitivity;
                    break;
                case Sensitivity_minus_Key:
                    Sensitivity -= Sensitivity_Sensitivity;
                    break;
                case MovementSpeed_add_Key:
                    MovementSpeed += MovementSpeed_Sensitivity;
                    break;
                case MovementSpeed_minus_Key:
                    MovementSpeed -= MovementSpeed_Sensitivity;
                    break;
                }
            }
            //lezem n7assen fi he4i
            if (key == MouseLocking_Key) {
                if (action) {
                    if (!ctrlPressed) {
                        ctrlPressed = true;
                        MouseLocked = !MouseLocked;
                    }
                }
                else {
                    ctrlPressed = false;
                }
            }
            
            UpdateViewMatrix();

                                                        });

        EventDispatcher::getInstance()->subscribe(Event_Scroll_STR,
                                                [this](std::shared_ptr<EventBase> event) {
            auto ScrollEvent = static_pointer_cast<Event_Scroll>(event);
            float yoffset = ScrollEvent->yoffset;

            Zoom -= (float)yoffset;
            if (Zoom < 1.0f) { Zoom = 1.0f; }
            if (Zoom > 45.0f) { Zoom = 45.0f; }

            UpdateProjectionMatrix();

            });


    }

    void Update(float deltaTime) {
        this->deltaTime = deltaTime;
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    void UpdateViewMatrix()
    {
        view = glm::lookAt(Position, Position + Front, Up);
    }

    void UpdateProjectionMatrix()
    {
        projection = glm::perspective(glm::radians(Zoom), Screen_Width / Screen_Height, Near, Far);
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return view;
    }

    glm::mat4 GetProjectionMatrix()
    {
        return projection;
    }

    glm::vec3 GetPosition()
    {
        return Position;
    }


    


private:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 LookingAt;
    //default values
    const float Default_Yaw = -90.0f;
    const float Default_Pitch = 0.0f;
    const float Default_Speed = 8.0f;
    const float Default_Sensitivity = 0.1f;
    const float Default_Zoom = 45.0f;
    const float Default_Near = 0.1f;
    const float Default_Far = 100.0f;
    const float Default_Screen_Width = 800.0f;
    const float Default_Screen_Height = 600.0f;
    const float Sensitivity_Sensitivity= 0.001f;
    const float MovementSpeed_Sensitivity= 0.01f;
    inline static const int Forward_Key = KEY_W;
    inline static const int Backward_Key = KEY_S;
    inline static const int Left_Key = KEY_A;
    inline static const int Right_Key = KEY_D;
    inline static const int Up_Key = KEY_Q;
    inline static const int Down_Key = KEY_E;
    inline static const int Sensitivity_add_Key = KEY_U;
    inline static const int Sensitivity_minus_Key = KEY_J;
    inline static const int MovementSpeed_add_Key = KEY_O;
    inline static const int MovementSpeed_minus_Key = KEY_L;
    inline static const int MouseLocking_Key = KEY_LEFT_CONTROL;

    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp=glm::vec3(0.0,1.0,0.0);
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed = Default_Speed;
    float Sensitivity = Default_Sensitivity ;
    float Zoom = Default_Zoom;
    //
    float Near = Default_Near;
    float Far = Default_Far;
    //
    float Screen_Width = Default_Screen_Width;
    float Screen_Height = Default_Screen_Height;

    bool constrainPitch =true;

    float deltaTime = 0.0f;

    bool MouseLocked=true;
    bool ctrlPressed = false;

    //Matrix
    glm::mat4 view, projection;

    EventDispatcher* eventSys;

    // constructor default


private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void update_Camera_Vectors_From_Angles()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));

    }

    void Update_Camera_Angles_From_Front(glm::vec3 Front) {

        Yaw = glm::degrees(atan2(Front.z, Front.x));
        if (Yaw < 0) Yaw += 360.0f; // Convert to range [0, 360]

        // Compute pitch (rotation around X-axis)
        Pitch = glm::degrees(asin(Front.y));
    }

    void update_Camera_Vectors_From_Front(glm::vec3 Front) {

        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));

    }

};
#endif
