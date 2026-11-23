#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

// Input helper declarations used by the classes below.
int readInteger(const string& message);
float readMarks(const string& message);
string readText(const string& message);

// Base class: common details of a person.
class Person {
private:
    int rollNo;
    string name;

public:
    Person(int roll, string studentName) : rollNo(roll), name(studentName) {}

    int getRollNo() const { return rollNo; }
    string getName() const { return name; }
    void setName(string newName) { name = newName; }

    virtual void display() const = 0;
    virtual ~Person() = default;
};

// Student inherits common details from Person.
class Student : public Person {
private:
    string course;
    float marks;

public:
    Student(int roll, string name, string studentCourse, float studentMarks)
        : Person(roll, name), course(studentCourse), marks(studentMarks) {}

    string getCourse() const { return course; }
    float getMarks() const { return marks; }

    void updateDetails(string newName, string newCourse, float newMarks) {
        setName(newName);
        course = newCourse;
        marks = newMarks;
    }

    string getGrade() const {
        if (marks >= 90) return "A+";
        if (marks >= 75) return "A";
        if (marks >= 60) return "B";
        if (marks >= 40) return "C";
        return "Fail";
    }

    void display() const override {
        cout << "\nRoll Number: " << getRollNo()
             << "\nName: " << getName()
             << "\nCourse: " << course
             << "\nMarks: " << marks
             << "\nGrade: " << getGrade()
             << "\n--------------------------\n";
    }
};

class StudentManagement {
private:
    vector<Student> students; // STL vector stores student records.

    Student& findStudent(int roll) {
        for (Student& student : students) {
            if (student.getRollNo() == roll)
                return student;
        }
        throw runtime_error("Student not found.");
    }

    void saveToFile() const {
        ofstream file("students.txt");
        if (!file)
            throw runtime_error("Could not open students.txt for saving.");

        for (const Student& student : students) {
            file << student.getRollNo() << '|'
                 << student.getName() << '|'
                 << student.getCourse() << '|'
                 << student.getMarks() << '\n';
        }
    }

    void loadFromFile() {
        ifstream file("students.txt");
        if (!file) return; // First run: no file exists yet.

        string line;
        while (getline(file, line)) {
            stringstream row(line);
            string rollText, name, course, marksText;

            getline(row, rollText, '|');
            getline(row, name, '|');
            getline(row, course, '|');
            getline(row, marksText, '|');

            try {
                students.emplace_back(stoi(rollText), name, course, stof(marksText));
            } catch (const exception&) {
                // Skip an incomplete or invalid record.
            }
        }
    }

public:
    StudentManagement() {
        loadFromFile();
    }

    void addStudent() {
        int roll = readInteger("Enter roll number: ");

        for (const Student& student : students) {
            if (student.getRollNo() == roll)
                throw runtime_error("That roll number already exists.");
        }

        string name = readText("Enter student name: ");
        string course = readText("Enter course: ");
        float marks = readMarks("Enter marks (0-100): ");

        students.emplace_back(roll, name, course, marks);
        saveToFile();
        cout << "Student added successfully.\n";
    }

    void displayStudents() const {
        if (students.empty()) {
            cout << "No student records found.\n";
            return;
        }

        for (const Student& student : students) {
            const Person* person = &student;
            person->display(); // Runtime polymorphism.
        }
    }

    void searchStudent() {
        int roll = readInteger("Enter roll number to search: ");
        findStudent(roll).display();
    }

    void updateStudent() {
        int roll = readInteger("Enter roll number to update: ");
        Student& student = findStudent(roll);

        string name = readText("Enter new name: ");
        string course = readText("Enter new course: ");
        float marks = readMarks("Enter new marks (0-100): ");

        student.updateDetails(name, course, marks);
        saveToFile();
        cout << "Student updated successfully.\n";
    }

    void deleteStudent() {
        int roll = readInteger("Enter roll number to delete: ");

        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->getRollNo() == roll) {
                students.erase(it);
                saveToFile();
                cout << "Student deleted successfully.\n";
                return;
            }
        }
        throw runtime_error("Student not found.");
    }
};

// Read input safely so letters are not accepted as numbers.
int readInteger(const string& message) {
    while (true) {
        cout << message;
        string line;
        getline(cin, line);
        stringstream input(line);
        int value;
        char extra;

        if (input >> value && !(input >> extra) && value > 0)
            return value;

        cout << "Please enter a valid positive whole number.\n";
    }
}

float readMarks(const string& message) {
    while (true) {
        cout << message;
        string line;
        getline(cin, line);
        stringstream input(line);
        float value;
        char extra;

        if (input >> value && !(input >> extra) && value >= 0 && value <= 100)
            return value;

        cout << "Marks must be between 0 and 100. Try again.\n";
    }
}

string readText(const string& message) {
    while (true) {
        cout << message;
        string value;
        getline(cin, value);
        if (!value.empty() && value.find('|') == string::npos)
            return value;

        cout << "Please enter text without the | character.\n";
    }
}

int main() {
    StudentManagement system;
    int choice = -1;

    do {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n"
             << "1. Add Student\n"
             << "2. Display Students\n"
             << "3. Search Student\n"
             << "4. Update Student\n"
             << "5. Delete Student\n"
             << "0. Save and Exit\n";

        // Menu allows zero as a valid choice, so read it separately.
        cout << "Enter your choice: ";
        string line;
        getline(cin, line);
        stringstream input(line);
        char extra;

        if (!(input >> choice) || (input >> extra)) {
            cout << "Please enter a valid menu number.\n";
            choice = -1;
            continue;
        }

        try {
            switch (choice) {
                case 1: system.addStudent(); break;
                case 2: system.displayStudents(); break;
                case 3: system.searchStudent(); break;
                case 4: system.updateStudent(); break;
                case 5: system.deleteStudent(); break;
                case 0:
                    cout << "Records saved. Goodbye!\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } catch (const exception& error) {
            cout << "Error: " << error.what() << '\n';
        }
    } while (choice != 0);

    return 0;
}
