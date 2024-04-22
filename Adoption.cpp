/*
The Adoption class contains functions of the adoption center cell and objects for the number of
dogs in the shelter, the capacity of the shelter, and the total number of stray dogs. It controls
for moving dogs into the shelter, growing the number of dogs through yearly repopulation, the 
adoption of a pet, and the distrubtion of strays among roads.
*/

#include "Adoption.h"
#include <cstdlib>
#include <ctime>
#include <queue>
#include <algorithm>

Adoption::Adoption() {
	dogsInShelter = MAX_DOGS; //starting at full capacity
	strayDogs = 0;
}

void Adoption::SetDogsInShelter(int dogsInShelter) {
	this->dogsInShelter = dogsInShelter;
}

int Adoption::GetDogsInShelter() {
	return dogsInShelter;
}

int Adoption::GetStrayDogs() {
	return strayDogs;
}

/*
This function allows for the addition of dogs to the shelter, particularly in instances
where the resident downgrades their living space. The dog is added to the shelter if it is
below its maximum capacity, and any overflowing dogs become strays.
*/
void Adoption::AddDogsToShelter(int dogs) {
	if ((dogsInShelter + dogs) <= MAX_DOGS) {
		dogsInShelter += dogs;
	}
	else {
		int newStrayDogs = (dogsInShelter + dogs) - MAX_DOGS;
		strayDogs += newStrayDogs;
		dogsInShelter += (dogs - newStrayDogs);
	}
}

/*
This function repopulates the number of dogs in the shelter for 50% chance rate of one new
puppy per year. There must be at least two dogs present for breeding to occur.
*/
void Adoption::GrowDogsAtRandom() {
	if ((rand() % 2) == 0 && dogsInShelter >= 2 && dogsInShelter < MAX_DOGS) {
		dogsInShelter++;
		//std::cout << "DOG ADDED TO SHELTER" << std::endl;
	}
	else if ((rand() % 2) == 0 && dogsInShelter == MAX_DOGS) {
		strayDogs++;
	}
}

//let's say each time step represents 1 year,
//and each population number represents 100 residents
//moving into this developing city per year,
//of which the People class selected 1 person to represent out of each hundred residents
//currently on the region.
//there is a 45% chance that each selected person will own at least one dog in their household that year
	//source: https://www.statista.com/statistics/517034/households-owning-cats-dogs-europe-romania/


/*
This function is to be called each consecutive time step to allow the chance for
the current residents to adopt a dog. It also controls for the displacement of dogs
whenever a resident has downgraded their living space.
*/
void Adoption::LookToAdoptDog(People& person) {
	if (person.livingChanged) {
		if (person.living == People::mansion) { //dogs they can own: 2
			if (dogsInShelter > 0 && (rand() % 100) < 45) { //upgraded from house
				person.dogs++;
				dogsInShelter--;
			}
		}
		if (person.living == People::house) { //dogs they can own: 1
			if (person.dogs == 2) { //downgraded from mansion
				person.dogs--;
				AddDogsToShelter(1);
			}
			if (person.dogs == 0) //upgraded to house
				if (dogsInShelter > 0 && (rand() % 100) < 45) {
					person.dogs++;
					dogsInShelter--;
				}
			if (person.living == People::apartment) { //dogs they can own: 0
				if (person.dogs == 1) { //downgraded from house
					person.dogs--;
					AddDogsToShelter(1);
				}
			}
		}
		person.livingChanged = false;
		return;
	}
	else if (person.living == People::mansion) {
		if (dogsInShelter > 0 && person.dogs < 2 && (rand() % 100) < 45) {
			person.dogs++;
			dogsInShelter--;
			//std::cout << "PET ADOPTED" << std::endl;
		}
	}
	else if (person.living == People::house) {
		if (dogsInShelter > 0 && person.dogs == 0 && (rand() % 100) < 45) {
			person.dogs++;
			dogsInShelter--;
		}
	}
}


