#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "header.h"

struct TableElement {
    int flight_number;
    int week_day;
    std::string destination;
    std::string transit_time;
    std::string delay_info;
};

void initTableElement(TableElement& element) {
    element.flight_number = 0;
    element.week_day = 0;
    element.destination = "";
    element.transit_time = "";
    element.delay_info = "";
}

void initTableElementWithInput(TableElement& element) {
    std::cout << "Enter flight number: ";
    std::cin >> element.flight_number;

    std::cout << "Enter weekday (1-7): ";
    std::cin >> element.week_day;

    std::cin.ignore();

    std::cout << "Enter destination: ";
    std::getline(std::cin, element.destination);

    std::cout << "Enter transit time: ";
    std::getline(std::cin, element.transit_time);

    std::cout << "Enter delay info: ";
    std::getline(std::cin, element.delay_info);
}

void initTableElementWithRandomData(TableElement& element) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string destinations[] = {"New York", "Moscow", "Las Vegas", "Tokio", "Hong Kong", "Shenzhen", "Beijing", "Paris", "London", "Berlin"};

    element.flight_number = rand() % 999999 + 1;
    element.week_day = rand() % 7 + 1;
    element.destination = destinations[rand() % 10];
    element.transit_time = std::to_string(rand() % 24 + 1) + " Hours";
    element.delay_info = rand() % 3 == 0 ? std::to_string(rand() % 6 + 1) + " Hours" : "No Delay";
}

void printTableElement(TableElement element) {
    std::cout << "flight_number: " << element.flight_number << "; ";
    std::cout << "week_day: " << element.week_day << "; ";
    std::cout << "destination: " << element.destination << "; ";
    std::cout << "transit_time: " << element.transit_time << "; ";
    std::cout << "delay_info: " << element.delay_info << "; " << std::endl;
}

void printNumber(int n, int m, bool b) {
    std::cout << n;
    int len = m - std::to_string(n).length();
    for (int i = 0; i < len; i++) std::cout << " ";
    if (b) std::cout << " | ";
}
void printString(std::string s, int m, bool b) {
    std::cout << s;
    int len = m - s.length();
    for (int i = 0; i < len; i++) std::cout << " ";
    if (b) std::cout << " | ";
}
