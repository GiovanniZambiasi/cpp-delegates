#pragma once
#include <vector>

class IDelegateMemberBase
{
public:
    
    virtual void Invoke() = 0;
};

template <class TObject>
class DelegateMember : public IDelegateMemberBase
{
public:
    
    typedef void (TObject::*SpecializedDelegate)();
    
    DelegateMember(TObject* target, SpecializedDelegate method)
        : _target(target)
        , _method(method)
    {    
    }
    
    void Invoke() override
    {
        (_target->*_method)();
    }

    bool IsMethodEquals(SpecializedDelegate method)
    {
        return _method == method;
    }

private:
    
    TObject* _target;
    SpecializedDelegate _method;
    
};

class Delegate
{
private:

    std::vector<IDelegateMemberBase*> _members;
    
public:

    template <class T>
    void Add(T* object, void(T::*method)())
    {
        IDelegateMemberBase* delmember = new DelegateMember(object, method);

        _members.push_back(delmember);
    }

    template <class T>
    void Remove(T* object, void(T::*method)())
    {
        for (int i = 0; i < _members.size(); i++)
        {
            DelegateMember<T>* member = dynamic_cast<DelegateMember<T>*>(_members[i]);

            if(member == nullptr)
                continue;
            else
            {
                if(member->IsMethodEquals(method))
                    _members.erase(_members.begin() + i);
            }
        }
    }
    
    void Invoke()
    {
        for (int i = 0; i < _members.size(); i++)
        {
            IDelegateMemberBase* member = _members[i];

            member->Invoke();
        }
    }
};
