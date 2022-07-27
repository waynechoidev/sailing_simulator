#include "mast.h"
#include <iostream>
#include <glm/gtx/vector_angle.hpp>

void Mast::createMast()
{
    createMesh(_vertices, _colors, _indices, sizeof(_vertices), sizeof(_indices));
}

glm::mat4 Mast::getModelMatrix(float angle)
{
    float mastAngle;

    if (angle <= -150.0f)
        mastAngle = 0.0f;
    else if (angle <= 0)
        mastAngle = (-90.0f / 150.0f) * angle - 90.0f;
    else if (angle < 150)
        mastAngle = (-90.0f / 150.0f) * angle + 90.0f;
    else
        mastAngle = 0.0f;

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
    model = glm::rotate(model, glm::radians(mastAngle), glm::vec3(0.0f, 0.0f, 1.0f));

    return model;
}
