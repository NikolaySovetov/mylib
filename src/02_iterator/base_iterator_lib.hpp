#pragma once
#include <cstddef>

namespace mylib {

template<typename T, typename Ptr = T*, typename Ref = T&>
class base_iterator {
protected:
    T*  it;

public:
    base_iterator();
    base_iterator(T*);
    base_iterator(const base_iterator&);
    base_iterator& operator=(const base_iterator&);
    base_iterator(base_iterator&&);
    base_iterator& operator=(base_iterator&&);
    virtual ~base_iterator();

    void operator++();
    bool operator!=(const base_iterator&) const;
    Ptr operator->() const;
    Ref operator*() const;
};


}   // mylib
