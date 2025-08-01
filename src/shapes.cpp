#include "shapes.hpp"
#include <cstdio>

Cube::Cube() {
    model_mat = glm::mat4(1.0f);
};

void Cube::translate(glm::vec3 offset) {

};

void Cube::scale(glm::vec3 factor) {
    model_mat = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f));
};

void Cube::apply_mvp(glm::mat4 view_matrix, glm::mat4 proj_matrix) {
    for (int i = 0; i < 8; i++) {
        points[i] = proj_matrix * view_matrix * model_mat * points[i];
    }
};

void Cube::window_transform(std::vector<glm::vec2> &screen_points, glm::vec2 viewport_size) {
    for (int i = 0; i < 8; i++) {
        screen_points[i] = ((glm::vec2(glm::vec3(points[i]) / points[i].w) + 1.0f) * 0.5f) * viewport_size;
    }
};

void Cube::render_cube(SDL_Renderer* renderer, std::vector<glm::vec2> &screen_points, int offset_x, int offset_y) {
    for (int i = 0; i < 3; i++) {
        SDL_RenderDrawLine(
            renderer, 
            offset_x + screen_points[i].x, 
            offset_y + screen_points[i].y, 
            offset_x + screen_points[i+1].x, 
            offset_y + screen_points[i+1].y
        );
    }
    for (int i = 4; i < 7; i++) {
        SDL_RenderDrawLine(
            renderer, 
            offset_x + screen_points[i].x,
            offset_y + screen_points[i].y, 
            offset_x + screen_points[i+1].x, 
            offset_y + screen_points[i+1].y
        );
    }
    SDL_RenderDrawLine(
        renderer, 
        offset_x + screen_points[3].x, 
        offset_y + screen_points[3].y, 
        offset_x + screen_points[0].x, 
        offset_y + screen_points[0].y
    );
    SDL_RenderDrawLine(
        renderer, 
        offset_x + screen_points[7].x,
        offset_y + screen_points[7].y, 
        offset_x + screen_points[4].x, 
        offset_y + screen_points[4].y
    );

    for (int i = 0; i < 4; i++) {
        SDL_RenderDrawLine(
            renderer, 
            offset_x + screen_points[i].x,
            offset_y + screen_points[i].y,
            offset_x + screen_points[i+4].x,
            offset_y + screen_points[i+4].y
        );
    }
};

void Cube::print_points() {
    for (int i = 0; i < 8; i++) {
        printf("x: %.2f\ty: %.2f\tz: %.2f\n", points[i].x, points[i].y, points[i].z);
    }
    printf("\n");
};
