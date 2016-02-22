// ���õ�ͷ�ļ�
#include <windows.h>	// Windows���ڳ����̣���Ҫ����ͷ�ļ� Windows.h
#include "snake.h"


#define SNAKE_CELL_SIZE 20
#define TIMER_ID 12340

/********************************************************************************
* ##########����Windows��������##########
*
* Windows��C���ԵĻ����϶����˺ܶ�Windows���е����͡�����ͨ��C���Թؼ���typedef����ġ�
* Windows���Ͷ���ȫ��д�� 
*
* BOOL DWORD LPSTR WPARAM LPARAM HWND��
* ���У���H��ͷ���������Ͷ��Ǿ��
*
*******************************************************************************/

/*******************************************************************************
* ##########   ���ھ��    ##########
*
* �����Windowsϵͳ�еĻ�����������
* �����ϵͳ����ı�ʶ��������Ψһ��ʾһ��ϵͳ����
* ���磺�ļ������ڡ��̡߳���ʱ���ȵȡ�
* ���������Ҳ��ϸ�֣������ľ����HANDLE�����ھ��HWND��GDI��ˢ���HBRUSH�ȡ�
* ������H��ͷ�����ͻ������Ǿ�����͡�
*
*******************************************************************************/

// ȫ�ֱ���
HINSTANCE hinst; /// HINSTANCE��������ʾ��������ʵ���ľ����ĳЩAPI������ʹ�õ����������
RECT rectBoundary;


extern POSITION food;
extern list <POSITION> snake;


// ��������

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int); 
BOOL  InitApplication(HINSTANCE); 
BOOL  InitInstance(HINSTANCE, int); 
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM); 




/*******************************************************************************
* ##########   ��ں���WinMain    ##########
*
* WindowsӦ�ó������ں�����WinMain���������λ���������Ʊ�׼C���Ե�main����
*
*******************************************************************************/

