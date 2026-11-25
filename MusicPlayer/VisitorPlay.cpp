#include "VisitorPlay.h"
#include <iostream>
#include "Collection.h"
#include "Song.h"
#include "Album.h"

void VisitorPlay::Visit(Collection const& collection)
{
    std::cout << "Playing collection: " << collection.GetTitle() << std::endl;
    std::cout << "Duration: " << collection.GetDuration() << std::endl;
}

void VisitorPlay::Visit(Song const& song)
{
    std::cout << "Playing song: " << song.GetTitle() << std::endl;
    std::cout << "Duration: " << song.GetDuration() << std::endl;
    std::cout << "Interpreter: " << song.GetInterpreter() << std::endl;
}

void VisitorPlay::Visit(Album const& album)
{
    std::cout << "Playing album: " << album.GetTitle() << std::endl;
    std::cout << "Duration: " << album.GetDuration() << std::endl;
    std::cout << "Number of songs: " << album.GetNumSongs() << std::endl;
}
