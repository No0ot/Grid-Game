#include "Hex.h"

class HexMap
{
private:

	std::vector<Hex*> m_pHexGrid;
	int m_mapRadius = 8;

public:

	HexMap();
	~HexMap();

	void BuildHexGrid();
	Hex* returnHex(glm::vec3 search);
	void MapGrid();
	void ResetHexs();
	std::vector<Hex*> ReturnGrid();

	std::vector<Hex*> GetReachableHexs(Hex* startingHex, int Movement);

};