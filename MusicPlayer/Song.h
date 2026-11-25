#ifndef SONG_H
#define SONG_H
#include "Media.h"

/// @author Leander
/// @date 25.11.2026
/// @brief Concrete class for a song.
///
/// The class represents a song with its interpreter.
class Song : public Media
{
public:
   /// @brief Constructor of a song.
   /// @param[in] title is the title of the song.
   /// @param[in] duration is the duration of the song.
   /// @param[in] interpreter is the name of the interpreter.
   ///
   /// Calls the constructor of a media.
   Song(std::string const& title, size_t const duration, std::string const& interpreter);

   /// @brief Accepts a visitor.
   /// @param[in] visitor is the visitor that visits the song.
   ///
   /// Implements the pure virtual method of class Media.
   void Accept(Visitor& visitor) const override;

private:
   std::string mInterpreter;  ///< Name of the interpreter.
};
#endif //SONG_H
