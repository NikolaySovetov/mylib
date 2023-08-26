#include "testexec.hpp"
#include "fortests.hpp"
#include "unique_ptr.hpp"
#include "shared_ptr.hpp"
#include "list.hpp"
#include <iostream>

int main()  {

/*     mylib::tests::informator.PrintMess(mylib::tests::Color::green, ">>> ",
                                       {"Hello", " ", "world" , "!!!", "\n"});
 */

/*     mylib::unique_ptr<mylib::tests::Person> uniq_p1 {new mylib::tests::Person{"Name"}};
    auto uniq_p2 = std::move(uniq_p1);
    std::cout << uniq_p2->GetName() << '\n';
    std::cout << "------------------\n";
 */

/*     mylib::shared_ptr<mylib::tests::Person> sh_p1 {new mylib::tests::Person{"Nik"}};
    auto sh_p2 {sh_p1};
    auto sh_p3 = sh_p2;
    auto sh_p4 = std::move(sh_p1);
    mylib::shared_ptr<mylib::tests::Person> sh_p5;
    sh_p5 = std::move(sh_p2);

    std::cout << "Name of Person is " << sh_p5->GetName() << '\n';
 */     

/*     mylib::list<mylib::tests::Person> list;
    list.pop_back(mylib::tests::Person{"Nik"});
    list.push_back(mylib::tests::Person{"Bob"});
    list.push_back(mylib::tests::Person{"Tom"});
    list.pop_back(mylib::tests::Person{"Ira"});
    list.pop_back(mylib::tests::Person{"Vika"});
    list.pop_back(mylib::tests::Person{"Anna"});
 */    

/*     mylib::list<int> list;
    std::cout << ((list.empty()) ? ("empty") : ("not empty") ) << '\n'; 

    mylib::list<int> list1 {101};
    std::cout << ((list1.empty()) ? ("empty") : ("not empty") ) << '\n'; 
 */

    MyClass c(101, 102, 103, 104);

    std::cout << "------------------\n";

    return 0;
}