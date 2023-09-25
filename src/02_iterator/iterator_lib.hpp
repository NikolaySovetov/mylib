#pragma once
#include <cstddef>

namespace mylib {

template<typename T>
class base_iterator {
private:
    T* it;

public:
    base_iterator();
    base_iterator(T*);
    base_iterator(const base_iterator&);
    base_iterator& operator=(const base_iterator&);
    base_iterator(base_iterator&&);
    base_iterator& operator=(base_iterator&&);
    virtual ~base_iterator();

    virtual void operator++();
    virtual bool operator!=(const base_iterator&) const;
    virtual T* operator->() const;
    virtual T& operator*() const;
};
 
}   // mylib
