#include "list_config.hpp"
#include "list_lib.hpp"
#include <exception>
#include <iostream>

#ifdef LIST_TEST
#include <typeinfo>
#include "fortests.hpp"
    mylib::tests::MsSettings list_set {mylib::tests::Color::magenta, ">> list"};
#endif

namespace mylib {

template<typename T>
struct list_data_type {
protected:
    mylib::allocator* alloc;
    struct base_node_type {
        base_node_type* next;
        base_node_type* prev;
    
        base_node_type(): prev{nullptr}, next{nullptr} {}
    };     
    struct node_type : public base_node_type {
        T object;

        template<typename... Args>
        node_type(Args&... args): base_node_type(), object(std::forward<Args>(args)...) {
        }
    };         

    base_node_type* base_node;     
    size_t size;

private:
    friend class list<T>;
    inline void insetr_first_node(node_type* new_node) {
        new_node->next = base_node;
        new_node->prev = base_node;
        base_node->next = new_node;
        base_node->prev = new_node;
        ++size;
    }
    inline void insert_back(node_type* new_node) {
        if (size == 0) {
            insetr_first_node(new_node);        
        } else {
            base_node_type* ptr = base_node->prev;
            base_node->prev = new_node;
            new_node->next = base_node;
            new_node->prev = ptr;
            ptr->next = new_node;
            ++size;
        }
    }
    inline void insert_front(node_type* new_node) {
        if (size == 0) {
            insetr_first_node(new_node);        
        } else {
            base_node_type* ptr = base_node->next;
            base_node->next = new_node;
            new_node->next = ptr;
            new_node->prev = base_node;
            ptr->prev = new_node;
            ++size;
        }
    }

protected: 
    list_data_type(mylib::allocator* a): alloc{a}, size{0} {     
        base_node = alloc->allocate<base_node_type>();
        alloc->construct<base_node_type>(base_node);
    }

    template<typename... Args>
    inline void emplace_back(Args&... args) {
        node_type* new_node = alloc->allocate<node_type>();
        alloc->construct<node_type, Args...>(new_node, args...);        
        insert_back(new_node);
    }
    template<typename... Args>
    inline void emplace_front(Args&... args) {
        node_type* new_node = alloc->allocate<node_type>();
        alloc->construct<node_type, Args...>(new_node, args...);        
        insert_front(new_node);
    }
    
    void push_back(const T& obj) {
        emplace_back(obj);
    }
    void push_back(T&& obj) {
        emplace_back(obj);
    }
    void push_front(const T& obj) {
        emplace_front(obj);
    }
    void push_front(T&& obj) {
        emplace_front(obj);
    }
    size_t sz() const {
        return size;
    }
    base_node_type* get_base() {
        return base_node;
    }
    node_type* get_node(base_node_type* base) {
        return static_cast<node_type*>(base);           
    }
};

template<typename T>
list<T>::list(mylib::allocator* alloc): list_data(alloc) {    
#ifdef LIST_TEST
    tests::informator.PrintMess(list_set, 
        {"( type: ", typeid(T).name(), " ) created\n"}); 
#endif
}

template<typename T>
list<T>::list(size_t sz, const T& t, mylib::allocator* alloc): list_data(alloc) {
#ifdef LIST_TEST
    tests::informator.PrintMess(list_set, 
        {"( type: ", typeid(T).name(), " ) created\n"}); 
#endif

    for (size_t i {0}; i < sz; ++i) {
        list_data.emplace_back(t);
    }
}

template<typename T>
list<T>::list(const std::initializer_list<T>& init_list, mylib::allocator* alloc)
: list_data(alloc) {
#ifdef LIST_TEST
    tests::informator.PrintMess(list_set, 
        {"( std::init_list of type: \"", typeid(T).name(), "\" ) created\n"}); 
#endif

    size_t size {init_list.size()};
    const T* arr = init_list.begin();
    for (size_t i {0}; i < size; ++i) {
        list_data.emplace_back(arr[i]);
    }
}

template<typename T>
list<T>::list(const list& other, mylib::allocator* alloc): list_data{alloc} {
#ifdef LIST_TEST
    tests::informator.PrintMess(list_set, 
        {"( std::init_list of type: \"", typeid(T).name(), "\" ) created\n"}); 
#endif

}

template<typename T>
list<T>::~list() {
}

template<typename T>
template<typename... Args>
void list<T>::emplace_back(Args&... args) {
}


}   // mylib


