// Testtreiber MusicPlayer
// Teil 1: Tests aller Klassen inkl. Fehlerfaelle und Grenzwerte
// Teil 2: Demo einer Playlist (Play und Search)

#include <climits>
#include <cstdint>
#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <new>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#ifdef HAVE_VLD
#include <vld.h>
#endif

#include "Album.h"
#include "Collection.h"
#include "MusicPlayer.h"
#include "SimpleMediaFactory.h"
#include "Song.h"
#include "Visitor.h"
#include "VisitorPlay.h"
#include "VisitorSearch.h"

static int sPassed = 0;
static int sFailed = 0;

static void Check(bool const ok, std::string const& text)
{
   if (ok) { ++sPassed; std::cout << "  [OK]     " << text << '\n'; }
   else    { ++sFailed; std::cerr << "  [FAILED] " << text << '\n'; }
}

// prueft, ob f eine Exception vom Typ E wirft
template <typename E, typename F>
static void CheckThrows(F f, std::string const& text)
{
   try { f(); Check(false, text + " (no exception)"); }
   catch (E const& e) { Check(true, text + " -> \"" + e.what() + "\""); }
   catch (std::exception const& e) { Check(false, text + " (wrong exception: " + e.what() + ")"); }
}

template <typename F>
static void CheckNoThrow(F f, std::string const& text)
{
   try { f(); Check(true, text); }
   catch (std::exception const& e) { Check(false, text + " (" + e.what() + ")"); }
}

// faengt alles ab, was f auf std::cout ausgibt
static std::string Capture(std::function<void()> const& f)
{
   std::ostringstream out;
   std::streambuf* const old = std::cout.rdbuf(out.rdbuf());
   try { f(); }
   catch (...) { std::cout.rdbuf(old); throw; }
   std::cout.rdbuf(old);
   return out.str();
}

// vergleicht eine Ausgabe und zeigt bei Abweichung beide Texte an
static void CheckOutput(std::string const& actual, std::string const& expected, std::string const& text)
{
   Check(actual == expected, text);
   if (actual != expected)
   {
      std::cerr << "--- expected ---\n" << expected << "--- actual ---\n" << actual << "---\n";
   }
}

// Visitor fuer die Tests, zaehlt die Aufrufe je Medientyp
class CountingVisitor : public Visitor
{
public:
   void Visit(Collection const&) override { ++collections; }
   void Visit(Song const&) override { ++songs; }
   void Visit(Album const&) override { ++albums; }

   int collections = 0;
   int songs = 0;
   int albums = 0;
};

static SimpleMediaFactory const sFactory;

static std::shared_ptr<Song> MakeSong(std::string const& title, size_t const duration = 60)
{
   return sFactory.CreateSong(title, "Interpreter", duration);
}

static void TestSong()
{
   std::cout << "\n--- Song ---\n";
   auto const song = sFactory.CreateSong("Yesterday", "Beatles", 125);
   Check(song->GetTitle() == "Yesterday", "GetTitle");
   Check(song->GetInterpreter() == "Beatles", "GetInterpreter");
   Check(song->GetDuration() == 125, "GetDuration 125 s");
   Check(MakeSong("Zero", 0)->GetDuration() == 0, "Limit value: duration 0");
   Check(MakeSong("Max", SIZE_MAX)->GetDuration() == SIZE_MAX, "Limit value: duration SIZE_MAX");
   Check(song->GetChild(0) == nullptr, "GetChild(0) of a song -> nullptr");
   Check(song->GetChild(-1) == nullptr, "GetChild(-1) of a song -> nullptr");

   CountingVisitor visitor;
   song->Accept(visitor);
   Check(visitor.songs == 1 && visitor.albums == 0 && visitor.collections == 0, "Accept calls Visit(Song)");

   CheckThrows<std::invalid_argument>([] { sFactory.CreateSong("", "I", 1); }, "Empty title");
   CheckThrows<std::invalid_argument>([] { sFactory.CreateSong("T", "", 1); }, "Empty interpreter");
   CheckNoThrow([] { sFactory.CreateSong(" ", " ", 1); }, "Title and interpreter with only one space are allowed");
}

