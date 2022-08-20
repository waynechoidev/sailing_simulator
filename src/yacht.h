#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <vector>
#include "../engine/mesh.h"

class Yacht : public Mesh
{
public:
    Yacht() : Mesh(){};
    void createYacht();
    glm::mat4 getModelMatrix(float deltaTime, glm::vec2 worldWind);
    void reset(glm::vec2 pos, float dirAngle);
    void turnToPort();
    void turnToStarboard();
    void turnEngine(bool isOn) { _isEngineOn = isOn; }
    float getMastAngle(glm::vec2 worldWind);
    void testCollision(glm::vec2 boxCenter, glm::vec2 boxLength);
    bool testGoal(glm::vec2 boxCenter, glm::vec2 boxLength);
    glm::vec2 getCurPos() { return _curPos; }

private:
    void initialize();
    glm::vec2 getDrag(float deltaTime);
    glm::vec2 getPoweredPropulsion(float deltaTime);
    glm::vec2 getWindPropulsion(glm::vec2 worldWind, float deltaTime);
    float getCurDir();

private:
    std::vector<unsigned int> _indices = {
        0, 1, 2,
        2, 3, 4,
        0, 2, 4};
    std::vector<GLfloat> _vertices = {
        -1.0f, -2.0f, 0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -2.0f, 0.2f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.2f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    glm::vec2 _curPos = {0.0f, 0.0f};
    float _prevAppWindAngle = 0.0f; // degrees
    glm::vec2 _prevVelocity = {0.0f, 0.0f};
    glm::vec2 _curDirVec = {0.0f, 1.0f};

    bool _isEngineOn = false;

    const glm::vec2 ZERO = {0.0f, 1.0f};

    float MAX_SPEED = 10.0f;
    float CIRCLE_RADIUS = 2.0f;
    float COR = 0.5f; // coefficient of restitution
};