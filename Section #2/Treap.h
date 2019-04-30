#ifndef TREAP_H_
#define TREAP_H_
#include <iostream>
#include <time.h>
#include <random>
#include <chrono>
using namespace std;
template<class T, class V>
class Treap {
public:
    class Node {
    public:
        Node *left, *right;
        T key;
        V value;
        int priority;
        Node(T k, V v)
        {
            key = k;
            value = v;
            priority = rand();
        }
        friend ostream& operator<<(ostream &o, Treap<T, V>::Node root)
        {
            o << "Key: " << root.key << " - Value: " << root.value << " - Priority: " << root.priority;
        }
    };
private:
    Node* treeRoot;

    // creates a new node and sets its left,right children to nullptr
    Node* newNode(T k, V v)
    {
        Node* p = new Node(k, v);
        p->left = nullptr;
        p->right = nullptr;
        return p;
    }
    Node* rotateRight(Node* Q)
    {
        Node* P = Q->left;
        Q->left = P->right;
        P->right = Q;
        return P;
    }
    Node* rotateLeft(Node* P)
    {
        Node* Q = P->right;
        P->right = Q->left;
        Q->left = P;
        return Q;
    }
    /*
     * Balances the treap to keep the min heap property while rotations keep the BST property
     */
    Node* balance(Node* root)
    {
        if (root->left != nullptr && root->left->priority < root->priority)
            return rotateRight(root);
        if (root->right != nullptr && root->right->priority < root->priority)
            return rotateLeft(root);
        return root;
    }
    Node* insert(Node* root, T k, V v)
    {
        // found right place to insert
        if (root == nullptr)
            return newNode(k, v);
        // element is duplicated
        if (root->key == k)
            return root;
        if (k < root->key)
            root->left = insert(root->left, k, v);
        else
            root->right = insert(root->right, k, v);
        root = balance(root);
        return root;
    }
    Node* find(Node* root, T k)
    {
        if (root == nullptr) // element not found
            return root;
        if (root->key == k)
            return root;
        if (k < root->key)
            return find(root->left, k);
        return find(root->right, k);
    }
    void print(ostream &o, Node* root)
    {
        if (root == nullptr)
            return;
        print(o, root->left);
        o << *root << endl;
        print(o, root->right);
    }
    int maxHeight(Node* root)
    {
        if (root == nullptr)
            return 0;
        return 1 + max(maxHeight(root->left), maxHeight(root->right));
    }
public:
    Treap()
    {
        treeRoot = 0;
    }
    void insert(T k, V v)
    {
        treeRoot = insert(treeRoot, k, v);
    }
    int getHeight()
    {
        return maxHeight(treeRoot);
    }
    Node* find(T k)
    {
        return find(treeRoot, k);
    }
    friend ostream& operator<<(ostream &o, Treap<T, V> tree)
    {
        tree.print(o, tree.treeRoot);
        return o;
    }
};

#endif /* TREAP_H_ */
