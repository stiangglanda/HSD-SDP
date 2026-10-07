/// @mainpage Example for a doxygen documentation
/// The implementation of SimpleAnimal models different 
/// animal species that are stored in a zoo. In the test driver, 
/// individual animals are first created and their methods tested. 
/// Then animals are added to the zoo and the zoo's methods 
/// are tested as well. 
/// 
/// @author Franz Wiesinger
/// @date 10.06.2026
/// @version 1.0

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <vld.h>
#include "Cat.h"
#include "Dog.h"
#include "Zoo.h"

using namespace std;

/// @brief OK is a constant for a positive test result.
static short const OK = 0;
/// @brief NOK is a constant for a negative test result.
static short const NOK = 1;


/// @brief Test function for verifying the weight of an Animal.
/// 
/// Compares the actual weight of the animal to the expected weight 
/// and outputs the test result.
/// 
/// @param[in] animal The Animal object whose weight will be tested.
/// @param[in] expectedWeight The expected weight of the animal.
void TestAnimalWeight(const Animal& animal, size_t const expectedWeight) {
   size_t actualWeight = animal.GetWeight();
   if (actualWeight == expectedWeight) {
      std::cout << "[PASS] Animal weight test passed." << std::endl;
   }
   else {
      std::cout << "[FAIL] Expected weight: " << expectedWeight << ", but got: " << actualWeight << std::endl;
   }
}

/// @brief Test function for verifying the ID of an Animal.
/// 
/// Compares the actual ID of the animal to the expected ID 
/// and outputs the test result.
/// 
/// @param[in] animal The Animal object whose ID will be tested.
/// @param[in] expectedId The expected unique ID of the animal.
void TestAnimalId(const Animal& animal, size_t const expectedId) {
   size_t actualId = animal.GetId();
   if (actualId == expectedId) {
      std::cout << "[PASS] Animal ID test passed." << std::endl;
   }
   else {
      std::cout << "[FAIL] Expected ID: " << expectedId << ", but got: " << actualId << std::endl;
   }
}

/// @brief Test function for verifying the sound produced by an Animal.
/// 
/// Calls the `GiveTongue` method of the animal and compares the output 
/// with the expected sound.
/// 
/// @param[in] animal The Animal object whose sound will be tested.
/// @param[in] expectedSound The expected sound as a string.
void TestAnimalSound(Animal const& animal, std::string const& expectedSound) {
   //Switching the std::cout buffer to a stringstream:
   //all output written to std::cout will be redirected to the string stream os instead.
   std::ostringstream os;
   std::streambuf* originalCoutBuffer = std::cout.rdbuf();
   std::cout.rdbuf(os.rdbuf());

   animal.GiveTongue();

   //reset the std::cout buffer:
   //The original buffer of std::cout is restored so that future outputs 
   //appear on the console again.
   std::cout.rdbuf(originalCoutBuffer);
   std::string actualSound = os.str();
   if (actualSound == expectedSound) {
      std::cout << "[PASS] Animal sound test passed." << std::endl;
   }
   else {
      std::cout << "[FAIL] Expected: " << expectedSound << ", but got: " << actualSound << std::endl;
   }
}

/// @brief Test function for verifying the string representation of an Animal.
/// 
/// Calls the `ToString` method of the animal and compares the returned string 
/// with the expected string.
/// 
/// @param[in] animal The Animal object whose string representation will be tested.
/// @param[in] expectedString The expected string output from the animal.
void TestAnimalToString(Animal const& animal, std::string const& expectedString) {
   std::string actualString = animal.ToString();
   if (actualString == expectedString) {
      std::cout << "[PASS] Animal ToString test passed." << std::endl;
   }
   else {
      std::cout << "[FAIL] Expected: " << expectedString << ", but got: " << actualString << std::endl;
   }
}

/// @brief Test function for verifying the cloning behavior of an Animal.
/// 
/// Creates a clone of the animal using the `Clone` method and compares 
/// its weight and ID to the original animal.
/// 
/// @param[in] animal The Animal object to be cloned.
void TestAnimalClone(Animal const& animal) {
   const Animal* clonedAnimal = animal.Clone();
   if (clonedAnimal->GetWeight() == animal.GetWeight() && clonedAnimal->GetId() == animal.GetId()) {
      std::cout << "[PASS] Animal cloning test passed." << std::endl;
   }
   else {
      std::cout << "[FAIL] Animal cloning test failed." << std::endl;
   }
   delete clonedAnimal;  // Make sure to free memory from cloning
}

