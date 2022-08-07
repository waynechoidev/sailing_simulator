#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../engine/mesh.h"

class Mast : public Mesh
{
public:
    Mast(){};
    ~Mast(){};

    void createMast();

    glm::mat4 getModelMatrix(float angle);

private:
    unsigned int _indices[6] = {
        0, 1, 2,
        0, 2, 3};

    GLfloat _vertices[32] = {
        -0.15f, 0.0f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.15f, -3.0f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.15f, -3.0f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.15f, 0.0f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    float angle = 0.0f;
};