int WINAPI WinMain(
	HINSTANCE hinstance,	// ����ʵ��������ڳ������У����̴������ɲ���ϵͳ��Ӧ�ó�����
	HINSTANCE hPrevInstance,	// �����̵ĳ���ʵ�����
	LPSTR lpCmdLine,		// �����в�������λ����������C����main��������argc��argv,����û�а��ո�����з�
	int nCmdShow)			// ����ָ�������Ƿ���Ҫ��ʾ�Ĳ�����
{ 

	hinst = hinstance; 

	/*******************************************************************************
	* ##########   ���� API ����   ##########
	*
	* API�� Application Programming Interface����д������Ӧ�ó����̽ӿڡ�
	* API��Windows����ϵͳ�ṩ��Ӧ�ó�����õ�һϵ�й��ܵĽӿں���������Ӧ�ó�����ò���ϵͳ�ĵײ㹦��
	*
	* API������ʹ�÷�������C���ԵĿ⺯������printf��fopen��fread�ȡ�
	* ��VS������ʹ��C����C++���б���ǣ�ֻ��#include <windows.h>���ɵ��ô󲿷�Windows API������
	*
	* ������һ�˴�����ʹ�õ��� LoadIcon LoadCursor GetStockObject RegisterClass CreateWindow�Ⱥ�������API
	* 
	* WindowsӦ�ó��򿪷������е���Ҫ��������ʹ��API��
	*
	*******************************************************************************/

	/*******************************************************************************
	* ##########   ������   ##########
	*
	* �ڴ�������֮ǰ��������Ҫע��һ�������࣬������������Ϊͬһ����Ĵ��ڡ�
	* һ����������Դ���������ڣ�����ͬһ������Ĵ��ھ�����ͬ����Ϣ�����������Ƶ���ʽ��
	*
	* �������C++�е���Ӣ�Ķ���class���������ǲ���ͬһ���
	* C++��ʹ��class�ؼ��ֶ��壬����������ʹ��RegisterClass API������Windowsϵͳע�ᡣ
	*
	* ����� WNDCLASS wc ��ע�ᴰ����� API����RegisterClass�Ĳ�������һ���ṹ�����ͣ�
	* �����洢һ��������ĸ�������
	*
	*******************************************************************************/
	WNDCLASS wc; 

	// Fill in the window class structure with parameters 
	// that describe the main window. 


	wc.style = CS_HREDRAW | CS_VREDRAW;		// ���������ʽ���������õ���ʽ��ʾ�����ڴ�С�仯����Ҫ�ػ�
	wc.lpfnWndProc = MainWndProc;		// һ������ָ�룬�������������������Ϣ�� ��� MainWndProc������ע�͡�
	wc.cbClsExtra = 0;		// no extra class memory 
	wc.cbWndExtra = 0;		// no extra window memory 
	wc.hInstance = hinstance;		// handle to instance 
	wc.hIcon = LoadIcon(NULL,		// hIcon��Ա����ָ�����ڵ�ͼ��
		IDI_APPLICATION);			// ����ֱ��ʹ��LoadIcon����������һ��ϵͳԤ�����ͼ�꣬������Ա��Ҳ�����Լ�����ͼ�ꡣ
	wc.hCursor = LoadCursor(NULL,	// Cursor������꣬�������趨����������ʽ��
		IDC_HAND);			// ֱ��ʹ��LoadCursor API����������һ��ϵͳԤ����Ĺ����ʽ������IDC_CROSS,IDC_HAND����ʽ 
	wc.hbrBackground = (HBRUSH)GetStockObject(	// GetStockObject�Ĺ����Ǽ���һ��ϵͳԤ���壨��ջ�У���GDI����
		WHITE_BRUSH);		// ������ص���һ����ɫ�Ļ�ˢ���йػ�ˢ��GDI�������GDI˵����
	wc.lpszMenuName =  "MainMenu";		// ���ڵĲ˵�����Դ����
	wc.lpszClassName = "MainWClass";	// ����������һ�����֣��ڴ�������ʱ��Ҫ������֡�

	// Register the window class. 

	if(!RegisterClass(&wc))
	{
		// ����ע��ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������classʧ��","����", MB_ICONERROR | MB_OK);
		return -1;
	}
	// ����ע��ɹ����������С�


	// ���ھ����hwnd�����������ڵľ�������������ֻ�õ���һ�����ڡ�
	HWND hwnd;


	// Create the main window. 

	hwnd = CreateWindow( 
		"MainWClass",        // �����������������Ѿ�ע���˵Ĵ�����
		"GDI-Snake-Demo",    // title-bar string 
		WS_OVERLAPPEDWINDOW, // ���ڵ�style�������ʾΪtop-level window 
		200,       // ����ˮƽλ��default horizontal POINT 
		100,       // ���ڴ�ֱλ��default vertical POINT 
		450,       // ���ڿ�� default width 
		550,       // ���ڸ߶� default height 
		(HWND) NULL,         // �����ھ�� no owner window 
		(HMENU) NULL,        // ���ڲ˵��ľ�� use class menu 
		hinstance,           // Ӧ�ó���ʾ����� handle to application instance 
		(LPVOID) NULL);      // ָ�򸽼����ݵ�ָ�� no window-creation data 

	if (!hwnd) 
	{
		// ���ڴ���ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������ʧ��","����", MB_ICONERROR | MB_OK);
		return -1;
	}

	// ���ڴ����ɹ����������С�

	// �ƶ����ڣ����ô��ڵ�λ�úʹ�С
	//MoveWindow(hwnd, 100, 100, 450, 550, TRUE);

	// ��ʾ���ڣ�WinMain������nCmdShow���������﷢�����ã�һ�㶼����ΪSW_SHOW
	ShowWindow(hwnd, nCmdShow); 

	// ˢ�´��ڣ��򴰿ڷ���һ��WM_PAINT��Ϣ��ʹ�ô��ڽ����ػ档
	UpdateWindow(hwnd); 


	/*******************************************************************************
	* ##########   MSG���ͺ���Ϣ    ##########
	*
	* Windows����Ӧ�ó�����һ����Ϣ�����ĳ����ܡ�
	* Windows����Ӧ�ó��������Ժ������߳̾�һֱ���� 
	* "�ȴ���Ϣ--��ȡ��Ϣ--ЧӦ��Ϣ" ��ѭ��֮�У�ֱ�������˳���
	*
	* ��ν��Ϣ��Windowsϵͳ���е�һ��ϵͳ����ͻ��ƣ�
	* �ǲ���ϵͳ��ĳЩϵͳ״̬����ʱ�ӣ����û����������������������ϵͳ�жϽ��з�װ�Ժ�
	* ���Է��͵�Ӧ�ó��򣬲���Ӧ�ó�����д�����û�̬����
	*
	* "MSG"����������ʾ"��Ϣ"���������͡� ���ﶨ����һ��MSG���͵ı�����������Ϊmsg
	*
	*******************************************************************************/
	MSG msg; 
	BOOL fGotMessage;

	// ���½�����Ϣѭ������ȡ��Ϣ--������Ϣ--������Ϣ���ɴ��ڵ���Ϣ��������������Ϣ��
	while ((fGotMessage = GetMessage(&msg, (HWND) NULL, 0, 0)) != 0 
		&& fGotMessage != -1) 
	{ 
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	} 
	return msg.wParam; 
} 


