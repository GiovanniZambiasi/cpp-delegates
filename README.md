# Gios C++ Delegates
A naive single-header implementation of delegates to member functions in c++. Insipred by the Unreal Engine 4 delegate system. For anyone looking to do the same, I recomment these two articles:
- [Implement a simple event and delegate system in C++ by Giang Tong](https://tongtunggiang.com/2017/cpp-event-delegate/)
- [C++ Delegates by Simon Coenen](https://tongtunggiang.com/2017/cpp-event-delegate/)

My goals were to:
- Make it as simple, and with as clean a syntax as possible
- Be able to bind member functions to it, regardless of their type
- Support any number of parameters
<br></br>
## Usage:
  To use, add the GiosDelegates.dll into your project's include directories, and add the include ``"Delegate.h"``. Only member functions can be added to a ``Delegate`` (no global functions are supported... yet?). You can bind any number of functions of any number of types to the same ``Delegate``, as long as their signatures are the same.
<br></br>
### Parameterless delegates:
```cpp
class Foo
{
public:

    void DoFoo()
    {
        cout << "Foo!" << endl;
    }
};


void main()
{
    Delegate simpleDelegate;
    
    Foo* foo = new Foo();
    simpleDelegate.Add(foo, &Foo::DoFoo);
    
    simpleDelegate.Invoke(); // "Foo!" is logged
}
```
<br></br>
The ``Delegate`` is not limited to a single listener type:
```cpp
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

    del.Invoke(); // "Foo!" and "Bar!" are logged
}
```
<br></br>
### Specialized delegates:
```cpp
class Foo
{
public:

    void DoFoo(float a, int b, bool c)
    {
        printf("Foo! %f %i %i\n", a, b, c);
    }
};

void main()
{
    Delegate<float, int, bool> specializedDelegate;
    
    Foo* foo = new Foo();
    specializedDelegate.Add(foo, &Foo::DoFoo);
    
    specializedDelegate.Invoke(10.0f, 1, false); // "Foo! 10.0000, 1, 1" is logged
}
```
<br></br>
You can also ``typedef`` your own delegate signature for a more readable approach:
```cpp
typedef Delegate<float, int, bool> MySpecialDelegate;

class Foo
{
public:

    void DoFoo(float a, int b, bool c)
    {
        printf("Foo! %f %i %i\n", a, b, c);
    }
};

void main()
{
    MySpecialDelegate specializedDelegate;
    
    Foo* foo = new Foo();
    specializedDelegate.Add(foo, &Foo::DoFoo);
    
    specializedDelegate.Invoke(10.0f, 1, false); // "Foo! 10.0000, 1, 0" is logged
}
```
