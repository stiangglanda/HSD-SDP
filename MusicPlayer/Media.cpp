#include "Media.h"
#include <limits>
#include <stdexcept>

Media::Media(std::string const& title)
   : mTitle(title)
{
   if (mTitle.empty())
   {
      throw std::invalid_argument("Title must not be empty");
   }
}

std::string const& Media::GetTitle() const
{
   return mTitle;
}

// virtual method should be overriden by derived classes with children
Media const* Media::GetChild(int const /*index*/) const
{
   return nullptr;
}

size_t Media::AddDuration(size_t const a, size_t const b)
{
   if (a > std::numeric_limits<size_t>::max() - b)
   {
      throw std::overflow_error("Duration is too large");
   }
   return a + b;
}
