#pragma once
#include <cstddef>

namespace mylib {

// first simple allocator
//TODO: memory manager
class allocator {
public:
    allocator();
    allocator(const allocator& other);
    allocator& operator=(const allocator& other);
    allocator(allocator&& other);
    allocator& operator=(allocator&& other);
    ~allocator();

template<typename T>
    inline T* allocate(size_t objects_num = 1);
template<typename T>
    inline void deallocate(T* ptr, size_t capacity = 1);
template<typename T>
    inline void construct(T* ptr);
template<typename T, typename... Args> 
    inline void construct(T* ptr, Args&&... args);
template<typename T>
    inline void destroy(T* ptr);
    
};

}   // mylib