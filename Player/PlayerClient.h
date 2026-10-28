#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H
#include "Object.h"
#include "Player.h"

/// @author Julian Rieger
/// @date 27.10.2026
/// @brief Uses a player through the Player interface.
class PlayerClient : public Object
{
public:

   /// @brief Sets the player to use.
   /// @param[in] player is the player to use.
   void SetPlayer(Player& player);

   /// @brief Starts playing.
   void Play();

   /// @brief Increases the volume.
   void VolInc();

   /// @brief Decreases the volume.
   void VolDec();

   /// @brief Stops playing.
   void Stop();

   /// @brief Switches to the next entry.
   void Next();

   /// @brief Switches to the previous entry.
   void Prev();

   /// @brief Selects an entry by its name.
   /// @param[in] name is the name of the entry.
   void Select(std::string const& name);

private:
	Player* mPlayer{ nullptr };

};

#endif //PLAYERCLIENT_H
