/*
The SimSystem class will manage the initialization of the city region, mutations onto the region per
time step (called with members of Adoption, Residential, Industrial, Commerical, and Pollution classes), and
the printing of the region per refresh rate.

***MESSAGE TO PROGRAMMERS*** if config1.txt can't be found, try running this code in the CELL machine! make sure
that config1.txt and region1.csv are in the same directory.
*/

#include "SimSystem.h"

SimSystem::SimSystem() {
	regionLayout = "";
	timeLimit = 0;
	refreshRate = 0;
	totalPollution = 0;
	availableWorkers = 0;
	availableGoods = 0;
	Adoption shelter;
	dogsInShelter = shelter.GetDogsInShelter();
	strayDogs = 0;
	food = 0;
	crops = 0;
	casualties = 0;
}

//Deallocates memory of each resident list in each cell
SimSystem::~SimSystem() {
	for (unsigned int i = 0; i < region.size(); i++) {
		for (unsigned int j = 0; j < region.at(i).size(); j++) {
			for (list<People*>::iterator it = region.at(i).at(j).residents.begin(); it != region.at(i).at(j).residents.end(); it++) {
				delete *it;
			}
			region.at(i).at(j).residents.clear();
		}
	}
}

//Accessor and mutators for available workers of the entire region:

void SimSystem::SetAvailableWorkers(int availableWorkers) {
	this->availableWorkers = availableWorkers;
}

void SimSystem::AddAvailableWorkers(int availableWorkers) {
	this->availableWorkers += availableWorkers;
}

void SimSystem::RemoveAvailableWorkers(int availableWorkers) {
	this->availableWorkers -= availableWorkers;
}

int SimSystem::GetAvailableWorkers() {
	return availableWorkers;
}

//Accessor and mutators for available goods of the entire region:

void SimSystem::SetAvailableGoods(int availableGoods) {
	this->availableGoods = availableGoods;
}

void SimSystem::AddAvailableGoods(int availableGoods) {
	this->availableGoods += availableGoods;
}

void SimSystem::RemoveAvailableGoods(int availableGoods) {
	this->availableGoods -= availableGoods;
}

int SimSystem::GetAvailableGoods() {
	return availableGoods;
}


//void to Get casualties from the industrial Class
int SimSystem::GetCasualties() {
    Industrial industrialObject; // Create an instance of Industrial class
    int casualties = industrialObject.GetCasualties();
	return casualties;
}
	

/*
This method prompts for and opens the file containing the simulation configuration. It stores each
configuration line into a string which is sliced to exclude the label and is assigned to its
respective private data object, converting the string into an integer if necessary.
*/
void SimSystem::ReadConfigFile() {
	ifstream configFile;
	string configFileName;
	cout << "Enter the simulation configuration file name: ";
	cin >> configFileName;
	configFile.open(configFileName);

	while (!configFile.is_open()) {
		cout << "This file is unable to be located. " << endl
			<< "Ensure that it's located in the same directory as the program files and try again: ";
		cin >> configFileName;
		configFile.open(configFileName);
	}

	string input;
	getline(configFile, input);
	regionLayout = input.substr(input.find(':') + 1);
	getline(configFile, input);
	timeLimit = stoi(input.substr(input.find(':') + 1));
	getline(configFile, input);
	refreshRate = stoi(input.substr(input.find(':') + 1));

	configFile.close();
}

