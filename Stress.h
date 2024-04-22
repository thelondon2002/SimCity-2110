#ifndef STRESS_H
#define STRESS_H
#include "SimSystem.h"
#include "Industrial.h"
#include "Cell.h"
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;


class Stress {
private:
    vector<vector<int>> stress;
    Cell cell;
    bool workersStrike;
    int randomNum;

public:
    int GenerateRandomNumber();
    void StressAccumulation(vector<vector<Cell>>& region);
    void InitializeStress(vector<vector<Cell>>& region);
    void Strike(vector<vector<Cell>>& region, int row, int column);
    int GetStress(int row, int column);
    int GetTotalStress();
};
#endif
