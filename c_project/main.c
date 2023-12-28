#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "game_head.h"

int main()
{
	User user;
	Player player, banker;
	Card deck[NSUFTS * NRANKS];
	char flag, choice;
	int playerResult, bankerResult, total, gameResult;

	srand((unsigned)time(NULL));
	while (1)
	{
		flag = 0; // �s��n�J�O�_���\���� �^��0(����) 1(���\)

		// �n�J&���U���q
		while (flag != 1)
		{
			printf("�аݭn�n�J�٬O���U(1���n�J�B2�����U�B0���h�X): ");
			scanf(" %c", &choice);
			// �P�_�ϥΪ̿�ܵ��U�B�n�J�B�h�X
			switch (choice)
			{
				case '1':
					if (loginUser(&user, MAX_USERS)) // �n�J
						flag = 1;
					else
						flag = 0;
					break;
				case '2':
					regsiterUser(&user); // ���U
					flag = 1;
					break;
				case '0':
					printf("...�{������...\n");
					Sleep(3000);
					return 0;
			}
		}

		// ��ܪ��a�T��
		printf("���a�W�� %s\n", user.username);
		printf("���a�Ѿl����: %d\n", user.money);

		// ��ܳW�h
		printf("�W�h:\n�I��\n2~10���P�ȥH�I�ƭp��\nJ�BQ�BK���P�ȥH10�I�p��\nAce���P�ȥi�O��11�I�Ϊ�1�I\n�I�ƦX�p�W�L21�I�ɡAAce�۰ʥH1�I�p��\n���a��P�̦h�i�ɦ�5�i\n�I�ƶW�L21�I�ɫh�z�P�ÿ鱼�Ӧ�����\n");
		printf("�y�{\n���a�~�P\n���a�o�@�i�P�����a\n���a�o�@�i�P���ۤv\n���a�A�U���o�@�i�P���C�쪱�a\n���a�A���o�@�i�P���ۤv\n���a�߰ݪ��a�O�_�[�P\n���a����17�I�h�ݸɵP�ܶW�L17�I\n");
		printf("�O�_�}�l�C��? (1���}�l�B0���W�@�B): ");

		scanf(" %c", &choice);
		if (choice == '0')
			continue;
		system("cls");

		// �C���}�l
		while (1)
		{
			// ��l�ƱƲաB���a�ά~�P
			initializeDeck(deck);
			shuffleDeck(deck);
			initializePlayer(&player); initializePlayer(&banker);

			// �U�`���q
			if (user.money <= 0) // ���������ɸ��X
			{
				printf("�A�S��\n");
				Sleep(2000);
				break;
			}
			playerBet(&player, user);	

			// �Ĥ@�^�X�o�P
			for (int i = 0; i < 2; i++)
			{
				deal(&player, &deck);
				deal(&banker, &deck);
			}

			// �L�X����ثe�������P
			printf("�z�ثe���P��: "); printBasicInfo(player, 1);
			printf("���a�ثe���P��: "); printBasicInfo(banker, 0);
	
			// ���a�^�X
			while (checkHandCardsNumber(player))
			{
				// �C���ˬd�I��
				playerResult = checkPoint(&player);
				if (playerResult >= 1) // �p�G�z�P�ε���21�I�h���a�^�X����
					break;

				printf("\n���P(1)���P(0): ");
				scanf(" %c", &choice);
				// �P�_�O�_���T��J
				if (choice != '1' && choice != '0')
				{
					printf("��J���~,�Э��s��J\n");
					continue;
				}
				else
				{
					// �p�G��1�h���P,�æL�X�ثe�����P
					if (choice == '1')
					{
						deal(&player, &deck);
						printf("�z�ثe���P��: "); printBasicInfo(player, 1);
					}
					// �p�G��0�h���a�^�X����
					else
						break;
				}
			}
			Sleep(1000);
			// ���a�^�X
			while (1)
			{
				// �Y�I��>=17�h���a�^�X����
				checkPoint(&banker);
				if (banker.point >= 17)
					break;
				
				// �Y�I��<17�ɵP��>=17
				deal(&banker, &deck);
				printf("���a�ثe���P��: "); printBasicInfo(banker, 1);
				Sleep(1000);
			}
			bankerResult = checkPoint(&banker); // �ˬd���a�I��

			system("cls");
			printf("���a�ثe���P��: "); printBasicInfo(banker, 1);
			printf("�z�ثe���P��: "); printBasicInfo(player, 1);
			
			// �B�z�z�P�H�ε���21������
			gameResult = bust_and_blackjack(playerResult, bankerResult);
			// ��������I��
			if (gameResult == 0)
				gameResult = compare(&player, &banker);

			Sleep(2000);
			switch (gameResult)
			{
				case 0:
					printf("�I�ƬۦP!\n");
					break;
				case 1:
					printf("�A��F!\n");
					user.money -= player.bet;
					break;
				case 2:
					printf("�AĹ�F!\n");
					user.money += player.bet;
					break;
			}
			
			saveUsersToFile(&user);
			printf("�ثe�Ѿl������%d\n", user.money);
			Sleep(2000);

			// �߰ݨϥΪ̬O�_�~��C��
			while (1)
			{
				printf("�n�~���? y(�~��) n(�h�X): "); scanf(" %c", &choice);
				if (choice != 'y' && choice != 'n')
				{
					printf("��J���~,�Э���\n");
					Sleep(1000);
					system("cls");
				}	
				else
					break;
			}
			if (choice == 'n')
				break;
			system("cls");
		}
	}
}