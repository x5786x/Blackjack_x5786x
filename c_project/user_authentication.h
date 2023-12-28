#ifndef USER_AUTHENTICATION_H
#define USER_AUTHENTICATION_H

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
	char username[MAX_USERNAME_LENGTH];
	char password[MAX_PASSWORD_LENGTH];
	int money;
}User;

int saveUsersToFile(User*);
int loadUsersFromFile(User);
void regsiterUser(User*);
int loginUser(User*, int);

#endif