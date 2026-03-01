//============================================================================
// Name            : ProjectTwo.cpp
// Author          : Chakira Lora
// Version         : 1.2
// Description     : Project Two Submission - Streamlined Hash Table
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits> 

using namespace std;

// Course Structure to hold CSV data
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Hash Table Node for Chaining
struct Node {
    Course course;
    Node* next;
    Node(Course c) : course(c), next(nullptr) {}
};

class HashTable {
private:
    static const int SIZE = 17;
    Node* table[SIZE];

    int hash(string key) {
        int hashVal = 0;
        for (char ch : key) hashVal = hashVal * 31 + ch;
        return abs(hashVal % SIZE);
    }

public:
    HashTable() { for (int i = 0; i < SIZE; i++) table[i] = nullptr; }

    ~HashTable() {
        for (int i = 0; i < SIZE; i++) {
            Node* curr = table[i];
            while (curr != nullptr) {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
    }

    void insert(Course course) {
        int index = hash(course.courseNumber);
        Node* newNode = new Node(course);
        newNode->next = table[index];
        table[index] = newNode;
    }

    Course* search(string courseNumber) {
        int index = hash(courseNumber);
        Node* curr = table[index];
        while (curr) {
            if (curr->course.courseNumber == courseNumber) return &curr->course;
            curr = curr->next;
        }
        return nullptr;
    }

    vector<Course> toVector() {
        vector<Course> list;
        for (int i = 0; i < SIZE; i++) {
            Node* curr = table[i];
            while (curr) {
                list.push_back(curr->course);
                curr = curr->next;
            }
        }
        return list;
    }
};

// Load the file
void LoadCourses(string fileName, HashTable* ht) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Could not open " << fileName << endl;
        return;
    }
    string line;
    int count = 0;
    while (getline(file, line)) {
        //cleaning logic to make sure files load correctly (assuming the name was typed in correctly)
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());

        if (line.empty()) continue;

        stringstream ss(line);
        string token;
        vector<string> row;
        
        while (getline(ss, token, ',')) {
            if (!token.empty()) row.push_back(token);
        }
        
        if (row.size() >= 2) {
            Course c;
            c.courseNumber = row[0];
            c.courseTitle = row[1];
            for (size_t i = 2; i < row.size(); i++) {
                c.prerequisites.push_back(row[i]);
            }
            ht->insert(c);
            count++;
        }
    }
    file.close();
    cout << "Data loaded successfully. (" << count << " courses)" << endl;
}

//Main menu
int main() {
    HashTable* courseTable = new HashTable();
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                //This gave me SO MANY errors, mainly because it would not read the CSV files properly when the file name had whitespaces " ".
                string fileName;
                cout << "Enter the file name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, fileName);
                LoadCourses(fileName, courseTable);
                break;
            }
            case 2: {
                vector<Course> courses = courseTable->toVector();
                if (courses.empty()) {
                    cout << "Error: Please load data first." << endl;
                    break;
                }
                sort(courses.begin(), courses.end(), [](Course a, Course b) {
                    return a.courseNumber < b.courseNumber;
                });
                cout << "\nHere is a sample schedule:" << endl;
                for (auto& c : courses) cout << c.courseNumber << ", " << c.courseTitle << endl;
                break;
            }
            case 3: {
                string searchID;
                cout << "What course do you want to know about? ";
                cin >> searchID;
                transform(searchID.begin(), searchID.end(), searchID.begin(), ::toupper);
                
                Course* c = courseTable->search(searchID);
                if (c) {
                    cout << c->courseNumber << ", " << c->courseTitle << "\nPrerequisites: ";
                    if (c->prerequisites.empty()) cout << "None";
                    else {
                        for (size_t i = 0; i < c->prerequisites.size(); i++) {
                            cout << c->prerequisites[i] << (i == c->prerequisites.size() - 1 ? "" : ", ");
                        }
                    }
                    cout << endl;
                } else cout << "Course not found." << endl;
                break;
            }
            case 9:
                cout << "Thank you for using the course planner!" << endl;
                break;
            default:
                cout << choice << " is not a valid option." << endl;
                break;
        }
    }

    delete courseTable;
    return 0;
}