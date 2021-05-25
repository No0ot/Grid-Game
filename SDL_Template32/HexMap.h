#include "Hex.h"
#include <unordered_set>
#include <unordered_map>

class HexMap
{
private:

	std::vector<Hex*> m_pHexGrid;
	int m_mapRadius = 4;

public:

	HexMap();
	~HexMap();

	void BuildHexGrid();
	Hex* returnHex(glm::vec3 search);
	void MapGrid();
	void ResetHexs();
	std::vector<Hex*> ReturnGrid();

	std::unordered_map<Hex*, Hex*> GetReachableHexs(Hex* startingHex, int Movement);

};
