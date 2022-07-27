#pragma once

#include <GL/glew.h>

class Mesh
{
public:
    Mesh();

    void createMesh(GLfloat *vertices, GLfloat *colors, unsigned int *indices, unsigned int sizeOfVertices, unsigned int sizeOfIndices);
    void renderMesh();

    ~Mesh();

protected:
    void clearMesh();

protected:
    GLuint _VAO, _VERTEX_VBO, _COLOR_VBO, _IBO;
    GLsizei _indexCount;
};
