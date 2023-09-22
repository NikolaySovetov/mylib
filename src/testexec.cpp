#include "testexec.hpp"
#include "fortests.hpp"
#include "unique_ptr.hpp"
#include "shared_ptr.hpp"
#include "list.hpp"
#include "pair.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>

int main()  {

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

/*    mylib::list<mylib::tests::Person> list;
   list.push_back(mylib::tests::Person{"Nik"});
   list.push_back(mylib::tests::Person{"Bob"});
   list.push_back(mylib::tests::Person{"Tom"});
   list.pop_back(mylib::tests::Person{"Ira"});
   list.pop_back(mylib::tests::Person{"Vika"});
   list.pop_back(mylib::tests::Person{"Anna"});

   std::cout << "******************\n";    

   //mylib::list<mylib::tests::Person>::iterator it{list.begin()};

   for (auto it = list.begin(); it != list.end(); ++it) {
      std::cout << it->GetName() << ' ';
   }
   std::cout << std::endl; */

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

/*    test_vector<mylib::shared_ptr<int>> sh_vect;
   sh_vect.push_back(new int{101});
   sh_vect.push_back(new int{102});
   sh_vect.push_back(new int{103});
   sh_vect.push_back(new int{104});
   sh_vect.push_back(new int{105});
 */

/*    OnlyMoved nc;
   test_vector<OnlyMoved> nc_v;
   nc_v.push_back(nc); 
   nc_v.push_back(nc); 
   nc_v.push_back(nc); 
   nc_v.push_back(nc); 
   nc_v.push_back(nc); 
 */

/*    test_vector<mylib::tests::Person> v;
   v.push_back(mylib::tests::Person{"Nik"});
   v.push_back(mylib::tests::Person{"Bob"});
   v.push_back(mylib::tests::Person{"Tom"});
 */

/*    test_vector<mylib::tests::Movable> copyable_vec;
   copyable_vec.push_back(mylib::tests::Movable()); 
   std::cout << "-------\n";
   copyable_vec.push_back(mylib::tests::Movable()); 
   std::cout << "-------\n";
   copyable_vec.push_back(mylib::tests::Movable()); 
   std::cout << "-------\n";

   test_vector<mylib::tests::Movable> movable_vec;
   movable_vec.push_back(mylib::tests::Movable());
   std::cout << "-------\n";
   movable_vec.push_back(mylib::tests::Movable());
   std::cout << "-------\n";
   movable_vec.push_back(mylib::tests::Movable());
   std::cout << "-------\n";
 */
      
/*    std::test_vector<mylib::tests::Person> v {mylib::tests::Person{"Nik"},
                                        mylib::tests::Person{"Tom"},
                                        mylib::tests::Person{"Bob"}};
 */

/*    std::cout << "\n------------------\n";
   size_t length {1};

   unsigned char* p_bytes01 = new unsigned char[sizeof(mylib::tests::Person) * length];  
   
   mylib::tests::Person* p_persons01 = reinterpret_cast<mylib::tests::Person*>(p_bytes01);
   for (size_t i {0}; i < length; ++i) {
      new (p_persons01 + i) mylib::tests::Person("Nikolai S " + std::to_string(i));
   }
   std::cout << "\n******************\n";

   unsigned char* p_bytes02 = new unsigned char[sizeof(mylib::tests::Person) * length * 2];  
   for (size_t i {0}; i < (sizeof(mylib::tests::Person) * length); ++i) {
      *(p_bytes02 + i) = *(p_bytes02 + i);
   }

   mylib::tests::Person* p_persons02 = reinterpret_cast<mylib::tests::Person*>(p_bytes02);

   delete p_bytes01;
   p_bytes01 = nullptr;

   for (size_t i {0}; i < length; ++i) {
      (p_persons02 + i)->~Person();
   }

   delete p_bytes02;
   p_bytes02 = nullptr;
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

   mylib::vector<mylib::tests::Movable> v;
   v.push_back(mylib::tests::Movable());
   v.push_back(mylib::tests::Movable());
   v.push_back(mylib::tests::Movable());



   return 0;
}


