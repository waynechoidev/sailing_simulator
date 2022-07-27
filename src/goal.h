#pragma once

#include <glm/glm.hpp>
#include "../engine/mesh.h"

class Goal : public Mesh
{
public:
    Goal(){};
    ~Goal(){};

    void createGoal(glm::vec2 centre, glm::vec2 length);
};
