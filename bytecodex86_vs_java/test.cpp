#include <iostream>
#include <string>


class Foo
{
public:
    Foo();
    void SetName(std::string name);
    std::string GetName();

private:
    std::string name_;
    int id_;
};

void Foo::SetName(std::string name)
{
    name_ = name;
}

std::string Foo::GetName()
{
    return name_;
}