#pragma once

namespace mylib {

template<typename T> 
class unique_ptr {
private:
    T* uniq_ptr;

public:
    unique_ptr();
    unique_ptr(T*);
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;
    unique_ptr(unique_ptr&&);
    unique_ptr& operator=(unique_ptr&&);
    ~unique_ptr();
    T* get() const;
    T& operator*() const;
    T* operator->() const;
    explicit operator bool() const;
    bool operator!() const;
};

}   // mylib