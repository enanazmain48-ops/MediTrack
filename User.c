#include <stdio.h>
#include <string.h>
#include "User.h"

void get_user_input(User *u) {
    printf("Enter username: ");
    fgets(u->username, sizeof(u->username), stdin);
    u->username[strcspn(u->username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(u->password, sizeof(u->password), stdin);
    u->password[strcspn(u->password, "\n")] = '\0';
}

int validate_user(const User *u) {
    if (strlen(u->username) < 3 || strlen(u->password) < 6) {
        printf("Username must be ≥ 3 chars, password ≥ 6 chars.\n");
        return 0;
    }
    return 1;
}

void save_user_to_csv(const User *u) {
    FILE *fp = fopen("credentials.csv", "a");
    if (fp != NULL) {
        fprintf(fp, "%s,%s\n", u->username, u->password);
        fclose(fp);
    }
}
