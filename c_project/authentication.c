#define _CRT_SECURE_NO_WARNINGS
#include "user_authentication.h"
#include <stdio.h>
#include <string.h>

int loadUsersFromFile(User* users, int max_users)
{
	FILE* usersdata = fopen("usersdata.txt", "r");
	if (usersdata == NULL) {
		printf("�L�k�s���ϥΪ̸��\n");
		return 0;
	}

	int num_users = 0;
	while (fscanf(usersdata, "%s %s %d", (users + num_users) -> username, (users + num_users) -> password, &((users + num_users)->money)) == 3)
	{
		num_users++;
		if (num_users > max_users)
			break;
	}
	fclose(usersdata);
	return 1;
}

int saveUsersToFile(User user)
{
	FILE* usersdata = fopen("usersdata.txt", "w+");
	if (usersdata == NULL) {
		printf("�L�k�g�J�ϥΪ̸��\n");
		return 0;
	}
	fprintf(usersdata, "%s %s %d", user.username, user.password, user.money);
	fclose(usersdata);
	return 1;
}

void regsiterUser(User *user)
{
	do {
		rewind(stdin);
		printf("�п�J�ϥΪ̦W��: "); scanf(" %s", user->username);
		printf("�п�J�K�X: "); scanf(" %s", user->password);
		user -> money = 1000;
		if (saveUsersToFile(*user))
			break;
		printf("���~�A�Э���\n");
	}while (1);
	printf("���U���\!\n");

}

int loginUser(User *user, int max_users)
{
	User usersdata[50];
	loadUsersFromFile(&usersdata, max_users);
	printf("�п�J�ϥΪ̦W��: ");
	scanf(" %s", user->username);
	printf("�п�J�K�X: ");
	scanf(" %s", user->password);
	for (int i = 0; i < 50; i++)
	{
		if ( (strcmp(user->username, usersdata[i].username) == 0) && (strcmp(user->password, usersdata[i].password) == 0))
		{
			printf("�n�J���\!\n");
			user->money = usersdata[i].money;
			return 1;
		}
	}
	printf("�n�J����!\n");
	return 0;
}