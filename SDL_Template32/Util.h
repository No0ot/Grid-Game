#pragma once

#include "GLM/vec2.hpp"
#include "GLM/vec3.hpp"

class Util
{
private:

public:
    Util();
    ~Util();

    static glm::vec2 cube_to_offset(glm::vec3 cube_coord);
    static glm::vec3 offset_to_cube(glm::vec2 offset_coord);
    static float RandomRange(float min, float max);


};

