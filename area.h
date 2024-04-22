#ifndef AREA_H
#define AREA_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;


class Area {
public:
    vector<vector<char>> region;
    string regionLayout;
    int timeLimit;
    int refreshRate;
    Area(int width, int height); // Constructor with city region dimensions
    vector<std::vector<Cell>> cityGrid; // 2D vector to represent the city grid
    int width, height; // Dimensions of the city grid

    
private
    void readRegionFile();
    void spreadPollution();
    void simulateStep();
    void runTimeStep();
    void printRegion();
    void updateSimulation(); // Method for dynamic simulation updates
    void outputInitialState(); // Method to output the initial state of the city region
    // Additional methods for interactions between zones, data collection, error handling, etc.

};

#endif
