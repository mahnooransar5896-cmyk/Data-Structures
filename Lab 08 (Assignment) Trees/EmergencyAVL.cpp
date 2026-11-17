#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

class Node {
public:
    int id;
    string location;
    int severity;
    int height;
    Node* left;
    Node* right;

    Node(int i, string loc, int sev) {
        id = i;
        location = loc;
        severity = sev;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

class AVL {
public:
    Node* root;

    AVL() {
        root = NULL;
    }

    int getHeight(Node* n) {
        if (n == NULL) return 0;
        return n->height;
    }

    int getBalance(Node* n) {
        if (n == NULL) return 0;
        return getHeight(n->left) - getHeight(n->right);
    }

    void updateHeight(Node* n) {
        n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balanceNode(Node* node) {
        updateHeight(node);
        int bf = getBalance(node);

        if (bf > 1 && getBalance(node->left) >= 0) {
            cout << "LL Rotation performed!\n";
            return rotateRight(node);
        }

        if (bf > 1 && getBalance(node->left) < 0) {
            cout << "LR Rotation performed!\n";
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (bf < -1 && getBalance(node->right) <= 0) {
            cout << "RR Rotation performed!\n";
            return rotateLeft(node);
        }

        if (bf < -1 && getBalance(node->right) > 0) {
            cout << "RL Rotation performed!\n";
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* insert(Node* node, int id, string location, int severity) {
        if (node == NULL) return new Node(id, location, severity);

        if (id < node->id)
            node->left = insert(node->left, id, location, severity);
        else if (id > node->id)
            node->right = insert(node->right, id, location, severity);
        else
            return node;

        return balanceNode(node);
    }

    Node* minNode(Node* node) {
        while (node->left != NULL) node = node->left;
        return node;
    }

    Node* deleteNode(Node* node, int id, bool& found) {
        if (node == NULL) return NULL;

        if (id < node->id) {
            node->left = deleteNode(node->left, id, found);
        } else if (id > node->id) {
            node->right = deleteNode(node->right, id, found);
        } else {
            found = true;
            if (node->left == NULL || node->right == NULL) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            Node* succ = minNode(node->right);
            node->id = succ->id;
            node->location = succ->location;
            node->severity = succ->severity;
            bool dummy = false;
            node->right = deleteNode(node->right, succ->id, dummy);
        }

        return balanceNode(node);
    }

    Node* search(Node* node, int id) {
        if (node == NULL || node->id == id) return node;
        if (id < node->id) return search(node->left, id);
        return search(node->right, id);
    }

    void printNode(Node* n) {
        cout << "ID: " << n->id
             << " | Location: " << n->location
             << " | Severity: " << n->severity
             << " | Height: " << n->height
             << " | Balance Factor: " << getBalance(n) << endl;
    }

    void inOrder(Node* node) {
        if (node == NULL) return;
        inOrder(node->left);
        printNode(node);
        inOrder(node->right);
    }

    void levelOrder(Node* node) {
        if (node == NULL) return;
        queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            Node* cur = q.front();
            q.pop();
            printNode(cur);
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
    }

    void displayTree(Node* node, int space = 0) {
        if (node == NULL) return;
        space += 5;
        displayTree(node->right, space);
        cout << endl;
        for (int i = 5; i < space; i++) cout << " ";
        cout << node->id << endl;
        displayTree(node->left, space);
    }
};

void demo(string title, int a, int b, int c) {
    cout << "\n===== " << title << " ROTATION DEMONSTRATION =====\n";
    AVL t;
    t.root = t.insert(t.root, a, "Lahore", 3);
    t.root = t.insert(t.root, b, "Karachi", 4);
    t.root = t.insert(t.root, c, "Islamabad", 5);

    cout << "\n" << title << " Rotation Final Tree:\n";
    t.displayTree(t.root);

    cout << "\n" << title << " Rotation Level Order:\n";
    t.levelOrder(t.root);
}

int main() {
    AVL tree;

    cout << "===== EMERGENCY RESCUE OPERATIONS =====\n";

    tree.root = tree.insert(tree.root, 50, "Islamabad", 5);
    tree.root = tree.insert(tree.root, 30, "Lahore", 3);
    tree.root = tree.insert(tree.root, 70, "Karachi", 4);
    tree.root = tree.insert(tree.root, 20, "Peshawar", 5);
    tree.root = tree.insert(tree.root, 40, "Quetta", 2);
    tree.root = tree.insert(tree.root, 60, "Multan", 4);
    tree.root = tree.insert(tree.root, 80, "Faisalabad", 3);
    tree.root = tree.insert(tree.root, 10, "Sialkot", 5);
    tree.root = tree.insert(tree.root, 25, "Hyderabad", 2);
    tree.root = tree.insert(tree.root, 35, "Gujranwala", 3);
    tree.root = tree.insert(tree.root, 45, "Abbottabad", 4);
    tree.root = tree.insert(tree.root, 90, "Bahawalpur", 5);

    cout << "\n12 Emergency Records Inserted!\n";

    cout << "\n===== IN-ORDER TRAVERSAL =====\n";
    tree.inOrder(tree.root);

    cout << "\n===== LEVEL-ORDER TRAVERSAL (BFS) =====\n";
    tree.levelOrder(tree.root);

    cout << "\n===== AVL TREE STRUCTURE =====\n";
    tree.displayTree(tree.root);

    int sid;
    cout << "\nEnter Emergency ID to search: ";
    cin >> sid;
    Node* found = tree.search(tree.root, sid);
    if (found != NULL) {
        cout << "\nEmergency Record Found!\n";
        tree.printNode(found);
    } else {
        cout << "\nEmergency Record Not Found!\n";
    }

    int did;
    cout << "\n===== DELETE EMERGENCY RECORD =====\n";
    cout << "Enter Emergency ID to delete: ";
    cin >> did;
    bool deleted = false;
    tree.root = tree.deleteNode(tree.root, did, deleted);
    if (deleted)
        cout << "Emergency Record Deleted Successfully!\n";
    else
        cout << "Emergency ID not found, nothing deleted.\n";

    cout << "\n===== FINAL IN-ORDER TRAVERSAL =====\n";
    tree.inOrder(tree.root);

    cout << "\n===== FINAL LEVEL-ORDER TRAVERSAL =====\n";
    tree.levelOrder(tree.root);

    cout << "\n===== FINAL AVL TREE STRUCTURE =====\n";
    tree.displayTree(tree.root);

    demo("LL", 30, 20, 10);
    demo("RR", 10, 20, 30);
    demo("LR", 30, 10, 20);
    demo("RL", 10, 30, 20);

    return 0;
}
