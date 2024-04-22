#ifndef FARM_H
#define FARM_H

#include "Cell.h"
#include "Commercial.h"
#include <vector>



class Cell;
class Commercial;

class Farm {
public:
    enum class WeatherCondition { DEFAULT, SUNNY, RAIN, SNOW };
  

    Farm(); // Constructor

    void ProduceFood(Commercial& commerce); // Produce food based on crop yield and type
    void SetWeatherCondition(); // Setter for weather condition
    WeatherCondition GetWeatherCondition();
    void PrintWeatherCondition();
    int GetFood() const;
    int GetCrops() const;

private:
    WeatherCondition weatherCondition; // Default weather condition
    int food;
    int crops;
};

#endif
