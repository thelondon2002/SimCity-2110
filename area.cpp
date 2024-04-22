#include "Area.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "Commercial_Class.h"
#include "Industrial_Class.h"
#include "Residential.h"
#include "SimSystem.h"
// Include other necessary headers

using namespace std;

Area::Area(string layoutPath, int time, int refresh) : regionLayout(layoutPath), timeLimit(time), refreshRate(refresh) {}

Area::~Area() {}

void Area::readRegionFile() {
    ifstream file(regionLayout);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << regionLayout << endl;
        return;
    }


  
string line;
while (getline(file, line)) {
    vector<Cell*> row;
    for (char ch : line) {
        for (char ch : line) {
            switch (ch) {
            case 'I': // Assuming 'I' represents an Industrial cell
                row.push_back(new Industrial_Class());
                break;
            case 'C': // Assuming 'C' represents a Commercial cell
                row.push_back(new Commercial_Class());
                break;
                // Handle other cell types
            case 'R': // Assuming 'R' represents a Residential cell
                row.push_back(new Residential());
                break;
            default:
                row.push_back(nullptr); // Empty or unrecognized cell
                break;
            }
        }
        grid.push_back(row);
    }
    file.close();
}


void Area::spreadPollution() {
    // Implementation depends on the specific logic for spreading pollution
    // Placeholder for pollution spreading logic
}

void Area::runTimeStep() {
    // Placeholder for running one time step of the simulation
    spreadPollution();
    // Apply cell growth rules and update populations here
}


void Area::printRegion() {
    for (const auto& row : grid) { // Changed to grid to match the revised readRegionFile method
        for (const auto cell : row) {
            if (cell != nullptr) {
                cout << cell->getSymbol(); // Assuming each Cell class has a getSymbol() method to return its representation
            }
            else {
                cout << " "; // Print a space for empty or unrecognized cells
            }
        }
        cout << endl;
    }
}
