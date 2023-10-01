#include "list_config.hpp"
#include "list_lib.hpp"
#include <exception>
#include <type_traits>
#include <iostream>

#ifdef LIST_TEST
#include <typeinfo>
#include "fortests.hpp"
    mylib::tests::MsSettings list_set {mylib::tests::Color::magenta, ">> list"};
#endif

namespace mylib {

// *** base_node_type ***
template<typename T>
list<T>::base_node_type::base_node_type()
: prev{nullptr}, next{nullptr} {
}

template<typename T>
typename list<T>::base_node_type* list<T>::base_node_type::get_next() {
    return this->next;
}

template<typename T>
T* list<T>::base_node_type::get_ptr(base_node_type* node) const {
    return &(reinterpret_cast<node_type*>(node)->object);
}

template<typename T>
T& list<T>::base_node_type::get_ref(base_node_type* node) const {
    return reinterpret_cast<node_type*>(node)->object;
}

// *** node_type ***
template<typename T>
template<typename... Args>
list<T>::node_type::node_type(Args&... args)
: base_node_type(), object(std::forward<Args>(args)...) {
}

template<typename T>
inline void list<T>::base_node_init() {
    base_node = alloc->allocate<base_node_type>();
    alloc->construct<base_node_type>(base_node);
}

// *** list ***
template<typename T>
template<typename... Args>
inline typename list<T>::node_type* list<T>::construct_node(Args&... args) {
    node_type* new_node = nullptr;
    try {
        new_node = alloc->allocate<node_type>();
        alloc->construct<node_type, Args...>(new_node, args...);        
    }
    catch(const std::bad_alloc& e) {
        std::cerr << e.what() << '\n';
        throw;
    }
    catch(...) {
        alloc->destroy(new_node); 
        throw;   
    }
    return new_node;
}

template<typename T>
inline void list<T>::copy_nodes_from(const base_node_type* base_node) {
    if (base_node == nullptr) {
        return;
    }    
    base_node_type* node = base_node->next;
    if (node != nullptr) {
        for (; node != base_node; node = node->next) {
            node_type* curr_node = reinterpret_cast<node_type*>(node);
            emplace_back(static_cast<const T&>(curr_node->object));    
        }
    }
}

template<typename T>
inline void list<T>::destroy_nodes() {
    base_node_type* temp_node = base_node->next;
    if (temp_node == nullptr) {
        return;
    }
    for (; temp_node != base_node;) {
        base_node_type* next_node = temp_node->next;
        node_type* cur_node = reinterpret_cast<node_type*>(temp_node);
        alloc->destroy<T>(&(cur_node->object));
        alloc->deallocate<node_type>(cur_node);
        temp_node = next_node;
    }
    base_node->next = nullptr;
    base_node->prev = nullptr;
    m_size = 0;
}

template<typename T>
inline void list<T>::insetr_first_node(node_type* new_node) {
    new_node->next = base_node;
    new_node->prev = base_node;
    base_node->next = new_node;
    base_node->prev = new_node;
    ++m_size;
}

template<typename T>
inline void list<T>::insert_back(node_type* new_node) {
    if (m_size == 0) {
        insetr_first_node(new_node);        
    } else {
        base_node_type* ptr = base_node->prev;
        base_node->prev = new_node;
        new_node->next = base_node;
        new_node->prev = ptr;
        ptr->next = new_node;
        ++m_size;
    }
}

template<typename T>
inline void list<T>::insert_front(node_type* new_node) {
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

template<typename T>
list<T>::list(mylib::allocator* a): alloc{a}, m_size{0} {    
#ifdef LIST_TEST
    tests::informator.PrintMess(list_set, 
        {"( type: ", typeid(T).name(), " ) created\n"}); 
#endif

    base_node_init();
}

template<typename T>
list<T>::list(size_t sz, const T& t, mylib::allocator* a): alloc{a}, m_size{0} {
#ifdef LIST_TEST
    tests::informator.PrintMess(list_set, 
        {"( type: ", typeid(T).name(), " ) created\n"}); 
#endif

    base_node_init();
    for (size_t i {0}; i < sz; ++i) {
        emplace_back(t);
    }
}

template<typename T>
list<T>::list(const std::initializer_list<T>& init_list, mylib::allocator* a)
: alloc{a}, m_size{0} {
#ifdef LIST_TEST
    tests::informator.PrintMess(list_set, 
        {"( std::init_list of type: \"", typeid(T).name(), "\" ) created\n"}); 
#endif

    base_node_init();
    size_t size {init_list.size()};
    const T* arr = init_list.begin();
    for (size_t i {0}; i < size; ++i) {
        emplace_back(arr[i]);
    }
}

template<typename T>
list<T>::list(const list& other, mylib::allocator* alloc) {
#ifdef LIST_TEST
    tests::informator.PrintMess(list_set, {"(&) copyed\n"}); 
#endif

    base_node_init();
    copy_nodes_from(other.base_node);
}

template<typename T>
list<T>& list<T>::operator=(const list& other) {
#ifdef LIST_TEST
    tests::informator.PrintMess(list_set, {"=(&) copyed\n"}); 
#endif

    if (this != &other) {
        alloc = other.alloc;
        destroy_nodes();
        copy_nodes_from(other.base_node);
    }
    return *this;
}

template<typename T>
list<T>::list(list&& other, mylib::allocator* alloc)
: alloc{other.alloc}, base_node{other.base_node}, m_size{other.m_size} {
#ifdef LIST_TEST
    tests::informator.PrintMess(list_set, {"(&&) moved\n"}); 
#endif

    other.base_node_init();            
    other.m_size = 0;            
    alloc = alloc;
}

template<typename T>
list<T>& list<T>::operator=(list&& other) {
#ifdef LIST_TEST
    tests::informator.PrintMess(list_set, {"=(&&) moved\n"}); 
#endif

    if (this != &other) {
        destroy_nodes();
        alloc->deallocate<base_node_type>(base_node);
        
        alloc = other.alloc;
        base_node = other.base_node;
        m_size = other.m_size;
        other.base_node_init();
        other.m_size = 0;
    }
    return *this;
}

template<typename T>
list<T>::~list() {
#ifdef LIST_TEST
    tests::informator.PrintMess(list_set, 
        {"( type: ", typeid(T).name(), " ) destroyed\n"}); 
#endif
    
    destroy_nodes();
    alloc->deallocate<>(base_node);    
}

template<typename T>
template<typename... Args>
void list<T>::emplace_back(Args&... args) {
    insert_back(construct_node(args...));
}

template<typename T>
template<typename... Args>
void list<T>::emplace_front(Args&... args) {
    insert_front(construct_node(args...));
}

template<typename T>
void list<T>::push_back(const T& obj) {
    emplace_back(obj);
}

template<typename T>
void list<T>::push_back(T&& obj) {
    emplace_back(obj);
}

template<typename T>
void list<T>::push_front(const T& obj) {
    emplace_front(obj);
}

template<typename T>
void list<T>::push_front(T&& obj) {
    emplace_front(obj);
}

template<typename T>
void list<T>::pop_back() {
    if (size == 0) {
        return;
    } else if (size == 1) {
        destroy_nodes();
    } else {
        node_type* dead_node = reinterpret_cast<node_type*>(base_node->next);
        base_node_type* live_node = dead_node->next;
        
        alloc->destroy<T>(&(dead_node->object));
        alloc->deallocate<node_type>(dead_node);
        
        live_node->prev = base_node;
        base_node->next = live_node;
        --size;
    }
}

template<typename T>
void list<T>::pop_front() {
    if (size == 0) {
        return;
    } else if (size == 1) {
        destroy_nodes();
    } else {
        node_type* dead_node = reinterpret_cast<node_type*>(base_node->prev);
        base_node_type* live_node = dead_node->prev;
        
        alloc->destroy<T>(&(dead_node->object));
        alloc->deallocate<node_type>(dead_node);
        
        live_node->next = base_node;
        base_node->prev = live_node;
        --size;
    }
}

template<typename T>
size_t list<T>::size() const {
    return this->m_size;
}

template<typename T>
bool list<T>::empty() const {
    return (base_node->next == nullptr);
}

// *** iterator ***
template<typename T>
typename list<T>::iterator list<T>::begin() {
    return base_iterator<list<T>::base_node_type, T*, T&>(base_node->next);
}

template<typename T>
typename list<T>::iterator list<T>::end() {
    return base_iterator<list<T>::base_node_type, T*, T&>(base_node);
}


}   // mylib


