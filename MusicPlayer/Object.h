#ifndef OBJECT_H
#define OBJECT_H

/// @author Julian Rieger
/// @date 25.11.2026
/// @brief Abstract base class of all classes.
///
/// The class has no attributes and no methods. It only provides a virtual destructor.
class Object
{
public:
   /// @brief Virtual destructor of an object.
   ///
   /// Makes sure that derived objects are deleted correctly.
   virtual ~Object() = 0;
};

inline Object::~Object() {}

#endif //OBJECT_H
