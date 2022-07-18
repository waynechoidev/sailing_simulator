#pragma once

#include <GL/glew.h>

class Mesh
{
public:
    Mesh();

    void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
    void RenderMesh();

    ~Mesh();

private:
    void ClearMesh();

private:
    GLuint _VAO, _VBO, _IBO;
    GLsizei _indexCount;
};
