#include "snake.h"

POSITION food;
list <POSITION> snake;
dirction snake_dir;

#define INIT_LEN 5

// �ж�����λ��POSITION�Ƿ��غϵĺ���
bool IsCoincide(POSITION one, POSITION two)
{ 
	if (one.x == two.x && one.y == two.y)
		return true;
	return false;
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

bool Gorwup()
{
	//POINT* posNewHead = new(POINT);
	POSITION posHead = snake.front();
	//snake.push_front(*posNewHead);
	switch (snake_dir)
	{
	case SNAKE_UP:
		posHead.y -= 1;
		break;
	case SNAKE_DOWN:
		posHead.y += 1;
		break;
	case SNAKE_LEFT:
		posHead.x -= 1;
		break;
	case SNAKE_RIGHT:
		posHead.x += 1;
		break;
	}
	snake.push_front(posHead);

	return true;
}




bool CreateFood()
{
	bool on_snake = false;

	while(true)
	{
		food.x = rand() % CELLS_X ;
		food.y = rand() % CELLS_Y ;

		// �ж��Ƿ�����ص��ˡ�
		list <POSITION>::iterator posbody;
		for(posbody = snake.begin(); posbody != snake.end(); posbody++)
		{
			if(IsCoincide(*posbody,food))
			{
				on_snake = true;
				break;
			}
		}
		if(!on_snake)
			return true;
	}
}


bool CreateSnake()
{
	SetDirction(SNAKE_LEFT);

	POSITION p;
	snake.clear();
	p.x = 10 ; // �ߵĳ�ʼλ��
	p.y = 10 ; // �ߵĳ�ʼλ��
	for(int i = 0; i<INIT_LEN; i++)
	{
		p.x+=1;
		snake.push_back(p);
	}
	return true;
}

// ���������ƶ�һ����
// ����ƶ�֮����û�����򷵻�0�� ��������ˣ�ײ��ǽ����ײ���Լ����򷵻� -1��
int SnakeMove()
{
	// ����ƶ��Ķ���
	POSITION posHead;
	posHead = snake.front();
	// ���ݵ����ߵķ������ж����Ǳ��ƶ�
	switch (snake_dir)
	{
	case SNAKE_UP:
		posHead.y -= 1;
		break;
	case SNAKE_DOWN:
		posHead.y += 1;	
		break;
	case SNAKE_LEFT:
		posHead.x -= 1;
		break;
	case SNAKE_RIGHT:
		posHead.x += 1;
		break;
	}

	snake.push_front(posHead);
	snake.pop_back();


	// �ж��Ƿ�Ե���ʳ��
	if (IsCoincide(posHead,food ))
	{
		CreateFood();
		Gorwup();
		return 0;
	}

	// �ж��Ƿ�����
	// �ж��Ƿ������Լ�
	list <POSITION>::iterator posbody;
	// �ӵڶ����ڵ㿪ʼ����һ��ͷ�ڵ�Ƚϡ�
	for(posbody = snake.begin(), posbody++; posbody != snake.end (); posbody++)
	{
		if(IsCoincide(posHead, *posbody))
		{
			return -1;
		}

	}
	// �ж��Ƿ�����ǽ
	if(posHead.x < 0 || posHead.x > CELLS_X  || 
		posHead.y < 0 || posHead.y > CELLS_Y )
	{
		return -1; 
	}

	return 0;
}