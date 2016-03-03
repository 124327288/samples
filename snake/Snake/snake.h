
#include <Windows.h>
#include "LinkList.h"

// �ߵ�״̬
#define SNAKE_MOVED			0
#define SNAKE_DEAD			1
#define SNAKE_COMPLETE		2
#define SNAKE_EATEN_FOOD	3
#define SNAKE_GROWUP		4
#define SNAKE_ERROR			5

// �ߵķ���
enum dirction
{
	SNAKE_UP,
	SNAKE_DOWN,
	SNAKE_LEFT,
	SNAKE_RIGHT,
};

// ��Ϸ����
typedef struct _GAME_COORD
{
	short x;
	short y;
}GAME_COORD, *PGAME_COORD;

// ��������

/// snake_and_food.c�еĽӿں���
void SetBoundary(int x, int y);
PGAME_COORD GetBoundary();

int CreateFood();
PGAME_COORD GetFood();

void SetDirction(dirction dir);
dirction GetDirction();

void CreateSnake(dirction dir, int head_x, int head_y, int init_len);
int SnakeGorwup();
int SnakeMove();
int GetSnakeSize();
PGAME_COORD GetSnakeHead();
PGAME_COORD GetSnakeTail();
PGAME_COORD GetSnakeAt(int n);
void DistroySnake();

/// game_opration.c �еĽӿں���
int GetScore();
int GetLevel();
void CreateGame(HWND hwnd,
	DWORD dwInitTimerElapse,
	unsigned int one_level_scores,
	DOUBLE level_speedup_ratio,
	int boundary_x, int boundary_y,
	int init_x, int init_y,
	int init_len,
	dirction init_dir);
void OnTimer(HWND hwnd);
void OnKeyDown(DWORD vk);