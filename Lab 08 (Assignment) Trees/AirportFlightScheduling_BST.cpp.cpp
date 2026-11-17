
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int flightNo;
    string destination;
    string departureTime;
    Node* left;
    Node* right;

    Node(int no, string dest, string time) {
        flightNo = no;
        destination = dest;
        departureTime = time;
        left = NULL;
        right = NULL;
    }
};

class BST {
public:
    Node* root;

    BST() {
        root = NULL;
    }

    Node* insert(Node* node, int no, string dest, string time) {
        if (node == NULL) {
            return new Node(no, dest, time);
        }

        if (no < node->flightNo) {
            node->left = insert(node->left, no, dest, time);
        }
        else if (no > node->flightNo) {
            node->right = insert(node->right, no, dest, time);
        }

        return node;
    }

    Node* search(Node* node, int no) {
        if (node == NULL || node->flightNo == no) {
            return node;
        }

        if (no < node->flightNo) {
            return search(node->left, no);
        }

        return search(node->right, no);
    }

    Node* findMin(Node* node) {
        while (node != NULL && node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    Node* findMax(Node* node) {
        while (node != NULL && node->right != NULL) {
            node = node->right;
        }
        return node;
    }

    Node* deleteFlight(Node* node, int no) {
        if (node == NULL) {
            return NULL;
        }

        if (no < node->flightNo) {
            node->left = deleteFlight(node->left, no);
        }
        else if (no > node->flightNo) {
            node->right = deleteFlight(node->right, no);
        }
        else {
            if (node->left == NULL && node->right == NULL) {
                delete node;
                return NULL;
            }
            else if (node->left == NULL) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == NULL) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            else {
                Node* temp = findMin(node->right);

                node->flightNo = temp->flightNo;
                node->destination = temp->destination;
                node->departureTime = temp->departureTime;

                node->right = deleteFlight(node->right, temp->flightNo);
            }
        }

        return node;
    }

    void inOrder(Node* node) {
        if (node != NULL) {
            inOrder(node->left);
            displayFlight(node);
            inOrder(node->right);
        }
    }

    void preOrder(Node* node) {
        if (node != NULL) {
            displayFlight(node);
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void postOrder(Node* node) {
        if (node != NULL) {
            postOrder(node->left);
            postOrder(node->right);
            displayFlight(node);
        }
    }

    void displayFlight(Node* node) {
        cout << node->flightNo << " - "
             << node->destination << " - "
             << node->departureTime << endl;
    }

    int countFlights(Node* node) {
        if (node == NULL) {
            return 0;
        }

        return 1 + countFlights(node->left)
                 + countFlights(node->right);
    }

    int height(Node* node) {
        if (node == NULL) {
            return 0;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        if (leftHeight > rightHeight) {
            return 1 + leftHeight;
        }

        return 1 + rightHeight;
    }

    void displayTree(Node* node, int space = 0) {
        if (node == NULL) {
            return;
        }

        space += 5;

        displayTree(node->right, space);

        cout << endl;
        for (int i = 5; i < space; i++) {
            cout << " ";
        }

        cout << node->flightNo << endl;

        displayTree(node->left, space);
    }
};

int main() {
    BST tree;

    cout << "===== AIRPORT FLIGHT SCHEDULING SYSTEM =====" << endl;

    tree.root = tree.insert(tree.root, 1050, "London", "08:00");
    tree.root = tree.insert(tree.root, 1030, "Dubai", "09:00");
    tree.root = tree.insert(tree.root, 1070, "Paris", "10:00");
    tree.root = tree.insert(tree.root, 1020, "Istanbul", "11:00");
    tree.root = tree.insert(tree.root, 1040, "Riyadh", "12:00");
    tree.root = tree.insert(tree.root, 1060, "Tokyo", "13:00");
    tree.root = tree.insert(tree.root, 1080, "New York", "14:00");
    tree.root = tree.insert(tree.root, 1010, "Doha", "15:00");
    tree.root = tree.insert(tree.root, 1025, "Jeddah", "16:00");
    tree.root = tree.insert(tree.root, 1035, "Qatar", "17:00");
    tree.root = tree.insert(tree.root, 1045, "Beijing", "18:00");
    tree.root = tree.insert(tree.root, 1090, "Toronto", "19:00");

    cout << "\n12 Flights Inserted Successfully!\n";

    cout << "\n===== IN-ORDER TRAVERSAL =====\n";
    tree.inOrder(tree.root);

    cout << "\n===== PRE-ORDER TRAVERSAL =====\n";
    tree.preOrder(tree.root);

    cout << "\n===== POST-ORDER TRAVERSAL =====\n";
    tree.postOrder(tree.root);

    int searchNo;

    cout << "\nEnter flight number to search: ";
    cin >> searchNo;

    Node* result = tree.search(tree.root, searchNo);

    if (result != NULL) {
        cout << "\nFlight Found!\n";
        tree.displayFlight(result);
    }
    else {
        cout << "\nFlight Not Found!\n";
    }

    Node* minimum = tree.findMin(tree.root);
    Node* maximum = tree.findMax(tree.root);

    cout << "\nMinimum Flight Number: " << minimum->flightNo << endl;
    cout << "Maximum Flight Number: " << maximum->flightNo << endl;

    cout << "Total Flights: " << tree.countFlights(tree.root) << endl;
    cout << "Tree Height: " << tree.height(tree.root) << endl;

    cout << "\n===== BST BEFORE DELETION =====\n";
    tree.displayTree(tree.root);

    int deleteNo;

    cout << "\nEnter leaf flight number to delete: ";
    cin >> deleteNo;

    tree.root = tree.deleteFlight(tree.root, deleteNo);
    cout << "Leaf flight deleted successfully!\n";

    cout << "\nEnter one-child flight number to delete: ";
    cin >> deleteNo;

    tree.root = tree.deleteFlight(tree.root, deleteNo);
    cout << "One-child flight deleted successfully!\n";

    cout << "\nEnter two-child flight number to delete: ";
    cin >> deleteNo;

    tree.root = tree.deleteFlight(tree.root, deleteNo);
    cout << "Two-child flight deleted successfully!\n";

    cout << "\n===== FINAL BST STRUCTURE =====\n";
    tree.displayTree(tree.root);

    cout << "\n===== FINAL IN-ORDER TRAVERSAL =====\n";
    tree.inOrder(tree.root);

    cout << "\nFinal Total Flights: " << tree.countFlights(tree.root) << endl;
    cout << "Final Tree Height: " << tree.height(tree.root) << endl;

    return 0;
}

