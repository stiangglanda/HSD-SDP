#include <iostream>
#include <chrono>
#include <memory>
#include <thread>

//zur Verwendung der analogen und digitalen Anzeige
#include "KFZ.h"
#include "PKW.h"
#include "WheelSpeedSensor.h"
#include "WindowsDisplay.h"

using namespace std;

int main() 
{
    //Erzeugen der Objekte
    DisplayClient::SPtr digDisp = make_shared<DigitalDisplay>();
    DisplayClient::SPtr anaDisp = make_shared<AnalogDisplay>();
    WheelSpeedSensor::UPtr wheel_speed_sensor = make_unique<WheelSpeedSensor>("../wheel_speeds.txt");
	PKW pkw(std::move(wheel_speed_sensor), 0.5);

	while (true)
	{
		pkw.Process();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	//send values to displays
	for (int i = 0; i < 4711; i++) {
      if (digDisp->SendValue(i * 5))
      {
         cout <<  "digi: " << i * 5 << endl;
      }
      if (anaDisp->SendValue((i * 5) % 220))
      {
         cout << "analog: " << i * 5 << endl;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	return 0;
}