/*******************************************************************************
* ##########   ��Ϣ����ص�����    ##########
* 
* ������ÿ�յ�һ����Ϣ���˺����ͱ�����һ�Ρ�
* ������Ϣ�ĵ����������ԣ���ˣ���Ϣ�����ĵ����ǻص��ģ�����
* Ӧ�ó��������Ϣ�����������ǲ�ֱ�ӵ��ã����ǽ�����ָ�봫�ݸ�����ϵͳ��ͨ��RigesterClass��
* ����Ϣ�ﵽʱ������ϵͳͨ���������ָ�������Ϣ���������������Ӧ��Ϣ��
*
* Windows����Ӧ�ó�����һ����Ϣ�����ĳ����ܡ�
* Windowsϵͳ��һ���м�������Ϣ�����õ��м�ʮ�֣��磺
*
* WM_CREATE �����ڱ������ǻ��յ�����Ϣ
* WM_PAINT ������Ӧ�û���GDIͼ���ǻ��յ�����Ϣ
* WM_SIZE �����ڴ�С�仯���
* WM_MOVE �����ڱ��ƶ���
* WM_DESTROY ��������ڵĹرհ�ť��
* WM_KEYDOWN �����̵ļ��������Ժ�
* WM_KEYUP �����̵ļ������Ժ�
* WN_CHAR �������ַ��Ժ�
* WM_TIMER ����ʱ����ʱ�Ժ�
* WM_LBUTTONDOWN WM_LBUTTONUP WM_RBUTTONDOWN WM_RBUTTONUP �ֱ�Ϊ������Ҽ����º͵���
* WM_LBUTTONDBLCLK ������˫��
* WM_COMMAND һ���ڴ��ڵĲ˵��������
* WN_NOTIFY һ�����Ӵ��ڱ�������ĳ�����ʱ�������ڻ��յ�����Ϣ�����Ӵ����ǿؼ�������³���ʹ��
* WM_SIZING �������ڴ�С�仯�Ĺ�����
* WM_MOVING ���������ƶ�������
* WM_SETFOCUS �����ڻ�����\���̽���
* WM_KILLFOCUS ������ʧȥ���\���̽���
*
*******************************************************************************/

