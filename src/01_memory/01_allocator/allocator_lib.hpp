#pragma once
#include <cstddef>

namespace mylib {

// first simple allocator
//TODO: memory manager
class allocator {
public:
    allocator();

template<typename T>
inline T* allocate();

template<typename T>
inline T* allocate(size_t objects_num);

template<typename T>
inline void deallocate(T* ptr);

template<typename T>
inline void construct(void* ptr);

template<typename T, typename... Args> 
inline void construct(void* ptr, Args&... args);

template<typename T>
inline void destroy(T* ptr);
    
} def_allocator;

}   // mylib