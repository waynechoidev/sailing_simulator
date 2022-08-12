#include "obstacle.h"
#include <vector>

void Obstacle::createObstacle(glm::vec2 center, glm::vec2 length)
{
    std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 2, 3};

    std::vector<GLfloat> vertices = {
        center.x - length.x / 2.0f, center.y - length.y / 2.0f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        center.x + length.x / 2.0f, center.y - length.y / 2.0f, 0.1f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        center.x + length.x / 2.0f, center.y + length.y / 2.0f, 0.1f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        center.x - length.x / 2.0f, center.y + length.y / 2.0f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f};

    createMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
}
