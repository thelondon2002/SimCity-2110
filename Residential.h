#ifndef RESIDENTIAL_H
#define RESIDENTIAL_H

#include "Cell.h"

class Residential {

public:

    Residential();  // Constructor
    void SetValues(int population, int workers);
    void ResetValues();
    int GetPopulation();
    int GetWorkers();
    void LivingSpace(People* person, int timeCounter);

    bool UpdateResidential(Cell& cell); // Update residential

private:
    int population;
    int workers;
    int apartments;
    int houses;
    int mansions;

};

#endif
