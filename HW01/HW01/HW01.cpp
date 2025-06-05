#include <iostream>

int main()
{
    int x[5];

    std::cout << "Hello World!\n";

    for (int i = 0; i < 5;  i++) {
        std::cin >> x[i];
    }

    for (int i = 0; i < 5; i++) {
        std::cout << x[i];
    }

}

