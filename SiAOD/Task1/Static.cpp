#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "header.h"

struct TableStatic {
    static const int N = 100;
    int n;
    TableElement elements[N];
};

void initTableStatic(TableStatic& table) {
    table.n = 0;
    for (int i = 0; i < TableStatic::N; i++) {
        initTableElement(table.elements[i]);
    }
}

void initTableStaticWithRandomData(TableStatic& table) {
    table.n = rand() % 5 + 5;  // between 5 and 10
    for (int i = 0; i < table.n; i++)
        initTableElementWithRandomData(table.elements[i]);
}

void sortTableStatic(TableStatic& table) {
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

void printTableStatic(TableStatic table, std::string name) {
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

void insertIntoTable(TableStatic& table, const TableElement& element) {
    if (table.n < table.N) {
        table.elements[table.n] = element;
        table.n++;
    } else {
        std::cout << "Table is full, element not inserted." << std::endl;
    }
}

TableElement removeElement(TableStatic& table, int index) {
    if (index >= table.n) {
        throw std::out_of_range("Index out of range");
    }

    TableElement removedElement = table.elements[index];

    for (int i = index; i < table.n - 1; i++) {
        table.elements[i] = table.elements[i + 1];
    }

    table.n--;

    return removedElement;
}

void operation1() {
    TableStatic schedule;
    initTableStaticWithRandomData(schedule);
    sortTableStatic(schedule);
    printTableStatic(schedule, "SCHEDULE");

    TableElement element = {1, 1, "New Entry", "New Entry", "New Entry"};
    insertIntoTable(schedule, element);
    sortTableStatic(schedule);
    printTableStatic(schedule, "SCHEDULE");
}

void operation2(int index) {
    TableStatic schedule;
    initTableStaticWithRandomData(schedule);
    sortTableStatic(schedule);

    TableStatic archive;
    initTableStatic(archive);

    std::cout << std::endl
              << "BEFORE: " << std::endl;
    printTableStatic(schedule, "SCHEDULE");
    printTableStatic(archive, "ARCHIVE");

    TableElement element = removeElement(schedule, index);
    insertIntoTable(archive, element);

    std::cout << std::endl
              << "AFTER: " << std::endl;
    printTableStatic(schedule, "SCHEDULE");
    printTableStatic(archive, "ARCHIVE");
}

void operation3(int week_day, std::string destination) {
    TableStatic schedule;
    initTableStaticWithRandomData(schedule);
    schedule.elements[0].flight_number -= schedule.elements[0].flight_number % 2 - 1;
    schedule.elements[0].week_day = week_day;
    schedule.elements[0].destination = destination;
    sortTableStatic(schedule);

    TableStatic departure;
    initTableStatic(departure);
    sortTableStatic(departure);

    std::cout << std::endl
              << "BEFORE: " << std::endl;
    printTableStatic(schedule, "SCHEDULE");
    printTableStatic(departure, "DEPARTURE");

    for (int i = 0; i < schedule.n; i++) {
        if (schedule.elements[i].flight_number % 2 == 1 &&
            schedule.elements[i].destination == destination &&
            schedule.elements[i].week_day == week_day) {
            TableElement element = removeElement(schedule, i);
            insertIntoTable(departure, element);
        }
    }

    std::cout << std::endl
              << "AFTER: " << std::endl;
    printTableStatic(schedule, "SCHEDULE");
    printTableStatic(departure, "DEPARTURE");
}

void operation4(int week_day) {
    TableStatic schedule;
    initTableStaticWithRandomData(schedule);
    sortTableStatic(schedule);
    printTableStatic(schedule, "SHEDULE");

    int count = 0;
    for (auto element : schedule.elements)
        if (element.flight_number % 2 == 0 && element.week_day == week_day) count++;

    std::cout << "Found " << count << " Planes arriving on day " << week_day << std::endl;
}