#ifndef GAME_HEAD_H
#define GAME_HEAD_H
#include "user_authentication.h"

#define MAX_USERS 50
#define NSUFTS 4
#define NRANKS 13
#define MAX_HAND_CARDS 5

extern int currentCardIndex;
extern const char* sufts[NSUFTS];
extern const char* ranks[NRANKS];

typedef struct
{
	int suitIndex;
	int rankIndex;
	int value;
}Card;

typedef struct
{
	Card hand[10];
	int numCard;
	int point;
	int bet;
}Player;


void initializeDeck(Card*); // 初始化牌組
void shuffleDeck(Card*); // 洗牌
void initializePlayer(Player*); // 每回合重製玩家數值
void playerBet(Player*); // 玩家下注
void deal(Player*, Card*); // 抽牌
int checkHandCardsNumber(Player); // 檢查手牌是否超過5張
void printBasicInfo(Player, int); // 印出目前玩家訊息
int checkPoint(Player*); // 檢查是否爆牌 回傳0(低於21)、1(爆牌)、3(等於21)
int compare(Player*, Player*); // 比較兩數 回傳0(相等)、1(輸)、2(贏)
int bust_and_blackjack(int, int); // 處理爆牌及21點 回傳0(沒問題)、1(輸)、2(贏)

#endif