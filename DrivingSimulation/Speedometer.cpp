#include "Speedometer.h"

Speedometer::Speedometer(const ISpeed& speed, DisplayClient::SPtr display) :
    MeterBase(speed, display)
{
    Update();
}

void Speedometer::Update()
{
    double const speed = mSpeed.GetCurrentSpeed();

    mDisplay->SendValue(static_cast<unsigned int>(speed));
}