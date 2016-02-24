#include "snake.h"

// �ߡ�ʳ��������з�����ȫ��Ψһ�ı�����
POSITION food;
PLIST snake;
dirction snake_dir;

#define INIT_LEN 5

// �ж�����λ��POSITION�Ƿ��غϵĺ���
int IsCoincide(POSITION* one, POSITION* two)
{
	if (one->x == two->x && one->y == two->y)
		return 1;
	return 0;
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
int Gorwup()
{
	POSITION* pNewTail = (POSITION*)malloc(sizeof(POSITION));
	POSITION* pTail;		// ������һ
	POSITION* pLastButOne;	// �����ڶ�
	int size = ListSize(snake);

	pTail = (POSITION*)ListGetAt(snake, size - 1);
	pLastButOne = (POSITION*)ListGetAt(snake, size - 2);
	// ���ŵ����ڶ�->������һ�ķ������һ���µĽڵ㡣
	pNewTail->x = pTail->x + (pTail->x - pLastButOne->x);
	pNewTail->y = pTail->y + (pTail->y - pLastButOne->y);

	ListPushBack(snake, pNewTail);

	return 1;
}


// ����һ��ʳ��
int CreateFood()
{
	POSITION* posbody;
	int i;
	int size = ListSize(snake);

new_food:

	food.x = rand() % CELLS_X;
	food.y = rand() % CELLS_Y;

	// �ж��Ƿ�����ص��ˡ�

	for (i = 0; i < size; i++)
	{
		posbody = (POSITION*)ListGetAt(snake, i);
		if (IsCoincide(posbody, &food))
		{
			goto new_food;
		}
	}
	return 1;

}

// ������
int CreateSnake()
{
	SetDirction(SNAKE_LEFT);

	//POSITION h;
	POSITION* p;
	snake = ListCreate(NULL);

	for (int i = 0; i < INIT_LEN; i++)
	{
		p = (POSITION*)malloc(sizeof(POSITION));
		// �ߵĳ�ʼλ�� 10�� 10��
		p->x = 10 + i;
		p->y = 10;
		ListPushBack(snake, p);
	}
	return 1;
}


// �ж����Ƿ����ˡ�
// ����0 ��û���� else �����ˡ�
int IsSnakeDead()
{
	POSITION* posBody;
	POSITION* posHead;

	int i;
	int size = ListSize(snake);


	// �ж��Ƿ�����
	/// �ж��Ƿ�����ǽ
	posHead = (POSITION*)ListGetAt(snake, 0);

	if (posHead->x < 0 || posHead->x > CELLS_X ||
		posHead->y < 0 || posHead->y > CELLS_Y)
	{
		return -1;
	}
	/// �ж��Ƿ������Լ�
	//// �ӵڶ����ڵ㿪ʼ����һ��ͷ�ڵ�Ƚϡ�
	size = ListSize(snake);

	for (i = 1; i < size; i++)
	{
		posBody = (POSITION*)ListGetAt(snake, i);
		if (IsCoincide(posHead, posBody))
		{
			return -1;
		}
	}
	return 0;
}


// ���������ƶ�һ����
// �ƶ��Ժ�
// ����Ե���ʳ���������
// ���������ǽ�����Լ������������������Ƿ�������״̬��
int SnakeMove()
{
	// ����ƶ��Ķ���
	POSITION* posHead;

	POSITION* posTail;
	//int i;
	//int size = ListSize(snake);

	// ����β�����ߵĵ�ǰ������õ���ͷ��
	posHead = (POSITION*)ListGetAt(snake, 0);
	posTail = (POSITION*)ListPopBack(snake);

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
	ListPushFront(snake, posTail);

	// �ж��Ƿ�Ե���ʳ��
	if (IsCoincide(posHead, &food))
	{
		CreateFood();
		Gorwup();
		return 0;
	}

	return IsSnakeDead();
}