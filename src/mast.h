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

    void setVertices(float x, float y);

    glm::mat4 getModelMatrix();

private:
    unsigned int _indices[6] = {
        0, 1, 2,
        0, 2, 3};

    GLfloat _vertices[12] = {
        -0.15f, 0.0f, 0.1f,
        -0.15f, -3.0f, 0.1f,
        0.15f, -3.0f, 0.1f,
        0.15f, 0.0f, 0.1f};

    float _x = 0.0f;
    float _y = 2.0f;
    float _angle = 0.0f;
};