/*
This method opens the region layout file as specified in the configuration file. It then iterates
through each line of the file, appending each Cell of the row into a Cell vector, then it
appends the row vector into a vector of Cell vectors. It then calls the AssignAdjacencies() method to
initialize each Cell's adjacent Cell pointers.
*/
void SimSystem::InitializeRegion() {
	if (regionLayout != "") {
		ifstream layoutFile;
		//path to enter for config file (on Marcus' laptop): C:\Users\weber\Downloads\config1.txt
		//FIXME: delete string "DELEGEregionLayout" and change parameter of layoutFile to regionLayout --- this is just so it works on VS
		//string DELETEregionLayout = "C:/Users/weber/Downloads/" + regionLayout;
		//layoutFile.open(DELETEregionLayout);
		layoutFile.open(regionLayout);

		string line;
		char cellSymbol;
		while (getline(layoutFile, line)) {
			vector<Cell> row; 
			for (unsigned int i = 0; i < line.size(); i++) {
				Cell newCell;
				cellSymbol = line.at(i);
				if (cellSymbol != ',') {
					if (cellSymbol == ' ') {
						newCell.SetType(Cell::empty);
					}
					else if (cellSymbol == 'R') {
						newCell.SetType(Cell::residential);
					}
					else if (cellSymbol == 'I') {
						newCell.SetType(Cell::industrial);
					}
					else if (cellSymbol == 'C') {
						newCell.SetType(Cell::commercial);
					}
					else if (cellSymbol == '-') {
						newCell.SetType(Cell::road);
					}
					else if (cellSymbol == 'T') {
						newCell.SetType(Cell::powerline);
					}
					else if (cellSymbol == '#') {
						newCell.SetType(Cell::powerlineOverRoad);
					}
					else if (cellSymbol == 'P') {
						newCell.SetType(Cell::powerPlant);
					}
					else if (cellSymbol == 'A') {
						newCell.SetType(Cell::adoptionShelter);
					}
					row.push_back(newCell);
				}
			}
			region.push_back(row);
			row.clear();
		}
		layoutFile.close();

		AssignAdjacencies(region);
	}
}
/*
This method iterates through each vector of a passed-by-reference region to assign each individual Cell with 
each of its surrounding adjacent Cell pointers. Parameters are set within if-statements to ensure that 
out-of-bounds elements aren't mutated; they would just remain as NULL.
*/
void SimSystem::AssignAdjacencies(vector<vector<Cell>> &regionToAssign) {
	Cell* topLeft = nullptr;
	Cell* top = nullptr;
	Cell* topRight = nullptr;
	Cell* left = nullptr;
	Cell* right = nullptr;
	Cell* botLeft = nullptr;
	Cell* bot = nullptr;
	Cell* botRight = nullptr;
	for (unsigned int i = 0; i < regionToAssign.size(); i++) {
		for (unsigned int j = 0; j < regionToAssign.at(i).size(); j++) {
			if (i > 0 && j > 0) {
				topLeft = &regionToAssign.at(i - 1).at(j - 1);
				regionToAssign.at(i).at(j).SetTopLeftAdj(topLeft);
			}
			if (i > 0) {
				top = &regionToAssign.at(i - 1).at(j);
				regionToAssign.at(i).at(j).SetTopAdj(top);
			}
			if (i > 0 && j < regionToAssign.at(i).size() - 1) {
				topRight = &regionToAssign.at(i - 1).at(j + 1);
				regionToAssign.at(i).at(j).SetTopRightAdj(topRight);
			}
			if (j > 0) {
				left = &regionToAssign.at(i).at(j - 1);
				regionToAssign.at(i).at(j).SetLeftAdj(left);
			}
			if (j < regionToAssign.at(i).size() - 1) {
				right = &regionToAssign.at(i).at(j + 1);
				regionToAssign.at(i).at(j).SetRightAdj(right);
			}
			if (i < regionToAssign.size() - 1 && j > 0) {
				botLeft = &regionToAssign.at(i + 1).at(j - 1);
				regionToAssign.at(i).at(j).SetBotLeftAdj(botLeft);
			}
			if (i < regionToAssign.size() - 1) {
				bot = &regionToAssign.at(i + 1).at(j);
				regionToAssign.at(i).at(j).SetBotAdj(bot);
			}
			if (i < regionToAssign.size() - 1 && j < regionToAssign.at(i).size() - 1) {
				botRight = &regionToAssign.at(i + 1).at(j + 1);
				regionToAssign.at(i).at(j).SetBotRightAdj(botRight);
			}
		}
	}
}

