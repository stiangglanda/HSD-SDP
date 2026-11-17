#include "KFZ.h"
#include <algorithm>
#include <stdexcept>

void KFZ::Attach(const Meter::SPtr& meter) {
    if (meter == nullptr) {
        throw std::invalid_argument("Meter is a null pointer");
    }

    // a meter is only attached once, otherwise it would be updated twice
    if (std::find(mMeters.cbegin(), mMeters.cend(), meter) == mMeters.cend()) {
        mMeters.push_back(meter);
    }
}

void KFZ::Detach(const Meter::SPtr& meter) {
    std::erase(mMeters, meter);
}

void KFZ::Notify() const {
    for (const auto& meter : mMeters) {
        meter->Update();
    }
}
