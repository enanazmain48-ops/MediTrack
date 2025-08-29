#ifndef MEDICINE_H
#define MEDICINE_H

// Structure to store medicine details
typedef struct {
    char name[50];    
    char dosage[20];  
    char time[20];     
} Medicine;


void add_medicine(const char *username);
void view_medicine_history(const char *username);
void edit_medicine_entry(const char *username);
void delete_medicine_entry(const char *username);

#endif