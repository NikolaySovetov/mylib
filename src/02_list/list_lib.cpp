#include "list_config.hpp"
#include "list_lib.hpp"
#include <iostream>

#ifdef LIST_TEST
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
    size_t m_size;
    shared_ptr<ListNode<T>> m_first;
    shared_ptr<ListNode<T>> m_last;

    ListData(const T& obj): m_first{new ListNode<T>{obj}},
                            m_last{}, m_size{1} {
#ifdef LIST_TEST 
    tests::informator.PrintMess(mylib::tests::Color::black, 
                                "    >> ", {"ListData(T&) created\n"});
#endif
    }
    ListData(T&& obj): m_first{new ListNode<T>{std::move(obj)}},
                       m_last{}, m_size{1} {
#ifdef LIST_TEST 
    tests::informator.PrintMess(mylib::tests::Color::black, 
                                "    >> ", {"ListData(T&&) created\n"});
#endif
    }

    void push_back(const T& obj) {
        if (m_size == 1) {
            m_first->m_next = {new ListNode<T>{obj}};
            m_last = m_first->m_next;
            ++m_size;
        } else {
            mylib::shared_ptr<ListNode<T>> ptr {new ListNode<T>{obj}};
            m_last->m_next = ptr;
            m_last = std::move(ptr);
            ++m_size;
        }
    } 
    void push_back(T&& obj) {
        if (m_size == 1) {
            m_first->m_next = {new ListNode<T>{std::move(obj)}};
            m_last = m_first->m_next;
            ++m_size;
        } else {
            mylib::shared_ptr<ListNode<T>> ptr {new ListNode<T>{std::move(obj)}};
            m_last->m_next = ptr;
            m_last = std::move(ptr);
            ++m_size;
        }
    } 
    void pop_back(const T& obj) {
        auto temp = m_first;
        m_first = {new ListNode<T>{obj}};
        m_first->m_next = std::move(temp);
        ++m_size;
    }
    void pop_back(T&& obj) {
        auto temp = m_first;
        m_first = {new ListNode<T>{std::move(obj)}};
        m_first->m_next = std::move(temp);
        ++m_size;
    }
    size_t counter() const { return m_size; }
};

template<typename T>
list<T>::list(): list_data{} {
#ifdef LIST_TEST 
    tests::informator.PrintMess(s4, {"() created\n"}); 
#endif
}

template<typename T>
list<T>::list(const T& obj): list_data{new ListData<T>{obj}} {
    list_data->m_size = 1;
#ifdef LIST_TEST 
    tests::informator.PrintMess(s4, {"(const T&) created\n"}); 
#endif
}

template<typename T>
list<T>::list(T&& obj): list_data{new ListData<T>{std::move(obj)}} {
    list_data->m_size = 1;
#ifdef LIST_TEST 
    tests::informator.PrintMess(s4, {"(T&&) created\n"}); 
#endif
}

template<typename T>
list<T>::list(const list& other) {
    if (other.empty()) {
        return; 
    } else {
        list_data = new ListData{*(other.begin())};
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
            list_data = new ListData<T>{/* std::move */(*(other.begin()))};
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
#ifdef LIST_TEST 
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
T* list<T>::front() const {
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
const size_t list<T>::size() const {
    if (!list_data) {
        return 0;
    }
    return list_data->m_size;
}

template<typename T>
typename list<T>::iterator list<T>::begin() const {
    return {iterator(list_data->m_first)};
}

template<typename T>
typename list<T>::iterator list<T>::end() const {
    return iterator();
}


// *** iterator ***
#ifdef LIST_TEST
    mylib::tests::MsSettings s4_1 {mylib::tests::Color::black, "    >> iterator"};
#endif

template<typename T>
class list<T>::iterator {
private:
    shared_ptr<ListNode<T>> m_itnode;

public:
    iterator() {

#ifdef LIST_TEST 
    tests::informator.PrintMess(s4_1, {"() created\n"}); 
#endif
    }
    iterator(const shared_ptr<ListNode<T>>& node): m_itnode{node} {
#ifdef LIST_TEST 
    tests::informator.PrintMess(s4_1, {"(list_node&) created\n"}); 
#endif
    }

    iterator(const iterator& other) {
        m_itnode = other.m_itnode;
#ifdef LIST_TEST 
    tests::informator.PrintMess(s4_1, {"(&) created\n"}); 
#endif
    }
    iterator& operator=(const iterator& other) {
        if (this != &other) {
            m_itnode.~shared_ptr();
            m_itnode = other.m_itnode;
        }
#ifdef LIST_TEST 
    tests::informator.PrintMess(s4_1, {"=(&) created\n"}); 
#endif
        return *this;
    }

    iterator(iterator&& other) {
        m_itnode = std::move(other.m_itnode);
#ifdef LIST_TEST 
    tests::informator.PrintMess(s4_1, {"(&&) moved\n"}); 
#endif
    }
    iterator& operator=(iterator&& other) {
        if (this != &other) {
            m_itnode.~shared_ptr();
            m_itnode = std::move(other.m_itnode);
        }
#ifdef LIST_TEST 
    tests::informator.PrintMess(s4_1, {"=(&&) moved\n"}); 
#endif
        return *this;
    }

    ~iterator() {

#ifdef LIST_TEST 
    tests::informator.PrintMess(s4_1, {"() destroyed\n"}); 
#endif
    }

    T* operator++() { 
        m_itnode = m_itnode->m_next;
        if (!m_itnode) {
            return nullptr;
        }
        return &(m_itnode->object);    
    }
    T* operator++(int) {
        if (!m_itnode) {
            return nullptr;
        }
        auto temp = m_itnode;
        m_itnode = m_itnode->m_next;
        return &(temp->object);
    }
    T* operator->() {
        if (!m_itnode) {
            return nullptr;
        }
        return &(m_itnode->object);
    }

    bool operator==(const iterator& other) {
        return (m_itnode == other.m_itnode);
    }
    bool operator!=(const iterator& other) {
        return (m_itnode != other.m_itnode);
    }

};


}   // mylib


