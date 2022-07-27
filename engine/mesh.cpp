#include "mesh.h"
#include <iostream>

Mesh::Mesh()
{
    _VAO = 0;
    _VERTEX_VBO = 0;
    _COLOR_VBO = 0;
    _IBO = 0;
    _indexCount = 0;
}

void Mesh::createMesh(GLfloat *vertices, GLfloat *colors, unsigned int *indices, unsigned int sizeOfVertices, unsigned int sizeOfIndices)
{
    _indexCount = sizeOfIndices / sizeof(indices[0]);

    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(1, &_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &_VERTEX_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VERTEX_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeOfVertices, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &_COLOR_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _COLOR_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeOfVertices, colors, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _VERTEX_VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, _COLOR_VBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Mesh::renderMesh()
{
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
    glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::clearMesh()
{
    if (_IBO != 0)
    {
        _IBO = 0;
        glDeleteBuffers(1, &_IBO);
    }

    if (_VERTEX_VBO != 0)
    {
        _VERTEX_VBO = 0;
        glDeleteBuffers(1, &_VERTEX_VBO);
    }

    if (_COLOR_VBO != 0)
    {
        _COLOR_VBO = 0;
        glDeleteBuffers(1, &_COLOR_VBO);
    }

    if (_VAO != 0)
    {
        _VAO = 0;
        glDeleteVertexArrays(1, &_VAO);
    }

    _indexCount = 0;
}

Mesh::~Mesh()
{
    clearMesh();
}