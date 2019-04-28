/**
 *  @file     bst_fci.h
 *  @authors  Mahmoud Ahmed(20160227) - Ahmad Khaled(20170377) - Mostafa Omar(20170292)
 *  @date     27/04/2019
 *  @version  1.0
 */
#pragma once

#ifndef BSTFCI_H_INCLUDED
#define BSTFCI_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template <class T>
class BSTFCI
{
private:
    class BSTNode
    {
        friend class BSTFCI;
        T data;
        BSTNode* right;
        BSTNode* left;
    };

    BSTNode *root; // Stores the address of the root node.
    bool flipped;

    BSTNode* createNode(T data)
    {
        BSTNode* ptr = new BSTNode;
        ptr->data = data;
        ptr->left = NULL;
        ptr->right = NULL;
        return ptr;
    }

    BSTNode* insertPrivate (T data, BSTNode* ptr)
    {
        /// returns a pointer to the node that contains data equal to (T data) before insertion, if such node doesn't exist, returns NULL
        if(root == NULL)
            root = createNode(data);
        else
        {
            if (data < ptr->data)
            {
                /// if the inserted data is less than or equal the data at the current node then left insertion is done.
                if (ptr->left != NULL)
                    return insertPrivate(data, ptr->left);
                else
                    ptr->left = createNode(data);
            }
            else if (data > ptr->data)
            {
                /// if the inserted data is greater than the data at the current node then right insertion is done.
                if (ptr->right != NULL)
                    return insertPrivate(data, ptr->right);
                else
                    ptr->right = createNode(data);
            }
            else /// a node containing (T data) already exists
                return ptr;
        }
        return NULL;
    }

    void privateLinearPrint(BSTNode* ptr)
    {
        if(root != NULL)
        {
            if(ptr->left != NULL)
            {
                privateLinearPrint(ptr->left);
            }
            cout << ptr->data << endl;
            if(ptr->right != NULL)
            {
                privateLinearPrint(ptr->right);
            }
        }
    }

    void privateLevelPrint(BSTNode* ptr, int space)
    {
        if(root == NULL) /// if the tree is empty
            throw "this instance of BSTFCI is empty";
        if(ptr == NULL)
            return;
        space += 5;
        privateLevelPrint(ptr->right, space);
        cout << endl;
        for (int i = 5; i < space; ++i)
            cout << " ";
        cout << ptr->data;
        privateLevelPrint(ptr->left, space);
    }

    int getHeight(BSTNode* node)
    {
        if (node == NULL)
            return -1;
        return (1 + max(getHeight(node->right), getHeight(node->left)));
    }

    bool privateIsBalanced(BSTNode* node)
    {
        if (node == NULL)
            return true;

        int absDifference = abs(getHeight(node->right) - getHeight(node->left));
        return ( (absDifference < 2) && (privateIsBalanced(node->right)) && (privateIsBalanced(node->left)) );
    }

    BSTNode* privateFind(T data, BSTNode* node)
    {
        if (node == NULL)
            return NULL;
        if(data == node->data)
            return node;
        else if (data > node->data)
            return privateFind(data, node->right);
        else
            return privateFind(data, node->left);
    }

    bool privateIsSubTree(BSTNode* curr, BSTNode* rhs)
    {
        if(curr == NULL && rhs == NULL)
            return true;
        if(rhs == NULL)  /// if curr contains an element that doesn't exist in rhs, then rhs is still a subtree
        {
            /**
             * if the function reaches this statement then curr and rhs cannot both equal null (because it passed the first if condition)
             * then either non of both is null or one of them is null
             */
            return true;
        }
        if (curr == NULL) /// if rhs contains an element that doesn't exist in curr, then rhs IS NOT a subtree.
            return false;

        return (curr->data == rhs->data && privateIsSubTree(curr->right, rhs->right) && privateIsSubTree(curr->left, rhs->left));

        /**
         * a tree is a subtree of another tree if:
         * 1- the data in the root of both trees is equal
         * 2- the right subtree of the root of one tree is equal to the right subtree of the root of the other tree
         * 3- the left subtree of the root of one tree is equal to the left subtree of the root of the other tree
         */
    }
public:
    // Constructor
    BSTFCI();

    // Unformatted output
    void linearPrint();
    void levelPrint();
    void printRange(T, T, BSTNode*);

    // Operations
    BSTNode* find(T);
    BSTNode* getRoot();

