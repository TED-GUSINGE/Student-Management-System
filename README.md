# Student Management System

A console-based Student Management System written in C++. It lets the user manage student records through a simple menu.

## Features

- Add a student record.
- Display all saved student records.
- Search for a student using their roll number.
- Update a student's details.
- Delete a student record.
- Calculate a grade automatically from the student's marks.
- Save records to `students.txt` and load them when the program starts.

## C++ concepts used

- **Classes and objects:** The program uses the `Student` and `StudentManagement` classes.
- **STL vector:** `vector<Student>` stores the student records in memory.
- **File handling:** `ofstream` writes records to `students.txt`, while `ifstream` reads them when the application starts.
- **Loops and conditions:** Used for menu repetition, searching records and calculating grades.
- **Member functions:** Functions such as `addStudent()`, `displayStudents()`, `searchStudent()`, `updateStudent()` and `deleteStudent()` organize the program's operations.

## Grade calculation

| Marks | Grade |
|---|---|
| 90 and above | A+ |
| 75–89 | A |
| 60–74 | B |
| 40–59 | C |
| Below 40 | Fail |

## Requirements

- A C++ compiler such as GCC or Clang.
- C++17 support is recommended.

## Compile and run

Open a terminal in the project folder and run:

```bash
g++ -std=c++17 main.cpp -o student
./student
```

Compile again whenever you make changes to `main.cpp`. If you have not changed the source code and have already compiled it, you can run the existing executable with `./student`.

## Data storage

The program stores records in a file named `students.txt`. Each student's information is written on separate lines in this order:

1. Roll number
2. Name
3. Course
4. Marks

The file is loaded automatically when a `StudentManagement` object is created. The file is updated after adding, updating or deleting a student.

## Project structure

- `main.cpp` — complete C++ source code.
- `students.txt` — data file created by the program when records are saved.
- `docs/class-diagram.mmd` — class diagram for the current source code.
- `docs/sample-output.md` — example of the program's console interaction.

## Testing

The following operations can be tested from the menu:

1. Add a student and enter their details.
2. Display the student records.
3. Search using an existing and a non-existing roll number.
4. Update an existing student's details.
5. Delete an existing student.
6. Exit, restart the program and check that saved records are loaded.

## Current scope

This version demonstrates classes, objects, a private STL vector, basic file input/output and menu-driven record management. It does not currently implement inheritance, polymorphism, exception handling or comprehensive input validation.
