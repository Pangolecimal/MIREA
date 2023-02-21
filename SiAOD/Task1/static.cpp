#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

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
void printTableStatic(TableStatic table, std::string name) {
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

    TableElement element;
    initTableElementWithInput(element);

    insertIntoTable(schedule, element);
    sortTableStatic(schedule);
    printTableStatic(schedule, "SCHEDULE");
}

void operation2() {
    int index = 0;
    std::cout << "Enter index of the element to remove (0..4+): ";
    std::cin >> index;

    TableStatic schedule;
    initTableStaticWithRandomData(schedule);
    sortTableStatic(schedule);

    TableStatic archive;
    initTableStatic(archive);

    printTableStatic(schedule, "SCHEDULE BEFORE");
    printTableStatic(archive, "ARCHIVE BEFORE");

    TableElement element = removeElement(schedule, index);
    insertIntoTable(archive, element);

    printTableStatic(schedule, "SCHEDULE AFTER");
    printTableStatic(archive, "ARCHIVE AFTER");
}

void operation3() {
    int week_day = 1;
    std::cout << "Enter week day (1..7): ";
    std::cin >> week_day;
    std::cin.ignore();

    std::string destination = "Moscow";
    std::cout << "Enter destination (Moscow, Paris, London...): ";
    std::getline(std::cin, destination);

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

void operation4() {
    int week_day = 1;
    std::cout << "Enter week day (1..7): ";
    std::cin >> week_day;
    std::cin.ignore();

    TableStatic schedule;
    initTableStaticWithRandomData(schedule);
    sortTableStatic(schedule);
    printTableStatic(schedule, "SHEDULE");

    int count = 0;
    for (auto element : schedule.elements)
        if (element.flight_number % 2 == 0 && element.week_day == week_day) count++;

    std::cout << "Found " << count << " Planes arriving on day " << week_day << std::endl;
}

int main() {
    srand(time(nullptr));

    int operationNumber;
    std::cout << "Enter index of the operation (1..4): ";
    std::cin >> operationNumber;

    int i = 0;
    int week_day = 0;
    std::string destination = "Moscow";

    if (operationNumber != 1 && operationNumber != 2 && operationNumber != 3 && operationNumber != 4)
        std::cout << "Invalid choice";
    if (operationNumber == 1) operation1();
    if (operationNumber == 2) operation2();
    if (operationNumber == 3) operation3();
    if (operationNumber == 4) operation4();
    system("pause");
}