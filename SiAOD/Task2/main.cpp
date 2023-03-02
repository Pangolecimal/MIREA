#include <cstdlib>
#include <ctime>
#include <iostream>

#include "node.h"

int main() {
    srand(time(nullptr));

    operation_1();
}

/*
make list L

1) check if there are two same values in L
2) delete max value node from L
3) function, that inserts a new value before every even node
*/