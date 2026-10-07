#ifndef CAT_H
#define CAT_H
#include "Animal.h"

/// @author Franz Wiesinger
/// @date 10.06.2022
/// @brief Concrete class for a cat.
/// 
/// The class represents a cat and all of its attributes.
class Cat : public Animal    
{
public:
   /// @brief Constructor of a cat.
   /// 
   /// Calls the constructor of an animal.
   /// @param[in] w is the weight as positive integer.</param>
   Cat(size_t const w);

   /// @brief Outputs the sound of a cat.
   /// 
   /// Implements the pure virtual method of class Animal.
   void GiveTongue() const override;

   /// @brief Returns a string representation of a cat.
   /// @returns a string of a cat with all attributes.
   std::string ToString() const override;

   /// @brief Clones a cat and returns itself as clone-object.
   /// @returns a cloned object of a cat.
   Animal const* Clone() const override;
};
#endif //CAT_H


