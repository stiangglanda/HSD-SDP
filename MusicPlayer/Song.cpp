#include "Song.h"
#include "Visitor.h"

Song::Song(std::string const& title, size_t const duration, std::string const& interpreter)
   : Media(title, duration), mInterpreter(interpreter)
{
}

std::string const& Song::GetInterpreter() const
{
   return mInterpreter;
}

void Song::Accept(Visitor& visitor) const
{
}
