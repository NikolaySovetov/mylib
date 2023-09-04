#include "list_config.hpp"
#include "list_lib.hpp"
#include <iostream>

#ifdef LIST_TEST
#include "fortests.hpp"
    mylib::tests::MsSettings s4 {mylib::tests::Color::magenta, ">> list"};
#endif

#ifdef LIST_TEST_ITERATOR
    mylib::tests::MsSettings s4_1 {mylib::tests::Color::black, " >> list::iterator"};
#endif


namespace mylib {

template<typename T>
struct list_node_type {
    T object;
    list_node_type<T>* next_node;

public:
    list_node_type(T&& obj): object{(std::move(obj))}, next_node{nullptr} {
    }
    list_node_type(const T& obj): object{obj}, next_node{nullptr} {
    }
};

template<typename T>
class list<T>::iterator {
private:
    list_node_type<T>* iter_node;

public:
    iterator(): iter_node{nullptr} {
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(s4_1, {"() created\n"});
#endif
    }
    iterator(list_node_type<T>* node): iter_node{node} {
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(s4_1, {"(node) created\n"});
#endif
    }
    iterator(const iterator& other): iter_node{other.iter_node} {
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(s4_1, {"(&) created\n"});
#endif
    }
    iterator& operator=(const iterator& other) {
        if (this != &other) {
            iter_node = other.iter_node;
        }
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(s4_1, {"=(&) created\n"});
#endif
    return *this;
    }
    iterator(iterator&& other): iter_node{other.iter_node}  {
        other.iter_node = nullptr;
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(s4_1, {"(&&) created\n"});
#endif
    }
    iterator& operator=(iterator&& other) {
        if (this != &other) {
            iter_node = other.iter_node;
            other.iter_node = nullptr;
        }
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(s4_1, {"=(&&) created\n"});
#endif
        return *this;
    }
    ~iterator() {
#ifdef LIST_TEST_ITERATOR 
    tests::informator.PrintMess(s4_1, {"() destroyed\n"});
#endif        
    }
    
    iterator operator++() {
        iter_node = iter_node->next_node;
        return iter_node;
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
struct list_data_type {
    list_node_type<T>* first_node;
    list_node_type<T>* last_node;
    typename list<T>::iterator<T> end_iterator();
    size_t size;

public:
    list_data_type(): first_node{nullptr},
                      last_node{nullptr},
                      //end_iterator{list<T>::iterator()},
                      size {0} {

                      }     
    inline void push_back(list_node_type<T>* new_node) {
        if (size == 0) {
            first_node = new_node;
            ++size;
        } else if (size == 1) {
            first_node->next_node = new_node;
            last_node = new_node;
            ++size;
        } else {
            auto temp = last_node;
            temp->next_node = new_node;
            last_node = new_node; 
            ++size;
        }
    }
    inline void pop_back(list_node_type<T>* new_node) {
        if (size == 0) {
            first_node = new_node;
            first_node->next_node = nullptr;
            ++size;
        } else if (size == 1) {
            last_node = first_node;    
            first_node = new_node;
            first_node->next_node = last_node;
            ++size;
        } else {
            new_node->next_node = first_node;
            first_node = new_node; 
            ++size;
        }
    }
};

template<typename T>
typename list<T>::iterator list<T>::begin() const {
    return iterator(list_data.first_node);
}

template<typename T>
typename list<T>::iterator list<T>::end() const {
    return iterator(list_data.last_node->next_node);
}

template<typename T>
list<T>::list() {
#ifdef LIST_TEST 
    tests::informator.PrintMess(s4, {"() created\n"});
#endif
}

template<typename T>
list<T>::~list() {
    if (list_data.size > 0) {
        auto ptr = list_data.first_node;
        do {
            auto next = ptr->next_node;
            delete ptr; 
            ptr = nullptr;
            ptr = next;
        } while (ptr);
    }
#ifdef LIST_TEST 
    tests::informator.PrintMess(s4, {"() destroyed\n"});
#endif
}

template<typename T>
void list<T>::push_back(const T& obj) {
    list_node_type<T>* new_node = new  list_node_type<T>(obj);
    if (!new_node) 
        throw;    
    list_data.push_back(new_node);
}

template<typename T>
void list<T>::push_back(T&& obj) {
    list_node_type<T>* new_node = new list_node_type<T>(std::move(obj));
    if (!new_node) 
        throw;    
    list_data.push_back(new_node);
}

template<typename T>
void list<T>::pop_back(const T& obj) {
    list_node_type<T>* new_node = new  list_node_type<T>(obj);
    if (!new_node) 
        throw;    
    list_data.pop_back(new_node);
}

template<typename T>
void list<T>::pop_back(T&& obj) {
    list_node_type<T>* new_node = new  list_node_type<T>(std::move(obj));
    if (!new_node) 
        throw;    
    list_data.pop_back(new_node);
}

template<typename T>
T* list<T>::front() const {
    if (list_data.size > 0)
        return &(list_data.first_node->object);
    return nullptr;
}

}   // mylib


