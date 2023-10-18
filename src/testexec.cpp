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

   mylib::vector<mylib::tests::Person> v;
   v.emplace_back("Nik");
   v.emplace_back("Bob");
   v.emplace_back("Tom");
   v.push_back(mylib::tests::Person{"Sarah"});

   mylib::tests::Person vika {"Vika"};
   mylib::tests::Person monika {"Monika"};
   v.push_back(vika);
   v.push_back(monika);

   std::cout << v.size() << '\n';

   auto it {v.begin()};
   auto it_end   {v.end()};

   for (; it != it_end; ++it) {
      std::cout << it->GetName() << ", ";
   }
   std::cout << std::endl;


   mylib::list<mylib::tests::Person> person_list {mylib::tests::Person{"Nik"},
                                                  mylib::tests::Person{"Bob"},
                                                  mylib::tests::Person{"Tom"},
                                                  mylib::tests::Person{"Tom"},
                                                  mylib::tests::Person{"Tom"},
                                                  mylib::tests::Person{"Tom"},
                                                  mylib::tests::Person{"Tom"}};

   auto test_list = person_list;

   mylib::vector<mylib::list<mylib::tests::Person>> person_vec {person_list,
                                                                person_list,
                                                                person_list,
                                                                person_list,
                                                                person_list,
                                                                person_list,
                                                                person_list,
                                                                person_list,
                                                                person_list};
   
   auto person_vec_copy {person_vec};
   auto person_vec_move {person_vec_copy};

   mylib::vector<mylib::list<mylib::tests::Person>> person_vec_move_oper {person_list,
                                                                          person_list,
                                                                          person_list};

   person_vec_move_oper = person_vec_move;



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


