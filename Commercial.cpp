#include "Commercial.h"
#include <cstdlib>
#include <ctime>

Commercial::Commercial() {
    population = 0;
    workers = 0;
    goods = 0;
    crops = 0;
    food = 0;
}

Commercial::~Commercial() {
}

int Commercial::GetCrops() {
    return crops;
}

int Commercial::GetFood() {
    return food;
}

void Commercial::AddCrops(int amount) {
    crops += amount;
}

void Commercial::AddFood(int amount) {
    food += amount;
}

void Commercial::SetValues(int population, int workers, int goods) {
    this->population = population;
    this->workers = workers;
    this->goods = goods;
}

void Commercial::ResetValues() {
    population = 0;
    workers = 0;
    goods = 0;
}

int Commercial::GetPopulation() {
    return population;
}

int Commercial::GetWorkers() {
    return workers;
}

int Commercial::GetGoods() {
    return goods;
}

bool Commercial::HasEnoughWorkers(int availableWorkers) {
	return availableWorkers >= 1;
}

bool Commercial::HasEnoughGoods(int availableGoods) {
	return availableGoods > 1;
}

bool Commercial::UpdateCommercial(Cell& cell, Farm& farm,  int availableWorkers, int availableGoods) {
    population = cell.GetPopulation();
    workers = cell.GetWorkers();
    goods = cell.GetGoods();

    if (population >= 0 && cell.IsAdjToPowerline() && HasEnoughWorkers(availableWorkers) && HasEnoughGoods(availableGoods)) {
        population += 1;
        cell.SetPopulation(population);
        workers += 1;
        cell.SetWorkers(workers);
        goods += 1;
        AddCrops(1); // Add 1 crop
        AddFood(1);
        farm.ProduceFood(*this);
        food = farm.GetFood(); // Update food with produced food from farm
        crops = farm.GetCrops();        
        cell.SetGoods(goods);
        return true;

    }
    else if (population >= 0 && cell.IsAdjToCellsPopOne() && HasEnoughWorkers(availableWorkers) && HasEnoughGoods(availableGoods)) {
        population += 1;
        cell.SetPopulation(population);
        workers += 1;
        cell.SetWorkers(workers);
        goods += 1;
        AddCrops(1); // Add 1 crop
        AddFood(1);
        farm.ProduceFood(*this);
        food = farm.GetFood(); // Update food with produced food from farm
        crops = farm.GetCrops();        
        cell.SetGoods(goods);
        return true;

    }
    else if (population >= 1 && cell.IsAdjToCellsPopTwoOrMore() && HasEnoughWorkers(availableWorkers) && HasEnoughGoods(availableGoods)) {
        population += 1;
        cell.SetPopulation(population);
        workers += 1;
        cell.SetWorkers(workers);
        goods += 1;
        AddCrops(1); // Add 1 crop
        AddFood(1);
        farm.ProduceFood(*this);
        food = farm.GetFood(); // Update food with produced food from farm
        crops = farm.GetCrops();        
        cell.SetGoods(goods);
        return true;
     }
     return false;
}
