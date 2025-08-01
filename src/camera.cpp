#include "camera.hpp"

Camera::Camera() {
    position = {0.0f, 0.0f, 0.0f};
    rotation = {0.0f, 0.0f, 1.0f};
}

void Camera::rotate(enum axis a, float degree) {
    switch(a) {
        case 0:
            
            break;
    }
}

void Camera::projection_matrix(float fov, float screen_width, float screen_height) {
    proj_mat = glm::perspective(glm::radians(fov), screen_width / screen_height, 0.1f, 100.0f);
}
