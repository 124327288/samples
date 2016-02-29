#include "snake.h"

#define INIT_LEN 5

GAME_COORD food;
PLIST snake_list;
dirction snake_dir;
int level_up_count;
int score = 0;
int level = 0;

// �ж�����λ��GAME_COORD�Ƿ��غϵĺ���
int CoordEqual(PGAME_COORD one, PGAME_COORD two)
{
	if (one->x == two->x && one->y == two->y)
		return 1;
	return 0;
}

dirction GetDirction()
{
	return snake_dir;
}

int GetScore()
{
	return score;
}

int GetLevel()
{
	return level;
}

PLIST GetSnakeList()
{
	return snake_list;
}

PGAME_COORD GetFood()
{
	return &food;
}

//�ı䷽����ǰ�ƶ����䳤���ı��ٶȡ��Ե�ʳ��֮��Ķ�����
void SetDirction(dirction dir)
{

	switch (snake_dir)
	{
	case SNAKE_UP:
		if (dir == SNAKE_DOWN)
			return;
		break;
	case SNAKE_DOWN:
		if (dir == SNAKE_UP)
			return;
		break;
	case SNAKE_LEFT:
		if (dir == SNAKE_RIGHT)
			return;
		break;
	case SNAKE_RIGHT:
		if (dir == SNAKE_LEFT)
			return;
		break;
	}
	snake_dir = dir;
}

// ������
int SnakeGorwup()
{
	PGAME_COORD pNewTail = (PGAME_COORD)malloc(sizeof(GAME_COORD));
	PGAME_COORD pTail;		// ������һ
	PGAME_COORD pLastButOne;	// �����ڶ�
	int size = ListSize(snake_list);

	if (size >= CELLS_X*CELLS_Y-1) //������ˣ���Ϸ������~
		return SNAKE_COMPLETE;

	if (size == 0) // û��ͷ����֪�Ӻ����������ش���
		return SNAKE_ERROR;

	if (size == 1) // ֻ��һ���ڵ㣬���յ�ǰ����������
	{
		pTail = (PGAME_COORD)ListGetAt(snake_list, 0/*ֻ��һ���ڵ㣬ͷ����β*/);
		switch (snake_dir)
		{
		case SNAKE_LEFT:
			pNewTail->x = pTail->x + 1;
			pNewTail->y = pTail->y;
			break;
		case SNAKE_RIGHT:
			pNewTail->x = pTail->x - 1;
			pNewTail->y = pTail->y;
			break;
		case SNAKE_UP:
			pNewTail->x = pTail->x ;
			pNewTail->y = pTail->y + 1;
			break;
		case SNAKE_DOWN:
			pNewTail->x = pTail->x;
			pNewTail->y = pTail->y - 1;
			break;
		}

	}
	else // ���������Ͻڵ㣬ȡ������һ�͵����ڶ�������������
	{
		pTail = (PGAME_COORD)ListGetAt(snake_list, size - 1);
		pLastButOne = (PGAME_COORD)ListGetAt(snake_list, size - 2);
		// ���ŵ����ڶ�->������һ�ķ������һ���µĽڵ㡣
		pNewTail->x = pTail->x + (pTail->x - pLastButOne->x);
		pNewTail->y = pTail->y + (pTail->y - pLastButOne->y);

	}

	ListPushBack(snake_list, pNewTail);
	if ((size + 1) % level_up_count == 0)
	{
		level++;
		return SNAKE_LEVELUP;
	}
	return SNAKE_GROWUP;

}


// ����һ��ʳ��
int CreateFood()
{
	PGAME_COORD posbody;
	int i;
	int size = ListSize(snake_list);

new_food:

	food.x = rand() % CELLS_X;
	food.y = rand() % CELLS_Y;

	// �ж��Ƿ�����ص��ˡ�

	for (i = 0; i < size; i++)
	{
		posbody = (PGAME_COORD)ListGetAt(snake_list, i);
		if (CoordEqual(posbody, &(food)))
		{
			goto new_food;
		}
	}
	return 1;

}

// ������
int CreateSnake(dirction dir, int head_x, int head_y, int level_up, int init_len)
{
	PGAME_COORD p;

	SetDirction(dir);
	level_up_count = level_up;
	
	snake_list = ListCreate(NULL);

	p = (PGAME_COORD)malloc(sizeof(GAME_COORD));
	// ��ͷ���ĳ�ʼλ�ã�
	p->x = head_x;
	p->y = head_y;
	ListPushFront(snake_list, p);

	for (int i = 1; i < init_len; i++)
	{
		//p = (PGAME_COORD)malloc(sizeof(GAME_COORD));
		SnakeGorwup();
	}
	return 1;
}


// �ж����Ƿ����ˡ�
// ����0 ��û���� else �����ˡ�
int IsSnakeDead()
{
	PGAME_COORD posBody;
	PGAME_COORD posHead;

	int i;
	int size = ListSize(snake_list);


	// �ж��Ƿ�����
	/// �ж��Ƿ�����ǽ
	posHead = (PGAME_COORD)ListGetAt(snake_list, 0);

	if (posHead->x < 0 || posHead->x > CELLS_X ||
		posHead->y < 0 || posHead->y > CELLS_Y)
	{
		return SNAKE_DEAD;
	}
	/// �ж��Ƿ������Լ�
	//// �ӵڶ����ڵ㿪ʼ����һ��ͷ�ڵ�Ƚϡ�
	size = ListSize(snake_list);

	for (i = 1; i < size; i++)
	{
		posBody = (PGAME_COORD)ListGetAt(snake_list, i);
		if (CoordEqual(posHead, posBody))
		{
			return SNAKE_DEAD;
		}
	}
	return SNAKE_MOVED;
}


// ���������ƶ�һ����
// �ƶ��Ժ�
// ����Ե���ʳ���������
// ���������ǽ�����Լ������������������Ƿ�������״̬��
int SnakeMove()
{
	// ����ƶ��Ķ���
	PGAME_COORD posHead;

	PGAME_COORD posTail;
	//int i;
	//int size = ListSize(snake_list);

	// ����β�����ߵĵ�ǰ������õ���ͷ��
	posHead = (PGAME_COORD)ListGetAt(snake_list, 0);
	posTail = (PGAME_COORD)ListPopBack(snake_list);

	// ���ݵ�ǰ�ߵķ������ж����Ǳ��ƶ�
	switch (snake_dir)
	{
	case SNAKE_UP:
		posTail->y = posHead->y - 1;
		posTail->x = posHead->x;
		break;
	case SNAKE_DOWN:
		posTail->y = posHead->y + 1;
		posTail->x = posHead->x;
		break;
	case SNAKE_LEFT:
		posTail->x = posHead->x - 1;
		posTail->y = posHead->y;
		break;
	case SNAKE_RIGHT:
		posTail->x = posHead->x + 1;
		posTail->y = posHead->y;
		break;
	}
	ListPushFront(snake_list, posTail);

	// �ж��Ƿ�Ե���ʳ��
	if (CoordEqual(posHead, &food))
	{
		CreateFood();
		return SnakeGorwup();
	}

	return IsSnakeDead();
}