// Testtreiber DrivingSimulation
// Teil 1: Tests aller Klassen inkl. Fehlerfaelle
// Teil 2: Simulation laut Angabe (Process im 500ms-Takt, echte Anzeigen)

#include <chrono>
#include <cmath>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <thread>

#ifdef HAVE_VLD
#include <vld.h>
#endif

#include "DisplayServer.h"
#include "Odometer.h"
#include "PKW.h"
#include "Speedometer.h"
#include "WheelSpeedSensor.h"
#include "WindowsDisplay.h"

using namespace std;

static int sPassed = 0;
static int sFailed = 0;

static void Check(bool ok, const string& text)
{
   if (ok) { ++sPassed; cout << "  [OK]     " << text << endl; }
   else    { ++sFailed; cerr << "  [FAILED] " << text << endl; }
}

// prueft, ob f eine Exception vom Typ E wirft
template <typename E, typename F>
static void CheckThrows(F f, const string& text)
{
   try { f(); Check(false, text + " (no exception)"); }
   catch (const E& e) { Check(true, text + " -> \"" + e.what() + "\""); }
   catch (const exception& e) { Check(false, text + " (wrong exception: " + e.what() + ")"); }
}

template <typename F>
static void CheckNoThrow(F f, const string& text)
{
   try { f(); Check(true, text); }
   catch (const exception& e) { Check(false, text + " (" + e.what() + ")"); }
}

static bool Near(double a, double b, double tol = 1e-5) { return fabs(a - b) <= tol; }

// schreibt eine Testdatei und liefert einen Sensor, der sie liest
static WheelSpeedSensor::UPtr Sensor(const string& content, const string& file = "test.txt")
{
   ofstream(file) << content;
   return make_unique<WheelSpeedSensor>(file);
}

// Hilfsklassen fuer die Tests
struct FakeSpeed : ISpeed {
   double speed = 0;
   double GetCurrentSpeed() const override { return speed; }
};

struct CountingMeter : Meter {
   int updates = 0;
   void Update() override { ++updates; }
};

struct TestDisplay : DisplayClient {
   explicit TestDisplay(uint16_t port) : DisplayClient(port) {}
};

// Display-Server im Testtreiber, merkt sich den zuletzt empfangenen Wert
struct Probe {
   unsigned last = 0;
   size_t received = 0;
   size_t expected = 0;
   DisplayServer server;

   explicit Probe(uint16_t port) : server(port, [this](unsigned v) { last = v; ++received; }) { server.Start(); }

   // wartet auf den naechsten Wert (max. 2 s) und liefert ihn
   unsigned Shown()
   {
      ++expected;
      for (int i = 0; i < 2000 && received < expected; ++i) {
         server.Poll();
         this_thread::sleep_for(chrono::milliseconds(1));
      }
      return last;
   }
};

static void TestSensor()
{
   cout << "--- WheelSpeedSensor ---" << endl;

   CheckThrows<runtime_error>([] { WheelSpeedSensor s("does_not_exist.txt"); }, "File does not exist");

   auto s = Sensor("100\n200\n300\n");
   bool order = s->GetRevolutions() == 100;
   order = order && s->GetRevolutions() == 200;
   order = order && s->GetRevolutions() == 300;
   Check(order, "Values in the order of the file (100, 200, 300)");
   Check(s->GetRevolutions() == 100, "Restart at the beginning after end of file");

   s = Sensor("5 6");
   bool noNewline = s->GetRevolutions() == 5;
   noNewline = noNewline && s->GetRevolutions() == 6;
   Check(noNewline && s->GetRevolutions() == 5, "File without newline at the end");

   s = Sensor("42\n");
   bool single = true;
   for (int i = 0; i < 5; ++i) single = single && s->GetRevolutions() == 42;
   Check(single, "File with only one value returns it on every call");

   s = Sensor("");
   CheckThrows<runtime_error>([&] { s->GetRevolutions(); }, "Empty file");

   s = Sensor("  \n\n \t\n");
   CheckThrows<runtime_error>([&] { s->GetRevolutions(); }, "File with only whitespace");

   s = Sensor("100\nabc\n");
   Check(s->GetRevolutions() == 100, "Valid value before invalid content");
   CheckThrows<runtime_error>([&] { s->GetRevolutions(); }, "Invalid content (text instead of number)");

   s = Sensor("-5\n");
   CheckThrows<runtime_error>([&] { s->GetRevolutions(); }, "Negative revolutions");

   s = Sensor("0\n1e9\n");
   Check(s->GetRevolutions() == 0, "Limit value 0 U/min");
   Check(s->GetRevolutions() == 1e9, "Very large value 1e9 U/min");

   s = make_unique<WheelSpeedSensor>("wheel_speeds.txt");
   double first = s->GetRevolutions(), max = first, last = first;
   for (int i = 1; i < 27; ++i) {
      last = s->GetRevolutions();
      if (last > max) max = last;
   }
   Check(first == 0 && max == 1379 && last == 0, "wheel_speeds.txt: 27 values from 0 up to 1379 and back to 0");
   Check(s->GetRevolutions() == 0, "wheel_speeds.txt: restart after 27 values");
   cout << endl;
}

