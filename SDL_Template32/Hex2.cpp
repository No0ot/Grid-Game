#include "Hex2.h"


Hex2::Hex2(int x, int y, int z) : m_cubeCoordinate(glm::vec3(x,y,z))
{

}

glm::vec3 Hex2::getCubeCoordinate()
{
    return m_cubeCoordinate;
}

Hex2 Hex2::Hex_add(Hex2 a, Hex2 b)
{
    return Hex2(a.getCubeCoordinate().x + b.getCubeCoordinate().x,
                a.getCubeCoordinate().y + b.getCubeCoordinate().y,
                a.getCubeCoordinate().z + b.getCubeCoordinate().z);
}

Hex2 Hex2::Hex_subtract(Hex2 a, Hex2 b)
{
    return Hex2(a.getCubeCoordinate().x + b.getCubeCoordinate().x,
        a.getCubeCoordinate().y + b.getCubeCoordinate().y,
        a.getCubeCoordinate().z + b.getCubeCoordinate().z);
}

Hex2 Hex2::Hex_multiply(Hex2 a, Hex2 b)
{
    return Hex2();
}

bool operator == (Hex2 a, Hex2 b) {
    return a.getCubeCoordinate().x == b.getCubeCoordinate().x && a.getCubeCoordinate().y == b.getCubeCoordinate().y && a.getCubeCoordinate().z == b.getCubeCoordinate().z;
}