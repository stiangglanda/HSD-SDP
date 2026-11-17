#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include "MeterBase.h"

/// @author Julian Rieger
/// @date 12.11.2026
/// @brief Meter that shows the current speed of a KFZ in km/h.
class Speedometer : public MeterBase
{
public:
   /// @brief Creates a speedometer and shows the current speed.
   /// @param[in] speed is the source of the current speed.
   /// @param[in] display is the display that shows the speed.
   /// @throws std::invalid_argument if display is a null pointer.
   Speedometer(const ISpeed& speed, const DisplayClient::SPtr& display);

   /// @brief Reads the current speed and sends it to the display.
   void Update() override;
};

#endif // SPEEDOMETER_H
