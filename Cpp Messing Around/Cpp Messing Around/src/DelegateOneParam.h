#include <vector>

template <typename TParam>
class DelegateMemberBaseOneParam
{
public:
    
    virtual void Invoke(TParam param) = 0;
};

template <class TObject, typename TParam>
class DelegateMemberOneParam : public DelegateMemberBaseOneParam<TParam>
{
public:
    
    typedef void (TObject::*SpecializedDelegateOneParam)(TParam param);
    
    DelegateMemberOneParam(TObject* target, SpecializedDelegateOneParam method)
        : _target(target)
        , _method(method)
    {    
    }
    
    void Invoke(TParam param) override
    {
        (_target->*_method)(param);
    }

private:

    TObject* _target;
    SpecializedDelegateOneParam _method;
    
};

template <typename TParam>
class DelegateOneParam
{
private:

    std::vector<DelegateMemberBaseOneParam<TParam>*> _members;
    
public:

    template <class T>
    void Add(T* object, void(T::*method)(TParam param))
    {
        DelegateMemberBaseOneParam<TParam>* delmember = new DelegateMemberOneParam(object, method);

        _members.push_back(delmember);
    }

    void Invoke(TParam param)
    {
        for (int i = 0; i < _members.size(); i++)
        {
            DelegateMemberBaseOneParam<TParam>* member = _members[i];

            member->Invoke(param);
        }
    }
};