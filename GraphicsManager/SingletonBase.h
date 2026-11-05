#ifndef SINGLETONBASE_H
#define SINGLETONBASE_H

#include <memory>
#include "Object.h"

/// @author Leander Kieweg
/// @date 05.11.2026
/// @brief Template base class for the Singleton design pattern.
///
/// Ensures that only one instance of the derived class T exists.
template <typename T>
class SingletonBase : public Object
{
public:
    /// @brief Accesses the single instance of the class.
    /// Creates the instance if it does not exist yet.
    /// @returns Reference to the singleton instance.
    static T& GetInstance()
    {
        if (mInstance == nullptr)
        {
            mInstance = std::unique_ptr<T>{ new T{} };
        }

        return *mInstance;
    }

    /// @brief Frees the singleton instance before the end of the program.
    static void Delete()
    {
        mInstance.reset();
    }

protected:
    /// @brief Protected constructor so that only derived classes can be created.
    SingletonBase() = default;
    
    /// @brief Virtual destructor.
    virtual ~SingletonBase() = default;

private:
    SingletonBase(SingletonBase const& s) = delete;
    SingletonBase& operator=(SingletonBase const& s) = delete;

    /// @brief Pointer to the single instance.
    static std::unique_ptr<T> mInstance;
};

// Initialize static member
template <typename T>
std::unique_ptr<T> SingletonBase<T>::mInstance = nullptr;

#endif