static void TestPKW()
{
   cout << "--- PKW ---" << endl;

   CheckThrows<invalid_argument>([] { PKW p(nullptr, 0.6); }, "Sensor is nullptr");
   CheckThrows<invalid_argument>([] { PKW p(Sensor("1"), 0.0); }, "Wheel diameter 0");
   CheckThrows<invalid_argument>([] { PKW p(Sensor("1"), -0.6); }, "Negative wheel diameter");
   CheckThrows<invalid_argument>([] { PKW p(Sensor("1"), numeric_limits<double>::quiet_NaN()); }, "Wheel diameter NaN");
   CheckThrows<invalid_argument>([] { PKW p(Sensor("1"), numeric_limits<double>::infinity()); }, "Wheel diameter infinity");

   PKW pkw(Sensor("500\n0\n"), 0.6);
   Check(pkw.GetCurrentSpeed() == 0, "Speed is 0 before the first Process");
   pkw.Process();
   cout << "  Speed at 500 U/min, 0.6 m: " << pkw.GetCurrentSpeed() << " km/h" << endl;
   Check(Near(pkw.GetCurrentSpeed(), 56.549, 0.001), "Example from the exercise: 500 U/min -> 56.549 km/h");
   pkw.Process();
   Check(pkw.GetCurrentSpeed() == 0, "0 U/min -> 0 km/h");
   CheckNoThrow([&] { pkw.Process(); }, "Process without attached meters");

   PKW empty(Sensor("", "test_empty.txt"), 0.6);
   CheckThrows<runtime_error>([&] { empty.Process(); }, "Process with empty sensor file");
   cout << endl;
}

static void TestObserver()
{
   cout << "--- KFZ Observer (Attach / Detach / Notify) ---" << endl;

   PKW pkw(Sensor("100\n"), 0.6);
   auto a = make_shared<CountingMeter>();
   auto b = make_shared<CountingMeter>();

   CheckThrows<invalid_argument>([&] { pkw.Attach(nullptr); }, "Attach nullptr");

   pkw.Attach(a);
   pkw.Attach(b);
   pkw.Process();
   Check(a->updates == 1 && b->updates == 1, "Both attached meters are updated once per Process");

   pkw.Attach(a);
   pkw.Process();
   Check(a->updates == 2, "A meter attached twice is still updated only once");

   pkw.Detach(a);
   pkw.Process();
   Check(a->updates == 2 && b->updates == 3, "Detached meter is not updated anymore, the other one is");

   CheckNoThrow([&] { pkw.Detach(a); }, "Detach a meter that is not attached");
   CheckNoThrow([&] { pkw.Detach(nullptr); }, "Detach nullptr");

   pkw.Attach(a);
   pkw.Process();
   Check(a->updates == 3, "Meter can be attached again after Detach");

   pkw.Detach(a);
   pkw.Detach(b);
   CheckNoThrow([&] { pkw.Process(); }, "Process after all meters are detached");
   cout << endl;
}

