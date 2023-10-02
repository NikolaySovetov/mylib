#include "testexec.hpp"
#include "fortests.hpp"
#include "unique_ptr.hpp"
#include "shared_ptr.hpp"
#include "base_iterator.hpp"
#include "list.hpp"
#include "pair.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>
#include <typeinfo>
#include <chrono>
#include <thread>


int main()  {

   //mylib::vector<mylib::tests::Person> v;
   //v.reserve(10);

   //mylib::vector<mylib::tests::Person> v (4);
   mylib::vector<mylib::tests::Person> v(4);



   mylib::list<mylib::tests::Person> list;
   list.emplace_back("Sara");
   list.emplace_back("Jasica");
   list.emplace_back("Suzan");
   list.emplace_back("Vika");
   std::cout << "--------------------\n";

   auto end = list.end();
   for (auto it {list.begin()}; it != end; ++it) {
      std::cout << it->GetName() << " "; 
   }
   std::cout << std::endl;

   for (const auto& it : list) {
      std::cout << it.GetName() << " "; 
   }
   std::cout << std::endl;
   std::cout << "--------------------\n";

   mylib::list<int> int_list;
   int_list.push_back(101);
   int_list.push_back(102);
   int_list.push_back(103);
   int_list.push_back(104);

   auto int_end = int_list.end();
   for (auto it {int_list.begin()}; it != int_end; ++it) {
      std::cout << *it << " "; 
   }
   std::cout << std::endl;


   return 0;
}


