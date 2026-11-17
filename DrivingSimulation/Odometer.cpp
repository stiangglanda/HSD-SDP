#include "Odometer.h"

Odometer::Odometer(const ISpeed& speed, const DisplayClient::SPtr& display) :
    MeterBase(speed, display)
{
    Show(mDistance);
}

void Odometer::Update()
{
    // v = s / t  =>  s = v * t with t = 0.5 s = 1/7200 h
    mDistance += mSpeed.GetCurrentSpeed() * cCycleTimeHours;

    Show(mDistance);
}

double Odometer::GetDistance() const
{
    return mDistance;
}
