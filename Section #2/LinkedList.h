#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <iostream>
using namespace std;
template<class T>
class LinkedList {
public:
    class Node {
    public:
        T value;
        Node* next;

        Node () {}
        Node(T v)
        {
            value = v;
        }
    };
private:
    Node* head; // Head is a dummy node with useless value and head->next is first element
    string delimeter; // delimeter is what i'll print in between the nodes when printing whole list
public:

    LinkedList(string delimeter = " ")
    {
        this->delimeter = delimeter;
        head = new Node;
        head->next = 0;
        delimeter =" - ";
    }
    Node* addSorted(T v)
    {
        Node* cur = head;
        while(cur->next != NULL && v > cur->next->value) // add me once next element is greater than or equal to me OR I'm the greatest element
            cur = cur->next;
        Node* p = new Node(v);
        p->next = cur->next;
        cur->next = p;
        return p;
    }
    Node* get(T v)
    {
        Node* cur = head->next;
        while(cur != 0 && cur->value != v)
            cur = cur->next;
        return cur;
    }

    // operator overloading for printing
    friend ostream& operator<<(ostream& o, LinkedList<T> & c)
    {
        Node* cur = c.head->next;
        while(true)
        {
            o << cur->value;
            cur = cur->next;
            if (cur == NULL)
                break;
            cout << c.delimeter;
        }
        return o;
    }
};

#endif  /* LINKED_LIST_H_ */
