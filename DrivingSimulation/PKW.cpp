#include "PKW.h"
#include <cmath>
#include <numbers>
#include <stdexcept>

PKW::PKW(WheelSpeedSensor::UPtr sensor, double wheelDiameter) : mSensor(std::move(sensor)), mWheelDiameter(wheelDiameter) {
    if (mSensor == nullptr) {
        throw std::invalid_argument("Sensor is a null pointer");
    }
    // !(x > 0) also catches NaN, isfinite catches infinity
    if (!(mWheelDiameter > 0.0) || !std::isfinite(mWheelDiameter)) {
        throw std::invalid_argument("Wheel diameter must be a positive finite number");
    }
}

void PKW::Process() {
    mRevolutions = mSensor->GetRevolutions();
    Notify();
}

double PKW::GetCurrentSpeed() const {
    // circumference (m) * revolutions per hour = m/h, divided by 1000 = km/h
    return (mRevolutions * mWheelDiameter * std::numbers::pi * cMinutesPerHour) / cMetersPerKilometer;
}
