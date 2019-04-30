#include <iostream>
#include "LinkedList.h"
#include "Contact.h"
#include "ContactManager.h"
#include "Treap.h"
#include <chrono>
#include <random>
#include <time.h>
using namespace std;
int main()
{
    srand(chrono::steady_clock::now().time_since_epoch().count());
    ContactManager cm("all-contacts.in");
    cout << cm << endl;
    cm.displayNumber("1217241657");

    return 0;
}