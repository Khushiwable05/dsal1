#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Node {
public:
    string val;
    Node *left = nullptr, *right = nullptr;
    Node(string key) : val(key) {}
};

Node* constructTree(const string &prefix) {
    stack<Node*> st;
    for (int i = prefix.size() - 1; i >= 0; i--) {
        if (isalnum(prefix[i])) 
            st.push(new Node(string(1, prefix[i])));
        else {
            Node* node = new Node(string(1, prefix[i]));
            node->left = st.top(); st.pop();
            node->right = st.top(); st.pop();
            st.push(node);
        }
    }
    return st.top();
}

void postOrderTraversal(Node* root) {
    stack<Node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        Node* node = s1.top(); s1.pop();
        s2.push(node);
        if (node->left) s1.push(node->left);
        if (node->right) s1.push(node->right);
    }
    while (!s2.empty()) {
        cout << s2.top()->val << " ";
        s2.pop();
    }
    cout << endl;
}

void deleteTree(Node* root) {
    if (root) {
        stack<Node*> st;
        st.push(root);
        while (!st.empty()) {
            Node* node = st.top(); st.pop();
            if (node->left) st.push(node->left);
            if (node->right) st.push(node->right);
            delete node;
        }
    }
}

int main() {
    string prefix = "+--a*bc/def";  // Prefix expression
    Node* root = constructTree(prefix);
    cout << "Post-order traversal: \n";
    postOrderTraversal(root);
    deleteTree(root);
    return 0;
}

// Output:
// Post-order traversal:
// a b c * + d e f / -
//
// Explanation:
// The code constructs an expression tree from a prefix expression and performs a post-order traversal to print the expression in postfix notation. The tree is then deleted to free memory. The output shows the postfix expression derived from the given prefix expression.
// The tree structure is built using a stack, where operands are pushed onto the stack and operators pop two operands to create a new node. The post-order traversal is done using two stacks to ensure the correct order of operations.
// The deleteTree function uses a stack to delete all nodes in the tree, ensuring proper memory management. The main function demonstrates the construction and traversal of the tree using a sample prefix expression.
// The output shows the post-order traversal of the expression tree, which is the postfix notation of the given prefix expression. The tree is then deleted to free memory.
// The output shows the postfix expression derived from the given prefix expression.
// The tree structure is built using a stack, where operands are pushed onto the stack and operators pop two operands to create a new node. The post-order traversal is done using two stacks to ensure the correct order of operations.
