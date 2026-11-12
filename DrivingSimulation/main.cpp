#include <iostream>
#include <chrono>
#include <memory>
#include <thread>

//zur Verwendung der analogen und digitalen Anzeige
#include "KFZ.h"
#include "Odometer.h"
#include "PKW.h"
#include "Speedometer.h"
#include "WheelSpeedSensor.h"
#include "WindowsDisplay.h"

using namespace std;

int main() 
{
	//Erzeugen der Objekte
	WheelSpeedSensor::UPtr wheel_speed_sensor = make_unique<WheelSpeedSensor>("../wheel_speeds.txt");
	PKW pkw(std::move(wheel_speed_sensor), 0.5);
	DisplayClient::SPtr digDisp = make_shared<DigitalDisplay>();
	DisplayClient::SPtr anaDisp = make_shared<AnalogDisplay>();
	Speedometer::SPtr speedometer = make_shared<Speedometer>(pkw, anaDisp);
	Odometer::SPtr odometer = make_shared<Odometer>(pkw, digDisp);

   pkw.Attach(speedometer);
   pkw.Attach(odometer);

	while (true)
	{
		pkw.Process();
		std::cout << "Current speed: " << pkw.GetCurrentSpeed() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	return 0;
}
