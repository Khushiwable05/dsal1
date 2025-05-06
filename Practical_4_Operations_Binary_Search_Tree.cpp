#include <iostream>
using namespace std;

class Node {
public:
    int val;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int key) : val(key) {}
};

Node* insert(Node* root, int key) {
    if (!root) return new Node(key);
    if (key < root->val) root->left = insert(root->left, key);
    else root->right = insert(root->right, key);
    return root;
}

int longest_path(Node* root) {
    if (!root) return 0;
    return max(longest_path(root->left), longest_path(root->right)) + 1;
}

Node* min_value_node(Node* root) {
    while (root && root->left) root = root->left;
    return root;
}

void swap_children(Node* root) {
    if (root) {
        swap(root->left, root->right);
        swap_children(root->left);
        swap_children(root->right);
    }
}

Node* search(Node* root, int key) {
    if (!root || root->val == key) return root;
    return search(key < root->val ? root->left : root->right, key);
}

void inorder(Node* root) {
    if (root) { inorder(root->left); cout << root->val << " "; inorder(root->right); }
}

int main() {
    Node* root = nullptr;
    int values[] = {50, 30, 20, 40, 70, 60, 80};
    for (int val : values) root = insert(root, val);
    
    root = insert(root, 25);  // i. Insert 25
    
    cout << "Longest path length: " << longest_path(root) << endl;  // ii. Longest path
    
    cout << "Minimum value: " << min_value_node(root)->val << endl;  // iii. Min value
    
    swap_children(root);  // iv. Swap children
    
    int key = 40;
    cout << (search(root, key) ? "Found " : "Not found ") << key << endl;  // v. Search for 40
    
    cout << "In-order traversal: ";
    inorder(root);  // Print the tree after swap
    cout << endl;

    return 0;
}

// Output:
// Longest path length: 4   
// Minimum value: 20
// Found 40
// In-order traversal: 20 25 30 40 50 60 70 80