#include "WheelSpeedSensor.h"

WheelSpeedSensor::WheelSpeedSensor(const std::string &path) : mFile(path) {
   if (!mFile.is_open()) {
      throw std::runtime_error("Could not open file: " + path);
   }
}

double WheelSpeedSensor::GetRevolutions() {
   double revolutions;
   if (!(mFile >> revolutions)) {
      if (!mFile.eof()) {
         throw std::runtime_error("Could not read from file");
      }

      mFile.clear();
      mFile.seekg(0, std::ios::beg);
      if (!(mFile >> revolutions)) {
         throw std::runtime_error("Could not read from file");
      }
   }
   return revolutions;
}
