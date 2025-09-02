#include <stdio.h>
#include <string.h>
#include "auth.h"

int authenticate_user(const char *username, const char *password) {
    FILE *fp = fopen("credentials.csv", "r");
    if (fp == NULL) {
        printf("Error opening credentials file.\n");
        return 0;
    }

    char line[100];
    char stored_username[50], stored_password[50];

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%49[^,],%49[^\n]", stored_username, stored_password);
        if (strcmp(username, stored_username) == 0 &&
            strcmp(password, stored_password) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}