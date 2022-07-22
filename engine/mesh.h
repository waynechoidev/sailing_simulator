#pragma once

#include <GL/glew.h>

class Mesh
{
public:
    Mesh();

    void createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
    void renderMesh();

    ~Mesh();

private:
    void clearMesh();

private:
    GLuint _VAO, _VBO, _IBO;
    GLsizei _indexCount;
};
