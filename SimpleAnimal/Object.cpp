#include "Object.h"
#include <sstream>
#include <iostream>
#include "Object.h"

using namespace std;

std::string Object::ToString() const
{
   {
      ostringstream strStream;
      strStream << "object of class 'Object:' " 
                << hex << this << endl;
      return strStream.str();
   }
}
