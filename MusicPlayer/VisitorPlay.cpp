#include "VisitorPlay.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include "Album.h"
#include "Collection.h"
#include "Song.h"

namespace
{
   size_t const cSecondsPerMinute = 60;  // seconds of one minute
   size_t const cIndentWidth = 2;        // spaces per nesting level
   int const cTimeFieldWidth = 2;        // digits of minutes and seconds
   char const cTimeFill = '0';           // fill character for mm:ss
}

std::string VisitorPlay::FormatDuration(size_t const seconds)
{
   std::ostringstream out;
   out << std::setfill(cTimeFill) << std::setw(cTimeFieldWidth) << seconds / cSecondsPerMinute
       << ':' << std::setw(cTimeFieldWidth) << seconds % cSecondsPerMinute;
   return out.str();
}

std::string VisitorPlay::Indent() const
{
   return std::string(cIndentWidth * mLevel, ' ');
}

void VisitorPlay::Visit(Collection const& collection)
{
   std::cout << Indent() << "Collection: " << collection.GetTitle()
             << " (" << collection.GetNumSongs() << " Songs) << "
             << FormatDuration(collection.GetDuration()) << '\n';

   ++mLevel;
   for (int i = 0; collection.GetChild(i) != nullptr; ++i)
   {
      collection.GetChild(i)->Accept(*this);
   }
   --mLevel;
}

void VisitorPlay::Visit(Album const& album)
{
   std::cout << Indent() << "Album: " << album.GetTitle()
             << " (" << album.GetNumSongs() << " Songs) << "
             << FormatDuration(album.GetDuration()) << '\n';

   ++mLevel;
   for (int i = 0; album.GetChild(i) != nullptr; ++i)
   {
      album.GetChild(i)->Accept(*this);
   }
   --mLevel;
}

void VisitorPlay::Visit(Song const& song)
{
   ++mSongCounter;
   std::cout << Indent() << mSongCounter << ". "
             << song.GetTitle()
             << " << " << FormatDuration(song.GetDuration())
             << " << " << song.GetInterpreter() << '\n';
}
