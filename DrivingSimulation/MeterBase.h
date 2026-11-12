#ifndef METERBASE_H
#define METERBASE_H

#include "Object.h"
#include "Meter.h"
#include "ISpeed.h"
#include "WindowsDisplay.h"

/// @author Julian Rieger
/// @date 12.11.2026
/// @brief Abstract base class for all meters.
///
/// Holds the display the meter writes its value to and the speed source
/// the meter reads its value from. The derived classes only implement
/// Update and so decide which value is calculated and shown.
class MeterBase : public Meter, public Object
{
protected:
   /// @brief Protected constructor that makes the class abstract.
   /// @param[in] speed is the source of the current speed.
   /// @param[in] display is the display that shows the value of the meter.
   /// @throws std::invalid_argument if display is a null pointer.
   MeterBase(const ISpeed& speed, DisplayClient::SPtr display);

   /// @brief Source of the current speed.
   const ISpeed& mSpeed;

   /// @brief Display that shows the value of the meter.
   DisplayClient::SPtr mDisplay;
};

#endif // METERBASE_H
