#define _CRT_SECURE_NO_WARNINGS
#include "game_head.h"

int currentCardIndex = 0;
const char* sufts[NSUFTS] = { "方塊", "梅花", "紅心", "黑桃" };
const char* ranks[NRANKS] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };


void deal(Player* player, Card* deck)
{
	player->hand[player->numCard] = *(deck + currentCardIndex);
	player->numCard++;
	currentCardIndex++;
}

int checkHandCardsNumber(Player player)
{
	if (player.numCard < 5)
		return 1;
	else
		return 0;
}

void printBasicInfo(Player player, int isPlayer)
{
	int i = 0;
	// 玩家回合莊家第一張牌為暗牌不顯示
	if (isPlayer != 1)
	{
		i = 1;
		printf("? ");
	}

	for (; i < player.numCard; i++)
		printf("%s%s ", sufts[player.hand[i].suitIndex], ranks[player.hand[i].rankIndex]);
	printf("\n");
}

void initializeDeck(Card* deck)
{
	for (int i = 0; i < NSUFTS; i++)
	{
		for (int j = 0; j < NRANKS; j++)
		{
			deck[i * NRANKS + j].suitIndex = i;
			deck[i * NRANKS + j].rankIndex = j;
			if (j == 0)
				deck[i * NRANKS + j].value = 11;
			else if (j > 9)
				deck[i * NRANKS + j].value = 10;
			else
				deck[i * NRANKS + j].value = j + 1;
		}
	}
}

void shuffleDeck(Card* deck)
{
	Card temp;
	int cards = NSUFTS * NRANKS, n;
	for (int i = 0; i < cards; i++)
	{
		n = rand() % (cards - i) + i;
		temp = deck[i];
		deck[i] = deck[n];
		deck[n] = temp;
	}
}

void initializePlayer(Player* player)
{
	player->numCard = 0;
	player->point = 0;
	player->bet = 0;
}

void playerBet(Player* player, User user)
{
	while (1)
	{
		printf("請下注(目前持有金額為%d): ", user.money);
		scanf("%d", &(player->bet));
		// 輸入金額不符合則重新輸入
		if (player->bet > user.money || player->bet <= 0)
			printf("輸入金額錯誤,請重新輸入\n");
		else
			break;
	}
}

int checkPoint(Player* player)
{
	int count = 0;
	player->point = 0;
	// 計算目前點數
	for (int i = 0; i < player->numCard; i++)
	{
		if (player->hand[i].rankIndex == 0)
			count++;
		player->point += player->hand[i].value;
	}
	while (count)
	{
		// 若A為11時點數超過21,則A為1
		if (player->point > 21)
		{
			player->point -= 10;
			count--;
		}
		// 若點數沒超過21則退出檢查
		else
			break;
	}

	// 檢查是否爆牌
	if (player->point < 21)
		return 0;
	else if (player->point > 21)
		return 1;
	else
		return 3;
}

int compare(Player* player, Player* banker)
{
	if (player->point == banker->point)
		return 0;
	if (player->point < banker->point)
		return 1;
	return 2;
}

int bust_and_blackjack(int playerResult, int bankerResult)
{
	int total = bankerResult + playerResult;
	if (total >= 1)
	{
		if (playerResult == 1) // 玩家爆牌 玩家輸
			return 1;
		if (bankerResult == playerResult)
		{
			if (playerResult == 3) // 相等且玩家21點 玩家贏
				return 2;
			return 1; // 相等且皆為爆牌 玩家輸
		}
		if (playerResult == 3 || bankerResult == 1) // 玩家21點或莊家爆牌 玩家贏
			return 2;
	}
	return 0;
}