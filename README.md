# Gio's C++ Delegates
A naive header-only implementation of delegates in c++. Insipred by the Unreal Engine delegate system. For anyone looking to do the same, I recommend these two articles:
- [Implement a simple event and delegate system in C++ by Giang Tong](https://tongtunggiang.com/2017/cpp-event-delegate/)
- [C++ Delegates by Simon Coenen](https://tongtunggiang.com/2017/cpp-event-delegate/)

My goals were to:
- Make it as simple, and with as clean a syntax as possible
- Be able to bind any functions to it, including:
  - Member functions
  - Static member functions
  - Global functions
  - Lambdas
- Support any number of parameters
<br>

## Installing:
  To use, simply include [/GioDelegates/Delegate.h](./GioDelegates/Delegate.h)
<br>

### Usage:
TBD...<br>
You can find all examples here [/GioDelegates/GioDelegateExamples.cpp](./GioDelegates/GioDelegateExamples.cpp)

# To-do
- [ ] Bind unique
- [ ] Unbind/Clear
- [ ] Remove by object