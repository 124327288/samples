#include <Windows.h>
#include "auto_fly.h"



LONG CALLBACK BackGroundWindowProc(
	HWND hwnd, //
	UINT msg, // ��Ϣ
	WPARAM wParam, // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
	LPARAM lParam); // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�


BOOL BackGroundWindwowRegister(HINSTANCE hinstance);

HWND BackgroundWindowCreate(HINSTANCE hinstance);

LONG CALLBACK FighterWindowProc(
	HWND hwnd, //
	UINT msg, // ��Ϣ
	WPARAM wParam, // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
	LPARAM lParam); // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�


HWND FighterWindowCreate(HINSTANCE hinstance);

BOOL FighterWindowRegister(HINSTANCE hinstance);

LONG AutoflysPaint(HWND hwnd);
LONG CALLBACK AutoflyWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND AutoflyWindowCreate(HINSTANCE hinstance);
BOOL AutoflysWindowRegister(HINSTANCE hinstance);


LONG BackgroundCreate(HWND hwnd);

LONG AutoflysCreate(HWND hwnd);
LONG BackgroundResizeAndMove(HWND hwnd, LPRECT lpRect);
LONG BackgroundPaint(HWND hwnd);
LONG FighterKeyDown(HWND hwnd, UINT vk);

LONG AutoFlysTimer(HWND hwnd);