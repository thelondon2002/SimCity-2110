#ifndef COMMERCIAL_H
#define COMMERCIAL_H

#include "Cell.h"
#include "Farm.h"
#include <iostream>

class Cell;
class Farm;


class Commercial {
private:
    int goods;
    int population;
    int workers;
    int crops;
    int food;


public:

    Commercial(); // Default Constructor
    ~Commercial();
    void SetValues(int population, int workers, int goods);
    void ResetValues();
    int GetPopulation();
    int GetWorkers();
    int GetGoods();
    int GetCrops();
    int GetFood();
    void AddCrops(int amount);
    void AddFood(int amount);
    bool UpdateCommercial(Cell& cell, Farm& farm, int availableWorkers, int availableGoods); // Updates Commercial
    //Bool Functions to check if there are available workers/goods.
    bool HasEnoughWorkers(int availableWorkers);
    bool HasEnoughGoods(int availableGoods);
};

#endif
