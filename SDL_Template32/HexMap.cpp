#include "HexMap.h"
#include <algorithm>
#include <queue>

using namespace std;

HexMap::HexMap()
{

}

HexMap::~HexMap()
{

}

void HexMap::BuildHexGrid()
{
	int map_radius = m_mapRadius;
	for (int q = -map_radius; q <= map_radius; q++) {
		int r1 = max(-map_radius, -q - map_radius);
		int r2 = min(map_radius, -q + map_radius);
		for (int r = r1; r <= r2; r++) {
			m_pHexGrid.push_back(new Hex(q, r, -q - r));
		}
	}
}

Hex* HexMap::returnHex(glm::vec3 search)
{
	Hex* temp = NULL;

	for (auto hex : m_pHexGrid)
	{
		if (hex->getCubeCoordinate() == search)
		{
			temp = hex;
		}
	}

	return temp;
}

void HexMap::MapGrid()
{
	for (auto hex : m_pHexGrid)
	{
		for (auto neighbour : hex->directions)
		{
			float x = hex->getCubeCoordinate().x + neighbour.x;
			float y = hex->getCubeCoordinate().y + neighbour.y;
			float z = hex->getCubeCoordinate().z + neighbour.z;

			if (x < m_mapRadius + 1.0f && x > -m_mapRadius - 1.0f && y < m_mapRadius + 1.0f && y > -m_mapRadius - 1.0f && z < m_mapRadius + 1.0f && z > -m_mapRadius - 1.0f)
			{
				Hex* temp = returnHex(glm::vec3(x, y, z));
				hex->m_pNeighbours.push_back(temp);
			}
		}
	}
}

void HexMap::ResetHexs()
{
	m_ThreatenedHexes.clear();
	m_ThreatenedHexes.shrink_to_fit();

	for (int count = 0; count < (int)m_pHexGrid.size(); count++)
	{
		m_pHexGrid[count]->setInteractiveState(Hex::INITIAL);
		m_pHexGrid[count]->setMouseState(Hex::STATE_OFF);
		m_pHexGrid[count]->b_visited = false;
		m_pHexGrid[count]->setLocalValue(INFINITY);
	}
}

std::vector<Hex*> HexMap::ReturnGrid()
{
	return m_pHexGrid;
}

std::vector<Hex*> HexMap::GetReachableHexs(Hex* startingHex, int Movement)
{
	//Get the current hex and add it to the visited Hexs
	std::list<Hex*> frontier;
	frontier.push_back(startingHex);
	Hex* current = frontier.front();
	current->setLocalValue(0.0f);

	std::vector<Hex*> reached;
	//reached.push_back(startingHex);
	//int cost_so_far = 0;
	while (!frontier.empty() && current->getLocalValue() < Movement)
	{
		frontier.sort([](const Hex* lhs, const Hex* rhs) {return lhs->getLocalValue() < rhs->getLocalValue(); });

		while(!frontier.empty() && frontier.front()->b_visited)
			frontier.pop_front();

		if (frontier.empty())
			break;

		current = frontier.front();
		current->b_visited = true;

		for (Hex* next : current->getNeighbours())
		{
			float templocal = current->getLocalValue() + next->getCost();
			if (next->getPathfindingState() != Hex::IMPASSABLE && templocal < next->getLocalValue())
			{
				next->setLocalValue(templocal);
			}

			if (next->getPathfindingState() != Hex::IMPASSABLE && !next->b_visited && next->getLocalValue() <= Movement)
			{
				frontier.push_front(next);
				reached.push_back(next);
			}
			else
				continue;

		}
	}
	return reached;
}

int HexMap::DistancebetweenHexs(Hex* a, Hex* b)
{
		return (abs(a->getCubeCoordinate().x - b->getCubeCoordinate().x) +
				  abs(a->getCubeCoordinate().y - b->getCubeCoordinate().y) +
				  abs(a->getCubeCoordinate().z - b->getCubeCoordinate().z)) / 2;
}

std::vector<Hex*> HexMap::HexLineDraw(Hex* a, Hex* b)
{
	int distance = DistancebetweenHexs(a, b);
	std::vector<Hex*> results;
	double step = 1.0 / max(distance, 1);

	for (int i = 1; i < distance; i++)
	{
		//std::cout << thing->getCubeCoordinate().x << " " << thing->getCubeCoordinate().y << " " << thing->getCubeCoordinate().z << std::endl;
		results.push_back(HexRound(HexLerp(a, b, step * i)));
	}

	return results;
}

bool HexMap::CheckLineofSight(std::vector<Hex*> line)
{
	for (auto hex : line)
	{
		if (hex->getPathfindingState() == Hex::IMPASSABLE)
		{
			return false;
			break;
		}
	}
	return true;
}

float HexMap::lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

glm::vec3 HexMap::HexLerp(Hex* a, Hex* b, float t)
{
	glm::vec3 temp = { lerp(a->getCubeCoordinate().x, b->getCubeCoordinate().x, t),
					   lerp(a->getCubeCoordinate().y, b->getCubeCoordinate().y, t),
					   lerp(a->getCubeCoordinate().z, b->getCubeCoordinate().z, t)};

	return temp;
}

Hex* HexMap::HexRound(glm::vec3 cube)
{
	float rx = round(cube.x);
	float ry = round(cube.y);
	float rz = round(cube.z);

	float x_diff = abs(rx - cube.x);
	float y_diff = abs(ry - cube.y);
	float z_diff = abs(rz - cube.z);

	if (x_diff > y_diff && x_diff > z_diff)
		rx = -ry - rz;
	else if (y_diff > z_diff)
		ry = -rx - rz;
	else
		rz = -rx - ry;

	return returnHex(glm::vec3(rx,ry,rz));
}
