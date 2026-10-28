#include <iostream>
#include "PlayerClient.h"
#include "VideoAdapter.h"
#include "MusicAdapter.h"
#include "VideoPlayer.h"
#include "MusicPlayer.h"

/// @brief Tests the VideoPlayer directly.
static void TestVideoPlayer()
{
   std::cout << "--- VideoPlayer ---" << std::endl;
   VideoPlayer player;

   player.Add("Video1", 120, VideoFormat::MP4);
   player.Add("Video2", 90, VideoFormat::AVI);
   player.Add("Video3", 200, VideoFormat::MKV);

   player.SetVolume(5);
   std::cout << "Volume: " << player.GetVolume() << std::endl;

   if (player.First())
   {
      do
      {
         std::cout << "Index " << player.ActIndex() << ": " << player.ActVideo() << std::endl;
         player.Play();
      } while (player.Next());
   }
   player.Stop();
}

/// @brief Tests the MusicPlayer directly.
static void TestMusicPlayer()
{
   std::cout << "--- MusicPlayer ---" << std::endl;
   MusicPlayer player;

   player.Add("Song1", 180);
   player.Add("Song2", 210);
   player.Add("Song3", 150);
   std::cout << "Count: " << player.GetCount() << std::endl;

   player.IncreaseVol(3);
   player.DecreaseVol(1);

   player.Start();
   std::cout << "Index: " << player.GetActIndex() << std::endl;
   player.SwitchNext();
   std::cout << "Index: " << player.GetActIndex() << std::endl;

   std::cout << "Find Song3: " << (player.Find("Song3") ? "yes" : "no") << std::endl;
   std::cout << "Find Song9: " << (player.Find("Song9") ? "yes" : "no") << std::endl;
   player.Stop();
}

/// @brief Tests all functions of the player of a client.
/// @param[in] client is the client to test.
static void TestClient(PlayerClient& client)
{
   client.Play();
   client.VolInc();
   client.VolDec();
   client.Next();
   client.Prev();
   client.Select("Test");
   client.Stop();
}

/// @brief Tests both adapters through the PlayerClient.
static void TestAdapters()
{
   PlayerClient client;

   std::cout << "--- VideoAdapter ---" << std::endl;
   VideoAdapter videoAdapter;
   client.SetPlayer(&videoAdapter);

   std::cout << "--- MusicAdapter ---" << std::endl;
   MusicAdapter musicAdapter;
   client.SetPlayer(&musicAdapter);
}

int main()
{
   TestVideoPlayer();
   TestMusicPlayer();
   TestAdapters();
   return 0;
}