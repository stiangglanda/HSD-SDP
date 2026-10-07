#ifndef HOUSE_H
#define HOUSE_H

#include "Floor.h"

class House
{
public:
private:
	std::vector<Floor> mFloors;
	std::string mZip;
	std::string mAddress;
};

#endif HOUSE_H