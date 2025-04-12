#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME 100
#define MAX_CONTENT 1024

// Function prototypes
void createFile();
void readFile();
void deleteFile();
void displayMenu();

int main() {
    int choice;

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character left by scanf

        switch (choice) {
            case 1:
                createFile();
                break;
            case 2:
                readFile();
                break;
            case 3:
                deleteFile();
                break;
            case 4:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

void displayMenu() {
    printf("\n--- Simple File System Simulation ---\n");
    printf("1. Create a file\n");
    printf("2. Read a file\n");
    printf("3. Delete a file\n");
    printf("4. Exit\n");
}

void createFile() {
    char filename[MAX_FILENAME];
    char content[MAX_CONTENT];

    printf("Enter the filename to create: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove newline character

    printf("Enter the content to write in the file: ");
    fgets(content, sizeof(content), stdin);
    content[strcspn(content, "\n")] = 0; // Remove newline character

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        return;
    }

    fprintf(file, "%s\n", content);
    fclose(file);
    printf("File '%s' created successfully.\n", filename);
}

void readFile() {
    char filename[MAX_FILENAME];
    char content[MAX_CONTENT];

    printf("Enter the filename to read: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove newline character

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error reading file");
        return;
    }

    printf("Contents of '%s':\n", filename);
    while (fgets(content, sizeof(content), file) != NULL) {
        printf("%s", content);
    }
    fclose(file);
}

void deleteFile() {
    char filename[MAX_FILENAME];

    printf("Enter the filename to delete: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove newline character

    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        perror("Error deleting file");
    }
}