static void TestAlbum()
{
   std::cout << "\n--- Album ---\n";
   auto const one = sFactory.CreateAlbum("One", "I", {MakeSong("A", 100)});
   Check(one->GetNumSongs() == 1, "Album with 1 song: GetNumSongs 1");
   Check(one->GetDuration() == 100, "Album with 1 song: GetDuration 100");
   Check(one->GetInterpreter() == "I", "GetInterpreter");

   auto const even = sFactory.CreateAlbum("Even", "I", {MakeSong("A", 10), MakeSong("B", 20)});
   Check(even->GetNumSongs() == 2 && even->GetDuration() == 30, "Album with 2 songs (even): 2 songs, 30 s");

   auto const s1 = MakeSong("S1", 1);
   auto const s2 = MakeSong("S2", 2);
   auto const s3 = MakeSong("S3", 3);
   auto const odd = sFactory.CreateAlbum("Odd", "I", {s1, s2, s3});
   Check(odd->GetNumSongs() == 3 && odd->GetDuration() == 6, "Album with 3 songs (odd): 3 songs, 6 s");
   Check(odd->GetChild(0) == s1.get() && odd->GetChild(1) == s2.get() && odd->GetChild(2) == s3.get(),
         "GetChild returns the songs in order");
   Check(odd->GetChild(3) == nullptr, "GetChild(size) -> nullptr");
   Check(odd->GetChild(-1) == nullptr, "GetChild(-1) -> nullptr");
   Check(odd->GetChild(INT_MAX) == nullptr, "GetChild(INT_MAX) -> nullptr");
   Check(odd->GetChild(INT_MIN) == nullptr, "GetChild(INT_MIN) -> nullptr");

   auto const twice = sFactory.CreateAlbum("Twice", "I", {s1, s1});
   Check(twice->GetNumSongs() == 2 && twice->GetDuration() == 2, "Same song twice in an album");
   Check(sFactory.CreateAlbum("Other", "I", {s1})->GetChild(0) == s1.get(), "Same song in a second album");

   CountingVisitor visitor;
   odd->Accept(visitor);
   Check(visitor.albums == 1 && visitor.songs == 0, "Accept calls only Visit(Album)");

   auto const zero = sFactory.CreateAlbum("Zero", "I", {MakeSong("A", 0), MakeSong("B", 0)});
   Check(zero->GetDuration() == 0, "Limit value: songs with duration 0");
   auto const max = sFactory.CreateAlbum("Max", "I", {MakeSong("A", SIZE_MAX), MakeSong("B", 0)});
   Check(max->GetDuration() == SIZE_MAX, "Limit value: total duration exactly SIZE_MAX");

   auto const overflow = sFactory.CreateAlbum("Overflow", "I", {MakeSong("A", SIZE_MAX), MakeSong("B", 1)});
   CheckThrows<std::overflow_error>([&] { overflow->GetDuration(); }, "Total duration greater than SIZE_MAX");
   CheckThrows<std::invalid_argument>([] { sFactory.CreateAlbum("A", "I", {}); }, "Album without songs");
   CheckThrows<std::invalid_argument>([] { sFactory.CreateAlbum("A", "I", {nullptr}); }, "Song is nullptr");
   CheckThrows<std::invalid_argument>([] { sFactory.CreateAlbum("A", "I", {MakeSong("S"), nullptr}); },
                                      "nullptr after a valid song");
   CheckThrows<std::invalid_argument>([] { sFactory.CreateAlbum("", "I", {MakeSong("S")}); }, "Empty title");
   CheckThrows<std::invalid_argument>([] { sFactory.CreateAlbum("A", "", {MakeSong("S")}); }, "Empty interpreter");
}

