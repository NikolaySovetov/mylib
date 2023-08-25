#include "configured/configured.h"
#include "shared_ptr_lib.hpp"

#ifdef TEST_ON 
#include "fortests.hpp"
    mylib::tests::MsSettings s3{mylib::tests::Color::green, "  >> sh_ptr"};
#endif

namespace mylib {

struct SharedData {
    uint16_t sh_count;

    SharedData(): sh_count{1} {}
    SharedData(const SharedData&) = delete;
    SharedData& operator=(const SharedData&) = delete;
    SharedData(SharedData&&) = delete;
    SharedData& operator=(SharedData&&) = delete;
    ~SharedData() = default;
    void operator++() { ++sh_count; }
    void operator--() { --sh_count; }
    bool operator<(uint16_t val) { return sh_count < val; }
};

template<typename T>
shared_ptr<T>::shared_ptr(): sh_data{nullptr}, sh_ptr{nullptr} {
#ifdef TEST_ON 
    tests::informator.PrintMess(s3, {"() created\n"}); 
#endif
}

template<typename T>
shared_ptr<T>::shared_ptr(T* ptr): sh_data{new SharedData()}, sh_ptr{ptr} {
#ifdef TEST_ON 
    tests::informator.PrintMess(s3, {"(T*) created\n"}); 
#endif
}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& sh): sh_data{sh.sh_data}, sh_ptr{sh.sh_ptr} {
    ++(*sh_data);
#ifdef TEST_ON 
    tests::informator.PrintMess(s3, {"(const sh_ptr&) copied\n"}); 
#endif
}

template<typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& sh) {
    if (this != &sh) {
        if (!sh_data) {
            sh_ptr = sh.sh_ptr;
            sh_data = sh.sh_data;
            ++(*sh_data);   
        } else {
            --(*sh_data);
            if ((*sh_data) < 1) {
                delete sh_ptr;
                delete sh_data;
            }
            sh_ptr = sh.sh_ptr;
            sh_data = sh.sh_data;
            ++(*sh_data);   
        }
    }
#ifdef TEST_ON 
    tests::informator.PrintMess(s3, {" =(sh_ptr) copied\n"}); 
#endif
    return *this;
}

template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& sh): sh_data{sh.sh_data}, sh_ptr{sh.sh_ptr} {
    sh.sh_ptr = nullptr;
    sh.sh_data = nullptr;
#ifdef TEST_ON 
    tests::informator.PrintMess(s3, {"(sh_ptr&&) moved\n"}); 
#endif
}

template<typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& sh) {
    if (this != &sh) {
        if (!sh_data) {
            sh_ptr = sh.sh_ptr;
            sh_data = sh.sh_data;
            sh.sh_ptr = nullptr;
            sh.sh_data = nullptr;
        } else {
            --(*sh_data);
            if ((*sh_data) < 1) {
                delete sh_ptr;
                delete sh_data;
            }
            sh_ptr = sh.sh_ptr;
            sh_data = sh.sh_data;
            sh.sh_ptr = nullptr;
            sh.sh_data = nullptr;
        }
    }
#ifdef TEST_ON 
    tests::informator.PrintMess(s3, {" =(sh_ptr) moved\n"}); 
#endif
    return *this;
}

template<typename T>
shared_ptr<T>::~shared_ptr() {
    if (sh_data) {
        --(*sh_data);
        if ((*sh_data) < 1) {
            delete sh_ptr;
            delete sh_data;
        }
    }
#ifdef TEST_ON 
    tests::informator.PrintMess(s3, {"() destroyed\n"}); 
#endif
}

template<typename T>
T* shared_ptr<T>::get() { return sh_ptr; }

template<typename T>
T& shared_ptr<T>::operator*() { return *sh_ptr; } 

template<typename T>
T* shared_ptr<T>::operator->() { return sh_ptr; }

template<typename T>
shared_ptr<T>::operator bool() { return (sh_ptr != nullptr); }

template<typename T>
bool shared_ptr<T>::operator!() { return (sh_ptr == nullptr); }

template<typename T>
const uint16_t shared_ptr<T>::counter() const {
    return sh_data->sh_count; 
}

}   // mylib