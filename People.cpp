/*
The People class contains objects to track the living space of a person (apartment, suburban
home, or mansion-like house) and the number of dogs they own. This class controls for movement
between living space types.
*/

#include "People.h"

People::People() {
	dogs = 0;
	living = house;
	livingChanged = false;
}

void People::SetLiving(Living living) {
	this->living = living;
}

/*
If upgraded from an apartment, the resident will move into a suburban house.
If upgraded from a suburban house, the resident will move into a mansion-like living
(which could also just be any upper-class home).
*/
void People::UpgradeLiving() {
	if (living == apartment) {
		living = house;
		livingChanged = true;
	}
	else if (living == house) {
		living = mansion;
		livingChanged = true;
	}
}

/*
If downgraded from a mansion-like living space, the resident will move into a suburban
home. If downgraded from a suburban home, the resident will move into an apartment.
*/
void People::DowngradeLiving() {
	if (living == mansion) {
		living = house;
		livingChanged = true;
	}
	else if (living == house) {
		living = apartment;
		livingChanged = true;
	}
}
