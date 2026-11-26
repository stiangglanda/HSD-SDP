#include "SimpleMediaFactory.h"
#include "Album.h"
#include "Collection.h"
#include "Song.h"

std::shared_ptr<Song> SimpleMediaFactory::CreateSong(std::string const &title, std::string const &interpreter,
    size_t const duration) {
    return std::make_shared<Song>(title, interpreter, duration);
}

std::shared_ptr<Album> SimpleMediaFactory::CreateAlbum(std::string const &title,
    std::vector<std::shared_ptr<Song>> songs) {
    return std::make_shared<Album>(title, songs);
}

std::shared_ptr<Collection> SimpleMediaFactory::CreateCollection(std::string const &title,
    std::vector<std::shared_ptr<Media>> medias) {
    return std::make_shared<Collection>(title, medias);
}
