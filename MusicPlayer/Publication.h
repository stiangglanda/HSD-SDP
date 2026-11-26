#ifndef PUBLICATION_H
#define PUBLICATION_H

#include "Media.h"

/// @author Julian Rieger
/// @date 25.11.2026
/// @brief Class Publication, parent class of Album and Song
///
///
class Publication : public Media
{
public:

   /// @brief Constructor.
   /// @param[in] interpreter sets mInterpreter, member of Publication.
   /// @param[in] title is the title of the media.
   Publication(std::string const& title, std::string const& interpreter);

   /// @brief Returns the interpreter of the publication.
   /// @returns the interpreter.
   std::string const& GetInterpreter() const;

private:

    std::string mInterpreter;  ///< Name of the interpreter.
};
#endif //PUBLICATION_H
