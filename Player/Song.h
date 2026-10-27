#ifndef SONG_H
#define SONG_H
#include "Media.h"

/// @author Leander Kieweg
/// @date 27.10.2026
/// @brief A song with a name and a duration.
class Song : public Media
{
public:
   /// @brief Creates a song.
   /// @param[in] name is the name of the song.
   /// @param[in] dur is the duration of the song.
   Song(std::string const& name, size_t const dur);
};

#endif //SONG_H
