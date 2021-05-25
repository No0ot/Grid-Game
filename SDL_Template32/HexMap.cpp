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

float HexMap::DistancebetweenHexs(Hex* a, Hex* b)
{

	std::cout << max(abs(a->getCubeCoordinate().x - b->getCubeCoordinate().x),
			abs(a->getCubeCoordinate().y - b->getCubeCoordinate().y),
			abs(a->getCubeCoordinate().z - b->getCubeCoordinate().z));
	return 0.0f;
}

std::vector<Hex*> HexMap::HexLineDraw(Hex* a, Hex* b)
{
	return std::vector<Hex*>();
}
