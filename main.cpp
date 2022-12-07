#include "FactoryStructure.h"

using namespace gyx;
using std::cin;
using std::cout;
using std::endl;

int main()
{
    while (1)
    {
        system("cls");
        cout << "Please choose the function:" << endl;
        cout << "1.Produce computers" << endl;
        cout << "2.Produce peripherals" << endl;
        cout << "3.Exit" << endl;
        int choice = 0;
        cin >> choice;
        if (choice == 1)
            function1();
        else if (choice == 2)
            function2();
        else if (choice == 3)
            break;
        else
            continue;
    }
}