#include "Util.h"

Util::Util()
= default;


Util::~Util()
= default;


glm::vec2 Util::cube_to_offset(glm::vec3 cube_coord)
{
        float col = cube_coord.x;
        float row = cube_coord.z + (cube_coord.x + ((int)cube_coord.x&1)) / 2;

	return glm::vec2(col, row);
}

glm::vec3 Util::offset_to_cube(glm::vec2 offset_coord)
{
    float x = offset_coord.y;
    float z = offset_coord.x - (offset_coord.y + ((int)offset_coord.y&1)) / 2;
    float y = (x * -1) - z;

    return glm::vec3(x,y,z);
}

float Util::RandomRange(const float min, const float max)
{
    return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}
