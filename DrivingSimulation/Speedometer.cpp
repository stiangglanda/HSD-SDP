#include "Speedometer.h"

Speedometer::Speedometer(const ISpeed& speed, const DisplayClient::SPtr& display) :
    MeterBase(speed, display)
{
    Update();
}

void Speedometer::Update()
{
    Show(mSpeed.GetCurrentSpeed());
}
