#include <algorithm>
#include <sstream>
#include "Zoo.h"
using namespace std;

Zoo::Zoo(Zoo const& z)
{
   for_each(z.cbegin(), z.cend(), [&](auto ani) {Add(ani->Clone()); });
}

Zoo::~Zoo()
{
   for (auto ani : mAnimals)
   {
      delete ani;
   }
   mAnimals.clear();
}

void Zoo::operator=(Zoo z)
{
   swap(mAnimals, z.mAnimals);
}

void Zoo::Add(Animal const* ani)
{
   if (ani == nullptr) 
      throw invalid_argument{ "null_pointer param in Zoo::Add(...)" };
   mAnimals.push_back(ani);
}

std::string Zoo::ToString() const
{
   ostringstream strStream;
   strStream << "This zoo has " << mAnimals.size() 
             << " animals:" << endl;
   for (auto const ani : mAnimals)
   {
      strStream << ani->ToString();
   }
   return strStream.str();
}

Zoo::CItor Zoo::cbegin() const 
{ 
   return mAnimals.cbegin(); 
}

Zoo::CItor Zoo::cend()   const 
{ 
   return mAnimals.cend(); 
}