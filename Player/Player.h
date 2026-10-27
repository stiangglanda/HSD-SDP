#ifndef PLAYER_H
#define PLAYER_H
#include <string>

/// @author Leander Kieweg
/// @date 27.10.2026
/// @brief Interface for all players.
class Player
{
public:
   /// @brief Destroys the player.
   virtual ~Player() = default;

   /// @brief Starts playing.
   virtual void Play() = 0;

   /// @brief Increases the volume.
   virtual void VolInc() = 0;

   /// @brief Decreases the volume.
   virtual void VolDec() = 0;

   /// @brief Stops playing.
   virtual void Stop() = 0;

   /// @brief Switches to the next entry.
   virtual void Next() = 0;

   /// @brief Switches to the previous entry.
   virtual void Prev() = 0;

   /// @brief Selects an entry by its name.
   /// @param[in] name is the name of the entry.
   virtual void Select(std::string const& name) = 0;
};

#endif //PLAYER_H
