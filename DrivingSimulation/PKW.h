#ifndef PKW_H
#define PKW_H

#include "KFZ.h"
#include "ISpeed.h"
#include "WheelSpeedSensor.h"

/// @author Leander Kieweg
/// @date 12.11.2026
/// @brief A passenger car that gets its speed from a wheel speed sensor.
///
/// On every call of Process the car reads the revolutions from its sensor
/// and notifies all attached meters.
class PKW : public KFZ, public ISpeed
{
public:
   /// @brief Creates a car.
   /// @param[in] sensor is the sensor that delivers the revolutions.
   /// @param[in] wheelDiameter is the diameter of the wheels.
   /// @throws std::invalid_argument if sensor is a null pointer.
   explicit PKW(WheelSpeedSensor::UPtr sensor, double wheelDiameter);

   /// @brief Reads the revolutions from the sensor and notifies all meters.
   /// @throws std::runtime_error if the sensor cannot deliver a value.
   void Process();

   /// @brief Access function for the current speed.
   /// @returns the current speed calculated from the revolutions.
   double GetCurrentSpeed() const override;

private:
   /// @brief Sensor that delivers the revolutions.
   WheelSpeedSensor::UPtr mSensor;

   /// @brief Last revolutions read from the sensor.
   double mRevolutions{0.0};

   /// @brief Diameter of the wheels.
   double mWheelDiameter{0.0};
};

#endif // PKW_H
