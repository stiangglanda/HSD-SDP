#include "Publication.h"

Publication::Publication(std::string const& title, std::string const& interpreter) :
    Media{title},
    mInterpreter(interpreter)
{
}

std::string Publication::GetInterpreter()
{
    return mInterpreter;
}