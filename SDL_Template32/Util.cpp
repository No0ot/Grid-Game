#include "Util.h"

Util::Util()
= default;


Util::~Util()
= default;


glm::vec2 Util::cube_to_offset(glm::vec3 cube_coord)
{
        float col = cube_coord.x;
        float row = cube_coord.z + (cube_coord.x + ((int)cube_coord.x % 2)) / 2;

	return glm::vec2(col, row);
}

glm::vec3 Util::offset_to_cube(glm::vec2 offset_coord)
{
    float x = offset_coord.x;
    float z = offset_coord.y - (offset_coord.x + ((int)offset_coord.x % 2)) / 2;
    float y = (x * -1) - z;

    return glm::vec3(x,y,z);
}
