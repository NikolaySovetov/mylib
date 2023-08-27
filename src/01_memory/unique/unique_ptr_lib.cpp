#include "configured/configured.h"
#include "unique_ptr_lib.hpp"

#ifdef TEST_ON
#include "fortests.hpp" 
    mylib::tests::MsSettings s2{mylib::tests::Color::cyan, "  >> unique"};
#endif

namespace mylib {

template<typename T>
unique_ptr<T>::unique_ptr(): uniq_ptr{nullptr} {
#ifdef TEST_ON 
    tests::informator.PrintMess(s2, {"() created\n"}); 
#endif
}

template<typename T>
unique_ptr<T>::unique_ptr(T* ptr): uniq_ptr{ptr} {
#ifdef TEST_ON 
    tests::informator.PrintMess(s2, {"(T*) created\n"}); 
#endif
}

template<typename T>
unique_ptr<T>::unique_ptr(unique_ptr&& u) {
    uniq_ptr = u.uniq_ptr;
    u.uniq_ptr = nullptr;
#ifdef TEST_ON 
    tests::informator.PrintMess(s2, {"(unique_ptr&&) moved\n"}); 
#endif
}

template<typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr&& u) {
    if (this != &u) {
        delete uniq_ptr;
        uniq_ptr = u.uniq_ptr;
        u.uniq_ptr = nullptr;
    }
#ifdef TEST_ON 
    tests::informator.PrintMess(s2, {"=(unique_ptr&&) moved\n"}); 
#endif
    return *this;
}

template<typename T>
unique_ptr<T>::~unique_ptr() {
    delete uniq_ptr;
    uniq_ptr = nullptr;
#ifdef TEST_ON 
    tests::informator.PrintMess(s2, {"() destroyed\n"}); 
#endif
}

template<typename T>
T* unique_ptr<T>::get() const {
    return uniq_ptr;
}

template<typename T>
T& unique_ptr<T>::operator*() const {
    return *uniq_ptr;
}

template<typename T>
T* unique_ptr<T>::operator->() const {
    return uniq_ptr;
}

template<typename T>
unique_ptr<T>::operator bool() const {
    return uniq_ptr != nullptr; 
}

template<typename T>
bool unique_ptr<T>::operator!() const {
    return uniq_ptr == nullptr; 
}

}// mylib