#include <iostream>

#include "Delegate.h"

using namespace std;

class Foo
{
public:

    void DoFoo()
    {
        cout << "Foo!" << endl;
    }
};

class Bar 
{
public:

    void DoBar() 
    {
        cout << "Bar!" << endl;
    }
};

void main()
{
    Delegate del;

    Foo* foo = new Foo();

    del.Add(foo, &Foo::DoFoo);
    
    Bar* bar= new Bar();

    del.Add(bar, &Bar::DoBar);

    del.Invoke();
}