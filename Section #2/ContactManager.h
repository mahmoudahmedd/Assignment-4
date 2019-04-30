#ifndef CONTACT_MANAGER_H_
#define CONTACT_MANAGER_H_

#include "LinkedList.h"
#include "Contact.h"
#include <fstream>
#include "Treap.h"
//#include "Treap.h"  // for Task 2

class ContactManager {
private:
    LinkedList<Contact> contacts;
    Treap<string, Contact*> tree;  // for Task 2
public:
    ContactManager() : contacts("\n") {}
    ContactManager(string fileName) : contacts("\n")
    {
        loadFromFile(fileName);
    }
    bool loadFromFile(string fileName)
    {
        ifstream fin(fileName.c_str(), ios::in|ios::binary);
        string number, name;

        while(fin >> number)
        {
            fin.ignore();
            getline(fin, name);
            fin.ignore();
            add(name, number);
        }
    }
    void add(string name, string phone_number)
    {
        Contact c(name);
        c.addPhoneNumber(phone_number);

        // Find a Contact::Node with that name (names are unique and comparison in Contact.h is based on name)
        LinkedList<Contact>::Node *p = contacts.get(c);

        // Name found. add this phone number to this contact.
        // Note that P is a Contat::Node* which holds 2 attributes: value (The contact object) and next. p->value accesses the contact object that the node is pointing to
        if (p != NULL)
            p->value.addPhoneNumber(phone_number);
        else
        {
            contacts.addSorted(c);
            p = contacts.get(c);
        }
        // get a contact pointer to the contact position in this linked list
        Contact* cp = &p->value;
        tree.insert(phone_number, cp);

    }
    void displayNumber(string phone_number)
    {
        Treap<string, Contact*>::Node* c = tree.find(phone_number);
        if (c == nullptr)
            cout << phone_number;
        else
            cout << c->value->getName();
        cout << endl;
    }
    void printTreap()
    {
        cout << tree << endl;
    }
    friend ostream& operator<<(ostream& o, ContactManager & c)
    {
        o << c.contacts;
    }
};

#endif  /* CONTACT_MANAGER_H_ */
