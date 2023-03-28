#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

struct Node {
    int key;
    int h;
    Node *left, *right, *parent;

    Node(int key) : key(key), h(1), left(nullptr), right(nullptr), parent(nullptr) {}
};

int height(Node *node) {
    if (node == NULL) {
        return 0;
    }
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return 1 + max(leftHeight, rightHeight);
}

int balanceOfNode(Node *node) {
    if (node == NULL) {
        return 0;
    }
    int leftHeight = (node->left != NULL) ? node->left->h : 0;
    int rightHeight = (node->right != NULL) ? node->right->h : 0;
    return leftHeight - rightHeight;
}

void updateHeight(Node *node) {
    node->h = 1 + max(height(node->left), height(node->right));
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = y;
    }
    x->right = y;

    x->parent = y->parent;
    y->parent = x;

    y->h = max(height(y->left), height(y->right)) + 1;
    x->h = max(height(x->left), height(x->right)) + 1;

    return x;
}


Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->left = x;

    y->parent = x->parent;
    x->parent = y;

    x->h = max(height(x->left), height(x->right)) + 1;
    y->h = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insert(Node* root, int key) {
    if (root == NULL) {
        return new Node(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    } else {
        // Ako se čvor s istom vrijednošću ključa već nalazi u stablu, ne radi ništa
        return root;
    }

    root->h = max(height(root->left), height(root->right)) + 1;

    int balance = balanceOfNode(root);

    if (balance > 1 && key < root->left->key) {
        return rightRotate(root);
    }

    if (balance < -1 && key > root->right->key) {
        return leftRotate(root);
    }

    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


void inorder(Node* root) {
    stack<Node*> s;
    Node* curr = root;

    while (curr != NULL || !s.empty()) {
        while (curr != NULL) {
            s.push(curr);
            curr = curr->left;
        }

        curr = s.top();
        s.pop();

        cout << curr->key << " ";

        curr = curr->right;
    }
}

int main() {
    Node *root = nullptr;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    inorder(root);
    cout << endl;

    return 0;
}
