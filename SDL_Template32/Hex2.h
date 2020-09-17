#pragma once
#include "GameObject.h"
class Hex2
{
	glm::vec3 m_cubeCoordinate;

	Hex2(int x, int y, int z);
public:
	glm::vec3 getCubeCoordinate();

	Hex2 Hex_add(Hex2 a, Hex2 b);
	Hex2 Hex_subtract(Hex2 a, Hex2 b);
	Hex2 Hex_multiply(Hex2 a, Hex2 b);
};

