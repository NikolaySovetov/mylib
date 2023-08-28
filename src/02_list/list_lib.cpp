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
};

template<typename T>
struct ListData {
    size_t m_counter;
    shared_ptr<ListNode<T>> m_first;
    shared_ptr<ListNode<T>> m_last;

    ListData(const T& obj): m_first{new ListNode<T>{obj}},
                            m_last{}, m_counter{1} {
#ifdef TEST_ON 
    tests::informator.PrintMess(mylib::tests::Color::black, 
                                "    >> ", {"ListData(T&) created\n"});
#endif
    }
    ListData(T&& obj): m_first{new ListNode<T>{std::move(obj)}},
                       m_last{}, m_counter{1} {
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
            ++m_counter;
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
            ++m_counter;
        }
    } 
    void pop_back(const T& obj) {
        auto temp = m_first;
        m_first = {new ListNode<T>{obj}};
        m_first->m_next = std::move(temp);
        ++m_counter;
    }
    void pop_back(T&& obj) {
        auto temp = m_first;
        m_first = {new ListNode<T>{std::move(obj)}};
        m_first->m_next = std::move(temp);
        ++m_counter;
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
list<T>::list(T&& obj): list_data{new ListData<T>{std::move(obj)}} {
    list_data->m_counter = 1;
#ifdef TEST_ON 
    tests::informator.PrintMess(s4, {"(T&&) created\n"}); 
#endif
}

template<typename T>
list<T>::list(const list& other) {
    if (other.empty()) {
        return; 
    } else {
        list_data = new ListData{*(other.first())};
        auto next_node = other.list_data->m_first->m_next.get();
        while (next_node) {
            this->push_back(next_node->object);
            next_node = next_node->m_next.get();
        }
    }
}

template<typename T>
list<T>& list<T>::operator=(const list& other) {
    if (this != &other) {
        list_data.~unique_ptr();
        if (!other.empty()) {
            list_data = new ListData<T>{std::move(*(other.first()))};
            auto next_node = other.list_data->m_first->m_next.get();
            while (next_node) {
                this->push_back(next_node->object);
                next_node = next_node->m_next.get();
            }
        }
    }
    return *this;
}

template<typename T>
list<T>::list(list&& other) {
    this->list_data = std::move(other.list_data);
}

template<typename T>
list<T>& list<T>::operator=(list&& other) {
    if (this != &other) {
        list_data.~unique_ptr();
        list_data = std::move(other.list_data);
    }
    return *this;
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
const T* list<T>::first() const {
    if (!list_data) {
        return nullptr;
    }
    return &(list_data->m_first->object);
}

template<typename T>
bool list<T>::empty() const {
    return !list_data;
}

template<typename T>
const size_t list<T>::counter() const {
    if (!list_data) {
        return 0;
    }
    return list_data->m_counter;
}


}   // mylib


