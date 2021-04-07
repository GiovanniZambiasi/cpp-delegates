#include <iostream>
#include <vector>

#include "Delegate.h"

using namespace std;

class Foo
{
public:

    void DoFoo()
    {
        cout << "Foo!" << endl;
    }

    void DoBar()
    {
        cout << "Bar!" << endl;
    }
    
    void DoFooWithParams(float a, int b, bool c)
    {
        cout << "Foo with params! " << a << " " << b << " " << c << endl;
    }
};


void main()
{
    Delegate simpleDelegate;
    
    Foo* foo = new Foo();
    simpleDelegate.Add(foo, &Foo::DoFoo);
    
    Foo* fooOther = new Foo();
    simpleDelegate.Add(fooOther, &Foo::DoBar);

    simpleDelegate.Invoke();

    Delegate<float, int, bool> specialized;

    specialized.Add(foo, &Foo::DoFooWithParams);

    specialized.Invoke(10.0f, 1, false);
    
    system("pause");
}