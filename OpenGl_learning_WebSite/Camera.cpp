#pragma once
#include "Camera.hpp"

void camera::Update_direction(const float xoffset, const float yoffset) {
    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}
void camera::Update_Zoom(double yoffset) {

    fov -= (float)yoffset * scroll_speed;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}
void camera::Update_Position(const int key) {
    switch (key)
    {
    case GLFW_KEY_W:
        cameraPos += mov_speed * cameraFront;
        break;
    case GLFW_KEY_S:
        cameraPos -= mov_speed * cameraFront;
        break;
    case GLFW_KEY_A:
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * mov_speed;
        break;
    case GLFW_KEY_D:
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * mov_speed;
        break;
    case GLFW_KEY_Q:
        cameraPos += mov_speed * cameraUp * 0.1f;
        break;
    case GLFW_KEY_E:
        cameraPos -= mov_speed * cameraUp * 0.1f;
        break;


    default:
        break;
    }

}
void camera::make_view_projection() {
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
}