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

struct TableStatic {
    static const int N = 100;
    int n;
    TableElement elements[N];
};

void printTableStatic(TableStatic table, std::string name);
void printTableDynamic(TableStatic table, std::string name);

void operation_1_static();
void operation_2_static();
void operation_3_static();
void operation_4_static();

void initTableElementWithInput(TableElement& element);
void insertIntoTable(TableStatic& table, const TableElement& element);

/* //? pseudo-code for operation 1 for the static variant
 *    void operation_1_static() {
 *        create an empty element "schedule" of type TableStatic;
 *        fill "schedule" with random data;
 *        sort elements array of "schedule" by flight_number;
 *        print "schedule" to the console;
 *
 *        create an empty element "element" of type TableElement;
 *        fill "element" with random data;
 *
 *        insert "element" into "schedule;
 *        sort elements array of "schedule" by flight_number;
 *        print "schedule" to the console;
 *    }
 */

// void operation_1_dynamic();
// void operation_2_dynamic();
// void operation_3_dynamic();
// void operation_4_dynamic();

// void operation_1_vector();
// void operation_2_vector();
// void operation_3_vector();
// void operation_4_vector();