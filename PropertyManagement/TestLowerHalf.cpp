/// \file TestLowerHalf.cpp
/// \author Leander

#include "TestLowerHalf.h"
#include "Floor.h"
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {

int gChecks = 0;
int gFailed = 0;

/// Counts one check and prints a line if it failed.
void Check(bool condition, const char* text, int line) {
    ++gChecks;
    if (!condition) {
        ++gFailed;
        std::cout << "  [FAIL] line " << line << ": " << text << "\n";
    }
}

#define CHECK(condition) Check((condition), #condition, __LINE__)

/// Runs a function and returns everything it printed to the console.
std::string CaptureOutput(const std::function<void()>& func) {
    std::ostringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    func();
    std::cout.rdbuf(old);
    return buffer.str();
}

/// Runs a function and tells if it threw the given exception type.
template <typename Exception>
bool Throws(const std::function<void()>& func) {
    try {
        func();
    } catch (const Exception&) {
        return true;
    } catch (...) {
        return false;
    }
    return false;
}

void TestTenant() {
    std::cout << "Tenant tests\n";

    Tenant t("Hans", "Huber", 1950);
    CHECK(t.GetFirstName() == "Hans");
    CHECK(t.GetLastName() == "Huber");
    CHECK(t.GetBirthYear() == 1950);

    t.SetFirstName("Johann");
    t.SetLastName("Maier");
    CHECK(t.GetFirstName() == "Johann");
    CHECK(t.GetLastName() == "Maier");
    CHECK(t.GetBirthYear() == 1950);

    Tenant p("Hans", "Huber", 1950);
    CHECK(CaptureOutput([&] { p.Print(); }) == "Hans Huber (1950)");
}

void TestFlat() {
    std::cout << "Flat tests\n";

    Tenant a("Hans", "Huber", 1950);
    Tenant b("Peter", "Bauer", 1972);

    Flat f(1, 65.0f, true, &a);
    CHECK(f.GetNumber() == 1);
    CHECK(f.GetArea() == 65.0f);
    CHECK(f.HasBalcony());
    CHECK(f.GetTenant() == &a);

    f.SetTenant(&b);
    CHECK(f.GetTenant() == &b);
    f.SetTenant(nullptr);
    CHECK(f.GetTenant() == nullptr);

    Flat empty(2, 78.0f, false);
    CHECK(empty.GetTenant() == nullptr);

    Flat withTenant(1, 65.0f, false, &a);
    CHECK(CaptureOutput([&] { withTenant.Print(); }) ==
          "    Flat 1, 65qm, no balcony: Hans Huber (1950)\n");

    Flat vacant(2, 78.0f, true);
    CHECK(CaptureOutput([&] { vacant.Print(); }) ==
          "    Flat 2, 78qm, with balcony: vacant\n");
}

void TestFloor() {
    std::cout << "Floor tests\n";

    CHECK(Throws<std::invalid_argument>([] { Floor f(0, {}); }));

    Tenant a("Hans", "Huber", 1950);
    Floor floor(1, {Flat(3, 65.0f, true, &a), Flat(4, 78.0f, true)});
    CHECK(floor.GetNumber() == 1);
    CHECK(floor.GetFlatCount() == 2);
    CHECK(floor.GetFlat(1).GetNumber() == 4);
    CHECK(Throws<std::out_of_range>([&] { floor.GetFlat(2); }));

    Tenant b("Peter", "Bauer", 1972);
    floor.GetFlat(1).SetTenant(&b);
    CHECK(floor.GetFlat(1).GetTenant() == &b);

    Floor printed(0, {Flat(1, 65.0f, false, &a), Flat(2, 78.0f, false)});
    CHECK(CaptureOutput([&] { printed.Print(); }) ==
          "  Floor 0\n"
          "    Flat 1, 65qm, no balcony: Hans Huber (1950)\n"
          "    Flat 2, 78qm, no balcony: vacant\n");
}

} // namespace

int RunLowerHalfTests() {
    gChecks = 0;
    gFailed = 0;

    TestTenant();
    TestFlat();
    TestFloor();

    std::cout << "Result: " << (gChecks - gFailed) << " of " << gChecks
              << " checks passed\n";
    return gFailed;
}