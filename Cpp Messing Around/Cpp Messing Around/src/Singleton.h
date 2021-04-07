#pragma once

template <class T> class Singleton
{
public:
    Singleton<T>()
    {
        instance = (T*)this;
    }

    ~Singleton<T>()
    {
        if(instance == (T*)this)
            instance = nullptr;
    }
    
    inline static T* instance;
};
