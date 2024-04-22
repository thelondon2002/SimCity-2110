/*
The Cell class contains functions to control mutations to individual Cells/zones within a 
region. It contains each zone's number of population, workers, goods, residents, and pollution levels. It
also contains pointers to each zone in the immediate vicinity to this zone, with booleans to check
for specific characteristics of the surrounding zones.
*/

#ifndef CELL_H
#define CELL_H

#include "People.h"
#include <list>
using namespace std;

class Cell {
public:
	Cell();
	enum Type { residential, industrial, commercial, road, powerline, powerlineOverRoad, powerPlant, adoptionShelter, empty };
	void SetType(Type cellType);
	Type GetType();
	char GetSymbol();

	void SetPopulation(int population);
	int GetPopulation();

	void SetWorkers(int workers);
	int GetWorkers();

	void SetGoods(int goods);
	int GetGoods();

	void SetPollutionLevel(int pollutionLevel);
	int GetPollutionLevel();

	//Accessors and mutators for pointing to adjecent cells
	void SetTopLeftAdj(Cell* topLeft);
	Cell* GetTopLeftAdj();

	void SetTopAdj(Cell* top);
	Cell* GetTopAdj();

	void SetTopRightAdj(Cell* topRight);
	Cell* GetTopRightAdj();

	void SetLeftAdj(Cell* left);
	Cell* GetLeftAdj();

	void SetRightAdj(Cell* right);
	Cell* GetRightAdj();

	void SetBotLeftAdj(Cell* botLeft);
	Cell* GetBotLeftAdj();

	void SetBotAdj(Cell* bot);
	Cell* GetBotAdj();

	void SetBotRightAdj(Cell* botRight);
	Cell* GetBotRightAdj();

	int GetTotalAdjPop();

	//Boolean methods for testing adjacent values in specific cases
	bool IsAdjToPowerline();
	bool IsAdjToCellsPopOne();
	bool IsAdjToCellsPopTwoOrMore();
	bool IsAdjToCellsPopFourOrMore();

	struct Adjacency {
		Cell* topLeft;
		Cell* top;
		Cell* topRight;
		Cell* left;
		Cell* right;
		Cell* botLeft;
		Cell* bot;
		Cell* botRight;
	};

	list<People*> residents;

private:
	int population;
	int workers;
	int goods;
	int pollutionLevel;
	char symbol;
	Type cellType;
	Adjacency adjCells;
};

#endif