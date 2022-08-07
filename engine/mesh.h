#pragma once

#include <GL/glew.h>

class Mesh
{
public:
    Mesh();

    void createMesh(GLfloat *vertices, unsigned int *indices, unsigned int sizeOfVertices, unsigned int sizeOfIndices);
    void renderMesh();

    ~Mesh();

protected:
    void clearMesh();

protected:
    GLuint _VAO, _VBO, _IBO;
    GLsizei _indexCount;
};
