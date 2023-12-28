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
		flag = 0; // 存放登入是否成功的值 回傳0(失敗) 1(成功)

		// 登入&註冊階段
		while (flag != 1)
		{
			printf("請問要登入還是註冊(1為登入、2為註冊、0為退出): ");
			scanf(" %c", &choice);
			// 判斷使用者選擇註冊、登入、退出
			switch (choice)
			{
				case '1':
					if (loginUser(&user, MAX_USERS)) // 登入
						flag = 1;
					else
						flag = 0;
					break;
				case '2':
					regsiterUser(&user); // 註冊
					flag = 1;
					break;
				case '0':
					printf("...程式結束...\n");
					Sleep(3000);
					return 0;
			}
		}

		// 顯示玩家訊息
		printf("玩家名稱 %s\n", user.username);
		printf("玩家剩餘金錢: %d\n", user.money);

		// 顯示規則
		printf("規則:\n點數\n2~10的牌值以點數計算\nJ、Q、K的牌值以10點計算\nAce的牌值可記為11點或者1點\n點數合計超過21點時，Ace自動以1點計算\n玩家手牌最多可補至5張\n點數超過21點時則爆牌並輸掉該次比賽\n");
		printf("流程\n莊家洗牌\n莊家發一張牌給玩家\n莊家發一張牌給自己\n莊家再各派發一張牌給每位玩家\n莊家再派發一張牌給自己\n莊家詢問玩家是否加牌\n莊家不足17點則需補牌至超過17點\n");
		printf("是否開始遊戲? (1為開始、0為上一步): ");

		scanf(" %c", &choice);
		if (choice == '0')
			continue;
		system("cls");

		// 遊戲開始
		while (1)
		{
			// 初始化排組、玩家及洗牌
			initializeDeck(deck);
			shuffleDeck(deck);
			initializePlayer(&player); initializePlayer(&banker);

			// 下注階段
			if (user.money <= 0) // 金錢不足時跳出
			{
				printf("你沒錢\n");
				Sleep(2000);
				break;
			}
			playerBet(&player, user);	

			// 第一回合發牌
			for (int i = 0; i < 2; i++)
			{
				deal(&player, &deck);
				deal(&banker, &deck);
			}

			// 印出雙方目前持有的牌
			printf("您目前的牌有: "); printBasicInfo(player, 1);
			printf("莊家目前的牌有: "); printBasicInfo(banker, 0);
	
			// 玩家回合
			while (checkHandCardsNumber(player))
			{
				// 每次檢查點數
				playerResult = checkPoint(&player);
				if (playerResult >= 1) // 如果爆牌或等於21點則玩家回合結束
					break;

				printf("\n拿牌(1)停牌(0): ");
				scanf(" %c", &choice);
				// 判斷是否正確輸入
				if (choice != '1' && choice != '0')
				{
					printf("輸入錯誤,請重新輸入\n");
					continue;
				}
				else
				{
					// 如果為1則拿牌,並印出目前有的牌
					if (choice == '1')
					{
						deal(&player, &deck);
						printf("您目前的牌有: "); printBasicInfo(player, 1);
					}
					// 如果為0則玩家回合結束
					else
						break;
				}
			}
			Sleep(1000);
			// 莊家回合
			while (1)
			{
				// 若點數>=17則莊家回合結束
				checkPoint(&banker);
				if (banker.point >= 17)
					break;
				
				// 若點數<17補牌到>=17
				deal(&banker, &deck);
				printf("莊家目前的牌有: "); printBasicInfo(banker, 1);
				Sleep(1000);
			}
			bankerResult = checkPoint(&banker); // 檢查莊家點數

			system("cls");
			printf("莊家目前的牌有: "); printBasicInfo(banker, 1);
			printf("您目前的牌有: "); printBasicInfo(player, 1);
			
			// 處理爆牌以及等於21的情形
			gameResult = bust_and_blackjack(playerResult, bankerResult);
			// 比較雙方點數
			if (gameResult == 0)
				gameResult = compare(&player, &banker);

			Sleep(2000);
			switch (gameResult)
			{
				case 0:
					printf("點數相同!\n");
					break;
				case 1:
					printf("你輸了!\n");
					user.money -= player.bet;
					break;
				case 2:
					printf("你贏了!\n");
					user.money += player.bet;
					break;
			}
			
			saveUsersToFile(&user);
			printf("目前剩餘金錢為%d\n", user.money);
			Sleep(2000);

			// 詢問使用者是否繼續遊玩
			while (1)
			{
				printf("要繼續嗎? y(繼續) n(退出): "); scanf(" %c", &choice);
				if (choice != 'y' && choice != 'n')
				{
					printf("輸入錯誤,請重試\n");
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