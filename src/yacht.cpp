#include "yacht.h"
#include <iostream>

void Yacht::createYacht()
{
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 4,
        0, 2, 4};

    GLfloat vertices[] = {
        -0.7f, 0.0f, 0.1f,
        0.7f, 0.0f, 0.1f,
        0.7f, 2.0f, 0.1f,
        0.0f, 4.0f, 0.1f,
        -0.7f, 2.0f, 0.1f};

    createMesh(vertices, indices, 15, 9);
}

glm::mat4
Yacht::getModelMatrix(float deltaTime)
{
    glm::vec2 worldWind = {0.0f, -5.0f};
    glm::vec2 velocity =
        _prevVelocity + getPoweredPropulsion(deltaTime) + getWindPropulsion(worldWind, deltaTime) - getDrag(deltaTime);

    if (glm::length(velocity) >= MAX_SPEED)
    {
        velocity = glm::normalize(velocity) * MAX_SPEED;
    }

    float x = _prevX + velocity.x * deltaTime;
    float y = _prevY + velocity.y * deltaTime;

    std::cout << glm::length(velocity) << std::endl;

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(x, y, 0.0f));
    model = glm::rotate(model, getCurAngle(), glm::vec3(0.0f, 0.0f, 1.0f));

    _prevVelocity = velocity;
    _prevX = x;
    _prevY = y;

    return model;
}

void Yacht::turnToPort()
{
    _curAngle = glm::rotate(_curAngle, glm::radians(0.5f));
}

void Yacht::turnToStarboard()
{
    _curAngle = glm::rotate(_curAngle, glm::radians(-0.5f));
}

glm::vec2 Yacht::getDrag(float deltaTime)
{
    // std::cout << _prevX << " , " << _prevY << std::endl;
    glm::vec2 drag;

    if (glm::length(_prevVelocity) > 0)
    {
        glm::vec2 froudeNumber = _prevVelocity * 0.2f;
        drag = froudeNumber * deltaTime;
    }
    else
    {
        drag = {0.0f, 0.0f};
    }

    return drag;
}

glm::vec2 Yacht::getPoweredPropulsion(float deltaTime)

{
    glm::vec2 propulsion;
    if (_isEngineOn)
    {
        float engineSpeed = 0.5f * deltaTime;
        propulsion = {0.0f, engineSpeed};
        propulsion = glm::rotate(propulsion, getCurAngle());
    }
    else
    {
        propulsion = {0.0f, 0.0f};
    }

    return propulsion;
}

glm::vec2 Yacht::getWindPropulsion(glm::vec2 worldWind, float deltaTime)
{
    glm::vec2 appWind = worldWind + _prevVelocity;

    float degree = glm::degrees(glm::orientedAngle(glm::normalize(appWind), _curAngle));

    glm::vec2 propulsion = {0.0f, 0.0f};

    if (degree >= -30.0f && degree <= 30.0f)
        propulsion.y = 3.0f;
    else if (degree >= -90.0f && degree <= 90.0f)
        propulsion.y = 2.0f;
    else if (degree >= -130.0f && degree <= 130.0f)
        propulsion.y = 1.0f;
    else if (degree >= -150.0f && degree <= 150.0f)
        propulsion.y = 0.5f;
    else
        propulsion.y = 0.0f;

    propulsion = glm::rotate(propulsion, getCurAngle());
    propulsion = propulsion * deltaTime;

    return propulsion;
}

float Yacht::getCurAngle()
{
    return glm::orientedAngle(ZERO, _curAngle);
}