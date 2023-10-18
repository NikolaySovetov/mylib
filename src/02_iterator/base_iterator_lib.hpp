#pragma once
#include <cstddef>

namespace mylib {

template<typename T, typename Ptr = T*, typename Ref = T&>
class base_iterator {
public:
    virtual void operator++() = 0;
    virtual Ref operator*() const = 0;
    virtual Ptr operator->() const = 0;
};


}   // mylib
