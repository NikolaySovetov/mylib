#include "pair_config.hpp"
#include "pair_lib.hpp"

#ifdef PAIR_TEST
#include "fortests.hpp"
    mylib::tests::MsSettings s5 {mylib::tests::Color::white, ">> pair"};
#endif

namespace mylib {

template<typename T1, typename T2>
struct pair_data_type {
    T1 first;
    T2 second;
};

template<typename T1, typename T2>
pair<T1,T2>::pair(): pair_data{T1(), T2()} {
#ifdef PAIR_TEST 
    tests::informator.PrintMess(s5, {"() created\n"}); 
#endif
}
 
template<typename T1, typename T2>
pair<T1,T2>::pair(const T1& first, const T2& second)
                 : pair_data{first, second} {

#ifdef PAIR_TEST 
    tests::informator.PrintMess(s5, {"(T1&, T&2) created\n"}); 
#endif
}

template<typename T1, typename T2>
pair<T1,T2>::pair(T1&& first, T2&& second)
: pair_data{std::move(first), std::move(second)} {

#ifdef PAIR_TEST 
    tests::informator.PrintMess(s5, {"(T1&&, T2&&) created\n"}); 
#endif
}

template<typename T1, typename T2>
pair<T1,T2>::pair(const pair& other) 
: pair_data{other.pair_data.first, other.pair_data.second} {

#ifdef PAIR_TEST 
    tests::informator.PrintMess(s5, {"(const pair&) copied\n"}); 
#endif
}

template<typename T1, typename T2>
pair<T1,T2>& pair<T1,T2>::operator=(const pair& other) {
    if (this != &other) {
        pair_data.~pair_data_type();
        pair_data.first = other.pair_data.first;
        pair_data.second = other.pair_data.second;
    }
#ifdef PAIR_TEST 
    tests::informator.PrintMess(s5, {"=(const pair&) copied\n"}); 
#endif
    return *this;
}

template<typename T1, typename T2>
pair<T1,T2>::pair(pair&& other): pair_data{std::move(other.pair_data.first),
                                           std::move(other.pair_data.second)}  {
#ifdef PAIR_TEST 
    tests::informator.PrintMess(s5, {"(pair&&) moved\n"}); 
#endif
}

template<typename T1, typename T2>
pair<T1,T2>& pair<T1,T2>::operator=(pair&& other) {
    if (this != &other) {
    pair_data.first = std::move(other.pair_data.first);
    pair_data.second = std::move(other.pair_data.second);
    }
#ifdef PAIR_TEST 
    tests::informator.PrintMess(s5, {"=(pair&&) moved\n"}); 
#endif
    return *this;
}

template<typename T1, typename T2>
pair<T1,T2>::~pair() {
#ifdef PAIR_TEST 
    tests::informator.PrintMess(s5, {"() destroyed\n"}); 
#endif
}

template<typename T1, typename T2>
T1* pair<T1,T2>::first() {
    return &(pair_data.first);
}

template<typename T1, typename T2>
T2* pair<T1,T2>::second() {
    return &(pair_data.second);
}


}   // mylib