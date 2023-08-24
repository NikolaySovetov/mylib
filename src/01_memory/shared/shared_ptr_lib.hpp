#pragma once
#include <cstdint>

namespace mlb /*my library*/ {

struct SharedData;

template<typename T> 
class shared_ptr {
private:
    T* m_ptr;
    SharedData* m_data;

public:
    shared_ptr();
    shared_ptr(T*);
    shared_ptr(const shared_ptr&);
    shared_ptr& operator=(const shared_ptr&);
    shared_ptr(shared_ptr&&);
    shared_ptr& operator=(shared_ptr&&);
    ~shared_ptr();
    T* get();
    T& operator*();
    const T* operator->();
    explicit operator bool();
    bool operator!();
    const uint16_t counter() const;
};

}// mlb