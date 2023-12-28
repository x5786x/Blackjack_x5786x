#define _CRT_SECURE_NO_WARNINGS
#include "user_authentication.h"
#include <stdio.h>
#include <string.h>

int loadUsersFromFile(User* users, int max_users)
{
	FILE* usersdata = fopen("usersdata.txt", "r");
	if (usersdata == NULL) {
		printf("無法存取使用者資料\n");
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
		printf("無法寫入使用者資料\n");
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
		printf("請輸入使用者名稱: "); scanf(" %s", user->username);
		printf("請輸入密碼: "); scanf(" %s", user->password);
		user -> money = 1000;
		if (saveUsersToFile(*user))
			break;
		printf("錯誤，請重試\n");
	}while (1);
	printf("註冊成功!\n");

}

int loginUser(User *user, int max_users)
{
	User usersdata[50];
	loadUsersFromFile(&usersdata, max_users);
	printf("請輸入使用者名稱: ");
	scanf(" %s", user->username);
	printf("請輸入密碼: ");
	scanf(" %s", user->password);
	for (int i = 0; i < 50; i++)
	{
		if ( (strcmp(user->username, usersdata[i].username) == 0) && (strcmp(user->password, usersdata[i].password) == 0))
		{
			printf("登入成功!\n");
			user->money = usersdata[i].money;
			return 1;
		}
	}
	printf("登入失敗!\n");
	return 0;
}