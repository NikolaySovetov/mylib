//#include "shared_configured.h"
#include "shared_config.hpp"
#include "shared_ptr_lib.hpp"

#ifdef SHARED_TEST 
#include "fortests.hpp"
    mylib::tests::MsSettings s3{mylib::tests::Color::green, " >> sh_ptr"};
        static int  common_shared_counter {0};
        static bool shared_destroyed_marker {false};
#endif

namespace mylib {

struct SharedData {
    uint16_t sh_count;

    SharedData(): sh_count{1} {}
    void operator++() { ++sh_count; }
    void operator--() { --sh_count; }
    bool operator<(uint16_t val) { return sh_count < val; }
};

template<typename T>
shared_ptr<T>::shared_ptr(): sh_data{nullptr}, sh_ptr{nullptr} {
#ifdef SHARED_TEST 
    tests::informator.PrintMess(s3, {"() created\n"});
    ++common_shared_counter;     
#endif
}

template<typename T>
shared_ptr<T>::shared_ptr(T* ptr): sh_data{new SharedData()}, sh_ptr{ptr} {
#ifdef SHARED_TEST 
    tests::informator.PrintMess(s3, {"(T*) created\n"}); 
    ++common_shared_counter; 
#endif
}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& sh): sh_data{sh.sh_data}, sh_ptr{sh.sh_ptr} {
    ++(*sh_data);
#ifdef SHARED_TEST 
    tests::informator.PrintMess(s3, {"(const sh_ptr&) copied\n"}); 
    ++common_shared_counter; 
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
#ifdef SHARED_TEST 
    tests::informator.PrintMess(s3, {" =(sh_ptr) copied\n"});  
#endif
    return *this;
}

template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& sh): sh_data{sh.sh_data}, sh_ptr{sh.sh_ptr} {
    sh.sh_ptr = nullptr;
    sh.sh_data = nullptr;
#ifdef SHARED_TEST 
    tests::informator.PrintMess(s3, {"(sh_ptr&&) moved\n"}); 
    ++common_shared_counter; 
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
#ifdef SHARED_TEST 
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
            sh_ptr = nullptr;
            sh_data = nullptr;
#ifdef SHARED_TEST
    shared_destroyed_marker = true;
#endif
        }
    }

#ifdef SHARED_TEST
    if (shared_destroyed_marker) {
        --common_shared_counter;
        tests::informator.PrintMess(s3, {"(T) destroyed\t\t--- counter: ", 
                                    std::to_string(common_shared_counter).c_str(),
                                    "\n"});
        shared_destroyed_marker = false;                             
    } else {
        --common_shared_counter;
        tests::informator.PrintMess(s3, {"() destroyed\t--- counter: ", 
                                    std::to_string(common_shared_counter).c_str(),
                                    "\n"}); 
    }
#endif

}

template<typename T>
T* shared_ptr<T>::get() const { return sh_ptr; }

template<typename T>
T& shared_ptr<T>::operator*() const { return *sh_ptr; } 

template<typename T>
T* shared_ptr<T>::operator->() const { return sh_ptr; }

template<typename T>
bool shared_ptr<T>::operator==(const shared_ptr& other) const { 
    return (sh_ptr == other.sh_ptr);
}

template<typename T>
bool shared_ptr<T>::operator!=(const shared_ptr& other) const { 
    return !(sh_ptr == other.sh_ptr);
}

template<typename T>
shared_ptr<T>::operator bool() const { return (sh_ptr != nullptr); }

template<typename T>
bool shared_ptr<T>::operator!() const { return (sh_ptr == nullptr); }

template<typename T>
const uint16_t shared_ptr<T>::counter() const {
    return sh_data->sh_count; 
}

}   // mylib