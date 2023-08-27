#pragma once
#include <vector>
#include <string>

namespace mylib {
namespace tests {   

enum class Color {
    black,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    white
};

struct MsSettings {
    Color text_color;
    const char* marker;
};

// Print a additional colored messages to the console
class PrintC {
private:
    Color m_color;
    const char* m_marker;

public:
    PrintC();
    PrintC(const Color& color, const char* marker);
    void SetMarker(const char*);
    void SetColor(const Color&);
    void SetParam(const Color&, const char*);
    void PrintMess(const std::vector<const char*>&) const;
    void PrintMess(const MsSettings&,
                   const std::vector<const char*>&);
    void PrintMess(const Color&, const char*,
                   const std::vector<const char*>&);
} static informator;

// Additionat class for common tests
class Person {
private:
    std::string m_name;

public:
    Person();
    Person(const std::string&);
    Person(const Person&);
    Person& operator=(const Person&);
    Person(Person&&);
    Person& operator=(Person&&);
    ~Person();
    const std::string& GetName() const; 
};

}   //tests
}   //mylib
