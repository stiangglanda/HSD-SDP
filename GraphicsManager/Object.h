#ifndef OBJECT_H
#define OBJECT_H

/// @author Julian Rieger
/// @date 05.11.2026
/// @brief Abstract base class of all classes of the image management.
///
/// The class can not be instantiated directly (protected constructor) and it
/// prevents copying and assigning of all derived classes.
class Object
{
public:
   /// @brief Copying is not allowed.
   Object(const Object&) = delete;

   /// @brief Assigning is not allowed.
   Object& operator=(const Object&) = delete;

   /// @brief Virtual destructor, so derived objects can be deleted via a base pointer.
   virtual ~Object();

protected:
   /// @brief Protected constructor, only derived classes can create an Object.
   Object();
};

#endif
