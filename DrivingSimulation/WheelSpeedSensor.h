#ifndef WHEELSPEEDSENSOR_H
#define WHEELSPEEDSENSOR_H

#include <fstream>
#include <memory>
#include <string>
#include "Object.h"

/// @author Leander Kieweg
/// @date 12.11.2026
/// @brief Simulates a wheel speed sensor.
///
/// The sensor reads the wheel revolutions from a file, one value per call.
class WheelSpeedSensor : public Object
{
public:
   /// @brief Shared pointer to a wheel speed sensor.
   using SPtr = std::shared_ptr<WheelSpeedSensor>;

   /// @brief Creates a sensor and opens the file with the revolutions.
   /// @param[in] path is the path of the file to read.
   /// @throws std::runtime_error if the file cannot be opened.
   explicit WheelSpeedSensor(const std::string& path);

   /// @brief Reads the next value from the file.
   /// @returns the wheel revolutions.
   /// @throws std::runtime_error if no value can be read.
   double GetRevolutions();

private:
   /// @brief File that contains the revolutions.
   std::ifstream mFile;
};

#endif // WHEELSPEEDSENSOR_H
