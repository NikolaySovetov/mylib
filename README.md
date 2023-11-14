Tested in GCC compiler.

Purpose of this project is reinforce the basic of C++ language. 
In this project I create simple container classes and test it with copying and moving a simple classes contained it.
  
About context.

00_testlib: This part contains simple classes for creating, copying and moving. Also there a "PrintC" class for output colored text on the console. This function is managed from the CMake files.

01_memory: This was first part of this project. I was repeats the move semantic by smart pointers. Allocator class was added later. Today it was no any logic. But next time I plan to create pool allocator and allocator based on red-black tree logic.

02_iterator: I tried some variants, but copy of std::iterator as base is better.  

03_initializer_list: My first acquaintance with variadic template.  

04_list. This is "list" container class. It uses "face node" as base and that is probably all features.

05_pair. I know that in the original used "tuple" class as base. My pair just template class with two types.

06_vector. vector is power! In this case I solved (i hope that solved) a problem with reallocation "only move" and "only copy" classes. Yes priority is copy, if it possible, because it more safety. But how to be with "only move" class.
I used "is_copy_constructible" of "type_traits" header. In my tests it is work.

Thank you to read this! I will be glad your criticism and comments: sovetov.k@gmail.com
