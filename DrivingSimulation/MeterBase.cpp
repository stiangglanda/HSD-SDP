#include "MeterBase.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

MeterBase::MeterBase(const ISpeed& speed, const DisplayClient::SPtr& display) :
    mSpeed{speed},
    mDisplay{display}
{
    if (mDisplay == nullptr)
    {
        throw std::invalid_argument("Error in MeterBase: cannot handle nullptr display.");
    }
}

void MeterBase::Show(double value) const
{
    constexpr double cMaxValue = std::numeric_limits<unsigned int>::max();

    // a cast of a value outside the range of unsigned int is undefined,
    // so the value is limited first (NaN is shown as 0)
    double shown = 0.0;
    if (!std::isnan(value))
    {
        shown = std::clamp(value, 0.0, cMaxValue);
    }

    mDisplay->SendValue(static_cast<unsigned int>(shown));
}
