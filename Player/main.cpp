/// @mainpage Player Adapter Test Driver
/// @brief Test driver for verifying the Player Adapter Pattern implementation with assertions.
/// 
/// Tests the direct usage of VideoPlayer and MusicPlayer, as well as their
/// unified access through the PlayerClient using the Adapter Pattern (VideoAdapter
/// and MusicAdapter). Additionally, edge cases such as empty playlists and
/// uninitialized client pointers are verified via assertions.
/// 
/// @author Leander Kieweg, Julian Rieger
/// @date 28.10.2026
/// @version 1.1

#include <iostream>
#include <string>
#include <cassert>
#include "PlayerClient.h"
#include "VideoAdapter.h"
#include "MusicAdapter.h"
#include "VideoPlayer.h"
#include "MusicPlayer.h"

/// @brief Tests the VideoPlayer directly and asserts expected states.
static void TestVideoPlayer()
{
    std::cout << "--- VideoPlayer ---" << std::endl;
    VideoPlayer player;

    player.Add("Video1", 120, VideoFormat::WMV);
    player.Add("Video2", 90, VideoFormat::AVI);
    player.Add("Video3", 200, VideoFormat::MKV);

    player.SetVolume(5);
    assert(player.GetVolume() == 5); // Prüfung: Lautstärke korrekt gesetzt?
    std::cout << "Volume verified: " << player.GetVolume() << std::endl;

    bool hasFirst = player.First();
    assert(hasFirst == true); // Prüfung: Playlist ist nicht leer

    size_t expectedIndex = 0;
    do
    {
        assert(player.ActIndex() == expectedIndex); // Prüfung: Index-Ablauf stimmt
        std::cout << "Index " << player.ActIndex() << ": " << player.ActVideo() << std::endl;
        player.Play();
        expectedIndex++;
    } while (player.Next());

    assert(player.ActIndex() == 2); // Prüfung: Am Ende des Vectors angelangt
    player.Stop();

    std::cout << "[SUCCESS] VideoPlayer passed" << std::endl << std::endl;
}

/// @brief Tests the MusicPlayer directly and asserts expected states.
static void TestMusicPlayer()
{
    std::cout << "--- MusicPlayer ---" << std::endl;
    MusicPlayer player;

    player.Add("Song1", 180);
    player.Add("Song2", 210);
    player.Add("Song3", 150);
    assert(player.GetCount() == 3); // Prüfung: Anzahl der Songs korrekt
    std::cout << "Count verified: " << player.GetCount() << std::endl;

    player.IncreaseVol(3);
    player.DecreaseVol(1);

    player.Start();
    assert(player.GetActIndex() == 0); // Prüfung: Startindex ist 0

    player.SwitchNext();
    assert(player.GetActIndex() == 1); // Prüfung: Wechsel auf Index 1 erfolgreich
    std::cout << "Index verified: " << player.GetActIndex() << std::endl;

    assert(player.Find("Song3") == true);  // Prüfung: Vorhandener Song gefunden
    assert(player.Find("Song9") == false); // Prüfung: Nicht vorhandener Song liefert false

    player.Stop();
    std::cout << "[SUCCESS] MusicPlayer passed" << std::endl << std::endl;
}

/// @brief Tests both adapters through the PlayerClient.
static void TestAdapters()
{
    PlayerClient client;

    std::cout << "--- VideoAdapter via Client ---" << std::endl;
    VideoPlayer videoPlayer;
    videoPlayer.Add("Video1", 120, VideoFormat::WMV);
    videoPlayer.Add("Video2", 90, VideoFormat::AVI);
    videoPlayer.Add("Video3", 200, VideoFormat::MKV);

    VideoAdapter videoAdapter(videoPlayer);
    client.SetPlayer(videoAdapter);

    client.Play();
    client.VolInc();
    client.Next();
    client.Play();
    client.Prev();
    client.Play();
    client.Select("Video3");
    client.Select("NonExisting");
    client.Stop();

    std::cout << "--- MusicAdapter via Client ---" << std::endl;
    MusicPlayer musicPlayer;
    musicPlayer.Add("Song1", 180);
    musicPlayer.Add("Song2", 210);
    musicPlayer.Add("Song3", 150);

    MusicAdapter musicAdapter(musicPlayer);
    client.SetPlayer(musicAdapter);

    client.Play();
    client.VolDec();
    client.Next();
    client.Play();
    client.Prev();
    client.Play();
    client.Select("Song2");
    client.Select("NonExisting");
    client.Stop();

    std::cout << "[SUCCESS] Adapters passed" << std::endl << std::endl;
}

/// @brief Tests edge cases like nullptr handling and empty playlists with assertions.
static void TestEdgeCases()
{
    std::cout << "--- Edge Cases ---" << std::endl;

    // Test uninitialized client pointer (should not crash)
    PlayerClient emptyClient;
    emptyClient.Play();

    // Test empty VideoPlayer behavior
    VideoPlayer emptyVideoPlayer;
    emptyVideoPlayer.Play();
    assert(emptyVideoPlayer.First() == false); // Prüfung: Leere Playlist gibt false zurück

    // Test empty MusicPlayer behavior
    MusicPlayer emptyMusicPlayer;
    emptyMusicPlayer.Start();
    assert(emptyMusicPlayer.GetCount() == 0); // Prüfung: Zähler ist 0

    std::cout << "[SUCCESS] EdgeCases passed" << std::endl << std::endl;
}

int main()
{
    TestVideoPlayer();
    TestMusicPlayer();
    TestAdapters();
    TestEdgeCases();

    std::cout << "All tests successfully executed and verified!" << std::endl;
    return 0;
}