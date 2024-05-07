/*
*Edix is an open-source lightweight and simple text editor designed for quick and efficient editing tasks. 
*It provides essential editing features in a minimalistic interface, allowing users to focus on their work without distractions.
*Edix is designed to be fast and responsive, making it ideal for editing small to medium-sized text files.
*Edix is a command-line text editor that runs in the terminal, providing a familiar and efficient editing environment for users.
*Edix is written in C programming language, making it lightweight and efficient in terms of resource usage.
*Edix is open-source software released under the MIT license, allowing users to modify and distribute the code freely.
*Edix is designed to be easy to use, with intuitive keybindings and commands that are easy to remember and use.
*Edix is a versatile text editor that can be used for a wide range of editing tasks, from simple text manipulation to more complex editing operations.
*
*
*
* copyrigth @2024 by Tanmoy Ganguly
*/


#include <stdio.h>
#include <stdlib.h> // For dynamic memory allocation
#include <string.h>
#include <stddef.h>
void edit_line(char* buffer, int current_line) {
    char* line_start = buffer;
    char* line_end;

    // Find the start and end of the current line
    for (int i = 0; i < current_line; i++) {
        line_start = strchr(line_start, '\n');
        if (line_start == NULL) {
            printf("Invalid line number.\n");
            return;
        }
        line_start++; // Move to the next character after '\n'
    }

    line_end = strchr(line_start, '\n');
    if (line_end == NULL) {
        line_end = strchr(line_start, '\0'); // End of buffer if no '\n' found
    }

    // Read new line from user input
    printf("Enter new line: ");
    char new_line[1024];
    fgets(new_line, sizeof(new_line), stdin);

    // Calculate the length of the old line
    size_t old_line_length = line_end - line_start;

    // Calculate the length of the new line
    size_t new_line_length = strlen(new_line);

    // Calculate the difference in length between the new line and the old line
    ptrdiff_t length_difference = new_line_length - old_line_length;

    // Calculate the end of the buffer
    char* buffer_end = buffer + strlen(buffer);

    // Move the remaining part of the buffer to make space for the new line
    memmove(line_end + length_difference, line_end, buffer_end - line_end + 1);

    // Copy the new line into the buffer
    strncpy(line_start, new_line, new_line_length);
}


int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    // Determine file size
    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    fseek(f, 0, SEEK_SET);

    // Allocate memory dynamically
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        printf("Memory allocation failed.\n");
        fclose(f);
        return 1;
    }

    // Read file contents into buffer
    fread(buffer, 1, file_size, f);
    fclose(f);
    buffer[file_size] = '\0'; // Null-terminate the buffer

    printf("Contents:\n%s\n", buffer);

    int current_line;
    char line_input[1024];
    printf("Enter line number to edit: ");
    fgets(line_input, sizeof(line_input), stdin);
    if (sscanf(line_input, "%d", &current_line) != 1) {
        printf("Invalid input. Please enter a valid line number.\n");
        free(buffer);
        return 1;
    }

    edit_line(buffer, current_line);

    // Write modified buffer back to file
    f = fopen(argv[1], "w");
    if (f == NULL) {
        printf("Failed to open file for writing.\n");
        free(buffer);
        return 1;
    }
    fwrite(buffer, 1, strlen(buffer), f);
    fclose(f);

    free(buffer); // Free dynamically allocated memory
    return 0;
}


