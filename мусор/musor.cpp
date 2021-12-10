#include <iostream>
#include <list>

int main()
{
    std::list < int > l = {5, 6, 8};
    //l.assign(1, 3);
    //std::list < int>::iterator ptr = l.begin();
    auto ptr = l.begin();
    std::cout << *ptr;
}
