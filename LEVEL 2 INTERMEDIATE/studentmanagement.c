#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define FILENAME "students.dat" // Ensure this is a valid path

typedef struct {
    char name[50];
    int id;
    float grades[5]; // Assuming each student has 5 grades
} Student;

void addStudent(Student *students, int *count);
void displayStudents(Student *students, int count);
void deleteStudent(Student *students, int *count);
void saveToFile(Student *students, int count);
void loadFromFile(Student *students, int *count);
void displayMenu();

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;

    // Load existing records from file
    loadFromFile(students, &count);
    
    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addStudent(students, &count);
                break;
            case 2:
                displayStudents(students, count);
                break;
            case 3:
                deleteStudent(students, &count);
                break;
            case 4:
                saveToFile(students, count);
                break;
            case 5:
                loadFromFile(students, &count);
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
    
    return 0;
}

void displayMenu() {
    printf("\n--- Student Management System ---\n");
    printf("1. Add Student\n");
    printf("2. Display Students\n");
    printf("3. Delete Student\n");
    printf("4. Save to File\n");
    printf("5. Load from File\n");
    printf("0. Exit\n");
}

void addStudent(Student *students, int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students. Maximum limit reached.\n");
        return;
    }
    
    Student newStudent;
    printf("Enter student name: ");
    getchar(); // Clear the newline character from the input buffer
    fgets(newStudent.name, sizeof(newStudent.name), stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0; // Remove newline character

    printf("Enter student ID: ");
    scanf("%d", &newStudent.id);
    printf("Enter 5 grades: ");
    for (int i = 0; i < 5; i++) {
        scanf("%f", &newStudent.grades[i]);
    }
    
    students[*count] = newStudent;
    (*count)++;
    printf("Student added successfully. Total records: %d\n", *count);
}

void displayStudents(Student *students, int count) {
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }
    
    printf("\n--- Student Records ---\n");
    for (int i = 0; i < count; i++) {
        printf("Name: %s, ID: %d, Grades: ", students[i].name, students[i].id);
        for (int j = 0; j < 5; j++) {
            printf("%.2f ", students[i].grades[j]);
        }
        printf("\n");
    }
}

void deleteStudent(Student *students, int *count) {
    if (*count == 0) {
        printf("No students to delete.\n");
        return;
    }
    
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);
    
    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            printf("Student deleted successfully. Total records: %d\n", *count);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

void saveToFile(Student *students, int count ) {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fwrite(students, sizeof(Student), count, file);
    fclose(file);
    printf("Records saved successfully.\n");
}

void loadFromFile(Student *students, int *count) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening file for reading. Starting with empty records.\n");
        return;
    }
    *count = fread(students, sizeof(Student), MAX_STUDENTS, file);
    fclose(file);
    printf("Records loaded successfully. Total records: %d\n", *count);
}
