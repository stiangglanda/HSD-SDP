#ifndef PUBLICATION_H
#define PUBLICATION_H

#include <string>
#include "Media.h"

/// @author Julian Rieger
/// @date 25.11.2026
/// @brief Abstract class for a publication, parent class of Album and Song.
///
/// The class adds an interpreter to a media.
class Publication : public Media
{
public:
   /// @brief Constructor of a publication.
   /// @param[in] title is the title of the media.
   /// @param[in] interpreter is the name of the interpreter.
   /// @throws std::invalid_argument if the title or the interpreter is empty.
   Publication(std::string const& title, std::string const& interpreter);

   /// @brief Returns the interpreter of the publication.
   /// @returns the interpreter.
   std::string const& GetInterpreter() const;

private:
   std::string mInterpreter;  ///< Name of the interpreter.
};
#endif //PUBLICATION_H