// Anzeigen senden an eigene Test-Displays (Port 4811/4812), damit geprueft
// werden kann, welcher Wert wirklich am Display ankommt
static void TestMeters()
{
   const uint16_t portA = 4811, portB = 4812;
   Probe probeA(portA), probeB(portB);
   DisplayClient::SPtr dispA = make_shared<TestDisplay>(portA);
   DisplayClient::SPtr dispB = make_shared<TestDisplay>(portB);
   FakeSpeed fake;

   cout << "--- Speedometer ---" << endl;
   CheckThrows<invalid_argument>([&] { Speedometer m(fake, nullptr); }, "Display is nullptr");

   fake.speed = 56.549;
   Speedometer speedo(fake, dispA);
   Check(probeA.Shown() == 56, "Constructor shows the current speed (56.549 -> 56)");

   fake.speed = 120.9;  speedo.Update();
   Check(probeA.Shown() == 120, "Decimal places are cut off (120.9 -> 120)");
   fake.speed = 0;      speedo.Update();
   Check(probeA.Shown() == 0, "Speed 0");
   fake.speed = -5;     speedo.Update();
   Check(probeA.Shown() == 0, "Negative speed is shown as 0");
   fake.speed = 1e20;   speedo.Update();
   Check(probeA.Shown() == numeric_limits<unsigned>::max(), "Very large speed is limited to UINT_MAX");
   fake.speed = numeric_limits<double>::quiet_NaN(); speedo.Update();
   Check(probeA.Shown() == 0, "NaN is shown as 0");
   cout << endl;

   cout << "--- Odometer ---" << endl;
   CheckThrows<invalid_argument>([&] { Odometer m(fake, nullptr); }, "Display is nullptr");

   Odometer odo(fake, dispB);
   Check(probeB.Shown() == 0 && odo.GetDistance() == 0, "Starts with a distance of 0 km");

   fake.speed = 56.549; odo.Update();
   probeB.Shown();
   cout << "  Distance after 500 ms at 56.549 km/h: " << odo.GetDistance() << " km" << endl;
   Check(Near(odo.GetDistance(), 0.00785), "Example from the exercise: 56.549 km/h for 500 ms -> 0.00785 km");

   Odometer fast(fake, dispB);
   probeB.Shown();
   fake.speed = 3600; fast.Update();
   Check(probeB.Shown() == 0 && Near(fast.GetDistance(), 0.5), "3600 km/h for 500 ms -> 0.5 km, display shows 0");
   fast.Update();
   Check(probeB.Shown() == 1 && Near(fast.GetDistance(), 1.0), "Distance is summed up -> 1.0 km, display shows 1");
   fake.speed = 0; fast.Update();
   probeB.Shown();
   Check(Near(fast.GetDistance(), 1.0), "Speed 0 does not change the distance");
   cout << endl;

   cout << "--- Integration PKW + Speedometer + Odometer ---" << endl;
   PKW pkw(Sensor("500\n1000\n"), 0.6);
   auto speedometer = make_shared<Speedometer>(pkw, dispA);
   auto odometer = make_shared<Odometer>(pkw, dispB);
   probeA.Shown();
   probeB.Shown();
   pkw.Attach(speedometer);
   pkw.Attach(odometer);

   pkw.Process();
   Check(probeA.Shown() == 56, "Process updates the speedometer automatically (500 U/min -> 56 km/h)");
   probeB.Shown();
   Check(Near(odometer->GetDistance(), 0.00785), "Process updates the odometer automatically (0.00785 km)");

   pkw.Process();
   Check(probeA.Shown() == 113, "Second Process (1000 U/min -> 113 km/h)");
   probeB.Shown();
   Check(Near(odometer->GetDistance(), 0.02356), "Distance of both intervals is summed up (0.02356 km)");
   cout << endl;
}

// Simulation laut Angabe: Tachometer auf AnalogDisplay, Kilometerzaehler auf DigitalDisplay
static void RunSimulation()
{
   const int cycles = 30;
   cout << "=== Simulation (" << cycles << " cycles every 500 ms) ===" << endl;

   PKW pkw(make_unique<WheelSpeedSensor>("wheel_speeds.txt"), 0.6);
   DisplayClient::SPtr digDisp = make_shared<DigitalDisplay>();
   DisplayClient::SPtr anaDisp = make_shared<AnalogDisplay>();
   auto speedometer = make_shared<Speedometer>(pkw, anaDisp);
   auto odometer = make_shared<Odometer>(pkw, digDisp);
   pkw.Attach(speedometer);
   pkw.Attach(odometer);

   for (int i = 1; i <= cycles; ++i) {
      pkw.Process();
      printf("Cycle %2d: speed %7.2f km/h, distance %.5f km\n", i, pkw.GetCurrentSpeed(), odometer->GetDistance());
      fflush(stdout);
      this_thread::sleep_for(chrono::milliseconds(500));
   }
}

int main()
{
   try {
      TestSensor();
      TestPKW();
      TestObserver();
      TestMeters();

      filesystem::remove("test.txt");
      filesystem::remove("test_empty.txt");
      cout << endl << "=== Summary: " << sPassed << " passed, " << sFailed << " failed ===" << endl << endl;

      RunSimulation();
      return sFailed == 0 ? 0 : 1;
   }
   catch (const bad_alloc& e) { cerr << "Out of memory: " << e.what() << endl; }
   catch (const exception& e) { cerr << "Error: " << e.what() << endl; }
   catch (...) { cerr << "Unknown error" << endl; }
   return 1;
}