/*
This method prints the region grid (a 2D vector object) by iterating through the columns per
iteration of the rows and outputting a dereference of the column object's character symbol. If the 
population is greater than 0, then the population is output instead.
*/
void SimSystem::PrintRegion() {
	vector<vector<Cell>>::iterator itRow;
	vector<Cell>::iterator itCol;
	for (itRow = region.begin(); itRow != region.end(); itRow++) {
		for (itCol = itRow->begin(); itCol != itRow->end(); itCol++) {
			//Deleting one space after a double-digit integer to maintain grid layout
			if (itCol->GetPopulation() >= 10) {
				cout << itCol->GetPopulation() << " ";
			}
			else if (itCol->GetPopulation() > 0 && (itCol->GetType() == Cell::road || itCol->GetType() == Cell::powerlineOverRoad)) {
				cout << itCol->GetPopulation() << itCol->GetSymbol() << " ";
			}
			else if (itCol->GetPopulation() > 0) {
				cout << itCol->GetPopulation() << "  ";
			}			else {
				cout << itCol->GetSymbol() << "  ";
			}
		}
		cout << endl;
	}
}

/*
This method outputs the public int variables of the SimSystem class with appropriate labels.
*/
void SimSystem::PrintRegionInfo() {

	Farm farm;

	cout << "Available workers: " << availableWorkers << endl;
	cout << "Available goods: " << availableGoods << endl; 
	cout << "Total pollution level: " << totalPollution << endl;
	cout << "Total dogs in shelter: " << dogsInShelter << endl;
	cout << "Total stray dogs: " << strayDogs << endl;
	cout << "Total amount of food: " << food << endl;
	cout << "Total amount of crops produced: " << crops << endl;
	cout << "Total number of casualties:" << casualties << endl;
	cout << "Total Stress: " << workerStress << endl;
	farm.SetWeatherCondition();
	farm.PrintWeatherCondition();

}

