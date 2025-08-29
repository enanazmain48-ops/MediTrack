#ifndef USER_H
#define USER_H

typedef struct {
    char username[50];
    char password[50];
} User;

void get_user_input(User *u);
int validate_user(const User *u);
void save_user_to_csv(const User *u);

#endif