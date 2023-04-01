// Copyright Giovanni Tramarin Zambiasi 2023

#include <iostream>
#include "Delegate.h"

class Foo
{
public:

    void DoFoo() 
    {
        std::cout << "Do Foo!" << std::endl;
    }

    void DoSpecialFoo(int x)
    {
        std::cout << "Do special foo " << x << "!" << std::endl;
    }

    static void DoStaticFoo()
    {
        std::cout << "Do static foo!" << std::endl;
    }
};

void GlobalFoo()
{
    std::cout << "Do global foo!" << std::endl;
}

class Base{};

class Child : public Base{};

int main()
{
    {
        Foo foo{};
        
        Gio::Delegate<> del{};
        del.Bind(&GlobalFoo);
        del.BindMember(foo,&Foo::DoFoo);

        del.Clear();

        del();
    }
    // Simple member function
    {
        Foo foo{};
    
        Gio::Delegate<> del{};    // From C++17 onwards, the "<>" can be omitted
    
        del.BindMember(foo, &Foo::DoFoo);
        del();                    // The delegates are callable!
    
        Gio::SimpleDelegate delAlternative;   // For versions earlier than C++17, this alternative syntax can be used
        delAlternative.BindMember(foo, &Foo::DoFoo);
        delAlternative();
    }
    
    // Specialized member function
    {
        Foo foo{};
        
        Gio::Delegate<int> del{};
    
        del.BindMember(foo, &Foo::DoSpecialFoo);
        del(10);
    
        typedef Gio::Delegate<int> MySpecialDelegate;   // You can also typedef your own specialized delegates!
        MySpecialDelegate specialDelAlternative{};
    
        specialDelAlternative.BindMember(foo, &Foo::DoSpecialFoo);
        del(5);
    }
    
    // Static member function
    {
        Gio::Delegate<> del{};
    
        del.Bind(&Foo::DoStaticFoo);
        del();
    }
    
    // Lambda
    {
        Gio::Delegate<int> del{};
    
        del.Bind([](int bar)
        {
           std::cout << "Do specialized lambda " << bar << "!" << std::endl; 
        });
    
        del(10);
    }
    
    // Global function
    {
        Gio::Delegate<> del{};
        del.Bind(&GlobalFoo);
        del();
    }

    std::getchar();
}