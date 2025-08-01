#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum axis {
    X_AXIS,
    Y_AXIS,
    Z_AXIS
};

class Camera {
public:
    glm::vec3 position;
    glm::vec3 rotation;

    glm::mat4 proj_mat;
    
    Camera();
    
    void rotate(enum axis a, float degree);
    void projection_matrix(float fov, float screen_width, float screen_height);
};
