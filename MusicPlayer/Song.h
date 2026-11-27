#ifndef SONG_H
#define SONG_H
#include <cstddef>
#include <string>

#include "Publication.h"

/// @author Julian Rieger
/// @date 25.11.2026
/// @brief Concrete class for a song.
///
/// The class represents a song with its interpreter and duration.
class Song : public Publication
{
public:
   /// @brief Constructor of a song.
   /// @param[in] title is the title of the song.
   /// @param[in] interpreter is the name of the interpreter.
   /// @param[in] duration is the duration of the song in seconds.
   /// @throws std::invalid_argument if the title or the interpreter is empty.
   Song(std::string const& title, std::string const& interpreter, size_t const duration);

   /// @brief Returns the duration of the song.
   /// @returns the duration in seconds.
   ///
   /// Implements the pure virtual method of class Media.
   size_t GetDuration() const override;

   /// @brief Accepts a visitor.
   /// @param[in] visitor is the visitor that visits the song.
   ///
   /// Implements the pure virtual method of class Media.
   void Accept(Visitor& visitor) const override;

private:
   size_t mDuration;  ///< Duration of the song in seconds.
};
#endif //SONG_H
