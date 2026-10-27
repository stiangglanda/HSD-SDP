#ifndef OBJECT_H
#define OBJECT_H

/// @author Leander Kieweg
/// @date 27.10.2026
/// @brief Abstract base class of all classes.
class Object
{
protected:
   /// @brief Creates an object. Only derived classes can call it.
   Object();

public:
   /// @brief Destroys the object.
   virtual ~Object() = default;
};

#endif //OBJECT_H
