#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "header.h"

int main() {
    srand(time(nullptr));

    std::string TableType;
    std::cout << "Enter Table Type (static, dynamic, vector): ";
    std::getline(std::cin, TableType);

    int operationNumber;
    std::cout << "Enter index of the operation (1..4): ";
    std::cin >> operationNumber;

    int i = 0;
    int week_day = 0;
    std::string destination = "Moscow";

    switch (operationNumber) {
        case 1:
            operation1(TableType);
            break;
        case 2:
            std::cout << "Enter index of the element to remove (0..4+): ";
            std::cin >> i;

            operation2(TableType, i);
            break;
        case 3:
            std::cout << "Enter week day (1..7): ";
            std::cin >> week_day;
            std::cin.ignore();
            std::cout << "Enter destination (Moscow, Paris, London...): ";
            std::getline(std::cin, destination);

            operation3(TableType, week_day, destination);
            break;
        case 4:
            std::cout << "Enter week day (1..7): ";
            std::cin >> week_day;

            operation4(TableType, week_day);
            break;
        default:
            std::cout << "Invalid choice" << std::endl;
            break;
    }
}