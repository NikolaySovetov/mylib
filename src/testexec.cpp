#include "testexec.hpp"
#include "fortests.hpp"
#include "unique_ptr.hpp"
#include "shared_ptr.hpp"
#include "list.hpp"
#include "pair.hpp"
#include <iostream>

int main()  {

/*  mylib::tests::informator.PrintMess(mylib::tests::Color::green, ">>> ",
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

    mylib::list<mylib::tests::Person> list;
    list.pop_back(mylib::tests::Person{"Nik"});
    list.push_back(mylib::tests::Person{"Bob"});
    list.push_back(mylib::tests::Person{"Tom"});
    list.pop_back(mylib::tests::Person{"Ira"});
    list.pop_back(mylib::tests::Person{"Vika"});
    list.pop_back(mylib::tests::Person{"Anna"});
    
    mylib::list<int>::iterator it;


/*  std::cout << "First node: " << list.first()->GetName() << '\n';


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
 
/*  mylib::pair<mylib::tests::Person, mylib::tests::Person> p1
     {mylib::tests::Person{"Nik"}, mylib::tests::Person{"Ira"}};
  //mylib::pair<mylib::tests::Person, mylib::tests::Person> p2;
  
  auto person = p1.first();
  mylib::tests::Person vera{"Vera"};
  *(person) = vera; 
 */    



   std::cout << "------------------\n";

   return 0;
}