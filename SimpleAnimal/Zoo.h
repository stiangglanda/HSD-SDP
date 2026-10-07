#ifndef ZOO_H
#define ZOO_H
#include <vector>
#include "Animal.h"

/// @author Franz Wiesinger
/// @date 10.06.2022
/// @brief Concret class Zoo -> stores all animals in a polymorphic container.
/// 
/// The class implements the copy constructor and the assignment operator and 
/// gives access to the animals via iterators.
class Zoo : public Object
{ 
public:
   
   /// @brief  Default CTor: must be implemented first when the CopyCTor 
   /// is defined.
   /// 
   /// The CopyCTor overrides the default constructor
   Zoo() = default;

   /// @brief The copy constructor copies a zoo with all its animals.
   /// @param[in] z is the zoo to copy.
   /// 
   /// The CopyCTor is implemented only when it becomes necessary in use.
   Zoo(Zoo const& z);

   /// @brief All animals must be released.
   /// 
   /// Dynamic memory was requested.
   ~Zoo();

   /// @brief Assign operator, implemented with elegant swap function.
   /// @param[in] z is the assigned zoo.
   /// 
   /// The zoo is copied when called and then the containers are swapped. 
   /// When exiting the method, the swapped zoo is deleted!
   void operator = (Zoo z);

   /// @brief Adds an animal to the zoo.
   /// @param[in] ani is a constant pointer to an animal.
   void Add(Animal const* ani);

   /// @brief Returns a string representation of a zoo and all its animals.
   /// @returns a string of a zoo with all attributes.
   virtual std::string ToString() const override;
   
   /// Constant Iterator to Animals.
   using CItor = std::vector<Animal const*>::const_iterator;

   /// @brief Access to begin of the the zoo via iterators.
   /// @returns a constant iterator to the first animal.
   CItor cbegin() const;

   /// @brief Access to the end in the zoo via iterators.
   /// @returns a constant iterator behind the last animal.
   CItor cend() const;

private:
   /// @brief Polymorphic container of animals. 
   /// @details The container knows only the common interface of all animals.
   std::vector<Animal const*> mAnimals; 
};



#endif //ZOO_H
