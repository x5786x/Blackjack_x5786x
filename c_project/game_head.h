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


void initializeDeck(Card*); // ��l�ƵP��
void shuffleDeck(Card*); // �~�P
void initializePlayer(Player*); // �C�^�X���s���a�ƭ�
void playerBet(Player*); // ���a�U�`
void deal(Player*, Card*); // ��P
int checkHandCardsNumber(Player); // �ˬd��P�O�_�W�L5�i
void printBasicInfo(Player, int); // �L�X�ثe���a�T��
int checkPoint(Player*); // �ˬd�O�_�z�P �^��0(�C��21)�B1(�z�P)�B3(����21)
int compare(Player*, Player*); // ������ �^��0(�۵�)�B1(��)�B2(Ĺ)
int bust_and_blackjack(int, int); // �B�z�z�P��21�I �^��0(�S���D)�B1(��)�B2(Ĺ)

#endif