/*
This method tracks the modification of each Cell in the 2D-vector region and calls upon the systems
provided by Commerical, Industrial, and Residential. The method will select one of these updates to occur
per time step onto a region which is copied. The copied region is re-initialized to how the region was at the
beginning of the time step each time another cell is accessed, thus ensuring that changes don't carry over into 
subsequently accessed cells during the same time step.
*/
void SimSystem::CommenceTimeSteps() {
	int timeCounter = 0;
	int refreshCounter = 0;
	Commercial commerce;
	Industrial industry;
	Residential residence;
	Adoption shelter;
	Farm farm;
	Stress stress;
	PollutionLevels pol;
	pol.InitializePollutionLevels(region);
	stress.InitializeStress(region);

	vector<vector<Cell>> regionCopy;
	vector<vector<Cell>> regionAtStartOfStep;
	bool breakOutOfLoops = false;

	while (timeCounter < timeLimit) {
		regionAtStartOfStep = region;
		AssignAdjacencies(regionAtStartOfStep);
		stress.StressAccumulation(region); // starts adding stress of the workers to all the industrial cells
		workerStress = stress.GetTotalStress();

		//Updating shelter per time step and allowing for adoption by residents
		shelter.SetDogsInShelter(dogsInShelter);
		srand(time(nullptr));
		for (unsigned int i = 0; i < region.size(); i++) {
			for (unsigned int j = 0; j < region.at(i).size(); j++) {
				if ((region.at(i).at(j)).GetType() == Cell::adoptionShelter) {
					shelter.GrowDogsAtRandom();
					dogsInShelter = shelter.GetDogsInShelter();
					shelter.AddStraysToRoad(&(region.at(i).at(j)), strayDogs);
				}
				if ((region.at(i).at(j)).GetType() == Cell::residential) {
					if (!region.at(i).at(j).residents.empty()) {
						for (list<People*>::iterator it = region.at(i).at(j).residents.begin(); it != region.at(i).at(j).residents.end(); ++it) {
							shelter.LookToAdoptDog(*(*it));
							dogsInShelter = shelter.GetDogsInShelter();
							shelter.AddStraysToRoad(&(region.at(i).at(j)), strayDogs);
						}
					}
				}
			}
		}
		shelter.GrowStraysAtRandom(region, strayDogs);

		for (unsigned int i = 0; i < region.size(); i++) {
			for (unsigned int j = 0; j < region.at(i).size(); j++) {
				regionCopy = regionAtStartOfStep;
				AssignAdjacencies(regionCopy);

				//Commercial cells are given a higher priority to update if the appropriate resources are available
				if (availableWorkers >= 1 && availableGoods >= 1) {
					if ((region.at(i).at(j)).GetType() == Cell::commercial) {
						commerce.SetValues((regionCopy.at(i).at(j)).GetPopulation(),
							(regionCopy.at(i).at(j)).GetWorkers(),
							(regionCopy.at(i).at(j)).GetGoods());
					farm.ProduceFood(commerce);
					food = commerce.GetFood();
					crops = commerce.GetCrops();
					commerce.AddCrops(1);
					commerce.AddFood(1);
						if (commerce.UpdateCommercial((regionCopy.at(i).at(j)), farm, availableWorkers, availableGoods)) {
							(region.at(i).at(j)).SetPopulation(commerce.GetPopulation());
							(region.at(i).at(j)).SetWorkers(commerce.GetWorkers());
							(region.at(i).at(j)).SetGoods(commerce.GetGoods());
							availableWorkers--;
							availableGoods--;
							regionCopy = regionAtStartOfStep;
							breakOutOfLoops = true;
							break;
						}
						commerce.ResetValues();
					}
				}
				//If Commercial cannot update, then Industrial is given priority if there are at least two available workers
				else if (availableWorkers >= 2) {
					if ((region.at(i).at(j)).GetType() == Cell::industrial) {
						industry.SetValues((regionCopy.at(i).at(j)).GetPopulation(),
							(regionCopy.at(i).at(j)).GetWorkers(),
							(regionCopy.at(i).at(j)).GetGoods());
					farm.ProduceFood(commerce);
					food = commerce.GetFood();
					crops = commerce.GetCrops();
					commerce.AddCrops(1);
					commerce.AddFood(1);
						if (industry.UpdateIndustrial((regionCopy.at(i).at(j)), availableWorkers)) {
							(region.at(i).at(j)).SetPopulation(industry.GetPopulation());
							(region.at(i).at(j)).SetWorkers(industry.GetWorkers());
							(region.at(i).at(j)).SetGoods(industry.GetGoods());
							availableWorkers -= 2;
							availableGoods++;
							totalPollution++;
							regionCopy = regionAtStartOfStep;
							breakOutOfLoops = true;
							break;
						}
						industry.ResetValues();
					}
				}
				//If neither Commerical or Industrial update, then a Residential cell grows in population
				else if ((region.at(i).at(j)).GetType() == Cell::residential) {
					residence.SetValues((regionCopy.at(i).at(j)).GetPopulation(), (regionCopy.at(i).at(j)).GetWorkers());
					if (residence.UpdateResidential(regionCopy.at(i).at(j))) {
						(region.at(i).at(j)).SetPopulation(residence.GetPopulation());
						(region.at(i).at(j)).SetWorkers(residence.GetWorkers());
						availableWorkers++;
						People* newPerson = new People;
						residence.LivingSpace(newPerson, timeCounter);
						(region.at(i).at(j)).residents.push_back(newPerson);
						regionCopy = regionAtStartOfStep;
						breakOutOfLoops = true;
						break;
					}
					residence.ResetValues();
				}
			}
			//This ensures that the nested for-loop terminates once a cell has been updated
			if (breakOutOfLoops) {
				breakOutOfLoops = false;
				break;
			}
		}
		timeCounter++;
		refreshCounter++;

		//The status of the region is output each time the refresh rate is reached
		if (refreshCounter == refreshRate) {
			cin.get();
			cout << "Time Step #" << timeCounter << ':' << endl;
			PrintRegion();
			PrintRegionInfo();
			cout << "Press [enter] to continue." << endl;

			refreshCounter = 0;
		}
	}
	cin.get();
}