static void TestCollection()
{
   std::cout << "\n--- Collection ---\n";
   auto const empty = sFactory.CreateCollection("Empty");
   Check(empty->GetTitle() == "Empty", "GetTitle");
   Check(empty->GetNumSongs() == 0, "Empty collection: GetNumSongs 0");
   Check(empty->GetDuration() == 0, "Empty collection: GetDuration 0");
   Check(empty->GetChild(0) == nullptr, "Empty collection: GetChild(0) -> nullptr");
   Check(!empty->Remove("X"), "Remove from empty collection -> false");

   auto const c = sFactory.CreateCollection("C");
   auto const song = MakeSong("Song", 10);
   c->Add(song);
   Check(c->GetNumSongs() == 1 && c->GetDuration() == 10 && c->GetChild(0) == song.get(),
         "Collection with 1 song");

   c->Add(sFactory.CreateAlbum("Album", "I", {MakeSong("A1", 20), MakeSong("A2", 30)}));
   Check(c->GetNumSongs() == 3 && c->GetDuration() == 60, "Songs of an album are counted");

   auto const inner = sFactory.CreateCollection("Inner");
   inner->Add(MakeSong("Deep", 40));
   c->Add(inner);
   Check(c->GetNumSongs() == 4 && c->GetDuration() == 100, "Songs of a nested collection are counted");
   c->Add(sFactory.CreateCollection("EmptyInner"));
   Check(c->GetNumSongs() == 4, "Empty nested collection adds no songs");
   Check(c->GetChild(3) != nullptr && c->GetChild(4) == nullptr, "GetChild after the last media -> nullptr");
   Check(c->GetChild(-1) == nullptr && c->GetChild(INT_MAX) == nullptr && c->GetChild(INT_MIN) == nullptr,
         "GetChild(-1 / INT_MAX / INT_MIN) -> nullptr");

   CountingVisitor visitor;
   c->Accept(visitor);
   Check(visitor.collections == 1 && visitor.songs == 0, "Accept calls only Visit(Collection)");

   auto const other = sFactory.CreateCollection("Other");
   CheckNoThrow([&] { other->Add(song); }, "Same song in a second collection");
   CheckNoThrow([&] { other->Add(inner); }, "Same collection in two collections");

   CheckThrows<std::invalid_argument>([&] { c->Add(nullptr); }, "Add nullptr");
   CheckThrows<std::invalid_argument>([&] { c->Add(c); }, "Add collection to itself");
   CheckThrows<std::invalid_argument>([&] { inner->Add(c); }, "Cycle over one level");
   auto const deep = sFactory.CreateCollection("Deeper");
   inner->Add(deep);
   CheckThrows<std::invalid_argument>([&] { deep->Add(c); }, "Cycle over two levels");
   CheckThrows<std::invalid_argument>([] { sFactory.CreateCollection(""); }, "Empty title");

   std::cout << "  Remove:\n";
   Check(!c->Remove("Missing"), "Remove missing title -> false");
   Check(c->Remove("Song") && c->GetNumSongs() == 3, "Remove song at top level");
   Check(c->Remove("Deep") && inner->GetNumSongs() == 0, "Remove song in nested collection");
   Check(c->Remove("Album") && c->GetNumSongs() == 0, "Remove album");
   Check(!c->Remove("A1"), "Song of an album cannot be removed (album is not a collection)");

   auto const dup = sFactory.CreateCollection("Dup");
   dup->Add(MakeSong("Same", 1));
   dup->Add(MakeSong("Same", 2));
   Check(dup->Remove("Same") && dup->GetDuration() == 2, "Remove removes only the first media with the title");

   auto const overflow = sFactory.CreateCollection("Overflow");
   overflow->Add(MakeSong("A", SIZE_MAX));
   overflow->Add(MakeSong("B", 1));
   CheckThrows<std::overflow_error>([&] { overflow->GetDuration(); }, "Total duration greater than SIZE_MAX");
}

