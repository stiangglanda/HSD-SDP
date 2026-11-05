#ifndef SINGLETONBASE_H
#define SINGLETONBASE_H

#include <memory>
#include "Object.h"

template <typename T>
class SingletonBase : public Object
{
public:
    static T& GetInstance()
    {
        if (mInstance == nullptr)
        {
            mInstance = std::unique_ptr<T>{ new T{} };
        }

        return *mInstance;
    }

    // Free singleton before end of program
    static void Delete()
    {
        mInstance.reset();
    }

protected:
    // Protected constructor so that only derived classes can be created and destroyed
    SingletonBase() = default;
    virtual ~SingletonBase() = default;

private:
    SingletonBase(SingletonBase const& s) = delete;
    SingletonBase& operator=(SingletonBase const& s) = delete;

    static std::unique_ptr<T> mInstance;
};

// Initialize static member
template <typename T>
std::unique_ptr<T> SingletonBase<T>::mInstance = nullptr;

#endif
