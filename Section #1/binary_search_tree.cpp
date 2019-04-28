/// Version 0.0
/// April 26th ~ April 27th
/// Khaled's part

#include <bits/stdc++.h>
using namespace std;

/// TODO: tree flip (should result in descending order linearPrint(), and mirrored tree levelPrint() ).
/// TODO: test ALL functions of BSTFCI on different data types
/// TODO: can complexity of printRange() be improved? current complexity is O(nlogn) (optional)
/// TODO: write a better pretty-printing function (optional).
/// TODO: write good documentation for the whole program (functions and main goal) (Khaled's task)


struct stringLine{
    string word;
    vector<int> line;
    /// overloading the comparison operators for tree insertion.
    bool operator< (const stringLine& rhs){
        return word < rhs.word;
    }
    bool operator> (const stringLine& rhs){
        return word > rhs.word;
    }
    bool operator== (const stringLine& rhs){
        return word == rhs.word;
    }
    friend ostream& operator<<(ostream& out, const stringLine& strL){
        out << strL.word << " ";
        for (int i = 0; i < strL.line.size(); ++i){
            out << strL.line[i] << " ";
        }
        out << endl;
        return out;
    }
};

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
    BSTNode* root; /// stores the address of the root node.

    BSTNode* createNode(T data){
        BSTNode* ptr = new BSTNode;
        ptr->data = data;
        ptr->left = NULL;
        ptr->right = NULL;
        return ptr;
    }

    BSTNode* insertPrivate (T data, BSTNode* ptr){
        /// returns a pointer to the node that contains data equal to (T data) before insertion, if such node doesn't exist, returns NULL
        if(root == NULL)
            root = createNode(data);
        else{
            if (data < ptr->data){
            /// if the inserted data is less than or equal the data at the current node then left insertion is done.
                if (ptr->left != NULL)
                    return insertPrivate(data, ptr->left);
                else
                    ptr->left = createNode(data);
            }
            else if (data > ptr->data){
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

    void privateLinearPrint(BSTNode* ptr){
        if(root != NULL){
            if(ptr->left != NULL){
                privateLinearPrint(ptr->left);
            }
            cout << ptr->data << endl;
            if(ptr->right != NULL){
                privateLinearPrint(ptr->right);
            }
        }
    }
    void privateLevelPrint(BSTNode* ptr, int space){
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
    int getHeight(BSTNode* node){
        if (node == NULL)
            return -1;
        return (1 + max(getHeight(node->right), getHeight(node->left)));
    }
    bool privateIsBalanced(BSTNode* node){
        if (node == NULL)
            return true;

        int absDifference = abs(getHeight(node->right) - getHeight(node->left));
        return ( (absDifference < 2) && (privateIsBalanced(node->right)) && (privateIsBalanced(node->left)) );
    }
    BSTNode* privateFind(T data, BSTNode* node){
        if (node == NULL)
            return NULL;
        if(data == node->data)
            return node;
        else if (data > node->data)
            return privateFind(data, node->right);
        else
            return privateFind(data, node->left);
    }
    bool privateIsSubTree(BSTNode* curr, BSTNode* rhs){
        if(curr == NULL && rhs == NULL)
            return true;
        if(rhs == NULL){ /// if curr contains an element that doesn't exist in rhs, then rhs is still a subtree
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
    BSTFCI() {root = NULL;}
    void insert(T data){
        insertPrivate(data, root);
    }
    void linearPrint() {privateLinearPrint(root);}
    void levelPrint() {
        /// prints the tree level by level from left to right (the leftmost node is the root of the tree)
        int space = 0;
        privateLevelPrint(root, space);
    }
    bool isBalanced(){return privateIsBalanced(root);}
    BSTNode* find(T data){
        /// returns a pointer to the node which has data equal to (T data), if this node isn't found, NULL is returned.
        return privateFind(data, root);
    }
    bool isSubTree(BSTFCI &rhsTree){
        BSTNode* temp = find(rhsTree.root->data);
        if(temp == NULL) /// if the data in the root of rhs isn't found in (this)
            return false;
        return privateIsSubTree(temp, rhsTree.root);
    }
    void printRange(T low, T high){ /// only valid for numerical values
        if (low <= high){
            BSTNode* node = this->find(low);
            if(node != NULL)
                cout << node->data << " ";
            printRange(low+1, high);
        }
        else
            cout << endl;
    }
    void insertStringLine(string str, int line){
        stringLine strL;
        strL.word = str;
        strL.line.push_back(line);
        BSTNode* node = insertPrivate(strL, root);
        if (node != NULL){
            node->data.line.push_back(line);
        }
    }
};

int main() {
    BSTFCI<int> tree;
    BSTFCI<int> tree2;
//    mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
//    for (int i = 0; i < 8; ++i){
//        int value = uniform_int_distribution<int>(0,15)(gen);
//        cout << "INSERTING: " << 'a' + value << endl;
//        tree.insert('g' + value);
//    }
    tree.insert(50);
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
    tree.levelPrint();
    cout << endl;
    cout << "===============================================" << endl;
    tree.printRange(17,60);
    cout << "===============================================" << endl;
    tree2.insert(5);
    tree2.insert(7);
    tree2.insert(6);
    tree2.insert(9);
    tree2.insert(10);
    tree2.levelPrint();
    cout << endl;
    cout << (tree.isSubTree(tree2) ? "tree2 is a subtree of tree" : "tree2 isn't a subtree of tree") << endl;
    cout << "=============================================" << endl;


    BSTFCI <stringLine> t;
    cout << "Enter text(enter DONE! on a separate line to exit): " << endl;
    int line = 0;
    while(true){
        string str;
        getline(cin, str);

        str.erase(remove(str.begin(), str.end(), '.'), str.end());
        str.erase(remove(str.begin(), str.end(), ','), str.end());

        if (str == "DONE!")
            break;

        ++line;
        string word = "";
        for (int i = 0; i < str.size(); ++i){
            if(str[i] != ' '){
                word.push_back(str[i]);
            }
            else{
                t.insertStringLine(word, line);
                word = "";
            }
        }
        if (!word.empty()){ /// handling last word in a line.
            t.insertStringLine(word, line);
        }
    }
    t.linearPrint();
/*
I am for truth,
no matter who tells it.
I am for justice,
no matter who it is for or against.
Malcom X
DONE!
*/
}
