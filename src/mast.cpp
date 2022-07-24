#include "mast.h"
#include <iostream>
#include <glm/gtx/vector_angle.hpp>

void Mast::createMast()
{
    createMesh(_vertices, _indices, sizeof(_vertices), sizeof(_indices));
}

void Mast::setVertices(float x, float y)
{
    _x = x;
    _y = y;
    _angle = glm::radians(90.0f);
}

glm::mat4 Mast::getModelMatrix()
{

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(_x, _y, 0.0f));
    model = glm::rotate(model, _angle, glm::vec3(0.0f, 0.0f, 1.0f));

    return model;
}
