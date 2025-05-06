#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class OptimalBST {
public:
    vector<int> keys;  // Keys (sorted)
    vector<double> prob;  // Search probabilities (using double for floating-point values)
    vector<vector<double>> dp;  // DP table for minimum cost
    vector<vector<double>> sumProb;  // Table for sum of probabilities

    // Constructor to initialize keys, probabilities, and tables
    OptimalBST(vector<int>& k, vector<double>& p) {
        keys = k;
        prob = p;
        int n = keys.size();
        
        dp.resize(n, vector<double>(n, 0));  // Initialize DP table with zeros
        sumProb.resize(n, vector<double>(n, 0));  // Initialize sumProb table
        
        // Calculate sum of probabilities from i to j
        for (int i = 0; i < n; i++) {
            sumProb[i][i] = prob[i];
            for (int j = i + 1; j < n; j++) {
                sumProb[i][j] = sumProb[i][j - 1] + prob[j];
            }
        }
    }

    // Function to calculate the minimum cost of the BST
    double constructOptimalBST() {
        int n = keys.size();
        
        // Initialize dp[i][i] to the probability of the key
        for (int i = 0; i < n; i++) {
            dp[i][i] = prob[i];
        }
        
        // Solve for all subproblems of size 2 to n
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                
                // Try every key as the root and take the minimum cost
                for (int r = i; r <= j; r++) {
                    double leftCost = (r > i) ? dp[i][r - 1] : 0;
                    double rightCost = (r < j) ? dp[r + 1][j] : 0;
                    double cost = leftCost + rightCost + sumProb[i][j];
                    dp[i][j] = min(dp[i][j], cost);
                }
            }
        }
        
        return dp[0][n - 1];  // The minimum search cost for the entire tree
    }
};

int main() {
    vector<int> keys = {10, 20, 30, 40};  // Sorted keys
    vector<double> prob = {0.1, 0.3, 0.2, 0.4};  // Search probabilities (now using double)

    OptimalBST tree(keys, prob);
    double minCost = tree.constructOptimalBST();
    
    cout << "The minimum cost of searching in the optimal BST is: " << minCost << endl;
    return 0;
}
// Output:
// The minimum cost of searching in the optimal BST is: 1.9
