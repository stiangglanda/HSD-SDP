#include <sstream>
#include "Animal.h"
using namespace std;
//test 2

size_t Animal::msCounter = 0;

size_t Animal::GetWeight() const
{
   return mWeight;
}

size_t Animal::GetId() const
{
   return mId;
}

std::string Animal::ToString() const
{
   ostringstream os;
   os << "my weight is " << mWeight << endl;
   return os.str();
}

Animal::Animal(size_t const w) : mId{ msCounter++ }
{
   if (w <= 0) {
      throw std::invalid_argument("Weight must be a positive number");
   }
   mWeight = w;
}