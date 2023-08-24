#include "configured/sharedconfig.h"
#include "shared_ptr_lib.hpp"
#include <iostream>

#ifdef TEST_ON 
#include "fortests.hpp"
    mylib::tests::MsSettings s3{mylib::tests::Color::green, "  >> sh_ptr"};
#endif

namespace mylib {

struct SharedData {
    uint16_t m_count;

    SharedData(): m_count{1} {}
    SharedData(const SharedData&) = delete;
    SharedData& operator=(const SharedData&) = delete;
    SharedData(SharedData&&) = delete;
    SharedData& operator=(SharedData&&) = delete;
    ~SharedData() = default;
    void operator++() { ++m_count; }
    void operator--() { --m_count; }
    bool operator<(uint16_t val) { return m_count < val; }
};

template<typename T>
shared_ptr<T>::shared_ptr(): m_data{nullptr}, m_ptr{nullptr} {
#ifdef TEST_ON 
    tests::informator.PrintMess(s3, {"() created\n"}); 
#endif
}

template<typename T>
shared_ptr<T>::shared_ptr(T* ptr): m_data{new SharedData()}, m_ptr{ptr} {
#ifdef TEST_ON 
    tests::informator.PrintMess(s3, {"(T*) created\n"}); 
#endif
}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& sh): m_data{sh.m_data}, m_ptr{sh.m_ptr} {
    ++(*m_data);
#ifdef TEST_ON 
    tests::informator.PrintMess(s3, {"(const sh_ptr&) copied\n"}); 
#endif
}

template<typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& sh) {
    if (this != &sh) {
        if (!m_data) {
            m_ptr = sh.m_ptr;
            m_data = sh.m_data;
            ++(*m_data);   
        } else {
            --(*m_data);
            if ((*m_data) < 1) {
                delete m_ptr;
                delete m_data;
            }
            m_ptr = sh.m_ptr;
            m_data = sh.m_data;
            ++(*m_data);   
        }
    }
#ifdef TEST_ON 
    tests::informator.PrintMess(s3, {" =(sh_ptr) copied\n"}); 
#endif
    return *this;
}

template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& sh): m_data{sh.m_data}, m_ptr{sh.m_ptr} {
    sh.m_ptr = nullptr;
    sh.m_data = nullptr;
#ifdef TEST_ON 
    tests::informator.PrintMess(s3, {"(sh_ptr&&) moved\n"}); 
#endif
}

template<typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& sh) {
    if (this != &sh) {
        if (!m_data) {
            m_ptr = sh.m_ptr;
            m_data = sh.m_data;
            sh.m_ptr = nullptr;
            sh.m_data = nullptr;
        } else {
            --(*m_data);
            if ((*m_data) < 1) {
                delete m_ptr;
                delete m_data;
            }
            m_ptr = sh.m_ptr;
            m_data = sh.m_data;
            sh.m_ptr = nullptr;
            sh.m_data = nullptr;
        }
    }
#ifdef TEST_ON 
    tests::informator.PrintMess(s3, {" =(sh_ptr) moved\n"}); 
#endif
    return *this;
}

template<typename T>
shared_ptr<T>::~shared_ptr() {
    if (m_data) {
        --(*m_data);
        if ((*m_data) < 1) {
            delete m_ptr;
            delete m_data;
        }
    }
#ifdef TEST_ON 
    tests::informator.PrintMess(s3, {"() destroyed\n"}); 
#endif
}

template<typename T>
T* shared_ptr<T>::get() { return m_ptr; }

template<typename T>
T& shared_ptr<T>::operator*() { return *m_ptr; } 

template<typename T>
T* shared_ptr<T>::operator->() { return m_ptr; }

template<typename T>
shared_ptr<T>::operator bool() { return (m_ptr != nullptr); }

template<typename T>
bool shared_ptr<T>::operator!() { return (m_ptr == nullptr); }

template<typename T>
const uint16_t shared_ptr<T>::counter() const {
    return m_data->m_count; 
}

}   // mylib