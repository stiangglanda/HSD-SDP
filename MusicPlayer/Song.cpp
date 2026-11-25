#include "Song.h"
#include "Visitor.h"

Song::Song(std::string const& title, size_t const duration, std::string const& interpreter)
   : Media(title, duration), mInterpreter(interpreter)
{
}

void Song::Accept(Visitor& visitor) const
{
}
