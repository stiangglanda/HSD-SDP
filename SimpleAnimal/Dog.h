#ifndef DOG_H
#define DOG_H
#include "Animal.h"

/// @author Franz Wiesinger
/// @date 10.06.2022
/// @brief Concrete class for a dog.
/// 
/// The class represents a dog and all of its attributes.
class Dog : public Animal
{
public:
   /// @brief Constructor of a dog.
   /// @param[in] w is the weight as positive integer.
   /// 
   /// Calls the constructor of an animal.
   Dog(size_t const w);

   /// @brief Outputs the sound of a dog.
   /// 
   /// Implements the pure virtual method of class Animal.
   void GiveTongue() const override;

   /// @brief Returns a string representation of a dog.
   /// @returns a string of a dog with all attributes.
   std::string ToString() const override;

   /// @brief Clones a dog and returns itself as clone-object.
   /// @returns a cloned object of a dog.
   Animal const* Clone() const override;
};
#endif //DOG_H
