#include <iostream>
#include "Delegate.h"

class Foo {

public:

    void DoFoo() 
    {
        std::cout << "Do Foo!" << std::endl;
    }

    void DoSpecialFoo(int x)
    {
        printf("Do special foo! %i\n", x);
    }
};

int main()
{
    // === Simple delegate
    Delegate del;

    Foo* foo = new Foo();

    del.Add(foo, &Foo::DoFoo);

    del.Invoke();


    // === Specialized delegate
    Delegate<int> specialDel;

    specialDel.Add(foo, &Foo::DoSpecialFoo);

    specialDel.Invoke(10);

    system("pause");
}