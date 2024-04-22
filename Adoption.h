/*
The Adoption class contains functions of the adoption center cell and objects for the number of
dogs in the shelter, the capacity of the shelter, and the total number of stray dogs. It controls
for moving dogs into the shelter, growing the number of dogs through yearly repopulation, the
adoption of a pet, and the distrubtion of strays among roads.
*/

#ifndef ADOPTION_H
#define ADOPTION_H

#include "People.h"
#include "Cell.h"
#include <vector>

class Adoption
{
public:
	Adoption();
	void SetDogsInShelter(int dogsInShelter);
	int GetDogsInShelter();
	int GetStrayDogs();
	void AddDogsToShelter(int dogs);
	void GrowDogsAtRandom();
	void LookToAdoptDog(People& person);
	Cell* FindNearestRoad(Cell* start);
	void AddStraysToRoad(Cell* toShelter, int& regionalDogs);
	void GrowStraysAtRandom(vector<vector<Cell>>& region, int& regionalStrays);

private:
	int dogsInShelter;
	const int MAX_DOGS = 10;
	int strayDogs;
};

#endif