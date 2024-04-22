#include "Stress.h"

int Stress::GenerateRandomNumber() {
	int randomNum;
	randomNum = rand() % 100;
	return randomNum;
}
void Stress::StressAccumulation(vector<vector<Cell>>& region) {
	unsigned int seed = 0;

	srand(seed);
	int randNum = GenerateRandomNumber();
	for (unsigned int i = 0; i < region.size(); i++) {						//itteration of region vector
		for (unsigned int j = 0; j < region[i].size(); j++) {
			if (region[i][j].GetSymbol() == 'I') {					//Checks if cell is Industrial
				//incrementation of stress
				cout << i << " " << j << endl;
				stress[i][j] += region[i][j].GetWorkers();				//number of workers in cell is added to the stress level
				if (randNum <= stress[i][j]) {						//Random number generated; if less than stress level it will create strike
					Strike(region, i, j);
				}
			}
		}
	}

}

void Stress::InitializeStress(vector<vector<Cell>>& region) {		//initializes the stress level to zero in every Industrial cell
	vector<vector<int>> stress(region.size(), vector<int>(region[0].size(), 0));
	for (unsigned int i = 0; i < region.size(); i++) {
		vector<int>row;
		for (unsigned int j = 0; j < region[i].size(); j++) {
			stress[i][j] = 0;
		}
	}
}

void Stress::Strike(vector<vector<Cell>>& region, int row, int col) {
	int newWorkers = 0;
	//workers in industrial cell decrement by 1 every time stamp
	newWorkers = region[row][col].GetWorkers() - 1;
	region[row][col].SetWorkers(newWorkers);
	// random variable
	int randNum = GenerateRandomNumber();
	//if rand num is less than stress*2; ends strike (bool false)
	if (randNum < (stress[row][col] * 2)) {
		workersStrike = false;
	}
	//else recursive function
	else {
		Strike(region, row, col);
	}
}


int Stress::GetStress(int row, int column) {
	return stress[row][column];
}

int Stress::GetTotalStress() {
	int totalStress = 0;
	for (unsigned int i = 0; i < stress.size(); i++) {
		for (unsigned int j = 0; j < stress[i].size(); j++) {
			totalStress += stress[i][j];
		}
	}
	return totalStress;
}
