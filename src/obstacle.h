#pragma once

#include <glm/glm.hpp>
#include "../engine/mesh.h"

class Obstacle : public Mesh
{
public:
    Obstacle(){};
    ~Obstacle(){};

    void createObstacle(glm::vec2 centre, glm::vec2 length);
};
