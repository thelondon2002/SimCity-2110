#include "Pollution.h"

void PollutionLevels::spreadPollution(vector<vector<Cell>> &region) {			//Spreads pollution to all ajacent cells in the region
		for (int i = 0; i < region.size(); i++) {						//nested for loop to iterate through the region vector to see wich is an industrial cell
			for (int j = 0; j < region[i].size(); j++) {
				if (region[i][j].GetSymbol() == 'I') {					//Checks if the cell is Industrial noted by 'I'
					//spread pollution
					 pollutionLevels[i][j] = region[i][j].GetPopulation(); //source cell

					 pollutionLevels[i][j] = region[i][j].GetTopLeftAdj().GetPopulation() -1 ; //top left cell

					 pollutionLevels[i][j] = region[i][j].GetTopAdj().GetPopulation() - 1; // top

					 pollutionLevels[i][j] = region[i][j].GetTopRightAdj().GetPopulation() - 1; // top right

					 pollutionLevels[i][j] = region[i][j].GetLeftAdj().GetPopulation() - 1; // left

					 pollutionLevels[i][j] = region[i][j].GetRightAdj().GetPopulation() - 1; // right

					 pollutionLevels[i][j] = region[i][j].GetBotLeftAdj().GetPopulation() - 1; //bottom left

					 pollutionLevels[i][j] = region[i][j].GetBotAdj().GetPopulation() - 1; // bottom

					 pollutionLevels[i][j] = region[i][j].GetBotRightAdj().GetPopulation() - 1; // bottom right
				}
			}
		}
		/*
		source cell: pollution level = source cell population
		ajacent cell: pollution level = population of ajacent cell - 1
		*/
}

PollutionLevels::PollutionLevels() {						//initializes the cell to what is initialized in the Cell() default constructor in the cell class
	cell = Cell();
}

void PollutionLevels::InitializePollutionLevels(vector<vector<Cell>>& region) {		//default constructor to inizialize everything to zero in pollutionLevels vector
	int row = region.size();
	int col = region[row].size();
	pollutionLevels[row][col];
	for (int i = 0; i < pollutionLevels.size(); i++) {
		for (int j = 0; j < pollutionLevels[i].size(); j++) {
			pollutionLevels[row][col] = 0;
		}
	}
}

int PollutionLevels::GetPollutionLevel(int row, int column) {				//Returns the Pollution at a specific cell in the 2d vector, pollutionLevels
	return pollutionLevels[row][column];
}

int PollutionLevels::GetTotalPollution() {									//Adds all the pollution to find the total regional pollution state.
	int totalPollution = 0;
	for (int i = 0; i < pollutionLevels.size(); i++) {
		for (int j = 0; j < pollutionLevels[i].size(); j++) {
			totalPollution += pollutionLevels[i][j];
		}
	}
	return totalPollution;													//returns the total pollution in the region
}
