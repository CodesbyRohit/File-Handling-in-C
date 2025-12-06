#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 512

static void create_and_write(const char *filename);
static void read_file(const char *filename);
static void append_to_file(const char *filename);

int main(void) {
    const char *filename = "data.txt";
    int choice = 0;

    while (1) {
        printf("\n========== FILE HANDLING MENU ==========\n");
        printf("1. Create & Write to File\n");
        printf("2. Read File\n");
        printf("3. Append to File\n");
        printf("4. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input. Exiting.\n");
            return EXIT_FAILURE;
        }

        getchar();  

        switch (choice) {
            case 1:
                create_and_write(filename);
                break;
            case 2:
                read_file(filename);
                break;
            case 3:
                append_to_file(filename);
                break;
            case 4:
                printf("Program terminated.\n");
                return EXIT_SUCCESS;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

static void create_and_write(const char *filename) {
    FILE *fp = fopen(filename, "w");

    if (fp == NULL) {
        perror("Error creating file");
        return;
    }

    char buffer[BUFFER_SIZE];
    printf("\nEnter text to WRITE (max %d chars):\n> ", BUFFER_SIZE - 1);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Input error.\n");
        fclose(fp);
        return;
    }

    size_t written = fwrite(buffer, sizeof(char), strlen(buffer), fp);
    if (written != strlen(buffer)) {
        fprintf(stderr, "Write error.\n");
    } else {
        printf("✔ Data successfully written to '%s'.\n", filename);
    }

    fclose(fp);
}

static void read_file(const char *filename) {
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        perror("Error opening file for reading");
        return;
    }

    printf("\n========== FILE CONTENT ==========\n");

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, stdout);
    }

    printf("==================================\n");

    fclose(fp);
}

static void append_to_file(const char *filename) {
    FILE *fp = fopen(filename, "a");

    if (fp == NULL) {
        perror("Error opening file for appending");
        return;
    }

    char buffer[BUFFER_SIZE];
    printf("\nEnter text to APPEND (max %d chars):\n> ", BUFFER_SIZE - 1);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Input error.\n");
        fclose(fp);
        return;
    }

    size_t written = fwrite(buffer, sizeof(char), strlen(buffer), fp);
    if (written != strlen(buffer)) {
        fprintf(stderr, "Append error.\n");
    } else {
        printf("✔ Data successfully appended to '%s'.\n", filename);
    }

    fclose(fp);
}
