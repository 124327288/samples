#include <Windows.h>
#include "snake.h"

#define SPEEDUP_GROWUP_TIME 5
// ��ʱ��ID��
#define TIMER_ID 12340

DWORD dwTimeInterval;
double dbSpeedUpRatio;


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
	case SNAKE_COMPLETE:
		// ������Ѿ����ˣ����ȹرռ�ʱ���������ٴε���SnakeMove��
		KillTimer(hwnd, TIMER_ID);
		// Ȼ��֪ͨ��ң�Game Over�ˣ��˳����̡�
		MessageBox(0, "You Win!", "You Win", 0);
		ExitProcess(0);
		break;
	case SNAKE_GROWUP:
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
	case SNAKE_LEVELUP:
		SpeedUp(hwnd);
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
void OnCreate(HWND hwnd)
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
	dbSpeedUpRatio = 0.9;
	dwTimeInterval = 300;
	//snake
	SetTimer(hwnd, TIMER_ID, dwTimeInterval, NULL);

	// ������ʾ̰���ߵ����ݽṹ
	CreateSnake(SNAKE_LEFT, 10, 10, 5, 5);

	// ������ʾʳ������ݽṹ
	CreateFood();
}