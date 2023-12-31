#pragma once
#include <cstdint>

namespace mylib {

struct SharedData;

template<typename T> 
class shared_ptr {
private:
    T* sh_ptr;
    SharedData* sh_data;

public:
    shared_ptr();
    shared_ptr(T*);
    shared_ptr(const shared_ptr&);
    shared_ptr& operator=(const shared_ptr&);
    shared_ptr(shared_ptr&&);
    shared_ptr& operator=(shared_ptr&&);
    ~shared_ptr();
    T* get() const;
    T& operator*() const;
    T* operator->() const;
    bool operator==(const shared_ptr&) const;
    bool operator!=(const shared_ptr&) const;
    explicit operator bool() const;
    bool operator!() const;
    const uint16_t counter() const;
};

}   // mylib