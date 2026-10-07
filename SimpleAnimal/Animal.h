#ifndef ANIMAL_H
#define ANIMAL_H
#include "Object.h"

/// @author Franz Wiesinger
/// @date 10.06.2022
/// @brief Abstract base class for all animals.
/// 
/// The base class specifies the weight and a unique identifier 
/// for each animal.
class Animal : public Object
{
public:
   /// @brief Access function for the weight.
   /// @returns the weight as a positive integer.
   size_t GetWeight() const;

   /// @brief Access function for the unique identifier.
   /// @returns the identifier as a positive integer.
   size_t GetId() const;
   
   /// @brief Outputs the sound of the respective animal on std::cout.
   /// 
   /// The method is pure virtual and must be implemented in 
   /// derived classes. Since the implementation is missing, 
   /// no object of this class can be created. 
   /// The class is therefore abstract.
   virtual void GiveTongue() const = 0;
    

   /// @brief String representation of class Animal.
   /// 
   /// Constructs a string representation of class Animal
   /// and can be overridden in derived classes.
   /// @returns a string for class Animal.
   std::string ToString() const override;

   /// @brief Creates a clone of the animal.
   /// 
   /// The method is pure virtual and must be implemented 
   /// in derived classes. 
   virtual Animal const* Clone() const = 0;

protected:
   /// @brief Protected constructor of an animal.
   /// @param[in] w is the weight of an Animal 
   Animal(size_t const w);

private:
   /// @brief Generates a sequential number.
   /// @details The generated number is used for the unique identifier.
   static size_t msCounter;

   /// @brief Unique identifier of an animal. 
   size_t mId;

   /// @brief The weight of an Animal in kilogram.
   size_t mWeight;
};



#endif //ANIMAL_H
