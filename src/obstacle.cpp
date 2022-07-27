#include "obstacle.h"

void Obstacle::createObstacle(glm::vec2 center, glm::vec2 length)
{
    unsigned int indices[6] = {
        0, 1, 2,
        0, 2, 3};

    GLfloat vertices[12] = {
        center.x - length.x / 2.0f, center.y - length.y / 2.0f, 0.1f,
        center.x + length.x / 2.0f, center.y - length.y / 2.0f, 0.1f,
        center.x + length.x / 2.0f, center.y + length.y / 2.0f, 0.1f,
        center.x - length.x / 2.0f, center.y + length.y / 2.0f, 0.1f};

    GLfloat colors[12] = {
        0.02f, 0.3f, 0.21f,
        0.02f, 0.3f, 0.21f,
        0.02f, 0.3f, 0.21f,
        0.02f, 0.3f, 0.21f};

    createMesh(vertices, colors, indices, sizeof(vertices), sizeof(indices));
}
