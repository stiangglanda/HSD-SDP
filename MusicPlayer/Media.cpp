#include "Media.h"

Media::Media(std::string const& title)
   : mTitle(title)
{
}

std::string const& Media::GetTitle() const
{
   return mTitle;
}

// virtual method should be overriden by derived classes
Media const* Media::GetChild(int const index) const
{
   return nullptr;
}
