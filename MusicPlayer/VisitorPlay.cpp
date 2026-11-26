#include "VisitorPlay.h"
#include <iostream>
#include "Collection.h"
#include "Song.h"
#include "Album.h"
#include <iomanip>
#include <sstream>

std::string VisitorPlay::FormatDuration(size_t const seconds)
{
    std::ostringstream out;
    out << std::setfill('0') << std::setw(2) << seconds / 60
        << ':' << std::setw(2) << seconds % 60;
    return out.str();
}

void VisitorPlay::Visit(Collection const& collection)
{
    std::cout << std::string(2 * mLevel, ' ') << "Collection: " << collection.GetTitle()
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
    std::cout << std::string(2 * mLevel, ' ') << "Album: " << album.GetTitle()
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
    std::cout << std::setw(static_cast<int>(2 * mLevel + 1)) << mSongCounter << ". "
              << song.GetTitle()
              << " << " << FormatDuration(song.GetDuration())
              << " << " << song.GetInterpreter() << '\n';
}
