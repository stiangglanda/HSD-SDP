#include "WheelSpeedSensor.h"
#include <stdexcept>

WheelSpeedSensor::WheelSpeedSensor(const std::string &path) : mFile(path) {
   if (!mFile.is_open()) {
      throw std::runtime_error("Could not open file: " + path);
   }
}

double WheelSpeedSensor::GetRevolutions() {
   double revolutions = 0.0;

   if (!ReadValue(revolutions)) {
      // end of file reached: start again at the beginning
      mFile.clear();
      mFile.seekg(0, std::ios::beg);
      if (!ReadValue(revolutions)) {
         throw std::runtime_error("Could not read from file: file is empty");
      }
   }

   if (revolutions < 0.0) {
      throw std::runtime_error("Invalid revolutions in file: value is negative");
   }
   return revolutions;
}

bool WheelSpeedSensor::ReadValue(double& revolutions) {
   if (mFile >> revolutions) {
      return true;
   }
   if (!mFile.eof()) {
      throw std::runtime_error("Could not read from file: invalid content");
   }
   return false;
}
