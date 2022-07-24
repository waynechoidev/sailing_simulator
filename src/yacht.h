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
    void turnToPort();
    void turnToStarboard();
    void turnEngine(bool isOn) { _isEngineOn = isOn; }

    float getXPos() { return _prevX; }
    float getYPos() { return _prevY; }

private:
    glm::vec2 getDrag(float deltaTime);
    glm::vec2 getPoweredPropulsion(float deltaTime);
    glm::vec2 getWindPropulsion(glm::vec2 worldWind, float deltaTime);
    float getCurAngle();
    float getAppWindAngle(glm::vec2 worldWind);

private:
    // unsigned int mastIndices[6] = {
    //     5, 6, 7,
    //     5, 7, 8};
    // GLfloat mastVertices[12] = {
    //     0.0f, 2.0f, 0.1f,
    //     3.0f, 2.0f, 0.1f,
    //     3.0f, 2.3f, 0.1f,
    //     0.0f, 2.3f, 0.1f};

    float _prevX = 0.0f;
    float _prevY = 0.0f;
    float _prevAppWindAngle = 0.0f;
    glm::vec2 _prevVelocity = {0.0f, 0.0f};
    glm::vec2 _curAngle = {0.0f, 1.0f};

    bool _isEngineOn = false;

    const glm::vec2 ZERO = {0.0f, 1.0f};

    float MAX_SPEED = 10.0f;
};