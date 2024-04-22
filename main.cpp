/*
Main calls the methods provided by SimSystem to read in the configuration file,
intitialize the region using the information provided by the file, and print
the initial region state. It then begins the time step sequence and outputs the
final region state upon completion.
*/

#include "SimSystem.h"

int main() {
	SimSystem simSystem;

	simSystem.ReadConfigFile();
	simSystem.InitializeRegion();

	cout << "Initial Region State:" << endl;
	simSystem.PrintRegion();
	simSystem.PrintRegionInfo();
	cout << "Press [enter] to commence time steps." << endl;
	cin.get();

	simSystem.CommenceTimeSteps();

	cout << "Final Region State:" << endl;
	simSystem.PrintRegion();
	simSystem.PrintRegionInfo();

	simSystem.AnalyzeRegionArea();

	cout << "Simulation Complete." << endl;
	return 0;
}