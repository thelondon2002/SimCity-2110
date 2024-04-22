/*
The Cell class contains functions to control mutations to individual Cells/zones within a
region. It contains each zone's number of population, workers, goods, residents, and pollution levels. It
also contains pointers to each zone in the immediate vicinity to this zone, with booleans to check
for specific characteristics of the surrounding zones.
*/

#include "Cell.h"

Cell::Cell() {
	population = 0;
	workers = 0;
	goods = 0;
	pollutionLevel = 0;
	symbol = ' ';
	cellType = empty;
	adjCells.topLeft = nullptr;
	adjCells.top = nullptr;
	adjCells.topRight = nullptr;
	adjCells.left = nullptr;
	adjCells.right = nullptr;
	adjCells.botLeft = nullptr;
	adjCells.bot = nullptr;
	adjCells.botRight = nullptr;
}

/*
This mutator will use the passed-in cell type specificed by the enumerator 
in the header file to also assign the symbol of each Cell for output in 
SimSystem's PrintRegion() method.
*/
void Cell::SetType(Type cellType) {
	this->cellType = cellType;

	switch (cellType) {
	case residential:
		symbol = 'R';
		break;
	case industrial:
		symbol = 'I';
		break;
	case commercial:
		symbol = 'C';
		break;
	case road:
		symbol = '-';
		break;
	case powerline:
		symbol = 'T';
		break;
	case powerlineOverRoad:
		symbol = '#';
		break;
	case powerPlant:
		symbol = 'P';
		break;
	case adoptionShelter:
		symbol = 'A';
		break;
	case empty:
		symbol = ' ';
		break;
	default:
		break;
	}
}

//Accessors and mutators for the remaining variables (no mutator necessary for symbol):

Cell::Type Cell::GetType() {
	return this->cellType;
}

char Cell::GetSymbol() {
	return this->symbol;
}

void Cell::SetPopulation(int population) {
	this->population = population;
}

int Cell::GetPopulation() {
	return this->population;
}

void Cell::SetWorkers(int workers) {
	this->workers = workers;
}

int Cell::GetWorkers() {
	return this->workers;
}

void Cell::SetGoods(int goods) {
	this->goods = goods;
}

int Cell::GetGoods() {
	return this->goods;
}

void Cell::SetPollutionLevel(int pollutionLevel) {
	this->pollutionLevel = pollutionLevel;
}

int Cell::GetPollutionLevel() {
	return this->pollutionLevel;
}

//Accessors and mutators for pointers pointing to adjacent cells:
//Note: if the user attempts to access an unassigned adjacent cell (nullptr), then
//      the program will return an empty cell with default values of 0.


void Cell::SetTopLeftAdj(Cell* topLeft) {
	this->adjCells.topLeft = topLeft;
}
Cell* Cell::GetTopLeftAdj() {
	if (this->adjCells.topLeft != nullptr) {
		return (this->adjCells.topLeft);
	}
	Cell emptyCell;
	return &emptyCell;
}

void Cell::SetTopAdj(Cell* top) {
	this->adjCells.top = top;
}
Cell* Cell::GetTopAdj() {
	if (this->adjCells.top != nullptr) {
		return (this->adjCells.top);
	}
	Cell emptyCell;
	return &emptyCell;
}

void Cell::SetTopRightAdj(Cell* topRight) {
	this->adjCells.topRight = topRight;
}
Cell* Cell::GetTopRightAdj() {
	if (this->adjCells.topRight != nullptr) {
		return (this->adjCells.topRight);
	}
	Cell emptyCell;
	return &emptyCell;
}

void Cell::SetLeftAdj(Cell* left) {
	this->adjCells.left = left;
}
Cell* Cell::GetLeftAdj() {
	if (this->adjCells.left != nullptr) {
		return (this->adjCells.left);
	}
	Cell emptyCell;
	return &emptyCell;
}

void Cell::SetRightAdj(Cell* right) {
	this->adjCells.right = right;
}
Cell* Cell::GetRightAdj() {
	if (this->adjCells.right != nullptr) {
		return (this->adjCells.right);
	}
	Cell emptyCell;
	return &emptyCell;
}

void Cell::SetBotLeftAdj(Cell* botLeft) {
	this->adjCells.botLeft = botLeft;
}
Cell* Cell::GetBotLeftAdj() {
	if (this->adjCells.botLeft != nullptr) {
		return (this->adjCells.botLeft);
	}
	Cell emptyCell;
	return &emptyCell;
}

void Cell::SetBotAdj(Cell* bot) {
	this->adjCells.bot = bot;
}
Cell* Cell::GetBotAdj() {
	if (this->adjCells.bot != nullptr) {
		return (this->adjCells.bot);
	}
	Cell emptyCell;
	return &emptyCell;
}

void Cell::SetBotRightAdj(Cell* botRight) {
	this->adjCells.botRight = botRight;
}
Cell* Cell::GetBotRightAdj() {
	if (this->adjCells.botRight != nullptr) {
		return (this->adjCells.botRight);
	}
	Cell emptyCell;
	return &emptyCell;
}


