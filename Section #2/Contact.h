#ifndef CONTACT_H_
#define CONTACT_H_

#include "LinkedList.h"

class Contact {
private:
    string name;
    LinkedList<string> phone_numbers;
public:
    Contact(string name = "") : phone_numbers(" - ") // use " - " in between phone numbers
    {
        this->name = name;
    }
    void addPhoneNumber(string number)
    {
        phone_numbers.addSorted(number);
    }
    string getName()
    {
        return name;
    }
    bool operator<(const Contact & c) const
    {
        return name < c.name;
    }
    bool operator > (const Contact &c) const
    {
        return name > c.name;
    }
    bool operator==(const Contact & c) const
    {
        return name == c.name;
    }
    bool operator !=(const Contact &c) const
    {
        return name != c.name;
    }
    friend ostream& operator<<(ostream& o, Contact & c)
    {
        o << c.name << ": ";
        o << c.phone_numbers;
        return o;
    }
};

#endif  /* CONTACT_H_ */
