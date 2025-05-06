#include <iostream>
#include <fstream>
using namespace std;

void add() {
    int r; 
    string n, d, a;
    ofstream f("data.txt", ios::app);
    cin >> r >> n >> d >> a;
    f << r << " " << n << " " << d << " " << a << "\n"; 
    f.close();
}

void show() {
    int r; 
    string n, d, a;
    ifstream f("data.txt");
    while (f >> r >> n >> d >> a) cout << r << " " << n << " " << d << " " << a << endl;
    f.close();
}

void search() {
    int key, r; 
    string n, d, a; 
    bool fnd = false;
    cin >> key; 
    ifstream f("data.txt");
    while (f >> r >> n >> d >> a)
        if (r == key) { cout << r << " " << n << " " << d << " " << a << endl; fnd = true; }
    if (!fnd) 
    cout << "Not found\n"; 
    f.close();
}

void del() {
    int key, r; 
    string n, d, a; 
    bool fnd = false;
    cin >> key; 
    ifstream f("data.txt"); 
    ofstream t("temp.txt");
    while (f >> r >> n >> d >> a)
        if (r != key) t << r << " " << n << " " << d << " " << a << "\n"; 
        else 
        fnd = true;
    f.close(); 
    t.close();
    remove("data.txt"); 
    rename("temp.txt", "data.txt");
    if (!fnd) 
    cout << "Not found\n";
}

int main() {
    int c;
    while (true) {
        cout << "1.Add 2.Del 3.Srch 4.Show 5.Exit\n";
        cin >> c;
        
        if (c == 1) add(); 
        else if (c == 2) del();
        else if (c == 3) search(); 
        else if (c == 4) show();
        else break;
    }
}

//Output:
// 1.Add 2.Del 3.Srch 4.Show 5.Exit
// 1
// 1 2 CSE 1234

// This code implements a simple sequential file system for managing student records.
// It allows adding, deleting, searching, and displaying records using a text file. 
// The records are stored in the format: roll number, name, department, and address.
// The program uses file I/O operations to read and write data to a file named "data.txt".
// The user can perform operations through a menu-driven interface, and the program continues until the user chooses to exit.