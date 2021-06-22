#include "Hex.h"
#include <unordered_set>
#include <unordered_map>

class HexMap
{
private:

	std::vector<Hex*> m_pHexGrid;
	int m_mapRadius = 5;

public:

	HexMap();
	~HexMap();

	void BuildHexGrid();
	Hex* returnHex(glm::vec3 search);
	void MapGrid();
	void ResetHexs();
	std::vector<Hex*> ReturnGrid();

	std::vector<Hex*> GetReachableHexs(Hex* startingHex, int Movement);
	int DistancebetweenHexs(Hex* a, Hex* b);
	std::vector<Hex*> HexLineDraw(Hex* a, Hex* b);
	bool CheckLineofSight(std::vector<Hex*> line);

	float lerp(float a, float b, float t);
	glm::vec3 HexLerp(Hex* a, Hex* b, float t);

	Hex* HexRound(glm::vec3 cube);

	std::vector<Hex*> m_ThreatenedHexes;
};
