#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_MARKING ":)" // Ascii happy face (ASCII values 9786, 9787) ☺, ☻
#define DEFAULT_FILENAME "default.txt"

// Function for string manipulation
void string_manipulation(char *str) {
    if (str == NULL) {
        str = "default string";
    }
    printf("String: %s\n", str);
}

// Function for keyboard input
void keyboard_input() {
    char input;
    printf("Enter a character: ");
    scanf("%c", &input);
    printf("You entered: %c\n", input);
}

// Function for caret browsing via mouse and controller
void caret_browsing() {
    printf("Caret browsing is active.\n");
}

// Function for file handling with default filename
void file_handling(char *filename) {
    if (filename == NULL) {
        filename = DEFAULT_FILENAME;
    }
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }
    printf("Opened file: %s\n", filename);
    fclose(file);
}

// Function for system calls
void system_calls() {
    printf("System calls are being executed.\n");
}

// Function for marking by specific user with default marking
void mark_by_user(char *username, char *marking) {
    if (username == NULL) {
        username = "default user";
    }
    if (marking == NULL) {
        marking = DEFAULT_MARKING;
    }
    printf("User '%s' marked with '%s'\n", username, marking);
}

int main() {
    // Test the utility functions
    string_manipulation(NULL);
    keyboard_input();
    caret_browsing();
    file_handling(NULL);
    system_calls();
    mark_by_user(NULL, NULL);

    return 0;
}
