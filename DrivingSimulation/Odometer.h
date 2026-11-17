#ifndef ODOMETER_H
#define ODOMETER_H

#include "MeterBase.h"

/// @author Julian Rieger
/// @date 12.11.2026
/// @brief Meter that shows the distance driven by a KFZ in km.
///
/// The distance is summed up from the current speed on every update.
/// It is assumed that Update is called every 500 ms and that the speed
/// is constant within this interval.
class Odometer : public MeterBase
{
public:
   /// @brief Creates an odometer with a distance of zero.
   /// @param[in] speed is the source of the current speed.
   /// @param[in] display is the display that shows the distance.
   /// @throws std::invalid_argument if display is a null pointer.
   Odometer(const ISpeed& speed, const DisplayClient::SPtr& display);

   /// @brief Adds the distance since the last update and sends the total
   ///        distance to the display.
   void Update() override;

   /// @brief Access function for the total distance.
   /// @returns the total distance driven so far in km.
   double GetDistance() const;

private:
   /// @brief Time between two updates in hours (500 ms = 1/7200 h).
   static constexpr double cCycleTimeHours = 0.5 / 3600.0;

   /// @brief Total distance driven so far in km.
   double mDistance = 0.0;
};

#endif // ODOMETER_H
