#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "header.h"

struct TableDynamic {
    int N;
    int n;
    TableElement* elements;

    TableDynamic(int size) {
        N = size;
        n = 0;
        elements = new TableElement[N];
    }

    ~TableDynamic() {
        delete[] elements;
    }
};

void initTableDynamic(TableDynamic*& table) {
    table->N = 100;
    table->n = 0;
    table->elements = new TableElement[table->N];

    for (int i = 0; i < table->N; i++) {
        initTableElement(table->elements[i]);
    }
}

void initTableDynamicWithRandomData(TableDynamic*& table) {
    table->n = rand() % 2 + 4;  // between 4 and 6
    for (int i = 0; i < table->n; i++)
        initTableElementWithRandomData(table->elements[i]);
}

void sortTableDynamic(TableDynamic*& table) {
    for (int i = 0; i < table->n; i++) {
        for (int j = 0; j < i; j++) {
            if (table->elements[i].flight_number < table->elements[j].flight_number) {
                auto temp = table->elements[i];
                table->elements[i] = table->elements[j];
                table->elements[j] = temp;
            }
        }
    }
}

void printTableDynamic(TableDynamic* table, std::string name) {
    std::cout << std::endl;
    std::cout << "Table " << name << std::endl;

    int flight_number_max_len = 13;
    int week_day_max_len = 8;
    int destination_max_len = 11;
    int transit_time_max_len = 12;
    int delay_info_max_len = 10;

    std::cout << "flight_number | week_day | destination | transit_time | delay_info" << std::endl;
    std::cout << "--------------+----------+-------------+--------------+-----------" << std::endl;

    for (int i = 0; i < table->n; i++) {
        printNumber(table->elements[i].flight_number, flight_number_max_len, true);
        printNumber(table->elements[i].week_day, week_day_max_len, true);
        printString(table->elements[i].destination, destination_max_len, true);
        printString(table->elements[i].transit_time, transit_time_max_len, true);
        printString(table->elements[i].delay_info, delay_info_max_len, false);
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void insertIntoTable(TableDynamic*& table, const TableElement& element) {
    if (table->n >= table->N) {
        int newN = 2 * table->N;
        TableElement* newElements = new TableElement[newN];

        for (int i = 0; i < table->N; i++)
            newElements[i] = table->elements[i];
        delete[] table->elements;

        table->N = newN;
        table->elements = newElements;
    }

    table->elements[table->n] = element;
    table->n++;
}

TableElement removeElement(TableDynamic*& table, int index) {
    if (index >= table->n) {
        throw std::out_of_range("Index out of range");
    }

    TableElement removedElement = table->elements[index];

    for (int i = index; i < table->n - 1; i++) {
        table->elements[i] = table->elements[i + 1];
    }

    table->n--;

    return removedElement;
}

void operation1() {
    TableDynamic* schedule = new TableDynamic(100);
    initTableDynamicWithRandomData(schedule);
    sortTableDynamic(schedule);
    printTableDynamic(schedule, "SCHEDULE BEFORE");

    TableElement element = {1, 1, "New Entry", "New Entry", "New Entry"};
    insertIntoTable(schedule, element);
    sortTableDynamic(schedule);
    printTableDynamic(schedule, "SCHEDULE AFTER");

    delete schedule;
}

void operation2(int i) {
    TableDynamic* schedule = new TableDynamic(100);
    initTableDynamicWithRandomData(schedule);
    sortTableDynamic(schedule);

    TableDynamic* archive = new TableDynamic(100);
    initTableDynamic(archive);

    printTableDynamic(schedule, "SCHEDULE BEFORE");
    printTableDynamic(archive, "ARCHIVE BEFORE");

    std::cout << std::endl;
    std::cout << std::endl;

    TableElement element = removeElement(schedule, i);
    insertIntoTable(archive, element);

    printTableDynamic(schedule, "SCHEDULE AFTER");
    printTableDynamic(archive, "ARCHIVE AFTER");
}

void operation3(int week_day, std::string destination) {
    TableDynamic* schedule = new TableDynamic(100);
    initTableDynamicWithRandomData(schedule);
    schedule->elements[0].flight_number += 1 - schedule->elements[0].flight_number % 2;
    schedule->elements[0].week_day = week_day;
    schedule->elements[0].destination = destination;
    sortTableDynamic(schedule);

    TableDynamic* departure = new TableDynamic(100);
    initTableDynamic(departure);
    sortTableDynamic(departure);

    printTableDynamic(schedule, "SCHEDULE BEFORE");
    printTableDynamic(departure, "DEPARTURE BEFORE");

    for (int i = 0; i < schedule->n; i++) {
        if (schedule->elements[i].flight_number % 2 == 1 &&
            schedule->elements[i].destination == destination &&
            schedule->elements[i].week_day == week_day) {
            TableElement element = removeElement(schedule, i);
            insertIntoTable(departure, element);
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;

    printTableDynamic(schedule, "SCHEDULE AFTER");
    printTableDynamic(departure, "DEPARTURE AFTER");
}

void operation4(int week_day) {
    TableDynamic* schedule = new TableDynamic(100);
    initTableDynamicWithRandomData(schedule);
    sortTableDynamic(schedule);
    printTableDynamic(schedule, "SHEDULE");
    int count = 0;
    for (int i = 0; i < schedule->n; i++)
        if (schedule->elements[i].flight_number % 2 == 0 && schedule->elements[i].week_day == week_day) count++;
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