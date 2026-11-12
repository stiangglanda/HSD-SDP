#ifndef KFZ_H
#define KFZ_H

#include <vector>
#include "Object.h"
#include "Meter.h"

/// @author Leander Kieweg
/// @date 12.11.2026
/// @brief Abstract base class for all vehicles.
///
/// The class is the subject of the design pattern Observer. Meters are
/// attached to the KFZ and are notified when its values have changed.
class KFZ : public Object
{
public:
   /// @brief Attaches a meter to the KFZ.
   /// @param[in] meter is the meter to attach.
   /// @throws std::invalid_argument if meter is a null pointer.
   void Attach(Meter::SPtr meter);

   /// @brief Detaches a meter from the KFZ.
   /// @param[in] meter is the meter to detach.
   void Detach(Meter::SPtr meter);

   /// @brief Calls Update on all attached meters.
   void Notify();

protected:
   /// @brief Protected default constructor that makes the class abstract.
   KFZ() = default;

private:
   /// @brief All attached meters.
   std::vector<Meter::SPtr> mMeters;

};

#endif // KFZ_H
