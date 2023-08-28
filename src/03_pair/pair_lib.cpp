#include "pair_lib.hpp"
#include "configured/configured.h"

#ifdef TEST_ON
#include "fortests.hpp"
    mylib::tests::MsSettings s5 {mylib::tests::Color::white, ">> pair"};
#endif

namespace mylib {

template<typename T1, typename T2>
struct PairData {
    T1 m_first;
    T2 m_second;
};

template<typename T1, typename T2>
pair<T1,T2>::pair(): pair_data{} {
#ifdef TEST_ON 
    tests::informator.PrintMess(s5, {"() created\n"}); 
#endif
}
 
template<typename T1, typename T2>
pair<T1,T2>::pair(const T1& first, const T2& second)
                 : pair_data{new PairData<T1,T2>{first, second}} {

#ifdef TEST_ON 
    tests::informator.PrintMess(s5, {"(T1&, T&2) created\n"}); 
#endif
}

template<typename T1, typename T2>
pair<T1,T2>::pair(T1&& first, T2&& second)
: pair_data{new PairData<T1,T2>{std::move(first), std::move(second)}} {

#ifdef TEST_ON 
    tests::informator.PrintMess(s5, {"(T1&&, T2&&) created\n"}); 
#endif
}

template<typename T1, typename T2>
pair<T1,T2>::pair(const pair& other) 
: pair_data{new PairData<T1,T2>{other.pair_data->m_first, other.pair_data->m_second}} {

#ifdef TEST_ON 
    tests::informator.PrintMess(s5, {"(const pair&) created\n"}); 
#endif
}

template<typename T1, typename T2>
pair<T1,T2>& pair<T1,T2>::operator=(const pair& other) {
    if (this != &other) {
        pair_data.~unique_ptr();
        pair_data = new PairData<T1,T2>
            {other.pair_data->m_first,
             other.pair_data->m_second};
    }

#ifdef TEST_ON 
    tests::informator.PrintMess(s5, {"=(const pair&) created\n"}); 
#endif
    return *this;
}

template<typename T1, typename T2>
pair<T1,T2>::pair(pair&& other) {
    pair_data = std::move(other.pair_data);

#ifdef TEST_ON 
    tests::informator.PrintMess(s5, {"(pair&&) created\n"}); 
#endif
}

template<typename T1, typename T2>
pair<T1,T2>& pair<T1,T2>::operator=(pair&& other) {
    if (this != &other) {
        pair_data = std::move(other.pair_data);
    }

#ifdef TEST_ON 
    tests::informator.PrintMess(s5, {"=(pair&&) created\n"}); 
#endif
    return *this;
}

template<typename T1, typename T2>
pair<T1,T2>::~pair() {

#ifdef TEST_ON 
    tests::informator.PrintMess(s5, {"() destroyed\n"}); 
#endif
}

template<typename T1, typename T2>
T1* pair<T1,T2>::first() const {
    if (!pair_data) {
        return nullptr;
    }
    return &(pair_data->m_first);
}

template<typename T1, typename T2>
T2* pair<T1,T2>::second() const {
    if (!pair_data) {
        return nullptr;
    }
    return &(pair_data->m_second);
}


}   // mylib