/*
This function provides a breadth-first search to locate nearest Road or
Powerline-Over-Road cell from a given cell with a top cell preference 
going clockwise. If a road isn't found, then a default empty cell will
be returned instead.
*/
Cell* Adoption::FindNearestRoad(Cell* start) {
	queue<Cell*> q;
	vector<Cell*> visited;

	q.push(start);
	visited.push_back(start);

	while (!q.empty()) {
		Cell* current = q.front();
		q.pop();

		if (current->GetType() == Cell::road || current->GetType() == Cell::powerlineOverRoad) {
			return current;
		}

		if (current->GetTopAdj()->GetType() != Cell::empty && find(visited.begin(), visited.end(), current->GetTopAdj()) == visited.end()) {
			q.push(current->GetTopAdj());
			visited.push_back(current->GetTopAdj());
		}
		if (current->GetTopRightAdj()->GetType() != Cell::empty && find(visited.begin(), visited.end(), current->GetTopRightAdj()) == visited.end()) {
			q.push(current->GetTopRightAdj());
			visited.push_back(current->GetTopRightAdj());
		}
		if (current->GetRightAdj()->GetType() != Cell::empty && find(visited.begin(), visited.end(), current->GetRightAdj()) == visited.end()) {
			q.push(current->GetRightAdj());
			visited.push_back(current->GetRightAdj());
		}
		if (current->GetBotRightAdj()->GetType() != Cell::empty && find(visited.begin(), visited.end(), current->GetBotRightAdj()) == visited.end()) {
			q.push(current->GetBotRightAdj());
			visited.push_back(current->GetBotRightAdj());
		}
		if (current->GetBotAdj()->GetType() != Cell::empty && find(visited.begin(), visited.end(), current->GetBotAdj()) == visited.end()) {
			q.push(current->GetBotAdj());
			visited.push_back(current->GetBotAdj());
		}
		if (current->GetBotLeftAdj()->GetType() != Cell::empty && find(visited.begin(), visited.end(), current->GetBotLeftAdj()) == visited.end()) {
			q.push(current->GetBotLeftAdj());
			visited.push_back(current->GetBotLeftAdj());
		}
		if (current->GetLeftAdj()->GetType() != Cell::empty && find(visited.begin(), visited.end(), current->GetLeftAdj()) == visited.end()) {
			q.push(current->GetLeftAdj());
			visited.push_back(current->GetLeftAdj());
		}
		if (current->GetTopLeftAdj()->GetType() != Cell::empty && find(visited.begin(), visited.end(), current->GetTopLeftAdj()) == visited.end()) {
			q.push(current->GetTopLeftAdj());
			visited.push_back(current->GetTopLeftAdj());
		}
	}

	static Cell noRoadsFound;
	return &noRoadsFound;
}

/*
This function takes the out-of-shelter stray dogs available and adds
them to the population of the road nearest the adoption shelter.
*/
void Adoption::AddStraysToRoad(Cell* toShelter, int &regionalStrays) {
	if (strayDogs > 0) {
		FindNearestRoad(toShelter)->SetPopulation(FindNearestRoad(toShelter)->GetPopulation() + strayDogs);
		regionalStrays += strayDogs;
		strayDogs = 0;
	}
}

/*
This function iterates through each cell in the region to target roads with a
population of two or more stray dogs. This population has a 50% chance to grow by
one new puppy per time step. If the targetted cell has more than four strays,
the packs will divide in two and one will leave to the closest road cell with the
lowest population.
*/
void Adoption::GrowStraysAtRandom(vector<vector<Cell>> &region, int &regionalStrays) {
	Cell* lowestPop;
	int travellingStrays;
	for (unsigned int i = 0; i < region.size(); i++) {
		for (unsigned int j = 0; j < region.at(i).size(); j++) {
			if (region.at(i).at(j).GetType() == Cell::road || region.at(i).at(j).GetType() == Cell::powerlineOverRoad) {
				if (region.at(i).at(j).GetPopulation() >= 2) {
					if ((rand() % 2) == 0) {
						region.at(i).at(j).SetPopulation(region.at(i).at(j).GetPopulation() + 1);
						regionalStrays++;
					}
				}
				if (region.at(i).at(j).GetPopulation() >= 4) {
					lowestPop = &(region.at(i).at(j));
					if (region.at(i).at(j).GetTopAdj()->GetPopulation() < lowestPop->GetPopulation() &&
						(region.at(i).at(j).GetTopAdj()->GetType() == Cell::road || region.at(i).at(j).GetTopAdj()->GetType() == Cell::powerlineOverRoad)) {
						lowestPop = region.at(i).at(j).GetTopAdj();
					}
					if (region.at(i).at(j).GetRightAdj()->GetPopulation() < lowestPop->GetPopulation() &&
						(region.at(i).at(j).GetRightAdj()->GetType() == Cell::road || region.at(i).at(j).GetRightAdj()->GetType() == Cell::powerlineOverRoad)) {
						lowestPop = region.at(i).at(j).GetRightAdj();
					}
					if (region.at(i).at(j).GetBotAdj()->GetPopulation() < lowestPop->GetPopulation() &&
						(region.at(i).at(j).GetBotAdj()->GetType() == Cell::road || region.at(i).at(j).GetBotAdj()->GetType() == Cell::powerlineOverRoad)) {
						lowestPop = region.at(i).at(j).GetBotAdj();
					}
					if (region.at(i).at(j).GetLeftAdj()->GetPopulation() < lowestPop->GetPopulation() &&
						(region.at(i).at(j).GetLeftAdj()->GetType() == Cell::road || region.at(i).at(j).GetLeftAdj()->GetType() == Cell::powerlineOverRoad)) {
						lowestPop = region.at(i).at(j).GetLeftAdj();
					}

					if (lowestPop != &(region.at(i).at(j))) {
						travellingStrays = region.at(i).at(j).GetPopulation() / 2;
						region.at(i).at(j).SetPopulation(region.at(i).at(j).GetPopulation() - travellingStrays);
						lowestPop->SetPopulation(lowestPop->GetPopulation() + travellingStrays);
					}
				}
			}
		}
	}
}