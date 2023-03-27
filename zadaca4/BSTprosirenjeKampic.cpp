#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct Node
{
    int key;
    Node *left, *right, *parent;
};

class BST
{
public:

    Node *root;

    Node* insert(int key, Node *node)
    {
        if (node == NULL)
        {
            node = new Node;
            node->key = key;
            node->left = node->right = node->parent = NULL;
        } else if (key > node->key)
        {
            node->right = insert(key, node->right);
            node->right->parent = node;
        } else
        {
            node->left = insert(key, node->left);
            node->left->parent = node;
        }
        return node;

    }

    void inorder(Node *node)
    {
        if (node == NULL)
            return;
        inorder(node->left);
        cout << node->key << ' ';
        inorder(node->right);
    }

    Node* search(int key, Node *node)
    {
        if (node == NULL || key == node->key)
            return node;
        if (key > node->key)
            return search(key, node->right);
        return search(key, node->left);
    }

    Node* find_min(Node *node)
    {
        if (node == NULL)
            return NULL;
        if (node->left == NULL)
            return node;
        return find_min(node->left);
    }

    Node* find_max(Node *node)
    {
        if (node == NULL)
            return NULL;
        if (node->right == NULL)
            return node;
        return find_min(node->right);
    }

    Node* successor(Node *node)
    {
        if (node->right != NULL)
            return find_min(node->right);

        Node *parent = node->parent;
        while (parent != NULL && node == parent->right) {
            node = parent;
            parent = node->parent;
        }

        return parent;
    }

    Node* predecessor(Node *node)
    {
        if (node->left != NULL)
            return find_max(node->left);

        Node *parent = node->parent;
        while (parent != NULL && node == parent->left) {
            node = parent;
            parent = node->parent;
        }

        return parent;
    }

public:
    BST() : root(NULL) {}

    void print()
    {
        inorder(root);
    }

    void insert(int key)
    {
        root = insert(key, root);
    }

    bool search(int key)
    {
        return search(key, root);
    }

    int find_min()
    {
        Node *node = find_min(root);
        if (node != NULL)
            return node->key;
        return -1;
    }

    int find_max()
    {
        Node *node = find_max(root);
        if (node != NULL)
            return node->key;
        return -1;
    }

    int successor(int key)
    {
        Node *node = search(key, root);
        if (node == NULL)
            return -1;
        node = successor(node);
        if (node == NULL)
            return -1;
        return node->key;
    }

    int predecessor(int key)
    {
        Node *node = search(key, root);
        if (node == NULL)
            return -1;
        node = predecessor(node);
        if (node == NULL)
            return -1;
        return node->key;
    }

};

//Zadatak1
bool nodesEqual(Node *root1, Node *root2){
    if((root1 == nullptr) && (root2 == nullptr)) {return true;}
    if((root1 != nullptr) && (root2 != nullptr)) {
        return (nodesEqual(root1->left, root2 -> left)
               && nodesEqual(root1 -> right, root2 -> right));
    }
    else return false;
}


bool structurallyEqual(BST T1, BST T2){
    return nodesEqual(T1.root, T2.root);
}

//Zadatak2
void nthPower(Node *node, int n) {
    if (node == NULL) return;
    node->key = pow(node->key, n);
    nthPower(node->left, n);
    nthPower(node->right, n);
}
BST nthPowerBST(BST T, int n){
    nthPower(T.root, n);
    return T;
}

int main()
{
    BST stablo1;
    stablo1.insert(50);
    stablo1.insert(25);
    stablo1.insert(75);
    stablo1.insert(10);
    stablo1.insert(30);
    stablo1.insert(100);

    BST stablo2;
    stablo2.insert(6);
    stablo2.insert(3);
    stablo2.insert(8);
    stablo2.insert(1);
    stablo2.insert(4);
    stablo2.insert(10);

    BST stablo3;
    stablo3.insert(50);
    stablo3.insert(25);
    stablo3.insert(75);
    stablo3.insert(20);
    stablo3.insert(100);

    BST stablo4;
    stablo4.insert(6);
    stablo4.insert(3);
    stablo4.insert(8);
    stablo4.insert(1);

    cout << "Zadatak 1" << endl;

    if (structurallyEqual(stablo1, stablo2))
        cout << "T1 i T2 su strukturalno jednaki" << endl;
    else
        cout << "T1 i T2 nisu strukturalno jednaki" << endl;

    if (structurallyEqual(stablo3, stablo4))
        cout << "T3 i T4 su strukturalno jednaki" << endl;
    else
        cout << "T3 i T4 nisu strukturalno jednaki" << endl;

    cout << "Zadatak 2" << endl;

    BST T;
    T.insert(5);
    T.insert(3);
    T.insert(7);
    T.insert(1);
    T.insert(4);
    T.insert(9);

    BST BSTT1 = nthPowerBST(T, 2);
    BSTT1.print();
    cout << endl;



}

