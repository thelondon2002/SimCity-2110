#include "Industrial.h"
#include "SimSystem.h"
#include "Pollution.h"

Industrial::Industrial() {
    population = 0;
    workers = 0;
    goods = 0;
    dead_workers= 0;
    last_goods = 0;
    timeCounter = 0;
}

void Industrial::SetValues(int population, int workers, int goods, int dead_workers, int last_goods, int timeCounter) {
    this->population = population;
    this->workers = workers;
    this->goods = goods;
    this->dead_workers = dead_workers;
    this->last_goods = last_goods;
    this->timeCounter = timeCounter;
}

int Industrial::GetPopulation() {
    return population;
}

int Industrial::GetWorkers() {
    return workers; 
}

int Industrial::GetGoods() {
    return goods;
}

void Industrial::ResetValues() {
    population = 0;
    workers = 0;
    goods = 0;
}

// Function to check if a cell has at least 2 available workers
bool Industrial::HasEnoughWorkers(int availableWorkers) {
    return availableWorkers >= 2;
}

     // Function to update the industrial cell based on specified conditions
bool Industrial::UpdateIndustrial(Cell& cell, int availableWorkers) {
    population = cell.GetPopulation();
    workers = cell.GetWorkers();

    if (population >= 0 && cell.IsAdjToPowerline() && HasEnoughWorkers(availableWorkers)) {
        population += 1;
        cell.SetPopulation(population);
        workers += 2; // Assign 2 workers to the job
        cell.SetWorkers(workers);
        goods += population; // Each population produces one good
        return true;
    }
    else if (population >= 0 && cell.IsAdjToCellsPopOne() && HasEnoughWorkers(availableWorkers)) {
        population += 1;
        cell.SetPopulation(population);
        workers += 2; // Assign 2 workers to the job
        cell.SetWorkers(workers);
        goods += population; // Each population produces one good
        return true;
    }
    else if (population >= 1 && cell.IsAdjToCellsPopTwoOrMore() && HasEnoughWorkers(availableWorkers)) {
        population += 1;
        cell.SetPopulation(population);
        workers += 2; // Assign 2 workers to the job
        cell.SetWorkers(workers);
        goods += population; // Each population produces one good
        return true;
    }
    else if (population >= 2 && cell.IsAdjToCellsPopFourOrMore() && HasEnoughWorkers(availableWorkers)) {
        population += 1;
        cell.SetPopulation(population);
        workers += 2; // Assign 2 workers to the job
        cell.SetWorkers(workers);
        goods += population; // Each population produces one good
        return true;
    }
        timeCounter++;
        // adding a value to store the goods at the end of this time step so that I can use it next time step
        last_goods = goods;
    // check if the time step is greater than 3
    if (timeCounter < 3)
    {
    // A function to cause worker deaths for every 5 goods added(%5)
            int change_in_goods = goods - last_goods;
            int casualties = change_in_goods % 5; // One death for every 5 goods produced
            dead_workers += casualties;
            workers -= dead_workers; // subtract workers by dead_workers
            cell.SetWorkers(workers);
    }
    return false;
}

int Industrial::GetCasualties() {
    return dead_workers;
}