/*******************************************************************************
* ##########   ����Callback�ص�����    ##########
*
* �ص����� Callback functions ��ϵͳ���򿪷��г��õ�һ�ֻ��ơ�
* 
* ���¼�\��Ϣ�����͵�ϵͳ�����ǻ��������������
* ��1��ϵͳ����֪��Ӧ�ó���Ҫ��δ����¼��������������
* ��2��Ӧ�ó���֪����ʱ�ᷢ���¼���������ʱ���������
* ��ˣ�Ӧ�ó�����ô����¼��ĺ�����Ȼ�����������ָ�봫�ݸ�����ϵͳ��ϵͳ�������ָ�룬
* ���¼�����ʱ��ϵͳͨ��ָ��������������
*
* ��Ϊ�ܶ�������¼��ķ�������Ӳ����صģ�ֻ�в���ϵͳͨ���ײ��������ܻ�ȡӲ����IO�����
* �ִ�����ϵͳ������ǲ�����Ӧ�ó���ֱ�Ӻ�Ӳ��ͨѶ�ģ�����ȫ���ɲ���ϵͳ�����й���
* 
* �ص������������أ�����ԭ����Ǻ���ָ�롣
* ����Ϣ���¼��������̡߳��첽IO������¾�����ʹ�õ���
* �ص����������ǡ���Ϣ�����͡�����Ļ���������
*
*******************************************************************************/
LONG APIENTRY MainWndProc(
	HWND hwnd,	//
	UINT msg,	// ��Ϣ
	WPARAM wParam,	// ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
	LPARAM lParam)	// ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
{
	// ע�⣬��switch-case, ÿ��������������ã�ֻ�����뵽һ��case�С�
	switch (msg)
	{
		// �����ڱ�����ʱ���յ��ĵ�һ����Ϣ����WM_CREATE��
		// һ���յ������Ϣ��������У�������������һЩ��ʼ���Ĺ���
	case WM_CREATE:
		
		// ����һ����ʱ��
		// ÿ300���룬hwnd���ڣ������ڣ��ͻ��յ�һ��WM_TIMER��Ϣ��
		// ͨ��TIMERʹ�ó������ʱ�������Ե�ˢ����Ϸ��
		// ����Windows���¼������͡�����ܹ���һ������
		SetTimer(hwnd, TIMER_ID, 300, NULL);

		// �������������
		FILETIME ft;
		GetSystemTimeAsFileTime(&ft);
		srand(ft.dwLowDateTime);

		// ������ʾ̰���ߵ����ݽṹ
		CreateSnake();

		// ������ʾʳ������ݽṹ
		CreateFood();

		// ������Ϸ�߽�
		rectBoundary.left = 10;
		rectBoundary.top = 10;
		rectBoundary.right = 10 + SNAKE_CELL_SIZE*(CELLS_X+1);
		rectBoundary.bottom = 10 + SNAKE_CELL_SIZE*(CELLS_Y+1);

		break; // ��Ϣ������ɡ�

		
		// ��ϵͳ��Ϊ�����ϵ�GDI����Ӧ�ñ��ػ�ʱ�����򴰿ڷ���һ��WM_PAINT��Ϣ��
		// ��ȻӦ�ó���Ҳ����ͨ������ UpateWindow�������򴰿ڷ���һ��WM_PAINT��Ϣ��
		// ����ʹ��GDI�ڴ����ϻ���ͼ�εĳ��� �����롱 д�����
		// ���������WM_PAINT��Ϣ�Ĵ�������л���GDIͼ�Σ���ô�ڴ���ˢ��ʱ�ͻᱻ�±�Ĩ���͸���
	case WM_PAINT: 
		{
			
			/*******************************************************************************
			* ##########   ���� GDI    ##########
			*
			* GDI��ȫ����Graphics Device Interface��ͼ���豸�ӿڡ�
			* GDI��Windowsϵͳ���������ͼ��ͼ��ӿڣ�������������ʾ����GDI��������Ĳ��֣�
			* ���Ƕ��ڱ�д̰����������С��Ϸ�Ѿ��㹻���ˡ�
			*
			* ����GDI��������������
			* 1��DC��DC��ȫ����Device Context�����Ʋ����ڴ˽��С�����������Ϊһ�黭������Ӧ��Ļ��һ������
			*      GDI�Ļ��Ʋ���������һ��DC�Ͻ��У���˵�һ�����ǵõ�DC�ľ����BeginPaint����GetDC������
			* 2��GDI���󣺰���PEN��BRUSH��FONT�ȣ�ÿһ�ֻ��Ʋ�������ʹ�õ�һ�����߶��GDI����
			*      ���ԣ��ڻ��Ʋ���֮ǰ�����һ�������ǽ��������õ�GDI�������DC�У�ʹ��SelectObject������ɡ�
			* 3�����Ʋ���������DC��ʹ�ñ�ѡ����DC�е�GDI�������ͼ�Ρ����������ֵȡ�
			*      ��LineTo����������Ellipse����(��)Բ��Rectangle�������Ρ�TextOut�������
			*
			* ʹ��GDI�������ͼ�������ض������̣�����:
			*******************************************************************************/

			PAINTSTRUCT ps;
			HDC hdc;

			HPEN hpen;
			HPEN hPenBoundary;
			HPEN hOldPen ;

			HBRUSH hbrushFood;
			HBRUSH hbrushSnake;
			HBRUSH hOldBrush;

			HFONT hFont, hOldFont; 

			/*******************************************************************************
			* #############  BeginPaint����  ################
			* BeginPaint ����֪ͨϵͳ��ͼ���̿�ʼ��ϵͳ���ػ����������Դ��DC,��֮��Ӧ����EndPaint��
			* BeginPaint �������Զ��ж���Щ������Ҫ���»��ƣ���Щ���á�
			* BeginPaint �� EndPaint ֻ����WM_PAINT��Ϣ�Ĵ�������е��ã����ұ������ʹ�á�
			*******************************************************************************/
			hdc = BeginPaint(hwnd, &ps);

			// ������Ҫ�õ���PEN��BRUSH
			hbrushFood = CreateSolidBrush(RGB(152, 251, 152 ));	// RGB��ɫ��ʵ��BRUSH
			hpen = CreatePen(PS_NULL, 0, RGB(0, 0, 0 ));		// PEN�� PS_NULL��ʾ���ɼ�
			hbrushSnake = CreateSolidBrush(RGB(193, 205, 205 ));
			hPenBoundary = CreatePen(0, 3, RGB(139, 134, 130 ));

			/*******************************************************************************
			* #############  ��ʳ��  ################
			*
			*******************************************************************************/

			// ����ͼ��Ҫ�õ�PEN��BRUSHѡ��DC��
			hOldBrush = (HBRUSH)SelectObject(hdc, hbrushFood);
			hOldPen = (HPEN)SelectObject(hdc, hpen);

			// ���֣�Բ�Σ�ʹ������ѡ���PEN���ձ߿�BRUSH���
			Ellipse(hdc, 
				food.x * SNAKE_CELL_SIZE + rectBoundary.left, 
				food.y * SNAKE_CELL_SIZE + rectBoundary.top,
				(food.x+1)*SNAKE_CELL_SIZE + rectBoundary.left, 
				(food.y+1)*SNAKE_CELL_SIZE + rectBoundary.top);

			/*******************************************************************************
			* #############  ����  ################
			*
			*******************************************************************************/

			SelectObject(hdc, hbrushSnake);

			list <POSITION>::iterator sn_pos;
			for(sn_pos = snake.begin(); sn_pos != snake.end(); sn_pos++)
			{
				POSITION p = *sn_pos;
				Ellipse(hdc,
					p.x * SNAKE_CELL_SIZE + rectBoundary.left, 
					p.y * SNAKE_CELL_SIZE + rectBoundary.top,
					(p.x+1)*SNAKE_CELL_SIZE + rectBoundary.left, 
					(p.y+1)*SNAKE_CELL_SIZE + rectBoundary.top);
			}

			/*******************************************************************************
			* #############  ���߿�  ################
			*
			*******************************************************************************/

			SelectObject(hdc, hPenBoundary);

			// ��PEN�ƶ�����Ҫ���Ƶķ�������Ͻ�
			MoveToEx(hdc, rectBoundary.left, rectBoundary.top, NULL);
			// ����һ��������ʾLineTo����
			LineTo(hdc, rectBoundary.left, rectBoundary.bottom);
			LineTo(hdc, rectBoundary.right, rectBoundary.bottom);
			LineTo(hdc, rectBoundary.right, rectBoundary.top);
			LineTo(hdc, rectBoundary.left, rectBoundary.top);

			/*******************************************************************************
			* #############  дһ����  ################
			*
			*******************************************************************************/
			
			// ������һ���������
			hFont = CreateFont(48,0,0,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Impact"));

			// �����FONT�������DC��
			if (hOldFont = (HFONT)SelectObject(hdc, hFont)) 
			{
				// ����ɹ���������ַ�����
				TextOut(hdc, rectBoundary.left+3, rectBoundary.bottom+3, 
					"̰����!", lstrlen("̰����!")); 
				// �����ɣ���ԭ�����������Ż�DC��
				SelectObject(hdc, hOldFont); 
			}

			/*******************************************************************************
			* #############  �ظ����ͷ���Դ  ################
			*
			*******************************************************************************/
			SelectObject(hdc, hOldBrush);
			SelectObject(hdc, hOldPen);

			DeleteObject(hbrushFood);
			DeleteObject(hbrushSnake);
			DeleteObject(hpen);
			DeleteObject(hPenBoundary);
			DeleteObject(hFont);
			/*******************************************************************************
			* #############  EndPaint����  ################
			* EndPaint�ͷ� BeginPaint ����ռ�õ�DC��ϵͳ��Դ��
			* BeginPaint �� EndPaint�����������ʹ�á�
			*******************************************************************************/
			EndPaint(hwnd,&ps);
			
		}
		break;

	case WM_KEYDOWN:
		{
			switch(wParam)
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
			// ���ô����ػ�������ȫ��Client���򣩣�Ȼ������ػ洰�ڣ�����WM_PAINT��Ϣ��
			// ������һ����WM_PAINT��BeginPaint������ϵĹ��̡�
			InvalidateRect (hwnd, NULL, TRUE);
			UpdateWindow (hwnd);
			break;
		}
	case WM_TIMER:
		{
			if(SnakeMove() != 0)
			{
				// ������Ѿ����ˣ����ȹرռ�ʱ���������ٴε���SnakeMove��
				KillTimer(hwnd, TIMER_ID);
				// Ȼ��֪ͨ��ң�Game Over�ˣ��˳����̡�
				MessageBox(0,"Game Over","Game Over",0);
				ExitProcess(0);
			}
			// ���ô����ػ��ƣ����´���
			// If this parameter is NULL, the entire client area is added to 
			// the update region.
			InvalidateRect (hwnd, NULL, TRUE);
			UpdateWindow (hwnd);

			break;
		}

	case WM_DESTROY:
		ExitProcess(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hwnd,
			msg,
			wParam,
			lParam);
}