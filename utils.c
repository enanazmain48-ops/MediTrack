#include <stdio.h>
#include <string.h>
#include "User.h"
#include "auth.h"
#include "medicine.h"
#include "utils.h"

void run_medicine_tracker() {
    char username[50], password[50];
    int choice;
    

    while (1) {
        printf("===        MediTrack        ===\n");
        printf("-------------------------------\n");
        printf("=== Medicine Tracker System ===\n");
        printf("-------------------------------\n");
        printf("\n1. Sign Up\n2. Log In\n3. Exit\nChoose an option: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // clear buffer
            continue;
        }
        while (getchar() != '\n'); // clear buffer after valid input

        if (choice == 1) {
            User newUser;
            get_user_input(&newUser);

            if (validate_user(&newUser)) {
                save_user_to_csv(&newUser);
                printf("Signup successful.\n");
            } else {
                printf("Invalid input. Try again.\n");
            }

        } else if (choice == 2) {
            printf("Username: ");
            fgets(username, sizeof(username), stdin);
            username[strcspn(username, "\n")] = '\0';

            printf("Password: ");
            fgets(password, sizeof(password), stdin);
            password[strcspn(password, "\n")] = '\0';

            if (authenticate_user(username, password)) {
                printf("Login successful. Welcome, %s!\n", username);

                int userChoice;
                do {
                    printf("\n--- Medicine Menu ---\n");
                    printf("1. Add Medicine\n");
                    printf("2. View History\n");
                    printf("3. Edit Entry\n");
                    printf("4. Delete Entry\n");
                    printf("5. Logout\n");
                    printf("Choose an option: ");
                    if (scanf("%d", &userChoice) != 1) {
                        printf("Invalid input. Please enter a number.\n");
                        while (getchar() != '\n'); // clear buffer
                        continue;
                    }
                    while (getchar() != '\n'); // clear buffer

                    switch (userChoice) {
                        case 1: add_medicine(username); break;
                        case 2: view_medicine_history(username); break;
                        case 3: edit_medicine_entry(username); break;
                        case 4: delete_medicine_entry(username); break;
                        case 5: printf("Logged out.\n"); break;
                        default: printf("Invalid option.\n");
                    }
                } while (userChoice != 5);

            } else {
                printf("Login failed. Invalid credentials.\n");
            }

        } else if (choice == 3) {
            printf("Exiting program. Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }
}
