#include <iostream>
#include <string>

struct TableElement {
    int flight_number;
    int week_day;
    std::string destination;
    std::string transit_time;
    std::string delay_info;
};

void initTableElement(TableElement& element) {}

void initTableElementWithInput(TableElement& element) {}

void initTableElementWithRandomData(TableElement& element) {}

void printTableElement(TableElement element) {}

void printNumber(int n, int m, bool b) {}
void printString(std::string s, int m, bool b) {}

void operation1(std::string TableType) {}
void operation2(std::string TableType, int index) {}
void operation3(std::string TableType, int week_day, std::string destination) {}
void operation4(std::string TableType, int week_day) {}