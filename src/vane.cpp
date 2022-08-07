#include "vane.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

void Vane::createVane()
{
    createMesh(_vertices, _indices, sizeof(_vertices), sizeof(_indices));
}

glm::mat4
Vane::getModelMatrix(glm::vec2 pos, glm::vec2 worldWind)
{
    glm::vec2 ZERO = {0.0f, 1.0f};
    float angle = glm::orientedAngle(ZERO, glm::normalize(worldWind));
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(pos.x, pos.y + 2.0f, 0.0f));
    model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));

    return model;
}
