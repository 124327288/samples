#include <Windows.h>
#include "snake.h"

// ��ʱ��ID��
#define TIMER_ID 12340

DWORD dwTimeInterval;
double dbSpeedUpRatio;
int level_up_period;


int score = 0;
int level = 0;

#define IS_SPEEDUP(size) (size % level_up_period) == 0

int GetScore()
{
	return score;
}

int GetLevel()
{
	return level;
}

// ����ٶȡ�
BOOL SpeedUp(HWND hwnd)
{
	dwTimeInterval = (DWORD)(dwTimeInterval *0.9);
	KillTimer(hwnd, TIMER_ID);
	SetTimer(hwnd, TIMER_ID, dwTimeInterval, NULL);
	return TRUE;
}

// �ڼ�ʱ����������
// ����ʱ������ʱ���еĴ����߼���
void OnTimer(HWND hwnd)
{
	switch (SnakeMove())
	{
	case SNAKE_DEAD:
		// ������Ѿ����ˣ����ȹرռ�ʱ���������ٴε���SnakeMove��
		KillTimer(hwnd, TIMER_ID);
		// Ȼ��֪ͨ��ң�Game Over�ˣ��˳����̡�
		MessageBox(0, "Game Over", "Game Over", 0);
		ExitProcess(0);
		break;

	case SNAKE_EATEN_FOOD:
		score++;
		CreateFood();
		switch (SnakeGorwup())
		{
		case SNAKE_COMPLETE:
			// ������Ѿ����ˣ����ȹرռ�ʱ���������ٴε���SnakeMove��
			KillTimer(hwnd, TIMER_ID);
			// Ȼ��֪ͨ��ң�Game Over�ˣ��˳����̡�
			MessageBox(0, "You Win!", "You Win", 0);
			ExitProcess(0);
			break;
		case SNAKE_ERROR:
			KillTimer(hwnd, TIMER_ID);
			MessageBox(hwnd, "Error!!", "Error!1", MB_OK);
			ExitProcess(0);
			break;
		case SNAKE_GROWUP:
			if (IS_SPEEDUP(GetSnakeSize()))
			{
				level++;
			}
			break;
		}
		InvalidateRect(hwnd, NULL, 1);
		UpdateWindow(hwnd);
		break;
	case SNAKE_MOVED:
		// ���ô����ػ��ƣ����´���
		// If this parameter is NULL, the entire client area is added to 
		// the update region.
		InvalidateRect(hwnd, NULL, 1);
		UpdateWindow(hwnd);
		break;
	}
	return;

}
// �����ڲ���ʱ���е��߼�����
// ����Ϸֻʹ�õ��˼����������Ҽ����ơ�
void OnKeyDown(DWORD vk)
{
	switch (vk)
	{
	case VK_LEFT:
		SetDirction(SNAKE_LEFT);
		break;
	case VK_RIGHT:
		SetDirction(SNAKE_RIGHT);
		break;
	case VK_UP:
		SetDirction(SNAKE_UP);
		break;
	case VK_DOWN:
		SetDirction(SNAKE_DOWN);
		break;
	default:
		break;
	}
	return;
}


// ���������Ժ���еĳ�ʼ��������
void CreateGame(HWND hwnd, 
	int init_timer_interval, int period, double speedup_ratio,
	int max_x, int max_y, int init_x, int init_y, 
	int init_len, dirction init_dir)
{
	// �������������
	// ʳ���λ��������ġ�
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	srand(ft.dwLowDateTime);

	// ����һ����ʱ��
	// ÿ300���룬hwnd���ڣ������ڣ��ͻ��յ�һ��WM_TIMER��Ϣ��
	// ͨ��TIMERʹ�ó������ʱ�������Ե�ˢ����Ϸ��
	// ����Windows���¼������͡�����ܹ���һ������
	dbSpeedUpRatio = speedup_ratio;
	dwTimeInterval = init_timer_interval;
	level_up_period = period;

	SetBoundary(max_x, max_y);

	//snake
	SetTimer(hwnd, TIMER_ID, dwTimeInterval, NULL);

	// ������ʾ̰���ߵ����ݽṹ
	CreateSnake(init_dir, init_x, init_y, 5);

	// ������ʾʳ������ݽṹ
	CreateFood();
}