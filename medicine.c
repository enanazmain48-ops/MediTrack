#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "medicine.h"

// Helper function to generate filename based on username
void get_medicine_filename(const char *username, char *filename) {
    sprintf(filename, "%s_meds.csv", username);
}

// Add a new medicine entry
void add_medicine(const char *username) {
    char filename[100];
    get_medicine_filename(username, filename);

    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    Medicine med;
    printf("Enter medicine name: ");
    fgets(med.name, sizeof(med.name), stdin);
    med.name[strcspn(med.name, "\n")] = '\0';

    printf("Enter dosage: ");
    fgets(med.dosage, sizeof(med.dosage), stdin);
    med.dosage[strcspn(med.dosage, "\n")] = '\0';

    printf("Enter time: ");
    fgets(med.time, sizeof(med.time), stdin);
    med.time[strcspn(med.time, "\n")] = '\0';

    fprintf(fp, "%s,%s,%s\n", med.name, med.dosage, med.time);
    fclose(fp);

    printf("Medicine entry saved successfully.\n");
}

// View all medicine entries in table format
void view_medicine_history(const char *username) {
    char filename[100];
    get_medicine_filename(username, filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("No medicine history found for %s.\n", username);
        return;
    }

    char line[100];
    int count = 0;

    printf("\nMedicine History for %s:\n", username);
    printf("--------------------------------------------------\n");
    printf("| %-3s | %-20s | %-8s | %-10s |\n", "No", "Medicine Name", "Dosage", "Time");
    printf("--------------------------------------------------\n");

    while (fgets(line, sizeof(line), fp)) {
        char name[50], dosage[20], time[20];
        if (sscanf(line, "%49[^,],%19[^,],%19[^\n]", name, dosage, time) == 3) {
            printf("| %-3d | %-20s | %-8s | %-10s |\n", ++count, name, dosage, time);
        }
    }

    printf("--------------------------------------------------\n");

    if (count == 0) {
        printf("No entries found.\n");
    }

    fclose(fp);
}

// Edit a specific medicine entry
void edit_medicine_entry(const char *username) {
    char filename[100];
    get_medicine_filename(username, filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("No medicine history found.\n");
        return;
    }

    char lines[100][100];
    int count = 0;

    while (fgets(lines[count], sizeof(lines[count]), fp)) {
        printf("%d. %s", count + 1, lines[count]);
        count++;
    }
    fclose(fp);

    int line_num;
    printf("Enter line number to edit: ");
    scanf("%d", &line_num);
    getchar(); // clear newline

    if (line_num < 1 || line_num > count) {
        printf("Invalid line number.\n");
        return;
    }

    Medicine med;
    printf("Enter new medicine name: ");
    fgets(med.name, sizeof(med.name), stdin);
    med.name[strcspn(med.name, "\n")] = '\0';

    printf("Enter new dosage: ");
    fgets(med.dosage, sizeof(med.dosage), stdin);
    med.dosage[strcspn(med.dosage, "\n")] = '\0';

    printf("Enter new time: ");
    fgets(med.time, sizeof(med.time), stdin);
    med.time[strcspn(med.time, "\n")] = '\0';

    sprintf(lines[line_num - 1], "%s,%s,%s\n", med.name, med.dosage, med.time);

    fp = fopen(filename, "w");
    for (int i = 0; i < count; i++) {
        fputs(lines[i], fp);
    }
    fclose(fp);

    printf("Entry updated successfully.\n");
}

// Delete a specific medicine entry
void delete_medicine_entry(const char *username) {
    char filename[100];
    get_medicine_filename(username, filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("No medicine history found.\n");
        return;
    }

    char lines[100][100];
    int count = 0;

    while (fgets(lines[count], sizeof(lines[count]), fp)) {
        printf("%d. %s", count + 1, lines[count]);
        count++;
    }
    fclose(fp);

    int line_num;
    printf("Enter line number to delete: ");
    scanf("%d", &line_num);
    getchar(); // clear newline

    if (line_num < 1 || line_num > count) {
        printf("Invalid line number.\n");
        return;
    }

    fp = fopen(filename, "w");
    for (int i = 0; i < count; i++) {
        if (i != line_num - 1) {
            fputs(lines[i], fp);
        }
    }
    fclose(fp);

    printf("Entry deleted successfully.\n");
}