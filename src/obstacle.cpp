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
        5 / 256.0f, 78 / 256.0f, 54 / 256.0,
        5 / 256.0f, 78 / 256.0f, 54 / 256.0,
        5 / 256.0f, 78 / 256.0f, 54 / 256.0,
        5 / 256.0f, 78 / 256.0f, 54 / 256.0};

    createMesh(vertices, colors, indices, sizeof(vertices), sizeof(indices));
}
