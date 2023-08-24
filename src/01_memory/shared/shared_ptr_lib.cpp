#include "configured/sharedconfig.h"
#include "shared_ptr_lib.hpp"
#include <iostream>

namespace mlb {

namespace shared_info {

template<typename... Args>
inline void PrintInfo(Args... words) {
#ifdef SHARED_TEST

#ifdef ONE_TAB
std::cout << "  ";
#endif    

#ifdef TWO_TAB
std::cout << "    ";
#endif    

#ifdef THREE_TAB
std::cout << "      ";
#endif    
    std::cout << ">>>";
    (std::cout << ... << words);
#endif    
}    
} // info

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
    shared_info::PrintInfo("shared_ptr() created\n");
}

template<typename T>
shared_ptr<T>::shared_ptr(T* ptr): m_data{new SharedData()}, m_ptr{ptr} {
    shared_info::PrintInfo("shared_ptr(T*) created\n");
}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& sh): m_data{sh.m_data}, m_ptr{sh.m_ptr} {
    ++(*m_data);
    shared_info::PrintInfo("shared_ptr(const shared_ptr&) copied\n");
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
    shared_info::PrintInfo("operator=(shared_ptr&&) copyed\n");
    return *this;
}

template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& sh): m_data{sh.m_data}, m_ptr{sh.m_ptr} {
    sh.m_ptr = nullptr;
    sh.m_data = nullptr;
    shared_info::PrintInfo("shared_ptr(shared_ptr&&) moved\n");
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
    shared_info::PrintInfo("operator=(shared_ptr&&) moved\n");
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
    shared_info::PrintInfo("~shared_ptr() destroyed\n");
}

template<typename T>
T* shared_ptr<T>::get() { return m_ptr; }

template<typename T>
T& shared_ptr<T>::operator*() { return *m_ptr; } 

template<typename T>
const T* shared_ptr<T>::operator->() { return m_ptr; }

template<typename T>
shared_ptr<T>::operator bool() { return (m_ptr != nullptr); }

template<typename T>
bool shared_ptr<T>::operator!() { return (m_ptr == nullptr); }

template<typename T>
const uint16_t shared_ptr<T>::counter() const {
    return m_data->m_count; 
}

}// mlb