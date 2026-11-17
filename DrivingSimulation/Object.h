#ifndef OBJECT_H
#define OBJECT_H

/// @brief Common abstract base class of all classes (except pure interfaces).
class Object{
protected:
   /// @brief Protected default constructor that makes the class abstract.
   Object() = default;
public:
   /// @brief Virtual default destructor for safe polymorphic deletion.
   virtual ~Object() = default;
};

#endif // OBJECT_H
