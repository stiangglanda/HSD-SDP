#ifndef OBJECT_H
#define OBJECT_H
#include <string>

/// @author Franz Wiesinger
/// @date 10.06.2022
/// @brief Base class of all base classes.
/// 
/// Is the common root class of all classes. If there is no other base class, 
/// this class is to be selected as the base class.
class Object
{
public:
   /// @brief Virtual default destructor -> once virtual, always virtual.
   /// 
   /// It is not necessary to declare another virtual destructor 
   /// in derived classes.
   virtual ~Object() = default;

   /// @brief String representation of class Object.
   /// @returns a string for class Object.
   /// 
   /// Constructs a string representation of class Object
   /// and can be overridden in derived classes.
   virtual std::string ToString() const;
   
protected:
   /// @brief Protected default constructor that makes the class abstract.
   Object() = default;
};

#endif // OBJECT_H