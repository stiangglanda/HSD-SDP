#include <iostream>
#include <sstream>
#include "Cat.h"
using namespace std;

Cat::Cat(size_t const w) : Animal{ w }  
{}

void Cat::GiveTongue() const
{
   cout << "miaow" << endl;
}

std::string Cat::ToString() const
{
   ostringstream os;
   os << "ID:" << GetId() << " I'm a cat and " << Animal::ToString();
   return os.str();
}

Animal const* Cat::Clone() const
{
   return new Cat(*this); 
}
