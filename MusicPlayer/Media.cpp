#include "Media.h"

Media::Media(std::string const& title, size_t const duration)
   : mTitle(title), mDuration(duration)
{
}

std::string const& Media::GetTitle() const
{
   return mTitle;
}

size_t Media::GetDuration() const
{
   return mDuration;
}

Media const* Media::GetChild(int const index) const
{
   return nullptr;
}
