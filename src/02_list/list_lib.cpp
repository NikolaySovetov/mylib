#include "configured/configured.h"
#include "list_lib.hpp"
#include "shared_ptr.hpp"

#ifdef TEST_ON
#include "fortests.hpp"
    mylib::tests::MsSettings s4 {mylib::tests::Color::magenta, ">> list"};
#endif

namespace mylib {

template<typename T>
struct ListNode {
    T object;
    shared_ptr<ListNode> m_next;

    ListNode() = delete;
    ListNode(const T& obj): m_next{}, object{obj} {
#ifdef TEST_ON
    tests::informator.PrintMess(mylib::tests::Color::black, 
                                "    >> ", {"ListNode(T&) created\n"}); 
#endif
    }      
    ListNode(T&& obj): m_next{}, object{std::move(obj)} {
#ifdef TEST_ON
    tests::informator.PrintMess(mylib::tests::Color::black, 
                                "    >> ", {"ListNode(T&) created\n"}); 
#endif
    }      
};

template<typename T>
struct ListData {
    size_t m_counter;
    shared_ptr<ListNode<T>> m_first;
    shared_ptr<ListNode<T>> m_last;

    ListData() = delete;
    ListData(const T& obj): m_first{new ListNode<T>{obj}},
                            m_last{}, 
                            m_counter{1} {
#ifdef TEST_ON 
    tests::informator.PrintMess(mylib::tests::Color::black, 
                                "    >> ", {"ListData(T&) created\n"});
#endif
    }
    ListData(T&& obj): m_first{new ListNode<T>{std::move(obj)}},
                            m_last{}, 
                            m_counter{1} {
#ifdef TEST_ON 
    tests::informator.PrintMess(mylib::tests::Color::black, 
                                "    >> ", {"ListData(T&&) created\n"});
#endif
    }

    void push_back(const T& obj) {
        if (m_counter == 1) {
            m_first->m_next = {new ListNode<T>{obj}};
            m_last = m_first->m_next;
            ++m_counter;
        } else {
            mylib::shared_ptr<ListNode<T>> ptr {new ListNode<T>{obj}};
            m_last->m_next = ptr;
            m_last = std::move(ptr);
        }
    } 
    void push_back(T&& obj) {
        if (m_counter == 1) {
            m_first->m_next = {new ListNode<T>{std::move(obj)}};
            m_last = m_first->m_next;
            ++m_counter;
        } else {
            mylib::shared_ptr<ListNode<T>> ptr {new ListNode<T>{std::move(obj)}};
            m_last->m_next = ptr;
            m_last = std::move(ptr);
        }
    } 
    void pop_back(const T& obj) {
        auto temp = m_first;
        m_first = {new ListNode<T>{obj}};
        m_first->m_next = std::move(temp);
    }
    void pop_back(T&& obj) {
        auto temp = m_first;
        m_first = {new ListNode<T>{std::move(obj)}};
        m_first->m_next = std::move(temp);
    }
    size_t counter() const { return m_counter; }
};

template<typename T>
list<T>::list(): list_data{} {
#ifdef TEST_ON 
    tests::informator.PrintMess(s4, {"() created\n"}); 
#endif
}

template<typename T>
list<T>::list(const T& obj): list_data{new ListData<T>{obj}} {
    list_data->m_counter = 1;
#ifdef TEST_ON 
    tests::informator.PrintMess(s4, {"(const T&) created\n"}); 
#endif
}

template<typename T>
list<T>::~list() {    
#ifdef TEST_ON 
    tests::informator.PrintMess(s4, {"() destroyed\n"}); 
#endif
}

template<typename T>
void list<T>::push_back(const T& obj) {
    if (!list_data) {
        list_data = new ListData<T>{obj}; 
    } else {
        list_data->push_back(obj);
    }
}

template<typename T>
void list<T>::push_back(T&& obj) {
    if (!list_data) {
        list_data = new ListData<T>{std::move(obj)}; 
    } else {
        list_data->push_back(std::move(obj));
    }
}

template<typename T>
void list<T>::pop_back(const T& obj) {
    if (!list_data) {
        list_data = new ListData<T>{obj}; 
    } else {
        list_data->pop_back(obj);
    }
}

template<typename T>
void list<T>::pop_back(T&& obj) {
    if (!list_data) {
        list_data = new ListData<T>{std::move(obj)}; 
    } else {
        list_data->pop_back(std::move(obj));
    }
}

template<typename T>
bool list<T>::empty() const {
    return !list_data;
}

template<typename T>
size_t list<T>::counter() const {
    if (!list_data) {
        return 0;
    }
    return list_data->m_counter;
}


}   // mylib


