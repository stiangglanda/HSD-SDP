#include "MusicPlayer.h"

int main()
{
   MusicPlayer player;
   SimpleMediaFactory factory;
   auto song = factory.CreateSong("Song Title", "Interpreter", 180);
   auto album = factory.CreateAlbum("Album Title", "Interpreter", {song});
   player.Add(album);
   player.Play();

   return 0;
}
