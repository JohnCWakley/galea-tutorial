#pragma once

#include <functional>
#include <memory>
#include <map>
#include <list>
#include <string>
#include <iostream>

template <typename... Args>
using Func = std::function<void(Args...)>;

class EventEmitter
{
public:
    EventEmitter() {}
    ~EventEmitter() {}

    template <typename... Args>
    void addListener(const std::string &name, std::function<void(Args...)> cb)
    {
        std::string listener_id = name + "_" + std::to_string(++lastListener);
        listeners.insert(std::make_pair(name, std::make_shared<Listener<Args...>>(listener_id, cb)));
    }

    void addListener(const std::string &name, std::function<void()> cb)
    {
        std::string listener_id = name + "_" + std::to_string(++lastListener);
        listeners.insert(std::make_pair(name, std::make_shared<Listener<>>(listener_id, cb)));
    }

    template <typename Lambda>
    void addListener(const std::string &name, Lambda cb)
    {
        addListener(name, make_function(cb));
    }

    void removeListener(const std::string &name)
    {
        std::cout << "removeListener: " << name << std::endl;
    }

    template <typename... Args>
    void emit(const std::string &name, Args... args)
    {
        std::list<std::shared_ptr<Listener<Args...>>> handlers;
        auto range = listeners.equal_range(name);
        handlers.resize(std::distance(range.first, range.second));

        std::transform(range.first, range.second, handlers.begin(), [](std::pair<std::string, std::shared_ptr<ListenerBase>> p)
                       {
                           auto l = std::dynamic_pointer_cast<Listener<Args...>>(p.second);
                           if (l)
                           {
                               return l;
                           }
                           else
                           {
                               throw std::logic_error("EventEmitter::emit: Invalid event signature.");
                           }
                       });

        for (auto &h : handlers)
        {
            h->callback(args...);
        }
    }

private:
    struct ListenerBase
    {
        ListenerBase(const std::string &n) : name(n) {}
        virtual ~ListenerBase() {}
        const std::string &name;
    };

    template <typename... Args>
    struct Listener : public ListenerBase
    {
        Listener() {}
        Listener(const std::string &name, std::function<void(Args...)> cb) : ListenerBase(name), callback(cb) {}
        std::function<void(Args...)> callback;
    };

    unsigned int lastListener;
    std::multimap<std::string, std::shared_ptr<ListenerBase>> listeners;

    // http://stackoverflow.com/a/21000981
    template <typename T>
    struct function_traits : public function_traits<decltype(&T::operator())>
    {
    };

    template <typename ClassType, typename ReturnType, typename... Args>
    struct function_traits<ReturnType (ClassType::*)(Args...) const>
    {
        typedef std::function<ReturnType(Args...)> f_type;
    };

    template <typename L>
    typename function_traits<L>::f_type make_function(L l)
    {
        return (typename function_traits<L>::f_type)(l);
    }
};
