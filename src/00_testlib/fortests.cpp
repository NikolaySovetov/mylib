#include "configured/configured.h"
#include "fortests.hpp"
#include <iostream>

namespace mylib {
namespace tests {

/* #RESET   "\033[0m"
#BLACK   "\033[30m" 
#RED     "\033[31m" 
#GREEN   "\033[32m" 
#YELLOW  "\033[33m" 
#BLUE    "\033[34m" 
#MAGENTA "\033[35m" 
#CYAN    "\033[36m" 
#WHITE   "\033[37m" 
 */

// *** PrintC ***
PrintC::PrintC(): m_color{Color::black}, m_marker{""} {}

PrintC::PrintC(const Color& cl, const char* mk)
: m_color{cl}, m_marker{mk} {}

void PrintC::SetMarker(const char* mk) {
    m_marker = mk;
}

void PrintC::SetColor(const Color& cl) {
    m_color = cl;
}

void PrintC::SetParam(const Color& cl, const char* mk) {
    m_color  = cl;
    m_marker = mk;
}

void PrintC::PrintMess(const std::vector<const char*>& v) const {

    switch (m_color) {
    case Color::black :
        std::cout << "\033[30m"; break;       
    case Color::red :
        std::cout << "\033[31m"; break;
    case Color::green :
        std::cout << "\033[32m"; break;
    case Color::yellow :
        std::cout << "\033[33m"; break;
    case Color::blue :
        std::cout << "\033[34m"; break;
    case Color::magenta :
        std::cout << "\033[35m"; break;
    case Color::cyan :
        std::cout << "\033[36m"; break;
    case Color::white :
        std::cout << "\033[37m"; break;
    default:
        break;
    }    

    std::cout << m_marker;
    for (const auto word: v) {
        std::cout << word;
    }
    std::cout << "\033[0m";
}

void PrintC::PrintMess(const MsSettings& mset, 
                       const std::vector<const char*>& v) {
    auto temp_color  = m_color;
    auto temp_marker = m_marker;
    m_color  = mset.text_color;
    m_marker = mset.marker;

    PrintMess(v);

    m_color  = temp_color;
    m_marker = temp_marker;
}

void PrintC::PrintMess(const Color& cl, const char* mk, 
                       const std::vector<const char*>& v) {
    auto temp_color  = m_color;
    auto temp_marker = m_marker;
    m_color  = cl;
    m_marker = mk;

    PrintMess(v);

    m_color  = temp_color;
    m_marker = temp_marker;
}

// *** Person ***
#ifdef TEST_MESSAGE 
MsSettings s1{Color::yellow, ">> "};
#endif

Person::Person(): m_name{"NONE NAME"} {
#ifdef TEST_MESSAGE 
    informator.PrintMess(s1, {"Person(", m_name.c_str(), ") created\n"}); 
#endif
}

Person::Person(const std::string& name): m_name{name} {
#ifdef TEST_MESSAGE 
    informator.PrintMess(s1, {"Person(", m_name.c_str(), ") created\n"}); 
#endif
} 

Person::Person(const Person& p) {
    m_name = p.m_name;
#ifdef TEST_MESSAGE 
    informator.PrintMess(s1, {"Person(", m_name.c_str(), ") copied\n"}); 
#endif
} 

Person& Person::operator=(const Person& p) {
    if (this != &p) {
        m_name.erase();
        m_name = p.m_name;
    }
#ifdef TEST_MESSAGE 
    informator.PrintMess(s1, {"operator= Person(", m_name.c_str(), ") copied\n"}); 
#endif
    return *this;
} 

Person::Person(Person&& p) {
    m_name = std::move(p.m_name);
#ifdef TEST_MESSAGE 
    informator.PrintMess(s1, {"operator= Person(", m_name.c_str(), ") moved\n"}); 
#endif
} 

Person& Person::operator=(Person&& p) {
    if (this != &p) {
        m_name = std::move(p.m_name);
    }
#ifdef TEST_MESSAGE 
    informator.PrintMess(s1, {"operator= Person(", m_name.c_str(), ") moved\n"}); 
#endif
    return *this;
} 

Person::~Person() {
#ifdef TEST_MESSAGE 
    informator.PrintMess(s1, {"Person(", m_name.c_str(), ") destroyed\n"}); 
#endif
} 

const std::string& Person::GetName() const {
    return m_name;
}


}   //tests    
}   //mylib

