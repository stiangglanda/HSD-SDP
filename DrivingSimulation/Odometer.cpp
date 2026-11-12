#include "Odometer.h"

Odometer::Odometer(const ISpeed& speed, DisplayClient::SPtr display) :
    MeterBase(speed, display)
{
    mDisplay->SendValue(0);
}

void Odometer::Update()
{
    double const speed = mSpeed.GetCurrentSpeed();
    // v = s / t  =>  s = v * t, t = 0.5 s = 1/7200 h  =>  s = v / 7200
    mDistance += speed / 7200.0;

    mDisplay->SendValue(static_cast<unsigned int>(mDistance));
}