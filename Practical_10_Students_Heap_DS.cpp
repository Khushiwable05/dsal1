#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n, mark;
    cout << "Enter number of students: ";
    cin >> n;

    vector<int> marks(n);
    priority_queue<int> maxHeap; // Max-Heap
    priority_queue<int, vector<int>, greater<int>> minHeap; // Min-Heap

    cout << "Enter marks:\n";
    for (int i = 0; i < n; ++i) {
        cin >> marks[i];
        maxHeap.push(marks[i]);
        minHeap.push(marks[i]);
    }

    cout << "Maximum Marks: " << maxHeap.top() << endl;
    cout << "Minimum Marks: " << minHeap.top() << endl;

    return 0;
}

//Output:
// Enter number of students: 5
// Enter marks:
// 78 85 92 67 88
// Maximum Marks: 92
// Minimum Marks: 67
