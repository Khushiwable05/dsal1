#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class AVLTree {
    struct Node {
        string word;
        string meaning;
        int height;
        Node* left;
        Node* right;
        Node(string w, string m) : word(w), meaning(m), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Utility function to get height of the node
    int height(Node* node) {
        return node ? node->height : 0;
    }

    // Utility function to calculate balance factor of the node
    int balanceFactor(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    // Right rotation for balancing
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    // Left rotation for balancing
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    // Recursive function to insert a new node with word and meaning
    Node* insert(Node* node, string word, string meaning) {
        if (!node)
            return new Node(word, meaning);

        if (word < node->word)
            node->left = insert(node->left, word, meaning);
        else if (word > node->word)
            node->right = insert(node->right, word, meaning);
        else
            node->meaning = meaning; // Update meaning if word already exists

        node->height = max(height(node->left), height(node->right)) + 1;

        int balance = balanceFactor(node);

        // Balancing the node if unbalanced
        if (balance > 1 && word < node->left->word) // Left Left Case
            return rightRotate(node);
        if (balance < -1 && word > node->right->word) // Right Right Case
            return leftRotate(node);
        if (balance > 1 && word > node->left->word) { // Left Right Case
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && word < node->right->word) { // Right Left Case
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Recursive function to delete a node with the given word
    Node* deleteNode(Node* root, string word) {
        if (!root)
            return root;

        if (word < root->word)
            root->left = deleteNode(root->left, word);
        else if (word > root->word)
            root->right = deleteNode(root->right, word);
        else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->word = temp->word;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->word);
            }
        }

        if (!root)
            return root;

        root->height = max(height(root->left), height(root->right)) + 1;

        int balance = balanceFactor(root);

        if (balance > 1 && balanceFactor(root->left) >= 0)
            return rightRotate(root);

        if (balance < -1 && balanceFactor(root->right) <= 0)
            return leftRotate(root);

        if (balance > 1 && balanceFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && balanceFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    // Utility function to find the node with minimum value
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left)
            current = current->left;
        return current;
    }

    // In-order traversal to display the tree in ascending order
    void inOrder(Node* node) {
        if (!node)
            return;
        inOrder(node->left);
        cout << node->word << " : " << node->meaning << " (BF=" << balanceFactor(node) << ")" << endl;
        inOrder(node->right);
    }

    // Reverse in-order traversal to display the tree in descending order
    void reverseInOrder(Node* node) {
        if (!node)
            return;
        reverseInOrder(node->right);
        cout << node->word << " : " << node->meaning << " (BF=" << balanceFactor(node) << ")" << endl;
        reverseInOrder(node->left);
    }

    // Search function to find a word and return the number of comparisons
    int search(Node* root, string word) {
        if (!root)
            return 0;

        int comparisons = 1;
        if (word < root->word)
            comparisons += search(root->left, word);
        else if (word > root->word)
            comparisons += search(root->right, word);
        return comparisons;
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(string word, string meaning) {
        root = insert(root, word, meaning);
    }

    void deleteWord(string word) {
        root = deleteNode(root, word);
    }

    void display(bool ascending) {
        if (ascending)
            inOrder(root);
        else
            reverseInOrder(root);
    }

    int searchWord(string word) {
        return search(root, word);
    }
};

int main() {
    AVLTree dictionary;
    int choice;
    string word, meaning;

    while (true) {
        cout << "1. Create\n2. Insert\n3. Delete\n4. Display\n5. Exit\n";
        cout << "Enter a choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the number of words: ";
                int n;
                cin >> n;
                for (int i = 0; i < n; ++i) {
                    cout << "Enter word " << i + 1 << ": ";
                    cin >> word;
                    cout << "Enter the meaning: ";
                    cin >> meaning;
                    dictionary.insert(word, meaning);
                }
                break;
            case 2:
                cout << "Enter word: ";
                cin >> word;
                cout << "Enter the meaning: ";
                cin >> meaning;
                dictionary.insert(word, meaning);
                break;
            case 3:
                cout << "Enter the word to delete: ";
                cin >> word;
                dictionary.deleteWord(word);
                break;
            case 4:
                cout << "Display in ascending (1) or descending (0): ";
                int order;
                cin >> order;
                dictionary.display(order);
                break;
            case 5:
                cout << "Exiting.\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
    return 0;
}
