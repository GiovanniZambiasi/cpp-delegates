#pragma once

#include <vector>

template <typename ...TArgs>
class IDelegateInvokable
{
public:
    
    virtual void Invoke(TArgs... params) = 0;
};

template <class TObject, typename ... TArgs>
class DelegateToMemeberMethod : public IDelegateInvokable<TArgs...>
{
public:
    
    typedef void (TObject::*SpecializedDelegateOneParam)(TArgs ... params);

    DelegateToMemeberMethod(TObject* target, SpecializedDelegateOneParam method);

    void Invoke(TArgs ... params) override
    {
        if(_target != nullptr)
            (_target->*_method)(params...);
    }

    bool Equals(TObject* object, SpecializedDelegateOneParam method)
    {
        return object == _target && method == _method;
    }

private:

    TObject* _target;
    SpecializedDelegateOneParam _method;
    
};

template <class TObject, typename ... TArgs>
DelegateToMemeberMethod<TObject, TArgs...
>::DelegateToMemeberMethod(TObject* target, SpecializedDelegateOneParam method): _target(target)
    , _method(method)
{
}

template <typename... TArgs>
class Delegate
{
private:
    
    std::vector<IDelegateInvokable<TArgs...>*> _members;
    
public:

    template <class T>
    void Add(T* object, void (T::*method)(TArgs ... params));

    template <class T>
    void Remove(T* object, void (T::*method)(TArgs ... params));
    
    void Invoke(TArgs ... params)
    {
        for (int i = 0; i < _members.size(); i++)
        {
            IDelegateInvokable<TArgs...>* member = _members[i];

            member->Invoke(params...);
        }
    }
};

template <typename ... TArgs>
template <class T>
void Delegate<TArgs...>::Add(T* object, void (T::* method)(TArgs ... params))
{
    IDelegateInvokable<TArgs...>* member = new DelegateToMemeberMethod<T, TArgs...>(object, method);

    _members.push_back(member);
}

template <typename ... TArgs>
template <class T>
void Delegate<TArgs...>::Remove(T* object, void (T::* method)(TArgs ... params))
{
    for (int i = 0; i < _members.size(); i++)
    {
        IDelegateInvokable<TArgs...>* invokable = _members[i];

        DelegateToMemeberMethod<T, TArgs...>* specializedInvokable = dynamic_cast<DelegateToMemeberMethod<T, TArgs...>*>
            (invokable);

        if (specializedInvokable != nullptr && specializedInvokable->Equals(object, method))
        {
            _members.erase(_members.begin() + i);

            delete invokable;
        }
    }
}

