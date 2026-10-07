#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include "Flat.h"

class Floor
{
public:

	void RemoveFlat(size_t num);
	void AddFlat(size_t num, Flat flat);

private:
	size_t mNumber;
	std::vector<Flat> mFlats;
};

#endif FLOOR_H