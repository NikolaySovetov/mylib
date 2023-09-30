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


   mylib::list<mylib::tests::Person> list;
   list.emplace_back("Sara");
   list.emplace_back("Jasica");
   list.emplace_back("Suzan");
   list.emplace_back("Vika");
   std::cout << "--------------------\n";

   mylib::list<mylib::tests::Person> new_list;
   new_list.emplace_back("Tom");
   new_list.emplace_back("Nik");
   std::cout << "--------------------\n";

   auto new_new__list {std::move(list)}; 
   
   mylib::list<mylib::tests::Person>::iterator it;  



   //mylib::list<mylib::tests::Person>::iterator list_iterator;


/*    mylib::list<mylib::tests::Person> list_01;
   list_01.emplace_back("Nik");
   list_01.emplace_back("Bob");
   list_01.emplace_back("Tom");

   mylib::list<mylib::tests::Person> list_02;
   list_02 = list_01;

   auto list_03 (std::move(list_01));
 */   

/*    mylib::tests::Person bob {"Bob"};
   test_list_data_type<mylib::tests::Person> list;
   list.emplace_front("Sam");
   list.emplace_back("Nik");
   list.push_back(mylib::tests::Person{"Nadine"});
   list.push_back(bob);
   list.push_front(mylib::tests::Person{"Jack"});
   list.emplace_back("Tony");
   list.emplace_back("Sara");
   list.emplace_back("Vika");

   auto base = list.get_base();
   auto it = base->next;
   for (; it != base; it = it->next) {
      auto node = list.get_node(it);
      std::cout << node->object.GetName() << ", ";
   }
   std::cout << '\n';
 */

/*    mylib::tests::informator.PrintMess(mylib::tests::Color::green, ">>> ",
                                       {"Hello", " ", "world" , "!!!", "\n"});


    mylib::unique_ptr<mylib::tests::Person> uniq_p1 {new mylib::tests::Person{"Name"}};
    auto uniq_p2 = std::move(uniq_p1);
    std::cout << uniq_p2->GetName() << '\n';
    std::cout << "------------------\n";


    mylib::shared_ptr<mylib::tests::Person> sh_p1 {new mylib::tests::Person{"Nik"}};
    auto sh_p2 {sh_p1};
    auto sh_p3 = sh_p2;
    auto sh_p4 = std::move(sh_p1);
    mylib::shared_ptr<mylib::tests::Person> sh_p5;
    sh_p5 = std::move(sh_p2);

    std::cout << "Name of Person is " << sh_p5->GetName() << '\n';
 */     

/*    std::cout << "First node: " << list.first()->GetName() << '\n';


    mylib::list<int> int_list;
    std::cout << ((int_list.empty()) ? ("empty") : ("not empty") ) << '\n'; 

    mylib::list<int> int_list1 {101};
    std::cout << ((int_list1.empty()) ? ("empty") : ("not empty") ) << '\n'; 

   mylib::list<mylib::tests::Person> list01 {mylib::tests::Person{"Nik"}};
   list01.push_back(mylib::tests::Person{"Sam"});
   list01.push_back(mylib::tests::Person{"Tom"});
   list01.push_back(mylib::tests::Person{"Bob"});
   list01.push_back(mylib::tests::Person{"Jack"});
   
   std::cout << "list01.empty():" << list01.empty() << '\n'; 
   std::cout << "==================\n";

   mylib::list<mylib::tests::Person> list02;// {mylib::tests::Person{"Nik_Nik"}};
   list02.push_back(mylib::tests::Person{"Sam_Sam"});
   list02.push_back(mylib::tests::Person{"Tom_Tom"});
   std::cout << "******************\n";

   //list02 = list01;
   list02 = std::move(list01);

   std::cout << "First name is " << list02.first()->GetName() << '\n';
 */      
 
/*    mylib::pair<mylib::tests::Person, mylib::tests::Person> p1
     {mylib::tests::Person{"Nik"}, mylib::tests::Person{"Ira"}};
  //mylib::pair<mylib::tests::Person, mylib::tests::Person> p2;
  
  auto person = p1.first();
  mylib::tests::Person vera{"Vera"};
  *(person) = vera; 
 */    

/*    mylib::list<mylib::tests::Person> list;
   list.pop_back();
   list.pop_front();

   list.push_back(mylib::tests::Person{"Nik"}); 
   list.pop_back();

   list.push_back(mylib::tests::Person{"Bob"}); 
   list.pop_front();

   list.push_back(mylib::tests::Person{"Tom"}); 
   list.push_back(mylib::tests::Person{"Jack"}); 
   std::cout << "------------------\n";

   list.push_front(mylib::tests::Person{"Front Jack"});
   list.push_front(mylib::tests::Person{"Front Bob"});
   std::cout << "------------------\n";

   list.pop_front();
   list.pop_back();
 */

/*    for (const auto& it : list) {
      std::cout << it.GetName() << ", ";
   }
   std::cout << "------------------\n";

   for (auto& it : list) {
      it.SetName("New " + it.GetName());
      std::cout << it.GetName() << ", ";
   }
   std::cout << "------------------\n";
 */
   
/*    mylib::pair<int, mylib::tests::Person> p{101, mylib::tests::Person{"Nik"}};
   std::cout << "key: " << *(p.first()) << ", name: " 
                        << p.second()->GetName() << ".\n";   
   
   std::cout << "------------------\n";

   auto p1 {p};   
   p = p1;
   auto p2 {std::move(p)};
   p = std::move(p2);   
 */   

/*    mylib::tests::Person nik {"Nik"};
   mylib::tests::Person bob {"Bob"};
   mylib::tests::Person tom {"Tom"};
   mylib::tests::Person sam {"Sam"};

   mylib::vector<mylib::tests::Person> v;
//   v.reserve(10);
   v.push_back(nik);
   v.push_back(bob);
   v.push_back(tom);
   v.push_back(sam);
 */

/*    mylib::vector<mylib::tests::OnlyMove> v;
   v.reserve(2);
   v.emplace_back();      
   v.emplace_back();      
   v.emplace_back();      
   v.emplace_back();

   std::cout << "size = " << v.size() << '\n';
   std::cout << "cap  = " << v.capacity() << '\n';

   mylib::vector<mylib::tests::OnlyMove> v1 {std::move(v)};

   v1.pop_back();

   std::cout << "size = " << v1.size() << '\n';
   std::cout << "cap  = " << v1.capacity() << '\n'; */ 

/*    mylib::vector<mylib::tests::Person> pv;
   pv.reserve(10);
   pv.push_back(mylib::tests::Person{"Nik"});
   pv.push_back(mylib::tests::Person{"Bob"});
   pv.push_back(mylib::tests::Person{"Tom"});




    mylib::vector<mylib::tests::Person> v;
   v.reserve(10);
   v.emplace_back("Nik");
   v.emplace_back("Bob");
   v.emplace_back("Tom");
   v.emplace_back("Sam");
   v.emplace_back("Jack");

   mylib::vector<mylib::tests::Person>::iterator it1 (v.begin());
   mylib::vector<mylib::tests::Person>::iterator it2;
   it2 = it1;
   auto it3 {std::move(it1)};
   mylib::vector<mylib::tests::Person>::iterator it4 (v.begin());
   it4 = std::move(it2);
   ++it4; 

   auto v_end {v.end()};
   for (; it4 != v_end; ++it4) {
      std::cout << it4->GetName() << ",   type:" << typeid(it4).name() << '\n';
   }
 */

   return 0;
}


