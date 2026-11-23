#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    string course;
    float marks;

    void input() {
        cout << "Enter Roll Number: ";
        cin >> rollNo;

        cin.ignore();

        cout << "Enter Student Name: ";
        getline(cin, name);

        cout << "Enter Course: ";
        getline(cin, course);

        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() {
        cout << "\nRoll Number: " << rollNo;
        cout << "\nName: " << name;
        cout << "\nCourse: " << course;
        cout << "\nMarks: " << marks;
        cout << "\nGrade: " << getGrade();
        cout << "\n--------------------------\n";
    }

    string getGrade() {
        if (marks >= 90) return "A+";
        else if (marks >= 75) return "A";
        else if (marks >= 60) return "B";
        else if (marks >= 40) return "C";
        else return "Fail";
    }
};

class StudentManagement {
private:
    vector<Student> students;

    void saveToFile() {
        ofstream file("students.txt");

        for (auto &s : students) {
            file << s.rollNo << "\n";
            file << s.name << "\n";
            file << s.course << "\n";
            file << s.marks << "\n";
        }

        file.close();
    }

    void loadFromFile() {
        ifstream file("students.txt");
        Student s;

        while (file >> s.rollNo) {
            file.ignore();
            getline(file, s.name);
            getline(file, s.course);
            file >> s.marks;
            file.ignore();

            students.push_back(s);
        }

        file.close();
    }

public:
    StudentManagement() {
        loadFromFile();
    }

    void addStudent() {
        Student s;

        cout << "\n--- Add Student ---\n";
        s.input();

        students.push_back(s);
        saveToFile();

        cout << "\nStudent Added Successfully!\n";
    }

    void displayStudents() {
        cout << "\n--- Student Records ---\n";

        if (students.empty()) {
            cout << "No Student Records Found!\n";
            return;
        }

        for (auto &s : students) {
            s.display();
        }
    }

    void searchStudent() {
        int roll;
        cout << "\nEnter Roll Number to Search: ";
        cin >> roll;

        for (auto &s : students) {
            if (s.rollNo == roll) {
                cout << "\nStudent Found!\n";
                s.display();
                return;
            }
        }

        cout << "\nStudent Not Found!\n";
    }

    void updateStudent() {
        int roll;
        cout << "\nEnter Roll Number to Update: ";
        cin >> roll;

        for (auto &s : students) {
            if (s.rollNo == roll) {
                cout << "\nEnter New Details:\n";
                s.input();
                saveToFile();

                cout << "\nStudent Updated Successfully!\n";
                return;
            }
        }

        cout << "\nStudent Not Found!\n";
    }

    void deleteStudent() {
        int roll;
        cout << "\nEnter Roll Number to Delete: ";
        cin >> roll;

        for (int i = 0; i < students.size(); i++) {
            if (students[i].rollNo == roll) {
                students.erase(students.begin() + i);
                saveToFile();

                cout << "\nStudent Deleted Successfully!\n";
                return;
            }
        }

        cout << "\nStudent Not Found!\n";
    }

    void menu() {
        int choice;

        do {
            cout << "\n================================";
            cout << "\n   STUDENT MANAGEMENT SYSTEM";
            cout << "\n================================";
            cout << "\n1. Add Student";
            cout << "\n2. Display Students";
            cout << "\n3. Search Student";
            cout << "\n4. Update Student";
            cout << "\n5. Delete Student";
            cout << "\n6. Exit";
            cout << "\n================================";
            cout << "\nEnter Your Choice: ";

            cin >> choice;

            switch (choice) {
                case 1: addStudent(); break;
                case 2: displayStudents(); break;
                case 3: searchStudent(); break;
                case 4: updateStudent(); break;
                case 5: deleteStudent(); break;
                case 6: cout << "\nThank You!\n"; break;
                default: cout << "\nInvalid Choice!\n";
            }

        } while (choice != 6);
    }
};

int main() {
    StudentManagement system;
    system.menu();

    return 0;
}
