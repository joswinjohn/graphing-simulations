#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL.h>
#include <vector>

class Cube {
public:
    glm::vec4 points[8] {
        {-0.5f, -0.5f, 0.5f, 1.0f},   // front bottom left
        {0.5f, -0.5f, 0.5f, 1.0f},    // front bottom right
        {0.5f, 0.5f, 0.5f, 1.0f},     // front top right
        {-0.5f, 0.5f, 0.5f, 1.0f},    // front top left
        {-0.5f, -0.5f, -0.5f, 1.0f},  // back bottom left
        {0.5f, -0.5f, -0.5f, 1.0f},   // back bottom right
        {0.5f, 0.5f, -0.5f, 1.0f},    // back top right
        {-0.5f, 0.5f, -0.5f, 1.0f},   // back top left
    };

    glm::mat4 model_mat;

    Cube();

    void apply_mvp(glm::mat4 view_matrix, glm::mat4 proj_matrix);
    void window_transform(std::vector<glm::vec2> &screen_points, glm::vec2 viewport_size);
    static void render_cube(SDL_Renderer* renderer, std::vector<glm::vec2> &screen_points, int offset_x, int offset_y);

    void translate(glm::vec3 offset);
    void scale(glm::vec3 factor);
    void rotate(glm::quat rot);

    void print_points();
    void print_screen_points();
};