/// @brief Test function for verifying the contents of a Zoo.
/// 
/// Compares the string output of the zoo's `ToString` method 
/// with the expected zoo string.
/// 
/// @param[in] zoo The Zoo object to be tested.
/// @param[in] expectedZooString The expected string representation of the zoo.
void TestZooContents(Zoo const& zoo, std::string const& expectedZooString) {
   std::string actualZooString = zoo.ToString();
   if (actualZooString == expectedZooString) {
      std::cout << "[PASS] Zoo ToString test passed." << std::endl;
   }
   else {
      std::cout << "[FAIL] Expected zoo string:\n" << expectedZooString << "\nBut got:\n" << actualZooString << std::endl;
   }
}

/// @brief Test function for handling exceptions during invalid animal creation.
/// 
/// Tests if the appropriate exception is thrown when attempting to create 
/// an animal with an invalid weight.
/// 
/// @return void This function does not return a value.
void TestInvalidAnimalCreation() {
   try {
      Dog invalidDog(0);  // Invalid weight, should throw exception
      std::cout << "[FAIL] Expected exception for invalid dog weight not thrown." << std::endl;
   }
   catch (const std::invalid_argument& e) {
      std::cout << "[PASS] Exception caught: " << e.what() << std::endl;
   }

   try {
      Cat invalidCat(-5);  // Invalid weight, should throw exception
      std::cout << "[FAIL] Expected exception for invalid cat weight not thrown." << std::endl;
   }
   catch (const std::invalid_argument& e) {
      std::cout << "[PASS] Exception caught: " << e.what() << std::endl;
   }
}

/// @brief Test function for handling null animal addition to the Zoo.
/// 
/// Tests if the appropriate exception is thrown when attempting to add 
/// a null pointer as an animal to the zoo.
/// 
/// @return void This function does not return a value.
void TestZooNullAnimal() {
   Zoo zoo;
   try {
      zoo.Add(nullptr);  // Trying to add null animal, should throw exception
      std::cout << "[FAIL] Expected exception for null animal not thrown." << std::endl;
   }
   catch (const std::invalid_argument& e) {
      std::cout << "[PASS] Exception caught: " << e.what() << std::endl;
   }
}


/// Start of the testdriver.
int main()
{
   try
   {
      // Additional Exception Handling Tests
      std::cout << "Testing Invalid Animal Creation..." << std::endl;
      TestInvalidAnimalCreation();

      std::cout << "Testing Null Animal Addition to Zoo..." << std::endl;
      TestZooNullAnimal();

      // Create animals
      Dog dog1(25);   // A dog with weight 25
      Dog dog2(30);   // Another dog with weight 30
      Cat cat1(10);   // A cat with weight 10

      // Test Animal Weight
      std::cout << "Testing Animal Weights..." << std::endl;
      TestAnimalWeight(dog1, 25);
      TestAnimalWeight(dog2, 30);
      TestAnimalWeight(cat1, 10);

      // Test Animal ID
      std::cout << "Testing Animal IDs..." << std::endl;
      TestAnimalId(dog1, 2);  // Assuming first created dog has ID 0
      TestAnimalId(dog2, 3);  // Assuming second created dog has ID 1
      TestAnimalId(cat1, 4);  // Assuming first created cat has ID 2

      // Test Animal Sounds
      std::cout << "Testing Animal Sounds..." << std::endl;
      TestAnimalSound(dog1, "bark\n");
      TestAnimalSound(dog2, "bark\n");
      TestAnimalSound(cat1, "miaow\n");

      // Test Animal ToString
      std::cout << "Testing Animal ToString..." << std::endl;
      TestAnimalToString(dog1, "ID:2 I'm a dog and my weight is 25\n");
      TestAnimalToString(dog2, "ID:3 I'm a dog and my weight is 30\n");
      TestAnimalToString(cat1, "ID:4 I'm a cat and my weight is 10\n");

      // Test Animal Cloning
      std::cout << "Testing Animal Cloning..." << std::endl;
      TestAnimalClone(dog1);
      TestAnimalClone(cat1);

      // Create a Zoo and add animals
      Zoo zoo;
      zoo.Add(new Dog{ dog1 });
      zoo.Add(new Dog{ dog2 });
      zoo.Add(new Cat{ cat1 });

      // Expected Zoo string output
      std::string expectedZooString = "This zoo has 3 animals:\n"
         "ID:2 I'm a dog and my weight is 25\n"
         "ID:3 I'm a dog and my weight is 30\n"
         "ID:4 I'm a cat and my weight is 10\n";
      
    
      // Test Zoo Contents
      std::cout << "Testing Zoo Contents..." << std::endl;
      TestZooContents(zoo, expectedZooString);
   }
   catch (invalid_argument const& ex)
   {
      cerr << ex.what() << endl;
      return 1;
   }
   catch (bad_alloc const& ex)
   {
      cerr << ex.what() << endl;
      return 1;
   }
   catch (...)
   {
      cerr << "unhandled exception" << endl;
      return 1;
   }
}