static void TestVisitorPlay()
{
   std::cout << "\n--- VisitorPlay ---\n";
   {
      VisitorPlay visitor;
      std::string const out = Capture([&] { MakeSong("Short", 0)->Accept(visitor); });
      CheckOutput(out, "1. Short << 00:00 << Interpreter\n", "Song with 0 s -> 00:00");
   }
   {
      VisitorPlay visitor;
      std::string const out = Capture([&] { MakeSong("Long", 3599)->Accept(visitor); });
      CheckOutput(out, "1. Long << 59:59 << Interpreter\n", "Song with 3599 s -> 59:59");
   }
   {
      VisitorPlay visitor;
      std::string const out = Capture([&] { MakeSong("Hour", 3600)->Accept(visitor); });
      CheckOutput(out, "1. Hour << 60:00 << Interpreter\n", "Song with 3600 s -> 60:00");
   }
   {
      VisitorPlay visitor;
      std::string const out = Capture([&] { sFactory.CreateCollection("Empty")->Accept(visitor); });
      CheckOutput(out, "Collection: Empty (0 Songs) << 00:00\n", "Empty collection");
   }
   {
      auto const c = sFactory.CreateCollection("Mix");
      c->Add(sFactory.CreateAlbum("Album", "Band", {MakeSong("A", 61), MakeSong("B", 59)}));
      auto const inner = sFactory.CreateCollection("Inner");
      inner->Add(MakeSong("C", 5));
      c->Add(inner);
      c->Add(MakeSong("D", 600));

      VisitorPlay visitor;
      std::string const out = Capture([&] { c->Accept(visitor); });
      CheckOutput(out,
                  "Collection: Mix (4 Songs) << 12:05\n"
                  "  Album: Album (2 Songs) << 02:00\n"
                  "    1. A << 01:01 << Interpreter\n"
                  "    2. B << 00:59 << Interpreter\n"
                  "  Collection: Inner (1 Songs) << 00:05\n"
                  "    3. C << 00:05 << Interpreter\n"
                  "  4. D << 10:00 << Interpreter\n",
                  "Nested collection: indentation, numbering and durations");
   }
}

static void TestVisitorSearch()
{
   std::cout << "\n--- VisitorSearch ---\n";
   auto const c = sFactory.CreateCollection("Rock Classics");
   c->Add(sFactory.CreateAlbum("Rock Album", "Band", {MakeSong("Rock Song"), MakeSong("Ballad")}));
   c->Add(MakeSong("rock lowercase"));

   {
      VisitorSearch visitor{"Rock"};
      CheckOutput(Capture([&] { c->Accept(visitor); }),
                  "Rock Classics\nRock Album\nRock Song\n",
                  "Search finds collection, album and song (case sensitive)");
   }
   {
      VisitorSearch visitor{"Ballad"};
      CheckOutput(Capture([&] { c->Accept(visitor); }), "Ballad\n", "Search finds a song inside an album");
   }
   {
      VisitorSearch visitor{"Jazz"};
      CheckOutput(Capture([&] { c->Accept(visitor); }), "", "No match -> no output");
   }
   {
      VisitorSearch visitor{"Rock Classics and more"};
      CheckOutput(Capture([&] { c->Accept(visitor); }), "", "Search term longer than the titles -> no output");
   }
   CheckThrows<std::invalid_argument>([] { VisitorSearch visitor{""}; }, "Empty search term");
}

