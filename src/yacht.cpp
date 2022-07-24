#include "yacht.h"
#include <iostream>
#include <cstring>

void Yacht::createYacht()
{
    update();
    createMesh(_vertices, _indices, sizeof(_vertices), sizeof(_indices));
}

glm::mat4
Yacht::getModelMatrix(float deltaTime, glm::vec2 worldWind)
{

    glm::vec2 velocity =
        _prevVelocity + getPoweredPropulsion(deltaTime) + getWindPropulsion(worldWind, deltaTime) - getDrag(deltaTime);

    if (glm::length(velocity) >= MAX_SPEED)
    {
        velocity = glm::normalize(velocity) * MAX_SPEED;
    }

    float x = _prevX + velocity.x * deltaTime;
    float y = _prevY + velocity.y * deltaTime;

    // std::cout << glm::length(velocity) << std::endl;

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(x, y, 0.0f));
    model = glm::rotate(model, getCurAngle(), glm::vec3(0.0f, 0.0f, 1.0f));

    _prevVelocity = velocity;
    _prevX = x;
    _prevY = y;

    return model;
}

void Yacht::update()
{

    glm::mat4 mastModel(1.0f);
    mastModel = glm::translate(mastModel, glm::vec3(0.0f, 0.0f, 0.0f));
    mastModel = glm::rotate(mastModel, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    for (int i = 0; i <= (sizeof(_mastVertices) / sizeof(_mastVertices[0])) / 3; i++)
    {
        int j = i * 3;
        glm::vec4 vec = {_mastVertices[j], _mastVertices[j + 1], _mastVertices[j + 2], 1.0f};
        vec = mastModel * vec;

        _mastVertices[j] = vec[0];
        _mastVertices[j + 1] = vec[1];
        _mastVertices[j + 2] = vec[2];
    }

    memcpy(_vertices, _hullVertices, sizeof(_hullVertices));
    memcpy(_vertices + (sizeof(_hullVertices) / sizeof(_hullVertices[0])), _mastVertices, sizeof(_mastVertices));
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

    float appWindAngle = getAppWindAngle(worldWind);

    glm::vec2 propulsion = {0.0f, 0.0f};

    if (appWindAngle >= -30.0f && appWindAngle <= 30.0f)
        propulsion.y = 3.0f;
    else if (appWindAngle >= -90.0f && appWindAngle <= 90.0f)
        propulsion.y = 2.0f;
    else if (appWindAngle >= -130.0f && appWindAngle <= 130.0f)
        propulsion.y = 1.0f;
    else if (appWindAngle >= -150.0f && appWindAngle <= 150.0f)
        propulsion.y = 0.5f;
    else
        propulsion.y = 0.0f;

    _prevAppWindAngle = appWindAngle;

    propulsion = glm::rotate(propulsion, getCurAngle());
    propulsion = propulsion * deltaTime;

    return propulsion;
}

float Yacht::getCurAngle()
{
    return glm::orientedAngle(ZERO, _curAngle);
}

float Yacht::getAppWindAngle(glm::vec2 worldWind)
{
    glm::vec2 appWind = worldWind + _prevVelocity;

    float appWindAngle = glm::degrees(glm::orientedAngle(glm::normalize(appWind), _curAngle));

    return appWindAngle;
}
