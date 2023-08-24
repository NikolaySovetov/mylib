#include "unique_ptr.hpp"
#include "fortests.hpp"
#include <iostream>

int main()  {

    mylib::unique_ptr<mylib::tests::Person> p1 {new mylib::tests::Person{"Name"}};
    auto p2 = std::move(p1);
    mylib::tests::informator.PrintMess(mylib::tests::Color::green, "  >> ", 
                            {(p2->GetName()).c_str(), "\n"});
    std::cout << "------------------\n";

    return 0;
}