#pragma once

#include <glm/glm.hpp>
#include "../engine/mesh.h"

class Vane : public Mesh
{
public:
    Vane(){};
    ~Vane(){};

    void createVane();
    glm::mat4 getModelMatrix(glm::vec2 pos, glm::vec2 worldWind);
    void renderVanes();

private:
    unsigned int _indices[9] = {
        0, 1, 2,
        0, 2, 6,
        4, 5, 3};

    GLfloat _vertices[56] = {
        -2.0f, -15.0f, 0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        2.0f, -15.0f, 0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        2.0f, -9.0f, 0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        4.0f, -9.0f, 0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -5.0f, 0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -4.0f, -9.0f, 0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -2.0f, -9.0f, 0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
};
