#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Employee {
    int id; string name, role; float salary;
};

void update_index() {
    ifstream fin("employee.txt");
    ofstream fout("index.txt");
    vector<pair<int, int>> index;
    Employee e; int pos = 0;

    while (fin >> e.id >> e.name >> e.role >> e.salary)
        index.push_back({e.id, pos++});

    sort(index.begin(), index.end());
    for (auto entry : index)
        fout << entry.first << " " << entry.second << "\n";

    fin.close(); fout.close();
}

void add() {
    ofstream fout("employee.txt", ios::app);
    Employee e;
    cout << "Enter ID Name Role Salary:\n";
    cin >> e.id >> e.name >> e.role >> e.salary;
    fout << e.id << " " << e.name << " " << e.role << " " << e.salary << "\n";
    fout.close();
    update_index();
}

void search() {
    int key, pos = -1;
    cout << "Enter ID to search:\n";
    cin >> key;

    ifstream fin("index.txt");
    while (!fin.eof()) {
        int id, p;
        fin >> id >> p;
        if (id == key) {
            pos = p;
            break;
        }
    }
    fin.close();

    if (pos == -1) {
        cout << "Not Found\n";
        return;
    }

    ifstream data("employee.txt");
    Employee e; int line = 0;
    while (data >> e.id >> e.name >> e.role >> e.salary) {
        if (line++ == pos) {
            cout << e.id << " " << e.name << " " << e.role << " " << e.salary << "\n";
            break;
        }
    }
    data.close();
}

void remove_record() {
    int key;
    cout << "Enter ID to delete:\n";
    cin >> key;
    Employee e;
    ifstream fin("employee.txt");
    ofstream fout("temp.txt");
    bool found = false;

    while (fin >> e.id >> e.name >> e.role >> e.salary) {
        if (e.id != key)
            fout << e.id << " " << e.name << " " << e.role << " " << e.salary << "\n";
        else
            found = true;
    }

    fin.close(); fout.close();
    remove("employee.txt");
    rename("temp.txt", "employee.txt");
    update_index();

    if (!found)
        cout << "Not Found\n";
    else
        cout << "Deleted successfully.\n";
}

int main() {
    int ch;
    while (true) {
        cout << "\n1.Add 2.Delete 3.Search 4.Exit\n";
        cin >> ch;
        if (ch == 1) add();
        else if (ch == 2) remove_record();
        else if (ch == 3) search();
        else break;
    }
}

