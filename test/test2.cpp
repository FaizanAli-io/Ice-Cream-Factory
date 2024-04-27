#include <unistd.h>
#include <iostream>

int main()
{
    srand(time(0));
    std::cout << "Hello ";
    std::cout << rand() << ' ';
    std::cout << rand() << ' ';
    std::cout << rand() << ' ';
    std::cout << rand() << ' ';
    std::cout << rand() << ' ';
    std::cout << "There";
}
