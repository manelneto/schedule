#include <iostream>
#include "Management.h"

using namespace std;

int main() {
    Management management;
    management.start();
    while (management.menu() != 0)
        cout << endl;
    management.end();
    return 0;
}
