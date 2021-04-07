#include <iostream>
#include <vector>

#include "Delegate.h"
#include "DelegateOneParam.h"

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

class Maths
{
public:
    void AddOne(int num)
    {
        cout << num + 1 << endl;
    }

    void SomeOtherMethod()
    {
        cout << "void" << endl;;
    }
};

void main()
{
    DelegateOneParam<int> delOneParam;

    Maths* maths = new Maths();

    delOneParam.Add(maths, &Maths::AddOne);

    delOneParam.Invoke(10);
    
    Delegate del;

    Foo* foo = new Foo();

    del.Add(foo, &Foo::DoFoo);

    del.Remove(foo, &Foo::DoFoo);
    
    Bar* bar = new Bar();
    
    del.Add(bar, &Bar::DoBar);

    del.Invoke();

    system("pause");
}
