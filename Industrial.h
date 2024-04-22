//
//  Industrial_Class.h

#ifndef INDUSTRIAL_H
#define INDUSTRIAL_H

#include "Cell.h"

class Industrial {

public:
    Industrial();
    void SetValues(int population, int workers, int goods, int dead_workers, int last_goods, int timeCounter);
    void SetValues(int population, int workers, int goods);
    void ResetValues();

    int GetPopulation();
    int GetWorkers();
    int GetGoods();
    int GetCasualties();

    bool UpdateIndustrial(Cell& cell, int availableWorkers);
    bool HasEnoughWorkers(int availableWorkers);
private:
    int population;
    int workers;
    int goods;
    int dead_workers;
    int last_goods;
    int timeCounter;
};

#endif
