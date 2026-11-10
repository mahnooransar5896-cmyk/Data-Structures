
#include <iostream>
#include <algorithm>
using namespace std;

class Node
{
public:
    int data;
    int height;
    Node* left;
    Node* right;

    Node(int value)
    {
        data = value;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

int getHeight(Node* root)
{
    if (root == NULL)
        return 0;

    return root->height;
}

int getBalance(Node* root)
{
    if (root == NULL)
        return 0;

    return getHeight(root->left) - getHeight(root->right);
}

Node* rightRotate(Node* y)
{
    Node* x = y->left;
    Node* temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

Node* leftRotate(Node* x)
{
    Node* y = x->right;
    Node* temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

Node* insert(Node* root, int value)
{
    if (root == NULL)
        return new Node(value);

    if (value < root->data)
        root->left = insert(root->left, value);

    else if (value > root->data)
        root->right = insert(root->right, value);

    else
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    
    if (balance > 1 && value < root->left->data)
        return rightRotate(root);

   
    if (balance < -1 && value > root->right->data)
        return leftRotate(root);

    
    if (balance > 1 && value > root->left->data)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    
    if (balance < -1 && value < root->right->data)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inOrder(Node* root)
{
    if (root == NULL)
        return;

    inOrder(root->left);

    cout << root->data << " ";

    inOrder(root->right);
}

void display(Node* root, string prefix = "", string side = "")
{
    if (root == NULL)
        return;

    cout << prefix << side << root->data;
    cout << " (Height: " << root->height;
    cout << ", Balance Factor: " << getBalance(root) << ")" << endl;

    display(root->left, prefix + "    ", "L--- ");
    display(root->right, prefix + "    ", "R--- ");
}

int main()
{
    Node* root = NULL;

    int tokens[] = {15, 25, 35, 45, 55, 65, 75};

    cout << "===== HOSPITAL APPOINTMENT SYSTEM =====" << endl;

    cout << "\nInserting Appointment Tokens:" << endl;

    for (int i = 0; i < 7; i++)
    {
        cout << tokens[i] << " ";
        root = insert(root, tokens[i]);
    }

    cout << "\n\nIn-order Traversal: ";
    inOrder(root);

    cout << "\n\nFinal Balanced AVL Tree:" << endl;
    display(root);

    return 0;
}

