#include "iterator_config.hpp"
#include "base_iterator_lib.hpp"
#include <exception>
#include <iostream>

#ifdef ITERATOR_TEST
#include "fortests.hpp"
    mylib::tests::MsSettings base_iterator_set {mylib::tests::Color::blue, "   --> iterator"};
#endif

namespace mylib {

template<typename T, typename Ptr, typename Ref>
base_iterator<T, Ptr, Ref>::base_iterator(): it {nullptr}  {
#ifdef ITERATOR_TEST
    tests::informator.PrintMess(base_iterator_set, {"() created\n"}); 
#endif
}

template<typename T, typename Ptr, typename Ref>
base_iterator<T, Ptr, Ref>::base_iterator(T* obj): it {obj}  {   
#ifdef ITERATOR_TEST
    tests::informator.PrintMess(base_iterator_set, {"(T*) created\n"}); 
#endif
}

template<typename T, typename Ptr, typename Ref>
base_iterator<T, Ptr, Ref>::base_iterator(const base_iterator& other): it {other.it} {
#ifdef ITERATOR_TEST
    tests::informator.PrintMess(base_iterator_set, {"(&) created\n"}); 
#endif
}

template<typename T, typename Ptr, typename Ref>
base_iterator<T, Ptr, Ref>& base_iterator<T, Ptr, Ref>::operator=(const base_iterator& other) {
#ifdef ITERATOR_TEST
    tests::informator.PrintMess(base_iterator_set, {" =(&) created\n"}); 
#endif

    if (this != &other) {
        it = nullptr;
        it = other.it;
    }
    return *this;
}

template<typename T, typename Ptr, typename Ref>
base_iterator<T, Ptr, Ref>::base_iterator(base_iterator&& other): it {other.it} {
#ifdef ITERATOR_TEST
    tests::informator.PrintMess(base_iterator_set, {"(&&) created\n"}); 
#endif

    other.it = nullptr;
}

template<typename T, typename Ptr, typename Ref>
base_iterator<T, Ptr, Ref>& base_iterator<T, Ptr, Ref>::operator=(base_iterator&& other) {
#ifdef ITERATOR_TEST
    tests::informator.PrintMess(base_iterator_set, {" =(&&) created\n"}); 
#endif

    if (this != &other) {
        it = nullptr;
        it = other.it;
        other.it = nullptr;
    }
    return *this;
}

template<typename T, typename Ptr, typename Ref>
base_iterator<T, Ptr, Ref>::~base_iterator() {
#ifdef ITERATOR_TEST
    tests::informator.PrintMess(base_iterator_set, {"() destroyed\n"}); 
#endif

    it = nullptr;
}

template<typename T, typename Ptr, typename Ref>
void base_iterator<T, Ptr, Ref>::operator++() {
    it = it->get_next();
}

template<typename T, typename Ptr, typename Ref>
bool base_iterator<T, Ptr, Ref>::operator!=(const base_iterator& other) const {
    return it != other.it;
}

template<typename T, typename Ptr, typename Ref>
Ptr base_iterator<T, Ptr, Ref>::operator->() const {
    return it->get_ptr(it);
}

template<typename T, typename Ptr, typename Ref>
Ref base_iterator<T, Ptr, Ref>::operator*() const {
    return it->get_ref(it);
}

template<typename T, typename Ptr, typename Ref>
Ptr base_iterator<T, Ptr, Ref>::get() const {
    return it->get_ptr(it);
}


}   // mylib


