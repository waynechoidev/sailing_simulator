#include "goal.h"

void Goal::createGoal(glm::vec2 center, glm::vec2 length)
{
    unsigned int indices[12] = {
        0, 1, 2,
        0, 2, 3,
        4, 5, 6,
        4, 6, 7};

    GLfloat vertices[24] = {
        center.x - length.x / 2.0f, center.y - length.y / 2.0f, 0.0f,
        center.x + length.x / 2.0f, center.y - length.y / 2.0f, 0.0f,
        center.x + length.x / 2.0f, center.y + length.y / 2.0f, 0.0f,
        center.x - length.x / 2.0f, center.y + length.y / 2.0f, 0.0f,

        center.x - length.x / 2.0f + 1.0f, center.y - length.y / 2.0f + 1.0f, 0.1f,
        center.x + length.x / 2.0f - 1.0f, center.y - length.y / 2.0f + 1.0f, 0.1f,
        center.x + length.x / 2.0f - 1.0f, center.y + length.y / 2.0f - 1.0f, 0.1f,
        center.x - length.x / 2.0f + 1.0f, center.y + length.y / 2.0f - 1.0f, 0.1f};

    GLfloat colors[24] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.64f, 0.77f, 0.86f,
        0.64f, 0.77f, 0.86f,
        0.64f, 0.77f, 0.86f,
        0.64f, 0.77f, 0.86f};

    createMesh(vertices, colors, indices, sizeof(vertices), sizeof(indices));
}
