#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "header.h"

struct TableVector {
    int n;
    int N;
    std::vector<TableElement> elements;

    TableVector(int N) : n(N), N(N), elements(N) {}
};

void initTableVector(TableVector& table) {
    table.n = 0;
    table.N = 100;
    table.elements = std::vector<TableElement>(table.N, {0, 0, "", "", ""});
}

void initTableVectorWithRandomData(TableVector& table) {
    table.n = rand() % 2 + 4;  // between 4 and 6
    for (int i = 0; i < table.n; i++)
        initTableElementWithRandomData(table.elements[i]);
}

void sortTableVector(TableVector& table) {
    for (int i = 0; i < table.n; i++) {
        for (int j = 0; j < i; j++) {
            if (table.elements[i].flight_number < table.elements[j].flight_number) {
                auto temp = table.elements[i];
                table.elements[i] = table.elements[j];
                table.elements[j] = temp;
            }
        }
    }
}

void printTableVector(TableVector table, std::string name) {
    std::cout << std::endl;
    std::cout << "Table " << name << std::endl;

    int flight_number_max_len = 13;
    int week_day_max_len = 8;
    int destination_max_len = 11;
    int transit_time_max_len = 12;
    int delay_info_max_len = 10;

    std::cout << "flight_number | week_day | destination | transit_time | delay_info" << std::endl;
    std::cout << "--------------+----------+-------------+--------------+-----------" << std::endl;

    for (int i = 0; i < table.n; i++) {
        printNumber(table.elements[i].flight_number, flight_number_max_len, true);
        printNumber(table.elements[i].week_day, week_day_max_len, true);
        printString(table.elements[i].destination, destination_max_len, true);
        printString(table.elements[i].transit_time, transit_time_max_len, true);
        printString(table.elements[i].delay_info, delay_info_max_len, false);
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void insertIntoTable(TableVector& table, const TableElement& element) {
    if (table.n < table.N) {
        table.elements[table.n] = element;
        table.n++;
    } else {
        std::cout << "Table is full, element not inserted." << std::endl;
    }
}

TableElement removeElement(TableVector& table, int index) {
    if (index < 0 || index >= table.n)
        throw std::out_of_range("Index out of range");

    TableElement removed_element = table.elements[index];
    table.elements.erase(table.elements.begin() + index);
    table.n--;
    return removed_element;
}

void operation1() {
    TableVector schedule(100);
    initTableVectorWithRandomData(schedule);
    sortTableVector(schedule);
    printTableVector(schedule, "SCHEDULE BEFORE");

    TableElement element = {1, 1, "New Entry", "New Entry", "New Entry"};
    insertIntoTable(schedule, element);
    sortTableVector(schedule);
    printTableVector(schedule, "SCHEDULE AFTER");
}

void operation2(int i) {
    TableVector schedule(100);
    initTableVectorWithRandomData(schedule);
    sortTableVector(schedule);

    TableVector archive(100);
    initTableVector(archive);

    printTableVector(schedule, "SCHEDULE BEFORE");
    printTableVector(archive, "ARCHIVE BEFORE");

    std::cout << std::endl;
    std::cout << std::endl;

    TableElement element = removeElement(schedule, i);
    insertIntoTable(archive, element);

    printTableVector(schedule, "SCHEDULE AFTER");
    printTableVector(archive, "ARCHIVE AFTER");
}

void operation3(int week_day, std::string destination) {
    TableVector schedule(100);
    initTableVectorWithRandomData(schedule);
    schedule.elements[0].flight_number += 1 - schedule.elements[0].flight_number % 2;
    schedule.elements[0].week_day = week_day;
    schedule.elements[0].destination = destination;
    sortTableVector(schedule);

    TableVector departure(100);
    initTableVector(departure);
    sortTableVector(departure);

    printTableVector(schedule, "SCHEDULE BEFORE");
    printTableVector(departure, "DEPARTURE BEFORE");

    for (int i = 0; i < schedule.n; i++) {
        if (schedule.elements[i].flight_number % 2 == 1 &&
            schedule.elements[i].destination == destination &&
            schedule.elements[i].week_day == week_day) {
            TableElement element = removeElement(schedule, i);
            insertIntoTable(departure, element);
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;

    printTableVector(schedule, "SCHEDULE AFTER");
    printTableVector(departure, "DEPARTURE AFTER");
}

void operation4(int week_day) {
    TableVector schedule(100);
    initTableVectorWithRandomData(schedule);
    sortTableVector(schedule);
    printTableVector(schedule, "SHEDULE");
    int count = 0;
    for (int i = 0; i < schedule.n; i++)
        if (schedule.elements[i].flight_number % 2 == 0 &&
            schedule.elements[i].week_day == week_day) count++;
    std::cout << "Found " << count << " Planes arriving on day " << week_day << std::endl;
}

int main() {
    srand(time(nullptr));

    int choice;
    std::cout << "Enter index of the operation (1..4): ";
    std::cin >> choice;

    int i = 0;
    int week_day = 0;
    std::string destination = "Tokio";

    switch (choice) {
        case 1:
            operation1();
            break;
        case 2:
            std::cout << "Enter index of the element to remove (0..4+): ";
            std::cin >> i;
            operation2(i);
            break;
        case 3:
            std::cout << "Enter week day (1..7): ";
            std::cin >> week_day;
            std::cin.ignore();
            std::cout << "Enter destination (Moscow, Paris, London...): ";
            std::getline(std::cin, destination);
            operation3(week_day, destination);
            break;
        case 4:
            std::cout << "Enter week day (1..7): ";
            std::cin >> week_day;
            operation4(week_day);
            break;
        default:
            std::cout << "Invalid choice" << std::endl;
            break;
    }
}