    // State flag functions
    bool isBalanced();
    bool isSubTree(BSTFCI&);
    bool isFlipped();

    // Modifiers
    void insert(T);
    void insertStringLine(string, int);
    void destroy(BSTNode*);
    void flip(BSTNode*);

    // Destructor
    ~BSTFCI();
};

/**
 * Default constructor
 */
template <class T>
BSTFCI<T>::BSTFCI()
{
    root = NULL;
    flipped = false;
}

/**
 * Display BSTFCI values on the screen
 */
template <class T>
void BSTFCI<T>::linearPrint()
{
    privateLinearPrint(root);
}

/**
 * xxxxxxxxxxxxxxxxxxx
 */
template <class T>
void BSTFCI<T>::levelPrint()
{
    if(root == NULL)
        return;
    /// prints the tree level by level from left to right (the leftmost node is the root of the tree)
    int space = 0;
    privateLevelPrint(root, space);
}

/**
 * xxxxxxxxxxxxxxxxxxx
 * @param T, T
 */
template <class T>
void BSTFCI<T>::printRange(T low, T high, BSTNode *cur)
{
    if (cur == NULL)
        return;

    // If cur->data is greater than low, then recursively call in left subtree
    if (low < cur->data)
        this->printRange(low, high, cur->left);

    // If cur->data is in range, then print the cur->data
    if(low <= cur->data && high >= cur->data)
        cout << cur->data << " ";

    // If cur->data is less than high, then recursively call in right subtree
    if (high > cur->data)
        this->printRange(low, high, cur->right);
}

/**
 * xxxxxxxxxxxxxxxxxxx
 * @param  T
 * @return BSTNode
 */
template <class T>
typename BSTFCI<T>::BSTNode* BSTFCI<T>::find(T data)
{
    /// returns a pointer to the node which has data equal to (T data), if this node isn't found, NULL is returned.
    return privateFind(data, root);
}

/**
 * xxxxxxxxxxxxxxxxxxx
 * @param  T
 * @return BSTNode
 */
template <class T>
typename BSTFCI<T>::BSTNode* BSTFCI<T>::getRoot()
{
    return this->root;
}

/**
 * xxxxxxxxxxxxxxxxxxx
 * @return bool
 */
template <class T>
bool BSTFCI<T>::isBalanced()
{
    return privateIsBalanced(root);
}

/**
 * xxxxxxxxxxxxxxxxxxx
 * @param  BSTFCI
 * @return bool
 */
template <class T>
bool BSTFCI<T>::isSubTree(BSTFCI &rhsTree)
{
    if(rhsTree.root == NULL)
        return true;

    BSTNode* temp = find(rhsTree.root->data);
    if(temp == NULL) /// if the data in the root of rhs isn't found in (this)
        return false;

    return privateIsSubTree(temp, rhsTree.root);
}

/**
 * xxxxxxxxxxxxxxxxxxx
 * @return bool
 */
template <class T>
bool BSTFCI<T>::isFlipped()
{
    return this->flipped;
}

/**
 * xxxxxxxxxxxxxxxxxxx
 * @param T
 */
template <class T>
void BSTFCI<T>::insert(T data)
{
    insertPrivate(data, root);
}

/**
 * xxxxxxxxxxxxxxxxxxx
 * @param string, int
 */
template <class T>
void BSTFCI<T>::insertStringLine(string str, int line)
{
    stringLine strL;
    strL.word = str;
    strL.line.push_back(line);
    BSTNode* node = insertPrivate(strL, root);
    if (node != NULL)
    {
        node->data.line.push_back(line);
    }
}

/**
 * ADD com-------------------------
 * @param Node
 */
template <class T>
void BSTFCI<T>::destroy(BSTNode* _node)
{
    if (_node == NULL)
        return;

    destroy(_node->left);
    destroy(_node->right);

    delete _node;
}

/**
 * xxxxxxxxxxx
 * @param Node
 */
template <class T>
void BSTFCI<T>::flip(BSTNode *_node)
{
    if (_node == NULL)
        return;
    else
    {
        flip(_node->left);
        flip(_node->right);

        BSTNode *temp = _node->left;
        _node->left   = _node->right;
        _node->right  = temp;
    }

    this->flipped = this->flipped ^ true;
}

/**
 * xxxxxxxxxxxxxxxxxxx
 */
template <class T>
BSTFCI<T>::~BSTFCI()
{
    this->destroy(this->root);
    this->root = NULL;
}
#endif // BSTFCI_H_INCLUDED
