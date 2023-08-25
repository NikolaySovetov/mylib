#include "configured/configured.h"
#include "list_lib.hpp"

#ifdef TEST_ON
#include "fortests.hpp"
    mylib::tests::MsSettings s4 {mylib::tests::Color::magenta, "    >> "};
#endif

namespace mylib {

template<typename T>
struct ListNode {
    T object;
    unique_ptr<ListNode> next;
};

template<typename T>
struct ListData {
    int counter;
    unique_ptr<ListNode<T>> first;
    unique_ptr<ListNode<T>> last;
};

template<typename T>
list<T>::list(): m_data{new T()} {

}

}   // mylib


