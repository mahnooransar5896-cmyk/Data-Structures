
#include <iostream>
using namespace std;

class Node
{
public:
    string name;
    Node* left;
    Node* right;

    Node(string n)
    {
        name = n;
        left = NULL;
        right = NULL;
    }
};

int main()
{
    Node* root = new Node("HOD");

    root->left = new Node("Coordinator_CS");
    root->right = new Node("Coordinator_AI");

    root->left->left = new Node("Faculty_1");
    root->left->right = new Node("Faculty_2");

    root->right->left = new Node("Faculty_3");
    root->right->right = new Node("Faculty_4");

    cout << "===== UNIVERSITY DEPARTMENT HIERARCHY =====" << endl;

    cout << "\nMember: " << root->name << endl;
    cout << "Left Child: " << root->left->name << endl;
    cout << "Right Child: " << root->right->name << endl;

    cout << "\nMember: " << root->left->name << endl;
    cout << "Left Child: " << root->left->left->name << endl;
    cout << "Right Child: " << root->left->right->name << endl;

    cout << "\nMember: " << root->right->name << endl;
    cout << "Left Child: " << root->right->left->name << endl;
    cout << "Right Child: " << root->right->right->name << endl;

    cout << "\nMember: " << root->left->left->name << endl;
    cout << "Left Child: NULL" << endl;
    cout << "Right Child: NULL" << endl;

    cout << "\nMember: " << root->left->right->name << endl;
    cout << "Left Child: NULL" << endl;
    cout << "Right Child: NULL" << endl;

    cout << "\nMember: " << root->right->left->name << endl;
    cout << "Left Child: NULL" << endl;
    cout << "Right Child: NULL" << endl;

    cout << "\nMember: " << root->right->right->name << endl;
    cout << "Left Child: NULL" << endl;
    cout << "Right Child: NULL" << endl;

    return 0;
}

