#include <iostream>
#include "bst_fci.h"
#include "string_line.h"

using namespace std;

void printMenu(bool _flipped)
{
    if(_flipped)
    {
        cout << "6) Print\n"
             "7) Flipping \n"
             "8) Exit\n\n\n";
    }
    else
    {
        cout << "1) Insert  \n"
             "2) Print Range\n"
             "3) Is SubTree\n"
             "4) Is Balanced\n"
             "5) Find\n"
             "6) Print\n"
             "7) Flipping\n"
             "8) Exit\n\n\n";
    }

    cout << "Please Enter Your Choice: ";
}

int main()
{
    bool flag = true;
    BSTFCI<int> tree;
    BSTFCI<int> tree2;


    tree.insert(5);
    tree.insert(2);
    tree.insert(4);
    tree.insert(3);
    tree.insert(1);

    tree2.insert(2);
    tree2.insert(1);
    tree2.insert(3);

    /*
    tree.insert(3);
    tree.insert(3);
    tree.insert(17);
    tree.insert(60);
    tree.insert(18);
    tree.insert(9);
    tree.insert(9);
    tree.insert(6);
    tree.insert(33);
    tree.insert(33);
    tree.insert(33);
    tree.insert(55);
    */
    /*
    tree2.insert(5);
    tree2.insert(7);
    tree2.insert(6);
    tree2.insert(9);
    tree2.insert(10);
    */
    while(flag)
    {
        char choice;
        printMenu(tree.isFlipped());
        cin >> choice;

        switch(choice)
        {
        case '1':
        {
            int x, value;
            cout << "TREE(1) OR TREE(2) :";
            cin >> x;

            if(x == 1)
            {
                cout << "ENTER A VALUE :";
                cin >> value;
                tree.insert(value);
            }
            else if(x == 2)
            {
                cout << "ENTER A VALUE :";
                cin >> value;
                tree2.insert(value);
            }

            break;
        }
        case '2':
        {
            int low, high;

            cout << "LOW  = ";
            cin >> low;
            cout << "HIGH = ";
            cin >> high;

            if(low > high)
                swap(low, high);

            tree.printRange(low, high, tree.getRoot());
            cout << endl;
            break;
        }
        case '3':
        {
            if(tree.isSubTree(tree2))
                cout << "tree2 is a subtree of tree" <<endl;
            else
                cout << "tree2 isn't a subtree of tree" <<endl;
            break;
        }
        case '4':
        {
            if(tree.isBalanced())
                cout << "tree1 is Balanced" <<endl;
            else
                cout << "tree1 isn't Balanced" <<endl;
            break;
        }
        case '5':
        {
            int value;
            cout << "VALUE  = ";
            cin >> value;

            if(tree.find(value))
                cout << "FOUND" <<endl;
            else
                cout << "NOT FOUND" <<endl;

            break;
        }
        case '6':
        {
            tree.levelPrint();
            cout << endl;
            break;
        }
        case '7':
        {
            tree.flip(tree.getRoot());
            break;
        }
        case '8':
        {
            flag = false;
            break;
        }
        default:
        {
            cin.ignore();
            cin.clear();
            cout << "ERROR." << endl << endl;
            break;
        }
        }
    }

    cout << "BYE." << endl;

    return 0;
}
