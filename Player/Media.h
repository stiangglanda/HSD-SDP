#ifndef MEDIA_H
#define MEDIA_H
#include <cstddef>
#include <string>
#include "Object.h"

/// @author Leander Kieweg
/// @date 27.10.2026
/// @brief Abstract base class of all media with a name and a duration.
class Media : public Object
{
public:
   /// @brief Name Getter
   /// @returns the Name
   const std::string& GetName() const;

   /// @brief Duration Getter
   /// @returns the Duration
   size_t GetDuration() const;

protected:
   /// @brief Creates a media.
   /// @param[in] name is the name of the media.
   /// @param[in] dur is the duration of the media.
   Media(std::string const& name, size_t const dur);

private:
   std::string mName;
   size_t mDuration;
};

#endif //MEDIA_H
