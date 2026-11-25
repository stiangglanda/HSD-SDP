#include "Media.h"

Media::Media(std::string const& title, size_t const duration)
   : mTitle(title), mDuration(duration)
{
}

Media const* Media::GetChild(int const index) const
{
   return nullptr;
}