int Cell::GetTotalAdjPop() {
	int totalPop = 0;

	totalPop += this->GetTopLeftAdj()->GetPopulation();
	totalPop += this->GetTopAdj()->GetPopulation();
	totalPop += this->GetTopRightAdj()->GetPopulation();
	totalPop += this->GetLeftAdj()->GetPopulation();
	totalPop += this->GetRightAdj()->GetPopulation();
	totalPop += this->GetBotLeftAdj()->GetPopulation();
	totalPop += this->GetBotAdj()->GetPopulation();
	totalPop += this->GetBotRightAdj()->GetPopulation();

	return totalPop;
}

//bools for testing adjacent cells in specific cases:

/*
This method returns True if one the adjacent Cells of a tested Cell is of the type
powerline or powerline over road.
*/
bool Cell::IsAdjToPowerline() {
	bool IsAdj = false;
	Type isPowerline = powerline;
	Type isPowerlineOverRoad = powerlineOverRoad;
	if ((this->GetTopLeftAdj())->GetType() == isPowerline ||
		(this->GetTopLeftAdj())->GetType() == isPowerlineOverRoad ||
		(this->GetTopAdj())->GetType() == isPowerline ||
		(this->GetTopAdj())->GetType() == isPowerlineOverRoad ||
		(this->GetTopRightAdj())->GetType() == isPowerline ||
		(this->GetTopRightAdj())->GetType() == isPowerlineOverRoad ||
		(this->GetLeftAdj())->GetType() == isPowerline ||
		(this->GetLeftAdj())->GetType() == isPowerlineOverRoad ||
		(this->GetRightAdj())->GetType() == isPowerline ||
		(this->GetRightAdj())->GetType() == isPowerlineOverRoad ||
		(this->GetBotLeftAdj())->GetType() == isPowerline ||
		(this->GetBotLeftAdj())->GetType() == isPowerlineOverRoad ||
		(this->GetBotAdj())->GetType() == isPowerline ||
		(this->GetBotAdj())->GetType() == isPowerlineOverRoad ||
		(this->GetBotRightAdj())->GetType() == isPowerline ||
		(this->GetBotRightAdj())->GetType() == isPowerlineOverRoad) {
		IsAdj = true;
	}
	return IsAdj;
}

/*
This method returns True if one the adjacent Cells of a tested Cell has a population
of one.
*/
bool Cell::IsAdjToCellsPopOne() {
	bool IsAdj = false;
	if ((this->GetTopLeftAdj())->GetPopulation() == 1 ||
		(this->GetTopAdj())->GetPopulation() == 1 ||
		(this->GetTopRightAdj())->GetPopulation() == 1 ||
		(this->GetLeftAdj())->GetPopulation() == 1 ||
		(this->GetRightAdj())->GetPopulation() == 1 ||
		(this->GetBotLeftAdj())->GetPopulation() == 1 ||
		(this->GetBotAdj())->GetPopulation() == 1 ||
		(this->GetBotRightAdj())->GetPopulation() == 1) {
		IsAdj = true;
	}
	return IsAdj;
}

/*
This method returns True if one the adjacent Cells of a tested Cell has a greater
than or equal to two.
*/
bool Cell::IsAdjToCellsPopTwoOrMore() {
	bool IsAdj = false;
	if ((this->GetTopLeftAdj())->GetPopulation() >= 2 ||
		(this->GetTopAdj())->GetPopulation() >= 2 ||
		(this->GetTopRightAdj())->GetPopulation() >= 2 ||
		(this->GetLeftAdj())->GetPopulation() >= 2 ||
		(this->GetRightAdj())->GetPopulation() >= 2 ||
		(this->GetBotLeftAdj())->GetPopulation() >= 2 ||
		(this->GetBotAdj())->GetPopulation() >= 2 ||
		(this->GetBotRightAdj())->GetPopulation() >= 2) {
		IsAdj = true;
	}
	return IsAdj;
}

/*
This method returns True if one the adjacent Cells of a tested Cell has a greater
than or equal to four.
*/
bool Cell::IsAdjToCellsPopFourOrMore() {
	bool IsAdj = false;
	if ((this->GetTopLeftAdj())->GetPopulation() >= 4 ||
		(this->GetTopAdj())->GetPopulation() >= 4 ||
		(this->GetTopRightAdj())->GetPopulation() >= 4 ||
		(this->GetLeftAdj())->GetPopulation() >= 4 ||
		(this->GetRightAdj())->GetPopulation() >= 4 ||
		(this->GetBotLeftAdj())->GetPopulation() >= 4 ||
		(this->GetBotAdj())->GetPopulation() >= 4 ||
		(this->GetBotRightAdj())->GetPopulation() >= 4) {
		IsAdj = true;
	}
	return IsAdj;
}