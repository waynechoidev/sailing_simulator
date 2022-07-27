#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "../engine/mesh.h"

class Yacht : public Mesh
{
public:
    Yacht() : Mesh(){};
    void createYacht();
    glm::mat4 getModelMatrix(float deltaTime, glm::vec2 worldWind);
    void reset(glm::vec2 pos);
    void turnToPort();
    void turnToStarboard();
    void turnEngine(bool isOn) { _isEngineOn = isOn; }
    float getMastAngle(glm::vec2 worldWind);
    bool testCollision(glm::vec2 boxCenter, glm::vec2 boxLength);

private:
    void initialize();
    glm::vec2 getDrag(float deltaTime);
    glm::vec2 getPoweredPropulsion(float deltaTime);
    glm::vec2 getWindPropulsion(glm::vec2 worldWind, float deltaTime);
    float getCurDir();

private:
    unsigned int _indices[9] = {
        0, 1, 2,
        2, 3, 4,
        0, 2, 4};
    GLfloat _vertices[15] = {
        -1.0f, 0.0f, 0.1f,
        1.0f, 0.0f, 0.1f,
        1.0f, 2.0f, 0.1f,
        0.0f, 4.0f, 0.1f,
        -1.0f, 2.0f, 0.1f};
    GLfloat _colors[15] = {
        0.3f, 0.3f, 0.3f,
        0.3f, 0.3f, 0.3f,
        0.3f, 0.3f, 0.3f,
        0.3f, 0.3f, 0.3f,
        0.3f, 0.3f, 0.3f};

    glm::vec2 _curPos = {0.0f, 0.0f};
    float _prevAppWindAngle = 0.0f; // degrees
    glm::vec2 _prevVelocity = {0.0f, 0.0f};
    glm::vec2 _curDirVec = {0.0f, 1.0f};

    bool _isEngineOn = false;

    const glm::vec2 ZERO = {0.0f, 1.0f};

    float MAX_SPEED = 10.0f;
    float CIRCLE_RADIUS = 1.0f;
};