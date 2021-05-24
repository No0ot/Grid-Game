#include "HexMap.h"
#include <algorithm>
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

std::vector<Hex*> HexMap::GetReachableHexs(Hex* startingHex, int Movement)
{
	//Get the current hex and add it to the visited Hexs
	Hex* current_hex = startingHex;
	std::list<Hex*> visited;
	visited.push_back(current_hex);

	std::list<Hex*> came_from;
	int cost_so_far = 0;

	for (int i = 0; i <= Movement; i++)
	{
		if (!visited.empty())
		{
			current_hex = visited.front();
		}
		std::vector<Hex*> adjacent = current_hex->getNeighbours();

		for (auto hex : adjacent)
		{
			if (hex != nullptr)
			{
				int new_cost = cost_so_far + hex->getCost();


			}
		}
		
	}

	return visited;
}
