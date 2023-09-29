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

template<typename T>
struct list_data_type {
protected:
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

    mylib::allocator* alloc;
    base_node_type* base_node;     
    size_t size;

private:
    friend class list<T>;
    inline void base_node_init() {
        base_node = alloc->allocate<base_node_type>();
        alloc->construct<base_node_type>(base_node);
    }
    template<typename... Args>
        inline node_type* construct_node(Args&... args) {
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
    inline void copy_nodes_from(const base_node_type* base_node) {
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
    inline void destroy_nodes() {
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
        size = 0;
    }
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
        base_node_init();
    }
    list_data_type(const list_data_type& other, mylib::allocator* a): alloc{a}, size{0} {
        base_node_init();
        copy_nodes_from(other.base_node);
    }
    list_data_type& operator=(const list_data_type& other) {
        alloc = other.alloc;
        destroy_nodes();
        copy_nodes_from(other.base_node);
        return *this;
    }
    list_data_type(list_data_type&& other)
    : alloc{other.alloc}, base_node{other.base_node}, size{other.size} {
        other.base_node_init();            
        other.size = 0;            
    }
    list_data_type& operator=(list_data_type&& other) {
        alloc = other.alloc;
        base_node = other.base_node;
        size = other.size;

        other.base_node_init();
        other.size = 0;
        return *this;
    }
    ~list_data_type() {
        destroy_nodes();
        alloc->deallocate<>(base_node);    
    }

    template<typename... Args>
        inline void emplace_back(Args&... args) {        
            insert_back(construct_node(args...));
    }
    template<typename... Args>
        inline void emplace_front(Args&... args) {
            insert_front(construct_node(args...));
    }
    inline void pop_back() {
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
    inline void pop_front() {
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
list<T>::list(const list& other, mylib::allocator* alloc)
: list_data{other.list_data, alloc} {
#ifdef LIST_TEST
    tests::informator.PrintMess(list_set, {"(&) copyed\n"}); 
#endif

}

template<typename T>
list<T>& list<T>::operator=(const list& other) {
#ifdef LIST_TEST
    tests::informator.PrintMess(list_set, {"=(&) copyed\n"}); 
#endif

    if (this != &other) {
        list_data = other.list_data;
    }
    return *this;
}

template<typename T>
list<T>::list(list&& other, mylib::allocator* alloc)
: list_data{std::move(other.list_data)} {
#ifdef LIST_TEST
    tests::informator.PrintMess(list_set, {"(&&) moved\n"}); 
#endif

    list_data.alloc = alloc;
}

template<typename T>
list<T>& list<T>::operator=(list&& other) {
#ifdef LIST_TEST
    tests::informator.PrintMess(list_set, {"=(&&) moved\n"}); 
#endif

    if (this != &other) {
        list_data = std::move(other.list_data);
    }
    return *this;
}

template<typename T>
list<T>::~list() {
#ifdef LIST_TEST
    tests::informator.PrintMess(list_set, 
        {"( type: ", typeid(T).name(), " ) destroyed\n"}); 
#endif
}

template<typename T>
template<typename... Args>
void list<T>::emplace_back(Args&... args) {
    list_data.emplace_back(args...);
}

template<typename T>
template<typename... Args>
void list<T>::emplace_front(Args&... args) {
    list_data.emplace_front(args...);
}

template<typename T>
void list<T>::push_back(const T& obj) {
    list_data.emplace_back(obj);
}

template<typename T>
void list<T>::push_back(T&& obj) {
    list_data.emplace_back(obj);
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
    list_data.pop_back();
}

template<typename T>
void list<T>::pop_front() {
    list_data.pop_front();
}

template<typename T>
size_t list<T>::size() const {
    return list_data.size;
}

template<typename T>
bool list<T>::empty() const {
    return (list_data.base_node->next == nullptr);
}

// *** iterator ***


/* 
template<typename T>
list<T>::iterator::iterator(T* ptr)
: base_iterator<T>(list_data.base_node->next) {
}

template<typename T>
list<T>::iterator::iterator(const iterator& other): base_iterator<T>(other) {
}

template<typename T>
typename list<T>::iterator& list<T>::iterator::operator=(const iterator& other) {
    if (this != &other) {
        this->it = nullptr;
        this->it = other.it;
    }
    return *this;
}

template<typename T>
list<T>::iterator::iterator(iterator&& other): base_iterator<T>(std::move(other)) {
}

template<typename T>
typename list<T>::iterator& list<T>::iterator::operator=(iterator&& other) {
    if (this != &other) {
        this->it = nullptr;
        this->it = other.it;
        other.it = nullptr;
    }
    return *this;
}

template<typename T>
list<T>::iterator::~iterator() {
}

 */
/* template<typename T>
void list<T>::iterator::operator++() {
    it = it->next;
}

template<typename T>
bool list<T>::iterator::operator!=(const base_iterator<T>& other) const {
    return (this->it != other.get());
}

template<typename T>
T* list<T>::iterator::operator->() const {
    return this->it;
}

template<typename T>
T& list<T>::iterator::operator*() const {
    return *(this->it);
}

template<typename T>
typename list<T>::iterator list<T>::begin() const {
    return typename list<T>::iterator(&(this->list.arr[0]));
}

template<typename T>
typename list<T>::iterator list<T>::end() const {
    return typename list<T>::iterator(&(this->list.arr[list.size]));
}
 */

/* template<typename T>
typename list<T>::iterator list<T>::begin() const {
    return typename list<T>::iterator(&(this->vector_data.arr[0]));
}
 */

}   // mylib