static void TestMusicPlayer()
{
   std::cout << "\n--- MusicPlayer ---\n";
   MusicPlayer player;
   CheckOutput(Capture([&] { player.Play(); }), "", "Play with empty playlist -> no output");
   CheckOutput(Capture([&] { player.Search("X"); }), "search for \"X\": found medias:\n",
               "Search with empty playlist -> only the header");
   Check(!player.Remove("X"), "Remove from empty playlist -> false");
   CheckThrows<std::invalid_argument>([&] { player.Add(nullptr); }, "Add nullptr");
   CheckThrows<std::invalid_argument>([&] { player.Search(""); }, "Search with empty search term");

   player.Add(MakeSong("Single", 30));
   CheckOutput(Capture([&] { player.Play(); }), "1. Single << 00:30 << Interpreter\n", "Playlist with 1 song");

   auto const outer = sFactory.CreateCollection("Outer");
   auto const inner = sFactory.CreateCollection("Inner");
   inner->Add(MakeSong("Deep", 5));
   outer->Add(inner);
   player.Add(outer);
   player.Add(sFactory.CreateAlbum("Album", "Band", {MakeSong("Track", 10)}));

   CheckOutput(Capture([&] { player.Play(); }),
               "1. Single << 00:30 << Interpreter\n"
               "Collection: Outer (1 Songs) << 00:05\n"
               "  Collection: Inner (1 Songs) << 00:05\n"
               "    2. Deep << 00:05 << Interpreter\n"
               "Album: Album (1 Songs) << 00:10\n"
               "  3. Track << 00:10 << Interpreter\n",
               "Play numbers songs across the whole playlist");
   CheckOutput(Capture([&] { player.Play(); }).substr(0, 3), "1. ", "Numbering starts again at 1 on every Play");
   CheckOutput(Capture([&] { player.Search("e"); }),
               "search for \"e\": found medias:\nSingle\nOuter\nInner\nDeep\n",
               "Search over the whole playlist");

   Check(!player.Remove("Missing"), "Remove missing title -> false");
   Check(player.Remove("Deep") && inner->GetNumSongs() == 0, "Remove song two levels deep");
   Check(player.Remove("Single"), "Remove song at top level");
   Check(player.Remove("Inner") && outer->GetChild(0) == nullptr, "Remove nested collection");
   Check(!player.Remove("Track"), "Song of an album is not removed");
   Check(player.Remove("Album") && player.Remove("Outer"), "Remove album and collection");
   CheckOutput(Capture([&] { player.Play(); }), "", "Playlist empty after removing everything");
}

static void RunDemo()
{
   std::cout << "\n=== Demo ===\n";
   MusicPlayer player;

   auto const abbey = sFactory.CreateAlbum("Abbey Road", "The Beatles", {
      sFactory.CreateSong("Come Together", "The Beatles", 259),
      sFactory.CreateSong("Something", "The Beatles", 182),
      sFactory.CreateSong("Here Comes the Sun", "The Beatles", 185)});

   auto const favourites = sFactory.CreateCollection("Favourites");
   favourites->Add(sFactory.CreateSong("Bohemian Rhapsody", "Queen", 354));
   favourites->Add(abbey);

   auto const chill = sFactory.CreateCollection("Chill");
   chill->Add(sFactory.CreateSong("Weightless", "Marconi Union", 480));
   favourites->Add(chill);

   player.Add(favourites);
   player.Add(sFactory.CreateSong("Imagine", "John Lennon", 183));

   std::cout << "\nPlay:\n";
   player.Play();
   std::cout << "\nSearch:\n";
   player.Search("Come");
   std::cout << "\nRemove \"Bohemian Rhapsody\" and \"Chill\", then Play:\n";
   player.Remove("Bohemian Rhapsody");
   player.Remove("Chill");
   player.Play();
}

int main()
{
   try
   {
      TestSong();
      TestAlbum();
      TestCollection();
      TestVisitorPlay();
      TestVisitorSearch();
      TestMusicPlayer();

      std::cout << "\n=== Result: " << sPassed << " passed, " << sFailed << " failed ===\n";

      RunDemo();
   }
   catch (std::bad_alloc const& e)
   {
      std::cerr << "Out of memory: " << e.what() << '\n';
      return 1;
   }
   catch (std::exception const& e)
   {
      std::cerr << "Error: " << e.what() << '\n';
      return 1;
   }
   catch (...)
   {
      std::cerr << "Unknown error\n";
      return 1;
   }

   return sFailed == 0 ? 0 : 1;
}
