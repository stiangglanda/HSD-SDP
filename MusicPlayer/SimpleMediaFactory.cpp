#include "SimpleMediaFactory.h"
#include "Album.h"
#include "Collection.h"
#include "Song.h"

std::unique_ptr<Media> SimpleMediaFactory::CreateMedia(MediaKind kind, std::string const& title, size_t const duration, std::string const& interpreter) {
    switch (kind) {
        case MediaKind::Song:
            return std::make_unique<Song>(title, duration, interpreter);
        case MediaKind::Album:
            return std::make_unique<Album>(title, duration);
        case MediaKind::Collection:
            return std::make_unique<Collection>(title, duration);
        default:
            return nullptr;
    }
}
