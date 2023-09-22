#include "list_config.hpp"
#include "list_lib.hpp"
#include <exception>
#include <iostream>

#ifdef LIST_TEST
#include "fortests.hpp"
    mylib::tests::MsSettings list_set {mylib::tests::Color::magenta, ">> list"};
#endif

#ifdef LIST_ITERATOR_TEST
    mylib::tests::MsSettings list_iterator_set01 
        {mylib::tests::Color::black, " >> list::iterator"};
    mylib::tests::MsSettings list_iterator_set02 
        {mylib::tests::Color::black, " >> list::const_iterator"};
#endif

namespace mylib {

template<typename T>
struct list_node_type {
    T object;
    list_node_type<T>* next_node;
    list_node_type<T>* prev_node;

public:
    list_node_type(T&& obj): object{(std::move(obj))}, 
                             next_node{nullptr},
                             prev_node{nullptr} {
    }
    list_node_type(const T& obj): object{obj}, 
                                  next_node{nullptr},
                                  prev_node{nullptr} {
    }
};

// ******* iterator *******
template<typename T>
class list<T>::iterator {
private:
    list_node_type<T>* iter_node;

public:
    iterator(): iter_node{nullptr} {
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(list_iterator_set01, {"() created\n"});
#endif
    }
    iterator(list_node_type<T>* node): iter_node{node} {
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(list_iterator_set01, {"(*node) created\n"});
#endif
    }
    iterator(const iterator& other): iter_node{other.iter_node} {
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(list_iterator_set01, {"(&) created\n"});
#endif
    }
    iterator& operator=(const iterator& other) {
        if (this != &other) {
            iter_node = other.iter_node;
        }
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(list_iterator_set01, {"=(&) created\n"});
#endif
        return *this;
    }
    iterator(iterator&& other): iter_node{other.iter_node}  {
        other.iter_node = nullptr;
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(list_iterator_set01, {"(&&) moved\n"});
#endif
    }
    iterator& operator=(iterator&& other) {
        if (this != &other) {
            iter_node = other.iter_node;
            other.iter_node = nullptr;
        }
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(list_iterator_set01, {"=(&&) moved\n"});
#endif
        return *this;
    }
    ~iterator() {
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(list_iterator_set01, {"() destroyed\n"});
#endif        
    }
    
    T& operator*() const { 
        return iter_node->object; 
    }
    void operator++() {
        iter_node = iter_node->next_node;
    }
    iterator operator++(int) {
        auto ptr = iter_node;
        iter_node = iter_node->next_node;
        return ptr;
    }
    bool operator==(const iterator& other) {
        return iter_node == other.iter_node;
    }     
    bool operator!=(const iterator& other) {
        return iter_node != other.iter_node;
    }     
    T* operator->() const {
        return &(iter_node->object);
    }

};

template<typename T>
typename list<T>::iterator list<T>::begin() const {
    return iterator(list_data.first_node);
}

template<typename T>
typename list<T>::iterator list<T>::end() const {
    //return iterator(list_data.last_node->next_node);
    return iterator();
}

// ******* const_iterator *******
template<typename T>
class list<T>::const_iterator {
private:
    list_node_type<T>* iter_node;

public:
    const_iterator(): iter_node{nullptr} {
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(list_iterator_set02, {"() created\n"});
#endif
    }
    const_iterator(list_node_type<T>* node): iter_node{node} {
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(list_iterator_set02, {"(*node) created\n"});
#endif
    }
    const_iterator(const const_iterator& other): iter_node{other.iter_node} {
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(list_iterator_set02, {"(&) created\n"});
#endif
    }
    const_iterator& operator=(const const_iterator& other) {
        if (this != &other) {
            iter_node = other.iter_node;
        }
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(list_iterator_set02, {"=(&) created\n"});
#endif
        return *this;
    }
    const_iterator(const_iterator&& other): iter_node{other.iter_node}  {
        other.iter_node = nullptr;
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(list_iterator_set02, {"(&&) moved\n"});
#endif
    }
    const_iterator& operator=(const_iterator&& other) {
        if (this != &other) {
            iter_node = other.iter_node;
            other.iter_node = nullptr;
        }
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(list_iterator_set02, {"=(&&) moved\n"});
#endif
        return *this;
    }
    ~const_iterator() {
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(list_iterator_set02, {"() destroyed\n"});
#endif        
    }
    
