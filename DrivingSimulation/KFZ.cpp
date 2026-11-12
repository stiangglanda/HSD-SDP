#include "KFZ.h"

void KFZ::Attach(Meter::SPtr meter) {
    if (meter) {
        mMeters.push_back(meter);
    } else {
        throw std::invalid_argument("Meter is a null pointer");
    }
}

void KFZ::Detach(Meter::SPtr meter) {
    std::erase_if(mMeters, [meter](Meter::SPtr m) { return m == meter; });
}

void KFZ::Notify() {
    for (const auto& meter : mMeters) {
        meter->Update();
    }
}
