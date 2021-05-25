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
	for (int count = 0; count < (int)m_pHexGrid.size(); count++)
	{
		m_pHexGrid[count]->setInteractiveState(Hex::INITIAL);
		m_pHexGrid[count]->setMouseState(Hex::STATE_OFF);
	}
}

std::vector<Hex*> HexMap::ReturnGrid()
{
	return m_pHexGrid;
}

std::unordered_map<Hex*, Hex*> HexMap::GetReachableHexs(Hex* startingHex, int Movement)
{
	//Get the current hex and add it to the visited Hexs
	std::queue<Hex*> frontier;
	frontier.push(startingHex);

	std::unordered_map<Hex*, Hex*> came_from;
	came_from[startingHex] = startingHex;
	//int cost_so_far = 0;
	while (!frontier.empty())
	{
		Hex* current = frontier.front();
		frontier.pop();

		for (Hex* next : current->getNeighbours())
		{
			if (came_from.find(next) == came_from.end())
			{
				frontier.push(next);
				came_from[next] = current;
			}
		}
	}
	return came_from;
}
