#pragma once
#include <cstddef>

namespace mylib {

template<typename T>
class base_iterator {
protected:
    T* it;

public:
    base_iterator();
    base_iterator(T*);
    base_iterator(const base_iterator&);
    base_iterator& operator=(const base_iterator&);
    base_iterator(base_iterator&&);
    base_iterator& operator=(base_iterator&&);
    virtual ~base_iterator();
    T* get() const;

    virtual void operator++() = 0;
    virtual bool operator!=(const base_iterator&) const = 0;
    virtual T* operator->() const = 0;
    virtual T& operator*() const = 0;
};
 
}   // mylib
