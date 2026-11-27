#include <iostream>
#include <memory>
#include <string>
#include "Album.h"
#include "Collection.h"
#include "MusicPlayer.h"
#include "SimpleMediaFactory.h"
#include "Song.h"

/// Counts the failed checks, the result is the return value of main.
static int gFailed = 0;

#define CHECK(cond)                                                          \
   do {                                                                      \
      if (cond) { std::cout << "  [ok]     " #cond "\n"; }                   \
      else { ++gFailed; std::cout << "  [FAILED] " #cond " (line " << __LINE__ << ")\n"; } \
   } while (false)

static void Section(std::string const& title)
{
   std::cout << "\n=== " << title << " ===\n";
}

/// 1. Everything on an empty player must work without a crash.
static void TestEmptyPlayer()
{
   Section("1. Empty player");
   MusicPlayer player;
   player.Play();            // expected: no output
   player.Search("Pride");   // expected: no output
   player.Remove("Pride");   // expected: no output, no crash
   player.Add(nullptr);      // expected: ignored
   player.Play();            // expected: still no output
}

/// 2. A single song directly in the playlist.
static void TestSingleSong()
{
   Section("2. Single song");
   MusicPlayer player;
   SimpleMediaFactory factory;
   player.Add(factory.CreateSong("Imagine", "John Lennon", 183));
   player.Play();            // expected: 1. Imagine << 03:03 << John Lennon
   player.Play();            // expected: the numbering starts at 1 again
}

/// 3. The example from the task. Compare the output with the task sheet.
static void TestExampleFromTask()
{
   Section("3. Example from the task");
   MusicPlayer player;
   SimpleMediaFactory factory;

   auto pride = factory.CreateSong("Pride", "U2", 202);
   auto angel = factory.CreateSong("Angel of Harlem", "U2", 192);
   auto wantYou = factory.CreateSong("All I want is you", "U2", 180);
   auto watchtower = factory.CreateAlbum("All Along the Watchtower", "U2", {pride, angel, wantYou});

   auto highway = factory.CreateSong("Highway to Hell", "AC/DC", 245);
   auto thunder = factory.CreateSong("Thunderstruck", "AC/DC", 200);
   auto runaway = factory.CreateSong("Runaway Train", "AC/DC", 185);
   auto best = factory.CreateAlbum("Best of 2010", "AC/DC", {highway, thunder, runaway});

   auto party = factory.CreateCollection("My own Party Hits", {pride, best});

   CHECK(watchtower->GetNumSongs() == 3);
   CHECK(watchtower->GetDuration() == 574);   // 09:34
   CHECK(best->GetNumSongs() == 3);
   CHECK(best->GetDuration() == 630);         // 10:30
   CHECK(party->GetNumSongs() == 4);          // counts the songs in the album
   CHECK(party->GetDuration() == 832);        // 13:52

   player.Add(watchtower);
   player.Add(best);
   player.Add(party);
   player.Play();   // expected: exactly the output of the task, numbers 1 to 10
}

/// 4. Edge cases of albums.
static void TestAlbums()
{
   Section("4. Albums");
   MusicPlayer player;
   SimpleMediaFactory factory;

   // an album needs at least one song (1..*)
   auto single = factory.CreateSong("Only Song", "Solo", 100);
   auto small = factory.CreateAlbum("One Song Album", "Solo", {single});
   CHECK(small->GetNumSongs() == 1);
   CHECK(small->GetDuration() == 100);

   // the same album twice in the playlist, numbering continues
   player.Add(small);
   player.Add(small);
   player.Play();   // expected: 1. and 2. both "Only Song"

   // album without songs, depends on your decision (exception, assert or empty):
   // auto empty = factory.CreateAlbum("Empty Album", "Nobody", {});
}

/// 5. Edge cases of collections: empty, nested, indentation and numbering.
static void TestCollections()
{
   Section("5. Collections");
   MusicPlayer player;
   SimpleMediaFactory factory;

   auto emptyCollection = factory.CreateCollection("Empty", {});
   CHECK(emptyCollection->GetNumSongs() == 0);
   CHECK(emptyCollection->GetDuration() == 0);
   player.Add(emptyCollection);
   player.Play();   // expected: Collection: Empty (0 Songs) << 00:00

   auto a = factory.CreateSong("Song A", "X", 60);
   auto b = factory.CreateSong("Song B", "Y", 61);
   auto c = factory.CreateSong("Song C", "Z", 62);
   auto album = factory.CreateAlbum("Deep Album", "Y", {b});
   auto inner = factory.CreateCollection("Inner", {album, c});
   auto middle = factory.CreateCollection("Middle", {inner});
   auto outer = factory.CreateCollection("Outer", {a, middle});
   CHECK(outer->GetNumSongs() == 3);
   CHECK(outer->GetDuration() == 183);

   player.Add(outer);
   player.Play();   // expected: indentation grows by 2 for each level, numbers 1 to 3
}

/// 6. Format of the duration.
static void TestDurations()
{
   Section("6. Durations");
   MusicPlayer player;
   SimpleMediaFactory factory;
   player.Add(factory.CreateSong("Zero", "T", 0));        // 00:00
   player.Add(factory.CreateSong("Seconds", "T", 59));    // 00:59
   player.Add(factory.CreateSong("One minute", "T", 60)); // 01:00
   player.Add(factory.CreateSong("Almost hour", "T", 3599)); // 59:59
   player.Add(factory.CreateSong("Long", "T", 6000));     // 100:00 (more than 99 minutes)
   player.Add(factory.CreateSong("", "", 10));            // empty title and interpreter
   player.Play();
}

/// 7. Search: top level, inside albums and collections, no hit, special terms.
static void TestSearch()
{
   Section("7. Search");
   MusicPlayer player;
   SimpleMediaFactory factory;

   auto pride = factory.CreateSong("Pride", "U2", 202);
   auto thunder = factory.CreateSong("Thunderstruck", "AC/DC", 200);
   auto best = factory.CreateAlbum("Best of 2010", "AC/DC", {thunder});
   auto party = factory.CreateCollection("My own Party Hits", {pride, best});
   player.Add(pride);
   player.Add(party);

   std::cout << "-- \"Pride\" (expected: top level song and song in collection)\n";
   player.Search("Pride");
   std::cout << "-- \"Thunder\" (expected: song inside album inside collection, partial hit)\n";
   player.Search("Thunder");
   std::cout << "-- \"Best of 2010\" (expected: the album)\n";
   player.Search("Best of 2010");
   std::cout << "-- \"Party\" (expected: the collection)\n";
   player.Search("Party");
   std::cout << "-- \"Nothing\" (expected: no output)\n";
   player.Search("Nothing");
   std::cout << "-- \"pride\" (lower case, expected: depends on your decision)\n";
   player.Search("pride");
   std::cout << "-- \"\" (empty term, expected: depends on your decision, find() matches everything)\n";
   player.Search("");
   std::cout << "-- \"U2\" (interpreter, expected: only a hit if you search the interpreter too)\n";
   player.Search("U2");
}

/// 8. Remove: top level, in collections, not found, duplicates, albums.
static void TestRemove()
{
   Section("8. Remove");
   MusicPlayer player;
   SimpleMediaFactory factory;

   auto prideTop = factory.CreateSong("Pride", "U2", 202);
   auto prideIn = factory.CreateSong("Pride", "U2", 202);
   auto thunder = factory.CreateSong("Thunderstruck", "AC/DC", 200);
   auto best = factory.CreateAlbum("Best of 2010", "AC/DC", {thunder});
   auto deep = factory.CreateSong("Deep Song", "X", 50);
   auto inner = factory.CreateCollection("Inner", {deep});
   auto party = factory.CreateCollection("Party", {prideIn, best, inner});
   player.Add(prideTop);
   player.Add(party);

   std::cout << "-- start\n";
   player.Play();

   std::cout << "-- Remove(\"Pride\") (expected: only the first one, at top level)\n";
   player.Remove("Pride");
   player.Play();

   std::cout << "-- Remove(\"Pride\") again (expected: now the one in Party)\n";
   player.Remove("Pride");
   player.Play();

   std::cout << "-- Remove(\"Pride\") a third time (expected: nothing happens)\n";
   player.Remove("Pride");
   player.Play();

   std::cout << "-- Remove(\"Thunderstruck\") (expected: still there, a song in an album can not be removed)\n";
   player.Remove("Thunderstruck");
   player.Play();

   std::cout << "-- Remove(\"Deep Song\") (expected: removed from Inner)\n";
   player.Remove("Deep Song");
   player.Play();

   std::cout << "-- Remove(\"Inner\") (expected: the empty collection is removed)\n";
   player.Remove("Inner");
   player.Play();

   std::cout << "-- Remove(\"Best of 2010\") (expected: the whole album is removed)\n";
   player.Remove("Best of 2010");
   player.Play();

   std::cout << "-- Remove(\"Party\") (expected: playlist is empty afterwards)\n";
   player.Remove("Party");
   player.Play();   // expected: no output
   player.Remove("Party");   // expected: no crash on an empty playlist
}

/// 9. A removed medium that is still used somewhere else must stay valid.
static void TestSharedOwnership()
{
   Section("9. Shared ownership");
   MusicPlayer player;
   SimpleMediaFactory factory;

   auto song = factory.CreateSong("Shared", "S", 100);
   auto collection = factory.CreateCollection("Holder", {song});
   player.Add(song);
   player.Add(collection);
   player.Remove("Shared");   // removes only the entry in the playlist
   player.Play();             // expected: the song is still printed inside Holder
   player.Remove("Holder");
   player.Play();             // expected: no output, song object is still valid in main
   CHECK(song->GetDuration() == 100);
}

int main()
{
   TestEmptyPlayer();
   TestSingleSong();
   TestExampleFromTask();
   TestAlbums();
   TestCollections();
   TestDurations();
   TestSearch();
   TestRemove();
   TestSharedOwnership();

   std::cout << "\n" << (gFailed == 0 ? "All checks passed." : "Some checks failed.") << "\n";
   return gFailed == 0 ? 0 : 1;
}