#ifndef ISPEED_H
#define ISPEED_H

/// @author Leander Kieweg
/// @date 12.11.2026
/// @brief Interface for read-only access to the current speed.
///
/// Follows the Interface Segregation Principle (ISP). The meters only need
/// the speed, so they do not depend on the whole KFZ.
class ISpeed
{
public:
   /// @brief Virtual default destructor for safe polymorphic deletion.
   virtual ~ISpeed() = default;

   /// @brief Access function for the current speed.
   /// @returns the current speed.
   virtual double GetCurrentSpeed() const = 0;
};

#endif // ISPEED_H
