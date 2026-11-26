#include "Collection.h"
#include "Visitor.h"

Collection::Collection(std::string const& title)
   : Media(title)
{
}

void Collection::Play()
{
}

void Collection::Add(Media* media)
{
}

void Collection::Remove(Media* media)
{
}

Media const* Collection::GetChild(int const index) const
{
   return nullptr;
}

void Collection::Accept(Visitor& visitor) const
{
}