    const T& operator*() const { 
        return iter_node->object; 
    }
    void operator++() {
        iter_node = iter_node->next_node;
    }
    const_iterator operator++(int) {
        auto ptr = iter_node;
        iter_node = iter_node->next_node;
        return ptr;
    }
    const bool operator==(const const_iterator& other) {
        return iter_node == other.iter_node;
    }     
    const bool operator!=(const const_iterator& other) {
        return iter_node != other.iter_node;
    }     
    const T* operator->() const {
        return &(iter_node->object);
    }

};

// *** list ***
template<typename T>
const typename list<T>::const_iterator list<T>::cbegin() const {
    return const_iterator(list_data.first_node);
}

template<typename T>
const typename list<T>::const_iterator list<T>::cend() const {
    return const_iterator();
}

// ******* list *******
template<typename T>
struct list_data_type {
    list_node_type<T>* first_node;
    list_node_type<T>* last_node;
    size_t size;

public:
    list_data_type(): first_node{nullptr},
                      last_node{nullptr},
                      size {0} {
                      }     
    inline void push_back(list_node_type<T>* new_node) {
        if (size == 0) {
            first_node = new_node;
            ++size;
        } else if (size == 1) {
            first_node->next_node = new_node;
            new_node->prev_node = first_node;
            last_node = new_node;
            ++size;
        } else {
            auto temp = last_node;
            temp->next_node = new_node;
            new_node->prev_node = temp;
            last_node = new_node; 
            ++size;
        }
    }
    inline void push_front(list_node_type<T>* new_node) {
        if (size == 0) {
            first_node = new_node;
            ++size;
        } else if (size == 1) {
            last_node = first_node;    
            first_node = new_node;
            first_node->next_node = last_node;
            last_node->prev_node = first_node;    
            ++size;
        } else {
            new_node->next_node = first_node;
            first_node->prev_node = new_node;
            first_node = new_node; 
            ++size;
        }
    }
    inline void pop_back() {
        if (size == 0)
            return;
        if (size == 1) {
            delete first_node;
            first_node = nullptr;
            --size;
        } else {
            last_node = last_node->prev_node;
            delete last_node->next_node;
            last_node->next_node = nullptr;
            --size;
        }    
    }
    inline void pop_front() {
        if (size == 0)
            return;
        if (size == 1) {
            delete first_node;
            first_node = nullptr;
            --size;
        } else {
            first_node = first_node->next_node;
            delete first_node->prev_node;
            first_node->prev_node = nullptr;
            --size;
        }    
    }
};

template<typename T>
list<T>::list() {
#ifdef LIST_TEST 
    tests::informator.PrintMess(list_set, {"() created\n"});
#endif
}

template<typename T>
list<T>::list(const list& other): list_data{} {
    if (other.list_data.size > 0) {
        auto other_node = other.list_data.first_node;
        do {
            list_data.push_back(new list_node_type<T>(other_node->object)); 
            other_node = other_node->next_node;
        } while (other_node);
    }

#ifdef LIST_TEST 
    tests::informator.PrintMess(list_set, {"(&) copied\n"});
#endif
}

template<typename T>
list<T>& list<T>::operator=(const list& other) {
    if (this != &other) {
        this->~list();
        if (other.list_data.size > 0) {
            auto other_node = other.list_data.first_node;
            do {
                list_data.push_back(new list_node_type<T>(other_node->object)); 
                other_node = other_node->next_node;
            } while (other_node);
        }
    }
#ifdef LIST_TEST 
    tests::informator.PrintMess(list_set, {"=(&) copied\n"});
#endif
    return *this;
}

template<typename T>
list<T>::list(list&& other): list_data{} {
    list_data.first_node = other.list_data.first_node;
    list_data.last_node = other.list_data.last_node;
    list_data.size = other.list_data.size;
    other.list_data.first_node = nullptr;
    other.list_data.last_node = nullptr;
    other.list_data.size = 0;
#ifdef LIST_TEST 
    tests::informator.PrintMess(list_set, {"(&&) movied\n"});
#endif
}

template<typename T>
list<T>& list<T>::operator=(list&& other) {
    if (this != &other) {
        this->~list();
        list_data.first_node = other.list_data.first_node;
        list_data.last_node = other.list_data.last_node;
        list_data.size = other.list_data.size;
        other.list_data.first_node = nullptr;
        other.list_data.last_node = nullptr;
        other.list_data.size = 0;
    }
#ifdef LIST_TEST 
    tests::informator.PrintMess(list_set, {"=(&&) movied\n"});
#endif
    return *this;
}

template<typename T>
list<T>::~list() {
    if (list_data.size > 0) {
        auto curr_node = list_data.first_node;
        do {
            auto next_node = curr_node->next_node;
            delete curr_node; 
            curr_node = nullptr;
            curr_node = next_node;
        } while (curr_node);
        list_data.size = 0;
    }
#ifdef LIST_TEST 
    tests::informator.PrintMess(list_set, {"() destroyed\n"});
#endif
}

template<typename T>
void list<T>::push_back(const T& obj) {
    list_node_type<T>* new_node = new  list_node_type<T>(obj);
    if (!new_node) 
        throw std::runtime_error("exception from \"list<T>::push_back(const T&)\"");    
    list_data.push_back(new_node);
}

template<typename T>
void list<T>::push_back(T&& obj) {
    list_node_type<T>* new_node = new list_node_type<T>(std::move(obj));
    if (!new_node) 
        throw std::runtime_error("exception from \"list<T>::push_back(T&&)\"");    
    list_data.push_back(new_node);
}

template<typename T>
void list<T>::push_front(const T& obj) {
    list_node_type<T>* new_node = new  list_node_type<T>(obj);
    if (!new_node) 
        throw std::runtime_error("exception from \"list<T>::pop_back(const T&)\"");    
    list_data.push_front(new_node);
}

template<typename T>
void list<T>::push_front(T&& obj) {
    list_node_type<T>* new_node = new  list_node_type<T>(std::move(obj));
    if (!new_node) 
        throw std::runtime_error("exception from \"list<T>::pop_back(T&&)\"");    
    list_data.push_front(new_node);
}

template<typename T>
void list<T>::pop_back() {
    list_data.pop_back();
}

template<typename T>
void list<T>::pop_front() {
    list_data.pop_front();
}

template<typename T>
T* list<T>::front() const {
    if (list_data.size > 0)
        return &(list_data.first_node->object);
    return nullptr;
}

template<typename T>
bool list<T>::empty() const {
    return list_data.size == 0;
}

template<typename T>
const size_t list<T>::size() const {
    return list_data.size;
}

}   // mylib


