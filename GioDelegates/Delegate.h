// Copyright Giovanni Tramarin Zambiasi 2023

#pragma once

#include <functional>
#include <memory>
#include <vector>

namespace Gio
{
    template <typename ... TArgs>
    class Listener
    {    
    public:
        virtual ~Listener() = default;
        
        virtual void Invoke(TArgs... Args) = 0;
    };

    template <typename TFunction, typename  ...TArgs>
    class StandardListener : public Listener<TArgs...>
    {
        std::function<void(TArgs...)> BoundListener{};
    
    public:
        StandardListener(TFunction function)
            : BoundListener(function)
        { }
    
        virtual void Invoke(TArgs... Args) override
        {
            BoundListener(Args...);
        }
    };

    template <typename TMemberType, typename TMethod, typename ... TArgs>
    class MemberMethodListener : public Listener<TArgs...>
    {
        TMemberType& Member;
        std::function<void(TMemberType&, TArgs...)> BoundListener{};

    public:
        MemberMethodListener(TMemberType& Object, TMethod Method)
        : Member(Object), BoundListener(Method)
        { }
    
        virtual void Invoke(TArgs... Args) override
        {
            BoundListener(Member, Args...);
        }
    };

    template <typename ... TArgs>
    class Delegate
    {
        typedef Listener<TArgs...> SpecializedListener;
    
        std::vector<std::shared_ptr<SpecializedListener>> Listeners{};
    
    public:
        void Invoke(TArgs... Args)
        {
            for (auto& Listener : Listeners)
            {
                Listener->Invoke(Args...);
            }
        }

        void operator()(TArgs... Args)
        {
            Invoke(Args...);
        }

        template<typename TFunc>
        void Bind(TFunc Method)
        {
            auto ListenerInstance = std::make_shared<StandardListener<TFunc, TArgs...>>(Method);
            Listeners.push_back(ListenerInstance);
        }

        template<typename TMemberType, typename TMethod>
        void BindMember(TMemberType& Member, TMethod Method)
        {
            auto Listener = std::make_shared<MemberMethodListener<TMemberType, TMethod, TArgs...>>(Member, Method);
            Listeners.push_back(Listener);
        }
        
        void Clear()
        {
            Listeners.clear();
        }
    };

    /**
     * Simple delegate returning void and taking in no arguments.
     * <br><br>
     * Alias of Delegate<>, for language versions lower than C++17. 
     */
    typedef Delegate<> SimpleDelegate;
}