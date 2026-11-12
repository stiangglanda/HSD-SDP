#ifndef METER_H
#define METER_H

#include <memory>

/// @author Julian Rieger
/// @date 12.11.2026
/// @brief Interface for all meters that observe a KFZ.
///
/// The interface is the observer of the design pattern Observer. A KFZ
/// calls Update on every attached meter when its values have changed.
class Meter
{
public:
   /// @brief Shared pointer to a meter.
   using SPtr = std::shared_ptr<Meter>;

   /// @brief Virtual default destructor for safe polymorphic deletion.
   virtual ~Meter() = default;

   /// @brief Is called by the KFZ when its values have changed.
   virtual void Update() = 0;
};

#endif // METER_H
