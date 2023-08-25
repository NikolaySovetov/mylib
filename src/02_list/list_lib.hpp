#pragma once
#include "shared_ptr.hpp"
#include "unique_ptr.hpp"

namespace mylib {

template<typename T>
struct ListData;

template<typename T>
class list {
private:
    unique_ptr<ListData<T>> m_data;

public:
    list();
    list(T);
    list(const list&);
    list& operator=(const list&);
    list(list&&);
    list& operator=(list&&);
    ~list();
};

}   // mylib
