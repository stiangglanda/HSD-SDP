#include "Publication.h"
#include <stdexcept>

Publication::Publication(std::string const& title, std::string const& interpreter) :
   Media{title},
   mInterpreter(interpreter)
{
   if (mInterpreter.empty())
   {
      throw std::invalid_argument("Interpreter must not be empty");
   }
}

std::string const& Publication::GetInterpreter() const
{
   return mInterpreter;
}
