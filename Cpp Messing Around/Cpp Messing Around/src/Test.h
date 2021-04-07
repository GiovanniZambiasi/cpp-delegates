#pragma once
#include "Singleton.h"

class Test : public Singleton<Test>
{
public:
    Test()
    {    }

    ~Test()
    {    }
};
