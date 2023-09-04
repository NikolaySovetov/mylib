#include "list_config.hpp"
#include "list_lib.hpp"
#include <iostream>

#ifdef LIST_TEST
#include "fortests.hpp"
    mylib::tests::MsSettings s4 {mylib::tests::Color::magenta, ">> list"};
#endif

namespace mylib {

template<typename T>
struct list_node_type {
    T object;
    list_node_type<T>* next_node;
};

template<typename T>
struct list_data_type {
    list_node_type<T>* first_node;
    list_node_type<T>* last_node;
    size_t size;

    inline void add_node(list_node_type<T>* new_node) {
        new_node->next_node = nullptr;
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
};

template<typename T>
list<T>::list(): list_data{.first_node = nullptr,
                           .last_node  = nullptr,
                           .size  = 0     } {
#ifdef LIST_TEST 
    tests::informator.PrintMess(s4, {"() created\n"});
#endif
}

template<typename T>
void list<T>::push_back(const T& obj) {
    list_node_type<T>* new_node = new  list_node_type<T>;
    if (!new_node) 
        throw;    
    new_node->object = obj;

    list_data.add_node(new_node);
}

template<typename T>
void list<T>::push_back(T&& obj) {
    list_node_type<T>* new_node = new list_node_type<T>;
    if (!new_node) 
        throw;    
    new_node->object = std::move(obj);

    list_data.add_node(new_node);
}




}   // mylib


