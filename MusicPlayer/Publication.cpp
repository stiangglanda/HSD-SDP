#include "Publication.h"

Publication::Publication(std::string const& title, std::string const& interpreter) :
    Media{title},
    mInterpreter(interpreter)
{
}

std::string const& Publication::GetInterpreter() const
{
    return mInterpreter;
}