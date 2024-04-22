/*
The People class contains objects to track the living space of a person (apartment, suburban
home, or mansion-like house) and the number of dogs they own. This class controls for movement
between living space types.
*/

#ifndef PEOPLE_H
#define PEOPLE_H

class People
{
public:
	People();
	void SetLiving(Living living);
	void UpgradeLiving();
	void DowngradeLiving();

	enum Living { apartment, house, mansion };
	Living living;
	bool livingChanged;
	int dogs;
};

#endif
