# Student Management System

A beginner-friendly console application written in C++17. This project manages student records and demonstrates the concepts required for a C++ mini project.

## Features

- Add, display, search, update and delete student records.
- Calculate a grade automatically from marks.
- Prevent duplicate roll numbers.
- Validate roll numbers, menu choices and marks.
- Save records in `students.txt` and load them when the program starts.
- Show clear error messages when a record is not found or an operation is invalid.

## C++ concepts demonstrated

- **Classes and objects:** `Person`, `Student` and `StudentManagement`.
- **Encapsulation:** student data is private and accessed through member functions.
- **Inheritance:** `Student` inherits from the abstract `Person` class.
- **Runtime polymorphism:** `display()` is overridden and called through a `Person` pointer.
- **STL:** `vector<Student>` stores the records.
- **Exception handling:** `runtime_error` reports duplicate roll numbers, missing students and file errors.
- **File handling:** `ifstream` loads records and `ofstream` saves them.

## Requirements

- C++17 compiler (GCC or Clang).
- macOS, Linux or Windows terminal.

## Compile and run

On macOS or Linux:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o student
./student
```

On Windows with MinGW:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o student.exe
student.exe
```

Run the program from the project folder so it can find `students.txt`.

## Data file

The program creates `students.txt` when the first student is added. Each line stores:

```text
roll number|name|course|marks
```

Do not use the pipe character (`|`) in names or course names because it separates the fields.

## Suggested tests

1. Add a student with marks of 92 and check the A+ grade.
2. Display all students.
3. Search for an existing roll number.
4. Try adding the same roll number again.
5. Update a student's details.
6. Delete a student.
7. Search for a roll number that does not exist.
8. Exit and restart to confirm records are loaded from the file.
9. Enter invalid marks (for example, 120) and confirm the program asks again.

## Project structure

- `main.cpp` — source code.
- `students.txt` — student records, created by the program.
- `docs/class-diagram.mmd` — UML class diagram.
- `docs/sample-output.md` — illustrative console output.

Capture screenshots of your own program run for the practical submission.