/*
This method commences the analysis of a specifed area between two coordinates in the region by asking
the user if they want to proceed, then prompting for the two coordinate pairs ensuring they stay in
bounds, then iterating through the region between the coordinates to gather the area's total population
and pollution levels, and the dog population, then asking the user if they want to try a different area.
*/
void SimSystem::AnalyzeRegionArea() {
	int x1 = -1;
	int y1 = -1;
	int x2 = -1;
	int y2 = -1;
	int minX = 0;
	int maxX = 0;
	int minY = 0;
	int maxY = 0;
	char comma = ',';
	char choice = 'n';
	int areaPopulation = 0;
	int areaPollution = 0;
	int totalPets = 0;
	int totalStrays = 0;
	int totalApartments = 0;
	int totalHouses = 0;
	int totalMansions = 0;

	cout << "Would you like to analyze the area between two coordinates? (Enter y or n): " ;
	cin >> choice;
	if (choice == 'y') {
		do {
			//acquiring first coordinate pair
			printf("Enter the first coordinate as x,y (0-%zu,0-%zu) assuming the top left is 0,0: ", region.size() - 1, region.at(0).size() - 1);
			cin >> x1 >> comma >> y1;
			while (static_cast<unsigned>(x1) >= region.size() || x1 < 0 || static_cast<unsigned>(y1) >= region.at(0).size() || y1 < 0) {
				printf("Out of bounds. Try again as 0-%zu,0-%zu: ", region.size() - 1, region.at(0).size() - 1);
				cin >> x1 >> comma >> y1;
			}

			//acquiring second coordinate pair
			printf("Now enter the second coordinate as 0-%zu,0-%zu: ", region.size() - 1, region.at(0).size() - 1);
			cin >> x2 >> comma >> y2;
			while (static_cast<unsigned>(x2) >= region.size() || x2 < 0 || static_cast<unsigned>(y2) >= region.at(0).size() || y2 < 0) {
				printf("Out of bounds. Try again as x,y (0-%zu,0-%zu): ", region.size() - 1, region.at(0).size() - 1);
				cin >> x2 >> comma >> y2;
			}

			minX = min(x1, x2);
			maxX = max(x1, x2);
			minY = min(y1, y2);
			maxY = max(y1, y2);
			for (int i = minY; i <= maxY; i++) {
				for (int j = minX; j <= maxX; j++) {
					areaPopulation += region.at(i).at(j).GetPopulation();
					if (region.at(i).at(j).GetType() == Cell::industrial) {
						areaPollution += region.at(i).at(j).GetPollutionLevel();
					}
					else if (region.at(i).at(j).GetType() == Cell::residential) {
						if (!region.at(i).at(j).residents.empty()) {
							for (list<People*>::iterator it = region.at(i).at(j).residents.begin(); it != region.at(i).at(j).residents.end(); ++it){
								totalPets += (*it)->dogs;
								if ((*it)->living == People::apartment) {
									totalApartments++;
								}
								else if ((*it)->living == People::house) {
									totalHouses++;
								}
								else if ((*it)->living == People::mansion) {
									totalMansions++;
								}
							}
						}
					}
					else if (region.at(i).at(j).GetType() == Cell::road || region.at(i).at(j).GetType() == Cell::powerlineOverRoad) {
						totalStrays += region.at(i).at(j).GetPopulation();
					}				}
			}
			areaPopulation -= totalStrays;
			
			printf("\nTotal population between (%d,%d) and (%d,%d): %d\n", x1, y1, x2, y2, areaPopulation);
			printf("Total pollution between (%d,%d) and (%d,%d): %d\n", x1, y1, x2, y2, areaPollution);
			printf("Total pets between (%d,%d) and (%d,%d): %d\n", x1, y1, x2, y2, totalPets);
			printf("Total stray dogs between (%d,%d) and (%d,%d): %d\n", x1, y1, x2, y2, totalStrays);
			printf("Total apartments between (%d,%d) and (%d,%d): %d\n", x1, y1, x2, y2, totalApartments);
			printf("Total houses between (%d,%d) and (%d,%d): %d\n", x1, y1, x2, y2, totalHouses);
			printf("Total mansions between (%d,%d) and (%d,%d): %d\n\n", x1, y1, x2, y2, totalMansions);
			areaPopulation = 0;
			areaPollution = 0;
			totalPets = 0;
			totalStrays = 0;
			totalApartments = 0;
			totalHouses = 0;
			totalMansions = 0;

			cout << "Would you like to analyze another area? (Enter y or n): ";
			cin >> choice;
			if (choice != 'y') {
				return;
			}
		} while (true);
	}
	else {
		return;
	}
}
