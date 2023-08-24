#include "fortests.hpp"
#include "unique_ptr.hpp"
#include "shared_ptr.hpp"
#include <iostream>

int main()  {

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





    std::cout << "------------------\n";

    return 0;
}