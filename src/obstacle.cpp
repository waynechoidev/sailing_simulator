#include "obstacle.h"

void Obstacle::createObstacle(glm::vec2 center, glm::vec2 length)
{
    unsigned int indices[6] = {
        0, 1, 2,
        0, 2, 3};

    GLfloat vertices[32] = {
        center.x - length.x / 2.0f, center.y - length.y / 2.0f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        center.x + length.x / 2.0f, center.y - length.y / 2.0f, 0.1f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        center.x + length.x / 2.0f, center.y + length.y / 2.0f, 0.1f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        center.x - length.x / 2.0f, center.y + length.y / 2.0f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f};

    createMesh(vertices, indices, sizeof(vertices), sizeof(indices));
}
