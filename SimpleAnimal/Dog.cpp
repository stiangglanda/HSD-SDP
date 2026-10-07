#include <iostream>
#include <sstream>
#include "Dog.h"
using namespace std;

Dog::Dog(size_t const w) : Animal{ w } 
{}

void Dog::GiveTongue() const
{
   cout << "bark" << endl;
}

std::string Dog::ToString() const
{
   ostringstream os;
   os << "ID:" << GetId() << " I'm a dog and " << Animal::ToString();
   return os.str();
}

Animal const* Dog::Clone() const
{
   return new Dog(*this); 
}
