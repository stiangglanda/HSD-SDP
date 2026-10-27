#include "Media.h"

Media::Media(std::string const& name, size_t const dur) : mName(name), mDuration(dur) {

}

const std::string& Media::GetName() const {
    return mName;
}

size_t Media::GetDuration() const {
    return mDuration;
}
