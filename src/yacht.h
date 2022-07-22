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
    glm::mat4 getModelMatrix(float deltaTime);

    void turnEngine(bool isOn) { _isEngineOn = isOn; }
    void turnToPort();
    void turnToStarboard();
    glm::vec2 getDrag(float deltaTime);
    glm::vec2 getPoweredPropulsion(float deltaTime);
    glm::vec2 getWindPropulsion(glm::vec2 worldWind, float deltaTime);
    float getCurAngle();

private:
    float _prevX = 0.0f;
    float _prevY = 0.0f;
    glm::vec2 _prevVelocity = {0.0f, 0.0f};
    glm::vec2 _curAngle = {0.0f, 1.0f};

    bool _isEngineOn = false;

    const glm::vec2 ZERO = {0.0f, 1.0f};

    float MAX_SPEED = 10.0f;
};