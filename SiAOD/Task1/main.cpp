#include <process.h>
#include <windows.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

int main() {
    srand(time(nullptr));

    std::string TableType;
    std::cout << "Enter Table Type (static, dynamic, vector): ";
    std::getline(std::cin, TableType);

    if (TableType == "static") system("start static.exe");
    if (TableType == "dynamic") system("start dynamic.exe");
    if (TableType == "vector") system("start vector.exe");
}

// 1) g++ -o static static.cpp ; g++ -o dynamic dynamic.cpp ; g++ -o vector vector.cpp
// 2) clear ; g++ -o main main.cpp ; ./main.exe