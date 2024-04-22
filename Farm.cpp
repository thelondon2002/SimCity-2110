#include <iostream>
#include <algorithm>
#include "Farm.h"
#include "Cell.h"
#include <random>
#include "Commercial.h"
using namespace std;

/// Constructor
Farm::Farm() : weatherCondition(WeatherCondition::DEFAULT), crops(0), food(0) {
    
}

void Farm::SetWeatherCondition() {

    srand(time(nullptr));

    int randomNum = rand() % 100;

// Determine weather condition based on random number
    if (randomNum < 50) {
        weatherCondition = WeatherCondition::DEFAULT;
    } else if (randomNum < 75) {
        weatherCondition = WeatherCondition::SUNNY;
    } else if (randomNum < 90) {
        weatherCondition = WeatherCondition::RAIN;
    } else {
        weatherCondition = WeatherCondition::SNOW;
    }
}

// Get current weather condition
Farm::WeatherCondition Farm::GetWeatherCondition() {
    return weatherCondition;
}

// Print current weather condition
void Farm::PrintWeatherCondition() {
    string weatherString;
    switch (weatherCondition) {
        case WeatherCondition::DEFAULT:
            weatherString = "Average Day Outside.";
            break;
        case WeatherCondition::SUNNY:
            weatherString = "It's sunny with clear skies.";
            break;
        case WeatherCondition::RAIN:
            weatherString = "It's raining heavily.";
            break;
        case WeatherCondition::SNOW:
            weatherString = "It's snowing heavily.";
            break;
        default:
            weatherString = "Unknown";
            break;
    }
    cout << "Weather Condition: " << weatherString << endl;
}


// Produce food based on weather conditions
void Farm::ProduceFood(Commercial& commerce) {
    int producedFood = commerce.GetGoods();
    switch (weatherCondition) {
        case WeatherCondition::RAIN:
            producedFood = crops / 7; 
            break;
        case WeatherCondition::SNOW:
            producedFood = crops / 10;
            break;
        case WeatherCondition::SUNNY:
            producedFood = crops / 3; 
            break;
        case WeatherCondition::DEFAULT:
        default:
            break;
    }
    food += producedFood;



    crops += 1;
}

int Farm::GetFood() const {
    return food;
}

int Farm::GetCrops() const {
    return crops;
}

