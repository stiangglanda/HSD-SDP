#ifndef ODOMETER_H
#define ODOMETER_H

#include "MeterBase.h"

/// @author Julian Rieger
/// @date 12.11.2026
/// @brief Meter that shows the distance driven by a KFZ.
///
/// The distance is summed up from the current speed on every update.
class Odometer : public MeterBase
{
public:
   /// @brief Creates an odometer with a distance of zero.
   /// @param[in] display is the display that shows the distance.
   /// @param[in] speed is the pointer to the interface that provides GetCurrentSpeed().
   /// @throws std::invalid_argument if display is a null pointer.
   Odometer(const ISpeed& speed, DisplayClient::SPtr display);

   /// @brief Adds the distance since the last update and sends the total
   ///        distance to the display.
   void Update() override;

private:
   /// @brief Total distance driven so far.
   double mDistance = 0;
};

#endif // ODOMETER_H
