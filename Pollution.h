#ifndef POLLUTION_H
#define POLLUTION_H
#include <iostream>
#include "Cell.h"
#include "SimSystem.h"
#include <vector>

using namespace std;


class PollutionLevels {

private:
    vector<vector<int>> pollutionLevels;
    Cell cell;

public:
    PollutionLevels();
    void InitializePollutionLevels(vector<vector<Cell>>& region);
    void spreadPollution(vector<vector<Cell>> &region);
    int GetPollutionLevel(int row, int column);
    int GetTotalPollution();
};

#endif
