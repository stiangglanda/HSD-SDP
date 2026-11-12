#include "PKW.h"
#include <numbers>
#include <stdexcept>

PKW::PKW(WheelSpeedSensor::UPtr sensor, double wheelDiameter) : mSensor(std::move(sensor)), mWheelDiameter(wheelDiameter) {
    if (!mSensor) {
        throw std::invalid_argument("Sensor is a null pointer");
    }
    if (mWheelDiameter <= 0) {
        throw std::invalid_argument("Wheel diameter must be positive");
    }
}

void PKW::Process() {
    mRevolutions = mSensor->GetRevolutions();
    Notify();
}

double PKW::GetCurrentSpeed() const {
    return (mSensor->GetRevolutions() * mWheelDiameter * std::numbers::pi * 60) / 1000.0;
}
