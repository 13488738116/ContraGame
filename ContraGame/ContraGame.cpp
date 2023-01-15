// ContraGame.cpp : 定义应用程序的入口点。
//

#include "ContraGame.h"

using namespace std;


#pragma region 全局变量

#define MAX_LOADSTRING			100		

// 全局变量: 
HINSTANCE hInst; // 当前窗体实例
WCHAR szTitle[MAX_LOADSTRING]; // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING]; // 主窗口类名



HBITMAP bmp_Grass;			//背景图像资源
HBITMAP bmp_HELPFACE;       //帮助界面

HBITMAP bmp_Unit_Red;		//红方主角图像资源
HBITMAP bmp_Unit_Blue;		//蓝方主角图像资源

HBITMAP bmp_Background;		//生成的背景图像
HBITMAP bmp_STARTGAME;      //开始按钮
HBITMAP bmp_HELP;           //帮助按钮
HBITMAP bmp_RETURN;           //返回按钮
HBITMAP bmp_PAUSE;           //暂停按钮
HBITMAP bmp_RESTART;        //重新开始
HBITMAP bmp_RESUME;			//恢复
HBITMAP bmp_RETURN1;		//返回按钮
HBITMAP bmp_ONE;			//关卡1
HBITMAP bmp_STONE1x1;
HBITMAP bmp_STONE2x1;
HBITMAP bmp_STONE3x2;
HBITMAP bmp_LADDER;
HBITMAP bmp_PROP_BOX;
HBITMAP bmp_PROP_SWITCH;
HBITMAP bmp_PROP_SWITCH1;
HBITMAP bmp_PROP_REDKEY;
HBITMAP bmp_PROP_BLUEKEY;
HBITMAP bmp_PROP_GREENKEY;
HBITMAP bmp_PROP_YELLOWKEY;
HBITMAP bmp_SNAG3x1;
HBITMAP bmp_SNAG5x1;
HBITMAP bmp_YELLOW;
HBITMAP bmp_SHOWYELLOWKEY;
HBITMAP bmp_SHOWBLUEKEY;
HBITMAP bmp_SHOWREDKEY;
HBITMAP bmp_SHOWGREENKEY;
HBITMAP bmp_FULLHEALTH;
HBITMAP bmp_HALFHEALTH;
HBITMAP bmp_ZEROHEALTH;
HBITMAP bmp_SWITCH1;
HBITMAP bmp_FAIL;
HBITMAP bmp_CONGRATULATIONS;
HBITMAP bmp_NEXT;
HBITMAP bmp_TWO;
HBITMAP bmp_LADDER2;
HBITMAP bmp_SHIFT;
HBITMAP bmp_myster;
HBITMAP bmp_mutton;
HBITMAP bmp_chunk;
HBITMAP bmp_arrow;
HBITMAP bmp_1x1;
HBITMAP bmp_2x1;
HBITMAP bmp_monster1;
HBITMAP bmp_monster2;
HBITMAP bmp_monster3;
HBITMAP bmp_transparent;
HBITMAP bmp_FLASH;
HBITMAP bmp_select;
HBITMAP bmp_first;
HBITMAP bmp_second;
HBITMAP bmp_play;
HBITMAP bmp_left;
HBITMAP bmp_right;
HBITMAP bmp_gonglue;
HBITMAP bmp_victory;
HBITMAP bmp_acknowledge;

Obstacle*FLOOR=NULL;
Obstacle*x1=NULL;
Stage* currentStage = NULL; //当前场景状态
vector<Unit*> units;		//单位
vector<Button*> buttons;	//按钮
vector<Obstacle*>obstacles; //障碍物
vector<Prop*>props;		//道具
vector<Showscreen*>showscreens;//屏幕显示
vector<Monster*>monsters; //怪物
Unit*unit1=NULL;
Unit*unit2=NULL;
Monster*monster1=NULL;
Monster*monster2=NULL;
Monster*monster3=NULL;
int mouseX = 0;
int mouseY = 0;
int angle=0;
int timecount=0;
int timecount1=0;
int timecount2=0;
int timecount3=0;
int timecount4=0;
int timecount5=0;
int num3=0;
int stage=-1;
bool mouseDown = false;
bool keyUpDown = false;
bool keyDownDown = false;
bool keyLeftDown = false;
bool keyRightDown = false;
bool keyADown=false;
bool keyWDown=false;
bool keyDDown=false;
bool keyspaceDown=false;
bool keyescDown=false;
bool keySDown=false;
bool keyKDown=false;
bool keyFDown=false;
bool health1=true;
bool flash=false;
bool monsters1=false;
int key=0;
int key1=0;
//帧
int FRAMES_HOLD[] = { 0 };
int FRAMES_HOLD_COUNT = 1;
int FRAMES_WALK[] = { 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5,5,1,1, 2, 2 };
int FRAMES_WALK_COUNT = 16;
int FRAMES_ATTACK[] = { 1, 1, 2, 2, 2,2,2,2,2,5,5,5,5, 5,5,5 };
int FRAMES_ATTACK_COUNT = 16;
int FRAMES_CLIMB[]={0};
int FRAMES_CLIMB_COUNT=1;
int FRAMES_JINENG[]={0};
int FRAMES_JINENG_COUNT=1;
int FRAMES_LEAP[]={2};
int FRAMES_LEAP_COUNT=1;

// TODO: 在此添加其它全局变量





double const PI = acos(double(-1));


#pragma endregion


#pragma region Win32程序框架



// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);




int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_CONTRAGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CONTRAGAME));

	MSG msg;

	// 主消息循环: 
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

int RestartStage(HWND hWnd,int stageID);
int ResumeStage(HWND hWnd,int stageID);
void CongratulationStage(HWND hWnd);
void FailStage(HWND hWnd);
	//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON6));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDI_ICON6);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON6));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindow(szWindowClass, szTitle,
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // 设置窗口样式，不可改变大小，不可最大化,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOW_WIDTH,
		WINDOW_HEIGHT + WINDOW_TITLEBARHEIGHT,
		nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		// 初始化游戏窗体
		InitGame(hWnd, wParam, lParam);
		break;
	case WM_KEYDOWN:
		// 键盘按下事件
		KeyDown(hWnd, wParam, lParam);
		if(keyescDown==true)
		{

			InitStage(hWnd, STAGE_PAUSE);
		}
		break;
	case WM_KEYUP:
		// 键盘松开事件
		KeyUp(hWnd, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		// 鼠标移动事件
		MouseMove(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONDOWN:
		// 鼠标左键按下事件
		LButtonDown(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		// 鼠标左键松开事件
		LButtonUp(hWnd, wParam, lParam);
		break;
	case WM_TIMER:
		// 定时器事件
		if (currentStage != NULL && currentStage->timerOn) TimerUpdate(hWnd, wParam, lParam);
		break;
	case WM_PAINT:
		// 绘图
		Paint(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	
		
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


#pragma endregion


#pragma region 事件处理函数

// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//加载图像资源
	bmp_Grass = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_GRASS));
	bmp_Unit_Red = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RED));
	bmp_Unit_Blue = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BLUE));
	bmp_Background=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_FINAL ));
	bmp_STARTGAME=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_STARTGAME ));
	bmp_HELP=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HELP ));
	bmp_HELPFACE=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_caozuo ));
	bmp_RETURN=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RETURN ));
	bmp_PAUSE=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_PAUSE ));
	bmp_RESTART=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RESTART ));
	bmp_RESUME=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RESUME ));
	bmp_RETURN1=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RETURN1 ));
	bmp_ONE=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_ONE ));
	bmp_STONE1x1=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_STONE1x1 ));
	bmp_STONE2x1=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_STONE2x1 ));
	bmp_STONE3x2=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_STONE3x2 ));
	bmp_LADDER=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_LADDER ));
	bmp_PROP_BOX=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_PROP_BOX ));
	bmp_PROP_SWITCH=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_PROP_SWITCH ));
	bmp_PROP_REDKEY=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_PROP_REDKEY ));
	bmp_PROP_BLUEKEY=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_PROP_BLUEKEY ));
	bmp_PROP_GREENKEY=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_PROP_GREENKEY ));
	bmp_PROP_YELLOWKEY=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_PROP_YELLOWKEY ));
	bmp_SNAG3x1=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_SNAG3x1 ));
	bmp_SNAG5x1=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_SNAG5x1 ));
	bmp_YELLOW=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_YELLOW ));
	bmp_SHOWYELLOWKEY=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_SHOWYELLOWKEY ));
	bmp_SHOWREDKEY=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_SHOWREDKEY ));
	bmp_SHOWBLUEKEY=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_SHOWBLUEKEY ));
	bmp_SHOWGREENKEY=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_SHOWGREENKAY ));
	bmp_FULLHEALTH=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_FULLHEALTH ));
	bmp_HALFHEALTH=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HALFHEALTH ));
	bmp_ZEROHEALTH=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_ZEROHEALTH ));
	bmp_SWITCH1=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_SWITCH1));
	bmp_CONGRATULATIONS=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_CONGRATULATIONS));
	bmp_FAIL=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_FAIL));
	bmp_NEXT=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_NEXT));
	bmp_TWO=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_TWO ));
	bmp_LADDER2=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_LADDER2 ));
    bmp_SHIFT=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_SHIFT ));
    bmp_myster=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_myster));
	bmp_mutton=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_mutton));
	bmp_chunk=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_chunk));
	bmp_1x1=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_1x1));
	bmp_2x1=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_2x1));
	bmp_arrow=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_arrow));
	bmp_monster1=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_MONSTER1));
	bmp_monster2=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_MONSTER2));
	bmp_monster3=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_MONSTER3));
	bmp_transparent=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_transparent));
	bmp_FLASH=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_FLASH));
	bmp_select=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_SELECT));
	bmp_first=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_first));
	bmp_second=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_second));
	bmp_play=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_PLAY));
	bmp_left=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_left));
	bmp_right=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_right));
	bmp_gonglue=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_gonglue));
	bmp_victory=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_victory));
	bmp_acknowledge=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_acknowledge));
	//添加按钮
	
	Button* startButton = CreateButton(BUTTON_STARTGAME, bmp_STARTGAME, BUTTON_STARTGAME_WIDTH, BUTTON_STARTGAME_HEIGHT,
		(WINDOW_WIDTH - BUTTON_STARTGAME_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_STARTGAME_HEIGHT) / 2);
	buttons.push_back(startButton);
	Button* helpButton = CreateButton(BUTTON_HELP, bmp_HELP, BUTTON_HELP_WIDTH, BUTTON_HELP_HEIGHT,
		(WINDOW_WIDTH - BUTTON_HELP_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_HELP_HEIGHT) / 2-100);
	buttons.push_back(helpButton);
	Button* returnButton = CreateButton(BUTTON_RETURN, bmp_RETURN, BUTTON_RETURN_WIDTH, BUTTON_RETURN_HEIGHT,
		(WINDOW_WIDTH - BUTTON_RETURN_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_RETURN_HEIGHT) / 2+30);
	buttons.push_back(returnButton);
	Button* restartButton = CreateButton(BUTTON_RESTART, bmp_RESTART, BUTTON_RESTART_WIDTH, BUTTON_RESTART_HEIGHT,
		(WINDOW_WIDTH - BUTTON_RESTART_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_RESTART_HEIGHT) / 2-80);
	buttons.push_back(restartButton);
	Button* return1Button = CreateButton(BUTTON_RETURN1, bmp_RETURN1, BUTTON_RETURN1_WIDTH, BUTTON_RETURN1_HEIGHT,
		(WINDOW_WIDTH - BUTTON_RETURN1_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_RETURN1_HEIGHT) / 2-10);
	buttons.push_back(return1Button);
	Button* resumeButton = CreateButton(BUTTON_RESUME, bmp_RESUME, BUTTON_RESUME_WIDTH, BUTTON_RESUME_HEIGHT,
		(WINDOW_WIDTH - BUTTON_RESUME_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_RESUME_HEIGHT) / 2+60);
	buttons.push_back(resumeButton);
	Button* secondButton = CreateButton(BUTTON_SECOND, bmp_second, BUTTON_NEXT_WIDTH+3, BUTTON_NEXT_HEIGHT-1,
		(WINDOW_WIDTH - BUTTON_RESUME_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_RESUME_HEIGHT) / 2+60);
	buttons.push_back(secondButton);
	Button* firstButton = CreateButton(BUTTON_FIRST, bmp_first, BUTTON_NEXT_WIDTH+3, BUTTON_NEXT_HEIGHT-1,
		(WINDOW_WIDTH - BUTTON_RESUME_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_RESUME_HEIGHT) / 2-60);
	buttons.push_back(firstButton);
		Button* leftButton = CreateButton(BUTTON_LEFT, bmp_left, 150, 70,
		0, 0);
	buttons.push_back(leftButton);
	Button* rightButton = CreateButton(BUTTON_RIGHT, bmp_right, 150, 70,WINDOW_WIDTH-150, 0);
	buttons.push_back(rightButton);
	Button* nextButton = CreateButton(BUTTON_NEXT, bmp_NEXT, 337, 61,(WINDOW_WIDTH - BUTTON_NEXT_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_NEXT_HEIGHT) / 2+60);
	buttons.push_back(nextButton);
	
	//初始化开始场景
	InitStage(hWnd, STAGE_STARTMENU);
	


	//初始化主计时器
	SetTimer(hWnd, TIMER_GAMETIMER, TIMER_GAMETIMER_ELAPSE, NULL);
	
}

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case VK_UP:
		keyUpDown = true;
		break;
	case VK_DOWN:
		keyDownDown = true;
		break;
	case VK_LEFT:
		keyLeftDown = true;
		break;
	case VK_RIGHT:
		keyRightDown = true;
		break;
	case 'A':
		keyADown=true;
		break;
	case 'W':
		keyWDown=true;
		break;
	case 'D':
		keyDDown=true;
		break;
	case ' ':
		keyspaceDown=true;
		break;
	case 27:
		keyescDown=true;
		break;
	case 'S':
		keySDown=true;
		break;
	case 'K':
		keyKDown=true;
		break;
	case 'F':
		keyFDown=true;
	default:
		break;
	}
}

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	// TODO
	switch (wParam)
	{
	case VK_UP:
		keyUpDown = false;
		break;
	case VK_DOWN:
		keyDownDown = false;
		break;
	case VK_LEFT:
		keyLeftDown = false;
		break;
	case VK_RIGHT:
		keyRightDown = false;
		break;
	case 'A':
		keyADown=false;
		break;
	case 'W':
		keyWDown=false;
		break;
	case 'D':
		keyDDown=false;
		break;
	case ' ':
		keyspaceDown=false;
		break;
	case 27:
		keyescDown=false;
		break;
	case 'S':
		keySDown=false;
		break;
	case'K':
		keyKDown=false;
		break;
	case 'F':
		keyFDown=false;
	default:
		break;
	}
}

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
}

// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = true;

	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->visible)
		{
			if (button->x <= mouseX
				&& button->x + button->width >= mouseX
				&& button->y <= mouseY
				&& button->y + button->height >= mouseY)
			{
				switch (button->buttonID) {
				case BUTTON_STARTGAME:
				{

				InitStage(hWnd,STAGE_SELECT);
					break;
				}
				case BUTTON_HELP:
					{
					    InitStage(hWnd,STAGE_HELP);
						break;
					}
				case BUTTON_RETURN:
					{
					InitStage(hWnd, STAGE_STARTMENU);
					break;
					
					}
				case BUTTON_RESTART:
					{
						if(stage==STAGE_1)
						{
							RestartStage(hWnd, STAGE_1);
						}
						if(stage==STAGE_2)
						{
							RestartStage(hWnd, STAGE_2);
						}
					break;
					}
				case BUTTON_RESUME:
					{
						if(stage==STAGE_1)
						{
							ResumeStage(hWnd, STAGE_1);
						}
							if(stage==STAGE_2)
						{
							ResumeStage(hWnd, STAGE_2);
						}
					break;
					}
				case BUTTON_RETURN1:
					{
					InitStage(hWnd, STAGE_STARTMENU);
					break;
					}
				case BUTTON_NEXT:
					InitStage(hWnd,STAGE_2);
					break;
				case BUTTON_SECOND:
					if(stage!=STAGE_1&&stage!=STAGE_2)
					{
					InitStage(hWnd,STAGE_2);
					}
					else
					{
						RestartStage(hWnd,STAGE_2);
					}
					break;
				case BUTTON_FIRST:
					if(stage!=STAGE_1&&stage!=STAGE_2)
					{
					InitStage(hWnd,STAGE_1);
					}
					else
					{
						RestartStage(hWnd,STAGE_1);
					}
					break;
				case BUTTON_LEFT:
					key++;
					if(stage==STAGE_gonglue&&key==1)
					{
						InitStage(hWnd,STAGE_caozuo);
						key=0;
					}
					if(stage==STAGE_caozuo&&key==1)
					{
						InitStage(hWnd,STAGE_HELP);
						key=0;
					}
					if(stage==STAGE_acknowledge&&key==1)
					{
						InitStage(hWnd,STAGE_victory);
						key=0;
					}
					break;
				case BUTTON_RIGHT:
					key1++;
					if(stage==STAGE_HELP&&key1==1)
					{
						InitStage(hWnd,STAGE_caozuo);
						key1=0;
					}
					if(stage==STAGE_caozuo&&key1==1)
					{
						InitStage(hWnd,STAGE_gonglue);
						key1=0;
					}
					if(stage==STAGE_victory&&key1==1)
					{
						InitStage(hWnd,STAGE_acknowledge);
						key1=0;
					}
					break;
					}
				}
			}
		}
	}



// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = false;
}

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	UpdateUnits(hWnd);

	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}


#pragma endregion


#pragma region 其它游戏状态处理函数



//TODO: 添加游戏需要的更多函数

// 添加按钮函数
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y)
{
	Button* button = new Button();
	button->buttonID = buttonID;
	button->img = img;
	button->width = width;
	button->height = height;
	button->x = x;
	button->y = y;

	button->visible = false;
	return button;
}
//添加障碍函数
Obstacle* CreatObstacle(int obstacleID,HBITMAP img,int x,int y,int width,int height)
{
	Obstacle*obstacle=new Obstacle();
	obstacle->obstacleID=obstacleID;
	obstacle->img=img;
	obstacle->x=x;
	obstacle->y=y;
	obstacle->height=height;
	obstacle->width=width;
	obstacle->visible=true;
	return obstacle;

}
//添加道具函数
Prop* CreatProp(int propID,HBITMAP img,int x,int y,int width,int height,bool visible)
{
	Prop*prop=new Prop();
	prop->propID=propID;
	prop->img=img;
	prop->x=x;
	prop->y=y;
	prop->length=height;
	prop->width=width;
	prop->visible=visible;
	return prop;

}
//添加角色函数
Unit* CreateUnit(int side, int state, int x, int y, int health)
{
	Unit* unit = new Unit();
	unit->side = side;
	if (side == UNIT_SIDE_RED) {
		unit->img = bmp_YELLOW;
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	else if (side == UNIT_SIDE_BLUE) {
		unit->img = bmp_Unit_Blue;
		unit->direction = UNIT_DIRECT_LEFT;
	}

	unit->state = state;

	unit->width=50;
	unit->length=63;
	unit->frame_row =3;
	unit->frame_column = UNIT_LAST_FRAME * unit->direction;

	unit->frame_sequence = FRAMES_HOLD;
	unit->frame_count = FRAMES_HOLD_COUNT;
	unit->frame_id = 0;
	unit->visible=true;
	unit->x = x;
	unit->y = y;
	unit->vx = 0;
	unit->vy = 0;
	unit->health = health;
	bool sky=false;
	return unit;
}
Monster*CreatMonster(HBITMAP img,int ID,int state,int direction,int x,int y, int r,double vx,double vy)
{
	Monster*monster=new Monster();
	monster->img=img;
	monster->ID=ID;
	monster->state=state;
	monster->direction=direction;
	monster->x=x;
	monster->y=y;
	monster->r=10;
	monster->vx=vx;
	monster->vy=vy;
	return monster;
}
//添加屏幕提示函数
Showscreen* CreatShowscreen(int showscreenID,HBITMAP img,int x,int y,int width,int length,bool visible)
{
	Showscreen*showscreen= new Showscreen();
	showscreen->img=img;
	showscreen->x=x;
	showscreen->y=y;
	showscreen->width=width;
	showscreen->length=length;
	showscreen->visible=visible;
	return showscreen;
}





//重新开始游戏函数
int RestartStage(HWND hWnd,int stageID)
{
	if (currentStage != NULL) delete currentStage;
	currentStage = new Stage();
	currentStage->stageID = stageID;


	if (stageID == STAGE_1) //TODO：添加多个游戏场景
	{
		stage=currentStage->stageID;
		currentStage->bg = bmp_ONE;
		currentStage->timeCountDown = 10000;
		currentStage->timerOn = true;
		//使角色不可见
		for (int i = 0; i < units.size(); i++)
		{
			Unit* unit = units[i];
			unit->visible=false;
		}
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			button->visible=false;
		}

		// 按场景初始化单位
		switch (stageID) {
		case STAGE_1:
			{
			stage=currentStage->stageID;
		currentStage->bg = bmp_ONE;
		currentStage->timeCountDown = 10000;
		currentStage->timerOn = true;
		
		//显示游戏界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			button->visible=false;
		}
					for(int i=0;i<units.size();i++)
					{
						delete units[i];
					}
					units.clear();
					unit1=CreateUnit(UNIT_SIDE_RED, UNIT_TYPE_WALK, 0, WINDOW_HEIGHT-3*63, 100);
					unit2=CreateUnit(UNIT_SIDE_BLUE, UNIT_TYPE_WALK, 27*63,WINDOW_HEIGHT-3*63, 100);
					units.push_back(unit1);
					units.push_back(unit2);
					if(stage>0)
					{
						showscreens.clear();
						props.clear();
						obstacles.clear();
		
					}
					//添加障碍物
					Obstacle*FLOOR=CreatObstacle(1,NULL,0,WINDOW_HEIGHT-2*63,1890,2*63);
					obstacles.push_back(FLOOR);
					Obstacle*stone1x1_1=CreatObstacle(1,bmp_STONE1x1,252,WINDOW_HEIGHT-189,63,63);
					obstacles.push_back(stone1x1_1);
					Obstacle*stone1x1_2=CreatObstacle(1,bmp_STONE1x1,11*63,3*63,63,63);
					obstacles.push_back(stone1x1_2);
					Obstacle*stone1x1_3=CreatObstacle(1,bmp_STONE1x1,63*12,3*63,63,63);
					obstacles.push_back(stone1x1_3);
					Obstacle*stone1x1_4=CreatObstacle(1,bmp_STONE1x1,13*63,WINDOW_HEIGHT-63*6,63,63);
					obstacles.push_back(stone1x1_4);
					Obstacle*stone1x1_5=CreatObstacle(1,bmp_STONE1x1,18*63,WINDOW_HEIGHT-5*63,63,63);
					obstacles.push_back(stone1x1_5);
					Obstacle*stone1x1_6=CreatObstacle(1,bmp_STONE1x1,20*63,WINDOW_HEIGHT-5*63,63,63);
					obstacles.push_back(stone1x1_6);
					Obstacle*stone1x1_7=CreatObstacle(1,bmp_STONE1x1,7*63,WINDOW_HEIGHT-5*63,63,63);
					obstacles.push_back(stone1x1_7);
					Obstacle*stone2x1_1=CreatObstacle(1,bmp_STONE2x1,5*63,WINDOW_HEIGHT-4*63,63,63*2);
					obstacles.push_back(stone2x1_1);
					Obstacle*stone2x1_2=CreatObstacle(1,bmp_STONE2x1,10*63,0,63,63*2);
					obstacles.push_back(stone2x1_2);
					Obstacle*stone2x1_3=CreatObstacle(1,bmp_STONE2x1,10*63,2*63,63,63*2);
					obstacles.push_back(stone2x1_3);
					Obstacle*stone2x1_4=CreatObstacle(1,bmp_STONE2x1,22*63,WINDOW_HEIGHT-4*63,63,63*2);
					obstacles.push_back(stone2x1_4);
					Obstacle*stone2x1_5=CreatObstacle(1,bmp_STONE2x1,9*63,WINDOW_HEIGHT-4*63,63,63*2);
					obstacles.push_back(stone2x1_5);
					Obstacle*stone3x2_1=CreatObstacle(1,bmp_STONE3x2,15*63,WINDOW_HEIGHT-5*63,123,63*3);
					obstacles.push_back(stone3x2_1);
					Obstacle*LADDER_1=CreatObstacle(3,bmp_LADDER,14*63,WINDOW_HEIGHT-5*63,63,63*3);
					obstacles.push_back(LADDER_1);
					Obstacle*SNAG3x1=CreatObstacle(2,bmp_SNAG3x1,6*63,WINDOW_HEIGHT-3*63,3*63,63);
					obstacles.push_back(SNAG3x1);
					Obstacle*SNAG5x1=CreatObstacle(2,bmp_SNAG5x1,17*63,WINDOW_HEIGHT-3*63,5*63,63);
					obstacles.push_back(SNAG5x1);
			  					//添加道具
					Prop*box=CreatProp(1,bmp_PROP_BOX,12*63,2*63,63,63,true);
					props.push_back(box);
					Prop*SWITCH=CreatProp(2,bmp_PROP_SWITCH,22*63,WINDOW_HEIGHT-5*63,63,63,true);
					props.push_back(SWITCH);
					Prop*REDKEY=CreatProp(3,bmp_PROP_REDKEY,7*63,3*63,63,63,true);
					props.push_back(REDKEY);
					Prop*BLUEKEY=CreatProp(4,bmp_PROP_BLUEKEY,11*63,2*63,63,63,true);
					props.push_back(BLUEKEY);
					Prop*GREENKEY=CreatProp(5,bmp_PROP_GREENKEY,13*63,7*63,63,63,true);
					props.push_back(GREENKEY);
					Prop*YELLOWKEY=CreatProp(6,bmp_PROP_YELLOWKEY,28*63,7*63,63,63,false);
					props.push_back(YELLOWKEY);
					Prop*SWITCH1=CreatProp(7,bmp_SWITCH1,22*63,WINDOW_HEIGHT-5*63,63,63,false);
					props.push_back(SWITCH1);
					//添加屏幕提示
					Showscreen*showREDKEY=CreatShowscreen(1,bmp_PROP_REDKEY,0,0,63,63,false);
					showscreens.push_back(showREDKEY);
					Showscreen*showGREENKEY=CreatShowscreen(1,bmp_PROP_GREENKEY,63,0,63,63,false);
					showscreens.push_back(showGREENKEY);
					Showscreen*showBLUEKEY=CreatShowscreen(1,bmp_PROP_BLUEKEY,126,0,63,63,false);
					showscreens.push_back(showBLUEKEY);
					Showscreen*showYELLOWKEY=CreatShowscreen(1,bmp_PROP_YELLOWKEY,189,0,63,63,false);
					showscreens.push_back(showYELLOWKEY);


					Showscreen*SHOWREDKEY=CreatShowscreen(2,bmp_SHOWREDKEY,0,0,63,63,true);
					showscreens.push_back(SHOWREDKEY);
					Showscreen*SHOWGREENKEY=CreatShowscreen(2,bmp_SHOWGREENKEY,63,0,63,63,true);
					showscreens.push_back(SHOWGREENKEY);
					Showscreen*SHOWBLUEKEY=CreatShowscreen(2,bmp_SHOWBLUEKEY,126,0,63,63,true);
					showscreens.push_back(SHOWBLUEKEY);
					Showscreen*SHOWYELLOWKEY=CreatShowscreen(2,bmp_SHOWYELLOWKEY,189,0,63,63,true);
					showscreens.push_back(SHOWYELLOWKEY);


					Showscreen*FULLHEALTH1=CreatShowscreen(3,bmp_FULLHEALTH,0,63,63,63,true);
					showscreens.push_back(FULLHEALTH1);
					Showscreen*HALFHEALTH1=CreatShowscreen(3,bmp_HALFHEALTH,0,63,63,63,false);
					showscreens.push_back(HALFHEALTH1);
					Showscreen*ZEROHEATH1=CreatShowscreen(3,bmp_ZEROHEALTH,0,63,63,63,false);
					showscreens.push_back(ZEROHEATH1);


					Showscreen*FULLHEALTH2=CreatShowscreen(3,bmp_FULLHEALTH,63,63,63,63,true);
					showscreens.push_back(FULLHEALTH2);
					Showscreen*HALFHEALTH2=CreatShowscreen(3,bmp_HALFHEALTH,63,63,63,63,false);
					showscreens.push_back(HALFHEALTH2);
					Showscreen*ZEROHEATH2=CreatShowscreen(3,bmp_ZEROHEALTH,63,63,63,63,false);
					showscreens.push_back(ZEROHEATH2);


					Showscreen*FULLHEALTH3=CreatShowscreen(3,bmp_FULLHEALTH,126,63,63,63,true);
					showscreens.push_back(FULLHEALTH3);
					Showscreen*HALFHEALTH3=CreatShowscreen(3,bmp_HALFHEALTH,126,63,63,63,false);
					showscreens.push_back(HALFHEALTH3);
					Showscreen*ZEROHEATH3=CreatShowscreen(3,bmp_ZEROHEALTH,126,63,63,63,false);
					showscreens.push_back(ZEROHEATH3);

			break;
			}
		default:
			break;
		}

	}
	if (stageID == STAGE_2)
	{
		health1=true;
		flash=false;
		timecount2=0;
		timecount3=0;
		timecount4=0;
		timecount5=0;
		monsters1=false;
		num3=0;
		stage=currentStage->stageID;
					currentStage->bg = bmp_TWO;
					currentStage->timeCountDown = 10000;
					currentStage->timerOn = true;
					//显示游戏界面的按钮
					for (int i = 0; i < buttons.size(); i++)
					{
						buttons[i]->visible=false;
					}
					units.clear();
					obstacles.clear();
					props.clear();
					showscreens.clear();
					if(monsters.size()!=0)
					{
						monsters.clear();
					}
					monster1=CreatMonster(bmp_monster1,1,MONSTER_STATE_HOLD,MONSTER_DIRECT_LEFT,18*63+21,7*63+21+21,21,0.5,0);
					monsters.push_back(monster1);
					monster2=CreatMonster(bmp_monster2,2,MONSTER_STATE_HOLD,MONSTER_DIRECT_LEFT,20*63+21,7*63+21+21,21,0.5,0);
					monsters.push_back(monster2);
					monster3=CreatMonster(bmp_monster3,3,MONSTER_STATE_HOLD,MONSTER_DIRECT_LEFT,28*63+21,7*63+21+21,21,0.5,0);
					monsters.push_back(monster3);
					unit1=CreateUnit(UNIT_SIDE_RED, UNIT_TYPE_WALK, 0, WINDOW_HEIGHT-5*63, 100);
					unit2=CreateUnit(UNIT_SIDE_BLUE, UNIT_TYPE_WALK, 37*63,WINDOW_HEIGHT-3*63, 100);
					units.push_back(unit1);
					units.push_back(unit2);	 
					//添加屏幕提示
					Showscreen*showREDKEY=CreatShowscreen(1,bmp_PROP_REDKEY,0,0,63,63,false);
					showscreens.push_back(showREDKEY);
					Showscreen*showGREENKEY=CreatShowscreen(1,bmp_PROP_GREENKEY,63,0,63,63,false);
					showscreens.push_back(showGREENKEY);
					Showscreen*showBLUEKEY=CreatShowscreen(1,bmp_PROP_BLUEKEY,126,0,63,63,false);
					showscreens.push_back(showBLUEKEY);
					Showscreen*showYELLOWKEY=CreatShowscreen(1,bmp_PROP_YELLOWKEY,189,0,63,63,false);
					showscreens.push_back(showYELLOWKEY);


					Showscreen*SHOWREDKEY=CreatShowscreen(2,bmp_SHOWREDKEY,0,0,63,63,true);
					showscreens.push_back(SHOWREDKEY);
					Showscreen*SHOWGREENKEY=CreatShowscreen(2,bmp_SHOWGREENKEY,63,0,63,63,true);
					showscreens.push_back(SHOWGREENKEY);
					Showscreen*SHOWBLUEKEY=CreatShowscreen(2,bmp_SHOWBLUEKEY,126,0,63,63,true);
					showscreens.push_back(SHOWBLUEKEY);
					Showscreen*SHOWYELLOWKEY=CreatShowscreen(2,bmp_SHOWYELLOWKEY,189,0,63,63,true);
					showscreens.push_back(SHOWYELLOWKEY);


					Showscreen*FULLHEALTH1=CreatShowscreen(3,bmp_FULLHEALTH,0,63,63,63,true);
					showscreens.push_back(FULLHEALTH1);
					Showscreen*HALFHEALTH1=CreatShowscreen(3,bmp_HALFHEALTH,0,63,63,63,false);
					showscreens.push_back(HALFHEALTH1);
					Showscreen*ZEROHEATH1=CreatShowscreen(3,bmp_ZEROHEALTH,0,63,63,63,false);
					showscreens.push_back(ZEROHEATH1);


					Showscreen*FULLHEALTH2=CreatShowscreen(3,bmp_FULLHEALTH,63,63,63,63,true);
					showscreens.push_back(FULLHEALTH2);
					Showscreen*HALFHEALTH2=CreatShowscreen(3,bmp_HALFHEALTH,63,63,63,63,false);
					showscreens.push_back(HALFHEALTH2);
					Showscreen*ZEROHEATH2=CreatShowscreen(3,bmp_ZEROHEALTH,63,63,63,63,false);
					showscreens.push_back(ZEROHEATH2);


					Showscreen*FULLHEALTH3=CreatShowscreen(3,bmp_FULLHEALTH,126,63,63,63,true);
					showscreens.push_back(FULLHEALTH3);
					Showscreen*HALFHEALTH3=CreatShowscreen(3,bmp_HALFHEALTH,126,63,63,63,false);
					showscreens.push_back(HALFHEALTH3);
					Showscreen*ZEROHEATH3=CreatShowscreen(3,bmp_ZEROHEALTH,126,63,63,63,false);
					showscreens.push_back(ZEROHEATH3);
					//添加障碍物
					Obstacle*TWO_1=CreatObstacle(1,NULL,0,6*63,4*63,4*63);
					obstacles.push_back(TWO_1);
					Obstacle*TWO_2=CreatObstacle(2,NULL,6*63,8*63,34*63,2*63);
					obstacles.push_back(TWO_2);
					Obstacle*LADDER_2=CreatObstacle(3,bmp_LADDER2,8*63,4*63,63,63*4);
	               obstacles.push_back(LADDER_2);
					Obstacle*LADDER_3=CreatObstacle(4,bmp_LADDER2,15*63,4*63,63,63*4);
	               obstacles.push_back(LADDER_3);
				   Obstacle*stone1x1=CreatObstacle(5,bmp_1x1,63*14,4*63,63,63);
					obstacles.push_back(stone1x1);
					Obstacle*stone1x1_2=CreatObstacle(6,bmp_STONE1x1,21*63,4*63,63,63);
					obstacles.push_back(stone1x1_2);
					Obstacle*SHIFT=CreatObstacle(7,bmp_SHIFT,63*9,4*63,63*5,63);
					obstacles.push_back(SHIFT);
					Obstacle*stone1x1_3=CreatObstacle(8,bmp_STONE1x1,63*33,5*63,63,63);
					obstacles.push_back(stone1x1_3);
					Obstacle*stone2x1_1=CreatObstacle(9,bmp_STONE2x1,34*63,4*63,63,63*2);
					obstacles.push_back(stone2x1_1);
					Obstacle*stone3x2_1=CreatObstacle(10,bmp_STONE3x2,23*63,5*63,123,63*3);
					obstacles.push_back(stone3x2_1);
					Obstacle*LADDER_1=CreatObstacle(11,bmp_LADDER,22*63,5*63,63,63*3);
	                obstacles.push_back(LADDER_1);
					Obstacle*stone2x1_2=CreatObstacle(12,bmp_1x1,31*63,7*63,63,63);
					obstacles.push_back(stone2x1_2);
					Obstacle*stone1x1_4=CreatObstacle(13,bmp_STONE1x1,63*31,3*63,63,63);
					obstacles.push_back(stone1x1_3);
					Obstacle*stone1x1_5=CreatObstacle(14,bmp_STONE1x1,63*32,3*63,63,63);
					obstacles.push_back(stone1x1_3);
					Obstacle*mutton=CreatObstacle(15,bmp_mutton,63*26,4*63,63*3,63);
					obstacles.push_back(mutton);
					Obstacle*x1=CreatObstacle(16,bmp_1x1,63*30,3*63,63,63);
					x1->visible=false;
					obstacles.push_back(x1);
					Obstacle*x2=CreatObstacle(17,bmp_2x1,63*31,3*63,63*2,63);
					obstacles.push_back(x2);
					Obstacle*chunk=CreatObstacle(18,bmp_chunk,63*27,5*63,63,3*63);
					obstacles.push_back(chunk);
					Obstacle*myster=CreatObstacle(19,bmp_myster,63*11,7*63,63,63);
					obstacles.push_back(myster);
					Obstacle*myster1=CreatObstacle(20,bmp_myster,63*19,4.8*63,63,63);
					obstacles.push_back(myster1);
					Obstacle*myster2=CreatObstacle(21,bmp_myster,63*27,63,63,63);
					obstacles.push_back(myster2);
					Obstacle*transparent=CreatObstacle(22,bmp_transparent,63*14,63*5,63,63*3);
					obstacles.push_back(transparent);
					transparent->visible=false;
				   //添加道具
					Prop*arrow=CreatProp(1,bmp_arrow,31*63,63*2,63,63,true);
					props.push_back(arrow);
					Prop*REDKEY=CreatProp(2,bmp_PROP_REDKEY,14*63,3*63,63,63,true);
					props.push_back(REDKEY);
					Prop*BLUEKEY=CreatProp(3,bmp_PROP_BLUEKEY,19*63,3.5*63,63,63,false);
					props.push_back(BLUEKEY);
					Prop*GREENKEY=CreatProp(4,bmp_PROP_GREENKEY,29*63,5*63,63,63,true);
					props.push_back(GREENKEY);
					Prop*YELLOWKEY=CreatProp(5,bmp_PROP_YELLOWKEY,39*63,7*63,63,63,false);
					props.push_back(YELLOWKEY);
					Prop*FLASH=CreatProp(6,bmp_FLASH,13*63,7*63,42,42,false);
					props.push_back(FLASH);
	}
	return stageID;
	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);

}
//恢复游戏场景函数
int ResumeStage(HWND hWnd,int stageID)
{
	if (currentStage != NULL) delete currentStage;
	currentStage = new Stage();
	currentStage->stageID = stageID;


	
	
	if (stageID == STAGE_1) //TODO：添加多个游戏场景
	{
		currentStage->bg = bmp_ONE;
		currentStage->timeCountDown = 10000;
		currentStage->timerOn = true;
	}
	if (stageID == STAGE_2) //TODO：添加多个游戏场景
	{
		currentStage->bg = bmp_TWO;
		currentStage->timeCountDown = 10000;
		currentStage->timerOn = true;
	}
	for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			button->visible = false;
		}
	return stageID;
	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);

}
void FailStage(HWND hWnd)
{
	stage=currentStage->stageID;
	if (currentStage != NULL) delete currentStage;
	currentStage = new Stage();
	currentStage->bg = bmp_FAIL;

	for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_RESTART||button->buttonID == BUTTON_RETURN1)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}

	
	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}
void CongratulationStage(HWND hWnd)
{
	stage=currentStage->stageID;
	if (currentStage != NULL) delete currentStage;
	currentStage = new Stage();
	currentStage->bg = bmp_CONGRATULATIONS;

	for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_RESTART||button->buttonID == BUTTON_RETURN1||button->buttonID == BUTTON_NEXT)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}

	
	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}
// 初始化游戏场景函数
void InitStage(HWND hWnd, int stageID)
{

	// 初始化场景实例
	if (currentStage != NULL) delete currentStage;
	currentStage = new Stage();
	currentStage->stageID = stageID;


	if (stageID == STAGE_STARTMENU) 
	{
		currentStage->bg = bmp_Background;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;

		//显示开始界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_STARTGAME||button->buttonID == BUTTON_HELP)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}


	}
	if (stageID == STAGE_victory) 
	{
		currentStage->bg = bmp_victory;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;

		//显示开始界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_RIGHT)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}


	}
	if (stageID == STAGE_acknowledge) 
	{
		stage=STAGE_acknowledge;
		currentStage->bg = bmp_acknowledge;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;

		//显示开始界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_LEFT||button->buttonID == BUTTON_RETURN)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}


	}
	 if(stageID==STAGE_SELECT)
	{
		currentStage->bg=bmp_select;
		currentStage->timeCountDown=0;
		currentStage->timerOn = false;
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_FIRST||button->buttonID==BUTTON_SECOND)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
	}
	else if(stageID==STAGE_HELP)
	{
		stage=STAGE_HELP;
		currentStage->bg=bmp_play;
		currentStage->timeCountDown=0;
		currentStage->timerOn = false;
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_RETURN||button->buttonID == BUTTON_RIGHT)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}

	}
	 else if(stageID==STAGE_caozuo)
	{
		stage=STAGE_caozuo;
		currentStage->bg=bmp_HELPFACE;
		currentStage->timeCountDown=0;
		currentStage->timerOn = false;
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_RETURN||button->buttonID == BUTTON_RIGHT||button->buttonID == BUTTON_LEFT)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}

	}
	else if(stageID==STAGE_gonglue)
	{
		stage=STAGE_gonglue;
		currentStage->bg=bmp_gonglue;
		currentStage->timeCountDown=0;
		currentStage->timerOn = false;
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_RETURN||button->buttonID == BUTTON_LEFT)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}

	}
	else if(stageID==STAGE_PAUSE)
	{
		currentStage->bg=bmp_PAUSE;
		currentStage->timeCountDown=0;
		currentStage->timerOn = false;
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_RESTART||button->buttonID == BUTTON_RESUME||button->buttonID == BUTTON_RETURN1)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}

	}
	
	else if (stageID == STAGE_1) 
	{
		stage=currentStage->stageID;
		currentStage->bg = bmp_ONE;
		currentStage->timeCountDown = 10000;
		currentStage->timerOn = true;
		
		//显示游戏界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			button->visible=false;
		}
					for(int i=0;i<units.size();i++)
					{
						delete units[i];
					}
					units.clear();
					unit1=CreateUnit(UNIT_SIDE_RED, UNIT_TYPE_WALK, 0, WINDOW_HEIGHT-3*63, 100);
					unit2=CreateUnit(UNIT_SIDE_BLUE, UNIT_TYPE_WALK, 27*63,WINDOW_HEIGHT-3*63, 100);
					units.push_back(unit1);
					units.push_back(unit2);
					if(stage>0)
					{
						showscreens.clear();
						props.clear();
						obstacles.clear();
		
					}
					//添加障碍物
					Obstacle*FLOOR=CreatObstacle(1,NULL,0,WINDOW_HEIGHT-2*63,1890,2*63);
					obstacles.push_back(FLOOR);
					Obstacle*stone1x1_1=CreatObstacle(1,bmp_STONE1x1,252,WINDOW_HEIGHT-189,63,63);
					obstacles.push_back(stone1x1_1);
					Obstacle*stone1x1_2=CreatObstacle(1,bmp_STONE1x1,11*63,3*63,63,63);
					obstacles.push_back(stone1x1_2);
					Obstacle*stone1x1_3=CreatObstacle(1,bmp_STONE1x1,63*12,3*63,63,63);
					obstacles.push_back(stone1x1_3);
					Obstacle*stone1x1_4=CreatObstacle(1,bmp_STONE1x1,13*63,WINDOW_HEIGHT-63*6,63,63);
					obstacles.push_back(stone1x1_4);
					Obstacle*stone1x1_5=CreatObstacle(1,bmp_STONE1x1,18*63,WINDOW_HEIGHT-5*63,63,63);
					obstacles.push_back(stone1x1_5);
					Obstacle*stone1x1_6=CreatObstacle(1,bmp_STONE1x1,20*63,WINDOW_HEIGHT-5*63,63,63);
					obstacles.push_back(stone1x1_6);
					Obstacle*stone1x1_7=CreatObstacle(1,bmp_STONE1x1,7*63,WINDOW_HEIGHT-5*63,63,63);
					obstacles.push_back(stone1x1_7);
					Obstacle*stone2x1_1=CreatObstacle(1,bmp_STONE2x1,5*63,WINDOW_HEIGHT-4*63,63,63*2);
					obstacles.push_back(stone2x1_1);
					Obstacle*stone2x1_2=CreatObstacle(1,bmp_STONE2x1,10*63,0,63,63*2);
					obstacles.push_back(stone2x1_2);
					Obstacle*stone2x1_3=CreatObstacle(1,bmp_STONE2x1,10*63,2*63,63,63*2);
					obstacles.push_back(stone2x1_3);
					Obstacle*stone2x1_4=CreatObstacle(1,bmp_STONE2x1,22*63,WINDOW_HEIGHT-4*63,63,63*2);
					obstacles.push_back(stone2x1_4);
					Obstacle*stone2x1_5=CreatObstacle(1,bmp_STONE2x1,9*63,WINDOW_HEIGHT-4*63,63,63*2);
					obstacles.push_back(stone2x1_5);
					Obstacle*stone3x2_1=CreatObstacle(1,bmp_STONE3x2,15*63,WINDOW_HEIGHT-5*63,123,63*3);
					obstacles.push_back(stone3x2_1);
					Obstacle*LADDER_1=CreatObstacle(3,bmp_LADDER,14*63,WINDOW_HEIGHT-5*63,63,63*3);
					obstacles.push_back(LADDER_1);
					Obstacle*SNAG3x1=CreatObstacle(2,bmp_SNAG3x1,6*63,WINDOW_HEIGHT-3*63,3*63,63);
					obstacles.push_back(SNAG3x1);
					Obstacle*SNAG5x1=CreatObstacle(2,bmp_SNAG5x1,17*63,WINDOW_HEIGHT-3*63,5*63,63);
					obstacles.push_back(SNAG5x1);
			  					//添加道具
					Prop*box=CreatProp(1,bmp_PROP_BOX,12*63,2*63,63,63,true);
					props.push_back(box);
					Prop*SWITCH=CreatProp(2,bmp_PROP_SWITCH,22*63,WINDOW_HEIGHT-5*63,63,63,true);
					props.push_back(SWITCH);
					Prop*REDKEY=CreatProp(3,bmp_PROP_REDKEY,7*63,3*63,63,63,true);
					props.push_back(REDKEY);
					Prop*BLUEKEY=CreatProp(4,bmp_PROP_BLUEKEY,11*63,2*63,63,63,true);
					props.push_back(BLUEKEY);
					Prop*GREENKEY=CreatProp(5,bmp_PROP_GREENKEY,13*63,7*63,63,63,true);
					props.push_back(GREENKEY);
					Prop*YELLOWKEY=CreatProp(6,bmp_PROP_YELLOWKEY,28*63,7*63,63,63,false);
					props.push_back(YELLOWKEY);
					Prop*SWITCH1=CreatProp(7,bmp_SWITCH1,22*63,WINDOW_HEIGHT-5*63,63,63,false);
					props.push_back(SWITCH1);
					//添加屏幕提示
					Showscreen*showREDKEY=CreatShowscreen(1,bmp_PROP_REDKEY,0,0,63,63,false);
					showscreens.push_back(showREDKEY);
					Showscreen*showGREENKEY=CreatShowscreen(1,bmp_PROP_GREENKEY,63,0,63,63,false);
					showscreens.push_back(showGREENKEY);
					Showscreen*showBLUEKEY=CreatShowscreen(1,bmp_PROP_BLUEKEY,126,0,63,63,false);
					showscreens.push_back(showBLUEKEY);
					Showscreen*showYELLOWKEY=CreatShowscreen(1,bmp_PROP_YELLOWKEY,189,0,63,63,false);
					showscreens.push_back(showYELLOWKEY);


					Showscreen*SHOWREDKEY=CreatShowscreen(2,bmp_SHOWREDKEY,0,0,63,63,true);
					showscreens.push_back(SHOWREDKEY);
					Showscreen*SHOWGREENKEY=CreatShowscreen(2,bmp_SHOWGREENKEY,63,0,63,63,true);
					showscreens.push_back(SHOWGREENKEY);
					Showscreen*SHOWBLUEKEY=CreatShowscreen(2,bmp_SHOWBLUEKEY,126,0,63,63,true);
					showscreens.push_back(SHOWBLUEKEY);
					Showscreen*SHOWYELLOWKEY=CreatShowscreen(2,bmp_SHOWYELLOWKEY,189,0,63,63,true);
					showscreens.push_back(SHOWYELLOWKEY);


					Showscreen*FULLHEALTH1=CreatShowscreen(3,bmp_FULLHEALTH,0,63,63,63,true);
					showscreens.push_back(FULLHEALTH1);
					Showscreen*HALFHEALTH1=CreatShowscreen(3,bmp_HALFHEALTH,0,63,63,63,false);
					showscreens.push_back(HALFHEALTH1);
					Showscreen*ZEROHEATH1=CreatShowscreen(3,bmp_ZEROHEALTH,0,63,63,63,false);
					showscreens.push_back(ZEROHEATH1);


					Showscreen*FULLHEALTH2=CreatShowscreen(3,bmp_FULLHEALTH,63,63,63,63,true);
					showscreens.push_back(FULLHEALTH2);
					Showscreen*HALFHEALTH2=CreatShowscreen(3,bmp_HALFHEALTH,63,63,63,63,false);
					showscreens.push_back(HALFHEALTH2);
					Showscreen*ZEROHEATH2=CreatShowscreen(3,bmp_ZEROHEALTH,63,63,63,63,false);
					showscreens.push_back(ZEROHEATH2);


					Showscreen*FULLHEALTH3=CreatShowscreen(3,bmp_FULLHEALTH,126,63,63,63,true);
					showscreens.push_back(FULLHEALTH3);
					Showscreen*HALFHEALTH3=CreatShowscreen(3,bmp_HALFHEALTH,126,63,63,63,false);
					showscreens.push_back(HALFHEALTH3);
					Showscreen*ZEROHEATH3=CreatShowscreen(3,bmp_ZEROHEALTH,126,63,63,63,false);
					showscreens.push_back(ZEROHEATH3);


	}
	else if(stageID==STAGE_2)
	{
					stage=currentStage->stageID;
					currentStage->bg = bmp_TWO;
					currentStage->timeCountDown = 10000;
					currentStage->timerOn = true;
					//显示游戏界面的按钮
					for (int i = 0; i < buttons.size(); i++)
					{
						buttons[i]->visible=false;
					}
					units.clear();
					obstacles.clear();
					props.clear();
					showscreens.clear();
					if(monsters.size()!=0)
					{
						monsters.clear();
					}
					monster1=CreatMonster(bmp_monster1,1,MONSTER_STATE_HOLD,MONSTER_DIRECT_LEFT,18*63+21,7*63+21+21,21,0.5,0);
					monsters.push_back(monster1);
					monster2=CreatMonster(bmp_monster2,2,MONSTER_STATE_HOLD,MONSTER_DIRECT_LEFT,20*63+21,7*63+21+21,21,0.5,0);
					monsters.push_back(monster2);
					monster3=CreatMonster(bmp_monster3,3,MONSTER_STATE_HOLD,MONSTER_DIRECT_LEFT,28*63+21,7*63+21+21,21,0.5,0);
					monsters.push_back(monster3);
					unit1=CreateUnit(UNIT_SIDE_RED, UNIT_TYPE_WALK, 0, WINDOW_HEIGHT-5*63, 100);
					unit2=CreateUnit(UNIT_SIDE_BLUE, UNIT_TYPE_WALK, 37*63,WINDOW_HEIGHT-3*63, 100);
					units.push_back(unit1);
					units.push_back(unit2);	 
					//添加屏幕提示
					Showscreen*showREDKEY=CreatShowscreen(1,bmp_PROP_REDKEY,0,0,63,63,false);
					showscreens.push_back(showREDKEY);
					Showscreen*showGREENKEY=CreatShowscreen(1,bmp_PROP_GREENKEY,63,0,63,63,false);
					showscreens.push_back(showGREENKEY);
					Showscreen*showBLUEKEY=CreatShowscreen(1,bmp_PROP_BLUEKEY,126,0,63,63,false);
					showscreens.push_back(showBLUEKEY);
					Showscreen*showYELLOWKEY=CreatShowscreen(1,bmp_PROP_YELLOWKEY,189,0,63,63,false);
					showscreens.push_back(showYELLOWKEY);


					Showscreen*SHOWREDKEY=CreatShowscreen(2,bmp_SHOWREDKEY,0,0,63,63,true);
					showscreens.push_back(SHOWREDKEY);
					Showscreen*SHOWGREENKEY=CreatShowscreen(2,bmp_SHOWGREENKEY,63,0,63,63,true);
					showscreens.push_back(SHOWGREENKEY);
					Showscreen*SHOWBLUEKEY=CreatShowscreen(2,bmp_SHOWBLUEKEY,126,0,63,63,true);
					showscreens.push_back(SHOWBLUEKEY);
					Showscreen*SHOWYELLOWKEY=CreatShowscreen(2,bmp_SHOWYELLOWKEY,189,0,63,63,true);
					showscreens.push_back(SHOWYELLOWKEY);


					Showscreen*FULLHEALTH1=CreatShowscreen(3,bmp_FULLHEALTH,0,63,63,63,true);
					showscreens.push_back(FULLHEALTH1);
					Showscreen*HALFHEALTH1=CreatShowscreen(3,bmp_HALFHEALTH,0,63,63,63,false);
					showscreens.push_back(HALFHEALTH1);
					Showscreen*ZEROHEATH1=CreatShowscreen(3,bmp_ZEROHEALTH,0,63,63,63,false);
					showscreens.push_back(ZEROHEATH1);


					Showscreen*FULLHEALTH2=CreatShowscreen(3,bmp_FULLHEALTH,63,63,63,63,true);
					showscreens.push_back(FULLHEALTH2);
					Showscreen*HALFHEALTH2=CreatShowscreen(3,bmp_HALFHEALTH,63,63,63,63,false);
					showscreens.push_back(HALFHEALTH2);
					Showscreen*ZEROHEATH2=CreatShowscreen(3,bmp_ZEROHEALTH,63,63,63,63,false);
					showscreens.push_back(ZEROHEATH2);


					Showscreen*FULLHEALTH3=CreatShowscreen(3,bmp_FULLHEALTH,126,63,63,63,true);
					showscreens.push_back(FULLHEALTH3);
					Showscreen*HALFHEALTH3=CreatShowscreen(3,bmp_HALFHEALTH,126,63,63,63,false);
					showscreens.push_back(HALFHEALTH3);
					Showscreen*ZEROHEATH3=CreatShowscreen(3,bmp_ZEROHEALTH,126,63,63,63,false);
					showscreens.push_back(ZEROHEATH3);
					//添加障碍物
					Obstacle*TWO_1=CreatObstacle(1,NULL,0,6*63,4*63,4*63);
					obstacles.push_back(TWO_1);
					Obstacle*TWO_2=CreatObstacle(2,NULL,6*63,8*63,34*63,2*63);
					obstacles.push_back(TWO_2);
					Obstacle*LADDER_2=CreatObstacle(3,bmp_LADDER2,8*63,4*63,63,63*4);
	               obstacles.push_back(LADDER_2);
					Obstacle*LADDER_3=CreatObstacle(4,bmp_LADDER2,15*63,4*63,63,63*4);
	               obstacles.push_back(LADDER_3);
				   Obstacle*stone1x1=CreatObstacle(5,bmp_1x1,63*14,4*63,63,63);
					obstacles.push_back(stone1x1);
					Obstacle*stone1x1_2=CreatObstacle(6,bmp_STONE1x1,21*63,4*63,63,63);
					obstacles.push_back(stone1x1_2);
					Obstacle*SHIFT=CreatObstacle(7,bmp_SHIFT,63*9,4*63,63*5,63);
					obstacles.push_back(SHIFT);
					Obstacle*stone1x1_3=CreatObstacle(8,bmp_STONE1x1,63*33,5*63,63,63);
					obstacles.push_back(stone1x1_3);
					Obstacle*stone2x1_1=CreatObstacle(9,bmp_STONE2x1,34*63,4*63,63,63*2);
					obstacles.push_back(stone2x1_1);
					Obstacle*stone3x2_1=CreatObstacle(10,bmp_STONE3x2,23*63,5*63,123,63*3);
					obstacles.push_back(stone3x2_1);
					Obstacle*LADDER_1=CreatObstacle(11,bmp_LADDER,22*63,5*63,63,63*3);
	                obstacles.push_back(LADDER_1);
					Obstacle*stone2x1_2=CreatObstacle(12,bmp_1x1,31*63,7*63,63,63);
					obstacles.push_back(stone2x1_2);
					Obstacle*stone1x1_4=CreatObstacle(13,bmp_STONE1x1,63*31,3*63,63,63);
					obstacles.push_back(stone1x1_3);
					Obstacle*stone1x1_5=CreatObstacle(14,bmp_STONE1x1,63*32,3*63,63,63);
					obstacles.push_back(stone1x1_3);
					Obstacle*mutton=CreatObstacle(15,bmp_mutton,63*26,4*63,63*3,63);
					obstacles.push_back(mutton);
					Obstacle*x1=CreatObstacle(16,bmp_1x1,63*30,3*63,63,63);
					x1->visible=false;
					obstacles.push_back(x1);
					Obstacle*x2=CreatObstacle(17,bmp_2x1,63*31,3*63,63*2,63);
					obstacles.push_back(x2);
					Obstacle*chunk=CreatObstacle(18,bmp_chunk,63*27,5*63,63,3*63);
					obstacles.push_back(chunk);
					Obstacle*myster=CreatObstacle(19,bmp_myster,63*11,7*63,63,63);
					obstacles.push_back(myster);
					Obstacle*myster1=CreatObstacle(20,bmp_myster,63*19,4.8*63,63,63);
					obstacles.push_back(myster1);
					Obstacle*myster2=CreatObstacle(21,bmp_myster,63*27,63,63,63);
					obstacles.push_back(myster2);
					Obstacle*transparent=CreatObstacle(22,bmp_transparent,63*14,63*5,63,63*3);
					obstacles.push_back(transparent);
					transparent->visible=false;
				   //添加道具
					Prop*arrow=CreatProp(1,bmp_arrow,31*63,63*2,63,63,true);
					props.push_back(arrow);
					Prop*REDKEY=CreatProp(2,bmp_PROP_REDKEY,14*63,3*63,63,63,true);
					props.push_back(REDKEY);
					Prop*BLUEKEY=CreatProp(3,bmp_PROP_BLUEKEY,19*63,3.5*63,63,63,false);
					props.push_back(BLUEKEY);
					Prop*GREENKEY=CreatProp(4,bmp_PROP_GREENKEY,29*63,5*63,63,63,true);
					props.push_back(GREENKEY);
					Prop*YELLOWKEY=CreatProp(5,bmp_PROP_YELLOWKEY,39*63,7*63,63,63,false);
					props.push_back(YELLOWKEY);
					Prop*FLASH=CreatProp(6,bmp_FLASH,13*63,7*63,42,42,false);
					props.push_back(FLASH);
	}

	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}
// 刷新单位状态函数
void UpdateUnits(HWND hWnd)
{
	if(currentStage->stageID==STAGE_1)
	{
				for(int i=0;i<units.size();i++)
				{
					Unit*unit=units[i]; 
					if(unit->side==UNIT_SIDE_RED)
					{
						UnitBehaviour_ONE_1(hWnd,unit);
					}
					else if(unit->side==UNIT_SIDE_BLUE)
					{
						if(unit->visible==true)
						UnitBehaviour_ONE_2(unit);
					}
				}
	}
	else if(currentStage->stageID==STAGE_2)
	{
			for(int i=0;i<units.size();i++)
				{
					Unit*unit=units[i]; 
					if(unit->side==UNIT_SIDE_RED)
					{
						UnitBehaviour_TWO_1(hWnd,unit);
					}
					else if(unit->side==UNIT_SIDE_BLUE)
					{
						if(unit->visible==true)
						UnitBehaviour_ONE_2(unit);
					}
				}
		MonsterBehavior_1(hWnd,monsters[0]);
		MonsterBehavior_2(hWnd,monsters[1]);
		MonsterBehavior_3(hWnd,monsters[2]);
	}
}

//单位行为函数
//障碍物碰撞函数
int Collision(Unit *unit,Obstacle*obstacle)
{
	if(unit->x>=obstacle->x)
	{
		if(unit->y<=obstacle->y)
		{
			if((unit->x-obstacle->x)>obstacle->width||(obstacle->y-unit->y)>unit->length)
				{
						return 0;
				}
			if(unit->x+unit->width<=obstacle->x+obstacle->width)
			{
				return 2;
			}
			else
			{
					 if((unit->x-obstacle->x)<=obstacle->width&&(obstacle->y-unit->y)<unit->length
						&&(double)((-unit->x+obstacle->x+obstacle->width)*1.00/unit->width)<(double)(-obstacle->y+unit->y+unit->length)*1.00/unit->length)
					{
						return 3;
					}
					else if((unit->x-obstacle->x)<obstacle->width&&(obstacle->y-unit->y)<=unit->length
						&&(double)((-unit->x+obstacle->x+obstacle->width)*1.00/unit->width)>=(double)(-obstacle->y+unit->y+unit->length)*1.00/unit->length)
					{
						return 2;
					}
					else
					{
						return 5;
					}
			}
		
		}
		else if(unit->y>obstacle->y)
		{
			if((unit->x-obstacle->x)>obstacle->width||(unit->y-obstacle->y)>obstacle->height)
					{
						return 0;
					}
			if((unit->y+unit->length)<=(obstacle->y+obstacle->height))
			{
				return 3;
			}
			if((unit->x+unit->width)<=(obstacle->x+obstacle->width))
			{
				return 4;
			}
			else
			{
				 if((unit->x-obstacle->x)<=obstacle->width&&(unit->y-obstacle->y)<obstacle->height
					&&(double)((-unit->x+obstacle->x+obstacle->width)*1.00/unit->width)<=(double)(-unit->y+obstacle->height+obstacle->y)*1.00/unit->length)
				{
					return 3;
				}
				else if((unit->x-obstacle->x)<obstacle->width&&(unit->y-obstacle->y)<=obstacle->height
					&&(double)((-unit->x-obstacle->x+obstacle->width)*1.00/unit->width)>(double)(-unit->y+obstacle->height+obstacle->y)*1.00/unit->length)
				{
					return 4;
				}
				else 
				{
					return 5;
				}
			}

		}
	}
	else if(unit->x<obstacle->x)
	{
		if(unit->y<=obstacle->y)
		{
			if((obstacle->x-unit->x)>unit->width||(obstacle->y-unit->y)>unit->length)
			{
				return 0;
			}
			else if((obstacle->x-unit->x)<=unit->width&&(obstacle->y-unit->y)<unit->length
				&&(double)((unit->x+unit->width-obstacle->x)*1.00/unit->width)<(double)((unit->y+unit->length-obstacle->y)*1.00/unit->length))
			{
				return 1;
			}
			else if((obstacle->x-unit->x)<unit->width&&(obstacle->y-unit->y)<=unit->length
				&&(double)((unit->x+unit->width-obstacle->x)*1.00/unit->width)>=(double)((unit->y+unit->length-obstacle->y)*1.00/unit->length))
			{
				return 2;
			}
			else
			{
				return 5;
			}
		}
		else if(unit->y>obstacle->y)
		{
			if((obstacle->x-unit->x)>unit->width||(unit->y-obstacle->y)>obstacle->height)
			{
				return 0;
			}
			if((unit->y+unit->length)<=(obstacle->height+obstacle->y))
			{
				return 1;
			}
			else
			{
                  if((obstacle->x-unit->x)<=unit->width&&(unit->y-obstacle->y)<obstacle->height
						&&(double)((unit->x+unit->width-obstacle->x)*1.00/unit->width)<(double)((obstacle->y+obstacle->height-unit->y)*1.00/unit->length))
					{
						return 1;
					}
					else if((obstacle->x-unit->x)<unit->width&&(unit->y-obstacle->y)<=obstacle->height
						&&(double)((unit->x+unit->width-obstacle->x)*1.00/unit->width)>(double)((obstacle->y+obstacle->height-unit->y)*1.00/unit->length))
					{
						return 4;
					}
					else 
					{
						return 5;
					}
			}
		}
	}
}
//道具碰撞函数
int Getprop(Unit*unit,Prop*prop)
{
	if(unit->x>=prop->x)
	{
		if(unit->y<=prop->y)
		{
			if((unit->x-prop->x)>=prop->width||(prop->y-unit->y)>=unit->length)
			{
				return 0;
			}
			else 
			{
				return 1;
			}
		}
		else if(unit->y>prop->y)
		{
			if((unit->x-prop->x)>=prop->width||(unit->y-prop->y)>=prop->length)
			{
				return 0;
			}
			else 
			{
				return 1;
			}
		}
	}
	else if(unit->x<prop->x)
	{
		if(unit->y<=prop->y)
		{
			if((prop->x-unit->x)>=unit->width||(prop->y-unit->y)>=unit->length)
			{
				return 0;
			}
			else 
			{
				return 1;
			}
		}
		else if(unit->y>prop->y)
		{
			if((prop->x-unit->x)>=prop->width||(unit->y-prop->y)>=prop->length)
			{
				return 0;
			}
			else 
			{
				return 1;
			}
		}
	}
}
void Blockdealing(HWND hWnd,Unit*unit)
{
	//障碍物碰撞处理
		for(int i=0;i<obstacles.size();i++)
	{
		Obstacle*obstacle=obstacles[i];
		if((obstacle->obstacleID==1)&&(Collision(unit,obstacle)==1)&&(unit->direction==0))
	    {
		    unit->vx=0;
		}
		if((obstacle->obstacleID==1)&&(Collision(unit,obstacle)==3)&&(unit->direction==1))
		{
			unit->vx=0;
		}
		if((obstacle->obstacleID==1)&&(Collision(unit,obstacle)==4))
		{
			unit->vy=0.5;
		}
		if(unit->x>=(13.7)*63&&unit->x<=(14.3)*63&&unit->y>=4*63&&unit->y<=7*63)//梯子检测
		{
             unit->state=UNIT_STATE_CLIMB;
		}
		if((Collision(unit,obstacle)!=0)&&(obstacle->obstacleID==2))
		{
			FailStage(hWnd);
		}

	}
}
void Propdealing(Unit*unit)
{
	if(units[1]->health<0)
	{
		units[1]->visible=false;
		props[5]->visible=true;
	}
	//道具处理
	for(int i=0;i<props.size();i++)
	{
		Prop*prop=props[i];
		if(Getprop(unit,prop)==1&&prop->propID==1)
		{
				if(prop->visible==true)
				{
					unit->vx=-unit->vx;
				}
		}
		if(Getprop(unit,prop)==1&&prop->propID==2)
		{
			prop->visible=false;
			Prop*prop0=props[6];
			prop0->visible=true;
			Prop*prop1=props[0];
			prop1->visible=false;
		}
		if(Getprop(unit,prop)==1&&prop->propID==3)
		{
			prop->visible=false;
			Showscreen*red=showscreens[0];
			red->visible=true;
			Showscreen*red1=showscreens[4];
			red1->visible=false;
		}
		if(Getprop(unit,prop)==1&&prop->propID==4)
		{
			prop->visible=false;
			Showscreen*blue=showscreens[2];
			blue->visible=true;
			Showscreen*blue1=showscreens[6];
			blue1->visible=false;
		}
		if(Getprop(unit,prop)==1&&prop->propID==5)
		{
			prop->visible=false;
			Showscreen*green=showscreens[1];
			green->visible=true;
			Showscreen*green1=showscreens[5];
			green1->visible=false;
		}
		if(Getprop(unit,prop)==1&&prop->propID==6&&prop->visible==true)
		{
			prop->visible=false;
			Showscreen*yellow=showscreens[3];
			yellow->visible=true;
			Showscreen*yellow1=showscreens[7];
			yellow1->visible=false;
		}
	}
}
void Jumpdealing(Unit*unit)
{
	//跳跃处理
	for(int i=0;i<obstacles.size();i++)
	{
		Obstacle*obstacle=obstacles[i];
		if(Collision(unit,obstacle)==2&&unit->state!=UNIT_STATE_CLIMB)
		{
			unit->vy=0;
			if(i==0||i==1||i==8||i==12||i==5||i==13||i==2||i==3||i==4||i==11)
			{
				unit->y=obstacle->y-unit->length;
			}
			unit->sky=false;
		}
	}
		int num=0;
	for(int i=0;i<obstacles.size();i++)
	{
		Obstacle*obstacle=obstacles[i];
		if(Collision(unit,obstacle)!=2)
		{
			num++;
		}
	}
	if(num==obstacles.size())
	{
		unit->sky=true;
	}
	if(unit->sky==false&&keyspaceDown==true&&unit->state!=UNIT_STATE_CLIMB)
	{
		unit->sky=true;
		unit->vy=unit->vy-LEAP_SPEED;
	}
	if(unit->sky==true&&unit->state!=UNIT_STATE_CLIMB)
	{
		unit->vy=unit->vy+2;
	}
}
void Boundarytest(Unit*unit)
{
	//边界检测
	if(unit->x<0)
	{
		unit->x=0;
		unit->y+=unit->vy;
		
	}
	else if(unit->x>1838)
	{
		    unit->x=1838;
		 unit->y+=unit->vy;
	}
	else if(unit->x>=0&&unit->x<=1838)
	{
			unit->y=unit->y+unit->vy;
			unit->x+=unit->vx;
	}
}
void Healthtest(Unit*unit)
{
	if(unit->health<=85&&unit->health>70)
	{
		showscreens[14]->visible=false;
		showscreens[15]->visible=true;
	}
	else if(unit->health<=70&&unit->health>55)
	{
		showscreens[14]->visible=false;
		showscreens[15]->visible=false;
		showscreens[16]->visible=true;
	}
		else if(unit->health<=55&&unit->health>40)
	{
		showscreens[14]->visible=false;
		showscreens[15]->visible=false;
		showscreens[11]->visible=false;
		showscreens[16]->visible=true;
		showscreens[12]->visible=true;
	}
		else if(unit->health<=40&&unit->health>25)
	{
		showscreens[14]->visible=false;
		showscreens[15]->visible=false;
		showscreens[11]->visible=false;
		showscreens[16]->visible=true;
		showscreens[12]->visible=false;
		showscreens[13]->visible=true;
	}
			else if(unit->health<=25&&unit->health>10)
	{
		showscreens[14]->visible=false;
		showscreens[15]->visible=false;
		showscreens[11]->visible=false;
		showscreens[16]->visible=true;
		showscreens[12]->visible=false;
		showscreens[13]->visible=true;
		showscreens[8]->visible=false;
		showscreens[9]->visible=true;
	}
			else if(unit->health<=10)
	{
		showscreens[14]->visible=false;
		showscreens[15]->visible=false;
		showscreens[11]->visible=false;
		showscreens[16]->visible=true;
			showscreens[11]->visible=false;
		showscreens[12]->visible=false;
		showscreens[13]->visible=true;
		showscreens[8]->visible=false;
		showscreens[9]->visible=false;
		showscreens[10]->visible=true;
	}

}
void UnitBehaviour_ONE_1(HWND hWnd,Unit* unit) 
{
	//判断当前状态, 以及判断是否需要状态变化
	int next_state = unit->state;
	switch (unit->state) {
	case UNIT_STATE_HOLD:
		if(keyDDown==true)
	    {
			unit->direction = UNIT_DIRECT_RIGHT;
			next_state=UNIT_STATE_RIGHTWALK;
	    }
		else if(keyADown==true)
		{
			unit->direction=UNIT_DIRECT_LEFT;
			next_state=UNIT_STATE_LEFTWALK;
		}
		else if(keyKDown==true)
		{
			next_state=UNIT_STATE_ATTACK;
		}
		break;
	case UNIT_STATE_LEFTWALK:
		if (keyADown==false&&keyspaceDown==false)
		{
			next_state = UNIT_STATE_HOLD;
		}
		else if(keyDDown==true)
		{
			unit->direction = UNIT_DIRECT_RIGHT;
			next_state=UNIT_STATE_RIGHTWALK;
		}
		else if(keyKDown==true)
		{
			next_state=UNIT_STATE_ATTACK;
		}
		break;
	case UNIT_STATE_RIGHTWALK:
		if(keyDDown==false&&keyADown==false)
		{
			next_state=UNIT_STATE_HOLD;
		}
		else if(keyADown==true)
		{
			unit->direction = UNIT_DIRECT_LEFT;
			next_state=UNIT_STATE_LEFTWALK;;
		}
		else if(keyKDown==true)
		{
			next_state=UNIT_STATE_ATTACK;
		}
		break;
	case UNIT_STATE_CLIMB:
		if(keyDDown==true&&unit->y<=5*63)
	    {
			unit->direction = UNIT_DIRECT_RIGHT;
			next_state=UNIT_STATE_RIGHTWALK;
	    }
		if(keyADown==true&&unit->y<=5*63)
	    {
			unit->direction = UNIT_DIRECT_LEFT;
			next_state=UNIT_STATE_LEFTWALK;
	    }
		if(unit->y>6*63&&unit->y<=(7*63+2)&&keyDDown==true)
		{
					
			unit->direction = UNIT_DIRECT_RIGHT;
			next_state=UNIT_STATE_RIGHTWALK;
		}
		if(unit->y>6*63&&unit->y<=(7*63+2)&&keyADown==true)
		{
					
			unit->direction = UNIT_DIRECT_LEFT;
			next_state=UNIT_STATE_LEFTWALK;
		}
		else if(unit->y<4*63)
		{
			next_state=UNIT_STATE_HOLD;
		}
		else if(unit->y>7*63)
		{
			unit->frame_row=2;
			unit->frame_sequence=FRAMES_CLIMB;
			unit->frame_count=FRAMES_CLIMB_COUNT;
			unit->y=WINDOW_HEIGHT-3*63-2;
		}
		else
		{
			unit->frame_row=2;
			unit->frame_sequence=FRAMES_CLIMB;
			unit->frame_count=FRAMES_CLIMB_COUNT;
			unit->vx=0;
			if(keyWDown==true)
			{
				unit->vy=-4;
			}
			if(keySDown==true)
			{
				unit->vy=4;
			}
			
			else if(keyWDown!=true&&keySDown!=true)
			{
				unit->vy=0;
			}
		}
		break;
	case UNIT_STATE_ATTACK:
		if(keyKDown==false)
		{
			next_state=UNIT_STATE_HOLD;
		}
		double dirX =unit2->x - unit->x;
		double dirY = unit2->y- unit->y;
		double dirLen = sqrt(dirX * dirX + dirY * dirY) + 0.0001;
		timecount1++;
		if(dirLen<32&&timecount1>=10)
		{
			units[1]->health-=17;
			timecount1=0;
		}
	};

	if (next_state != unit->state) {
		//状态变化
		unit->state = next_state;
		unit->frame_id = -1;

		switch (unit->state) {
		case UNIT_STATE_HOLD:
			unit->frame_row=3;
			unit->frame_sequence = FRAMES_HOLD;
			unit->frame_count = FRAMES_HOLD_COUNT;
			unit->vx = 0;
			break;
		case UNIT_STATE_RIGHTWALK:
			unit->frame_row=3;
			unit->frame_sequence = FRAMES_WALK;
			unit->frame_count = FRAMES_WALK_COUNT;
			unit->vx = UNIT_SPEED;
			break;
		case UNIT_STATE_LEFTWALK:
			unit->frame_row=3;
			unit->frame_sequence = FRAMES_WALK;
			unit->frame_count = FRAMES_WALK_COUNT;
			unit->vx = -UNIT_SPEED;
			break;
		case UNIT_STATE_ATTACK:
			unit->frame_row=4;
			unit->frame_sequence = FRAMES_ATTACK;
			unit->frame_count = FRAMES_ATTACK_COUNT;
			unit->vx = 0;
			break;
		};
	}
		//修复小BUG
	if(Collision(unit,obstacles[10])==4)
	{
		unit->vy=0.5;
	}
	if(Collision(unit,obstacles[10])==1)
	{
		unit->vx=-0.5;
	}
	if(props[0]->visible==true&&unit->x<=(13*63+3)&&unit->y<=135)
	{
		unit->direction=UNIT_DIRECT_RIGHT;
		unit->x+=1;

	}
	if(unit->direction==UNIT_DIRECT_RIGHT&&keyADown==true&unit->y<=(5*63+3))
	{
		unit->vx=0;
	}
	Blockdealing(hWnd,unit);
	Propdealing(unit);
	Jumpdealing(unit);
	Healthtest(unit);
	Boundarytest(unit);

	//失败条件判断
	if(showscreens[10]->visible==true||(showscreens[2]->visible==false&&showscreens[3]->visible==true))
	{
		FailStage(hWnd);
	}
		//通关条件判断
	if(showscreens[3]->visible==true&&showscreens[2]->visible==true&&showscreens[1]->visible==true&&showscreens[0]->visible==true)
	{
		CongratulationStage(hWnd);
	}
	
		//动画运行到下一帧
	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;
	int column = unit->frame_sequence[unit->frame_id];
	unit->frame_column = column + unit->direction * (UNIT_LAST_FRAME - 2 * column);
}

void UnitBehaviour_ONE_2(Unit* unit) {

	double dirX =unit1->x - unit->x;
	double dirY = unit1->y- unit->y;
	double dirLen = sqrt(dirX * dirX + dirY * dirY) + 0.0001;
	

	if (dirX > 0) 
	{
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	else 
	{
		unit->direction = UNIT_DIRECT_LEFT;
	}


	//判断当前状态, 以及判断是否需要状态变化
	int next_state = unit->state;
	switch (unit->state) {
	case UNIT_STATE_HOLD:
	if(dirLen<=189)
	{
		next_state = UNIT_STATE_RIGHTWALK;	
	}
		break;
	case UNIT_STATE_RIGHTWALK:
		if (dirLen < 32) 
		{
		next_state = UNIT_STATE_ATTACK;
		timecount=0;//计时器
		}
		else  if(dirLen>189)
		{
			next_state=UNIT_STATE_HOLD;
		}
		else if(unit->direction==UNIT_DIRECT_LEFT)
		{
			next_state=UNIT_STATE_LEFTWALK;
		}
		break;
		case UNIT_STATE_LEFTWALK:
			if (dirLen < 32) 
		{
		next_state = UNIT_STATE_ATTACK;
		timecount=0;//计时器
		}
		else  if(dirLen>189)
		{
			next_state=UNIT_STATE_HOLD;
		}
		else if(unit->direction==UNIT_DIRECT_RIGHT)
		{
			next_state=UNIT_STATE_RIGHTWALK;
		}
		break;
	case UNIT_STATE_ATTACK:
		if(timecount>=30)
		{
			units[0]->health-=10;
			timecount=0;
		}
		timecount++;
		if (dirLen >= 32) {
			next_state = UNIT_STATE_RIGHTWALK;
		}
		break;
	};

	if (next_state != unit->state) {
		//状态变化
		unit->state = next_state;
		unit->frame_id = -1;

		switch (unit->state) {
		case UNIT_STATE_HOLD:
			unit->frame_sequence = FRAMES_HOLD;
			unit->frame_count = FRAMES_HOLD_COUNT;
			unit->vx = 0;
			unit->vy = 0;
			break;
		case UNIT_STATE_RIGHTWALK:
			unit->frame_sequence = FRAMES_WALK;
			unit->frame_count = FRAMES_WALK_COUNT;
			unit->vx = UNIT_SPEED*2/3;
			unit->vy=0;
			break;
		case UNIT_STATE_LEFTWALK:
			unit->frame_sequence = FRAMES_WALK;
			unit->frame_count = FRAMES_WALK_COUNT;
			unit->vx = -UNIT_SPEED*2/3;
			unit->vy=0;
			break;
		case UNIT_STATE_ATTACK:
			unit->frame_row=2;
			unit->frame_sequence = FRAMES_ATTACK;
			unit->frame_count = FRAMES_ATTACK_COUNT;
			unit->vx = 0;
			unit->vy = 0;
			if(timecount>=30)
			{
				units[0]->health-=5;
				timecount=0;
			}
			break;
		};
	}
	//边界检测
	if(unit->x<=23*63)
	{
		unit->vx=3;
	}
	//动画运行到下一帧
	unit->x += unit->vx;
	unit->y += unit->vy;

	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;

	int column = unit->frame_sequence[unit->frame_id];
	unit->frame_column = column + unit->direction * (UNIT_LAST_FRAME - 2 * column);


}
int Touch(Unit *unit,Monster*monster)
{
	int xa=unit->x;
	int ya=unit->y+unit->length;
	int xb=unit->x+unit->width-15;
	int yb=unit->y+unit->length;
	if(ya>=monster->y+10)
	{
		if((xa-monster->x)>monster->r||(monster->x-xb)>monster->r)
		{
			return 0;
		}
		else if((xa-monster->x)<=monster->r&&(xa-monster->x)>0)
		{
			return 3;
		}
		else if((monster->x-xb)<=monster->r&&(monster->x-xb)>0)
		{
			return 1;
		}
	}
	if(ya<monster->y+10&&(xa-monster->x)*(xb-monster->x)>0)
	{
		double d1=sqrt((xa-monster->x)*(xa-monster->x)+(ya-monster->y)*(ya-monster->y));
		double d2=sqrt((xb-monster->x)*(xb-monster->x)+(yb-monster->y)*(yb-monster->y));
		if(d1>monster->r&&d2>monster->r)
		{
			return 0;
		}
		if(d1<=monster->r&&d2>monster->r)
		{
			return 5;
		}
		if(d1>monster->r&&d2<=monster->r)
		{
			return 4;
		}
	}
	if(ya<monster->y+10&&(xa-monster->x)*(xb-monster->x)<=0)
	{
		if((monster->y-ya)>monster->r)
		{
			return 0;
		}
		else
		{
			return 2;
		}
	}

	
	}
void Propdealing_TWO(Unit*unit)
{
	
	if(units[1]->health<0)
	{
		units[1]->visible=false;
		if(showscreens[3]->visible==false)
		{
		 props[4]->visible=true;
		}
	}
	//道具处理
	for(int i=0;i<props.size();i++)
	{
		Prop*prop=props[i];

		if(Getprop(unit,prop)==1&&prop->propID==2)
		{
			prop->visible=false;
			Showscreen*red=showscreens[0];
			red->visible=true;
			Showscreen*red1=showscreens[4];
			red1->visible=false;
		}
		if(Getprop(unit,prop)==1&&prop->propID==3&&prop->visible==true)
		{
			prop->visible=false;
			Showscreen*blue=showscreens[2];
			blue->visible=true;
			Showscreen*blue1=showscreens[6];
			blue1->visible=false;
		}
		if(Getprop(unit,prop)==1&&prop->propID==4)
		{
			prop->visible=false;
			Showscreen*green=showscreens[1];
			green->visible=true;
			Showscreen*green1=showscreens[5];
			green1->visible=false;
		}
		if(Getprop(unit,prop)==1&&prop->propID==5&&prop->visible==true)
		{
			prop->visible=false;
			Showscreen*yellow=showscreens[3];
			yellow->visible=true;
			Showscreen*yellow1=showscreens[7];
			yellow1->visible=false;
		}
		if(Getprop(unit,prop)==1&&prop->propID==6&&prop->visible==true&&flash==false)
		{
			prop->visible=false;
			flash=true;
		}
	}

	//陷阱
	if(Collision(unit,obstacles[18])!=0&&flash==false)
	{
		props[5]->visible=true;
		obstacles[21]->visible=true;
	}
	if(obstacles[6]->visible==false)
	{
		obstacles[21]->visible=true;
	}
}
void Jumpdealing_TWO(Unit*unit)
{
	//跳跃处理	
	if(timecount2)
	{
		timecount2++;
	}
	for(int i=0;i<obstacles.size();i++)
	{
		Obstacle*obstacle=obstacles[i];
		if(Collision(unit,obstacle)==2&&unit->state!=UNIT_STATE_CLIMB)
		{
			if(unit->x>7.3*63)
			{
			health1=false;
			}
				if(obstacle->obstacleID==7&&timecount2==0)
				{
					timecount2=1;
				}
				if(obstacle->visible==true)
				{
			    unit->vy=0;
				unit->y=obstacle->y-unit->length;
			    unit->sky=false;

				}
			
		}
	}
	          if(unit->vy>25&&health1==false)
			{
				unit->health-=30;
				health1=true;
			}
		int num=0;
	for(int i=0;i<obstacles.size();i++)
	{
		Obstacle*obstacle=obstacles[i];
		if(Collision(unit,obstacle)!=2)
		{
			num++;
		}
	}
	if(num==obstacles.size())
	{
		unit->sky=true;
	}
	if(unit->sky==false&&keyspaceDown==true&&unit->state!=UNIT_STATE_CLIMB)
	{
		unit->sky=true;
		unit->vy=unit->vy-LEAP_SPEED;
	}
	if(unit->sky==true&&unit->state!=UNIT_STATE_CLIMB)
	{
		unit->vy=unit->vy+2;
	}

	if(timecount2>=30)
	{
		obstacles[6]->visible=false;
		unit->sky=true;
	}
}
void Blockdealing_TWO(HWND hWnd,Unit*unit)
{
	//障碍物碰撞处理
		for(int i=0;i<obstacles.size();i++)
	{
		Obstacle*obstacle=obstacles[i];

		if(obstacle->visible==true)
		{
						if((Collision(unit,obstacle)==1)&&(unit->direction==0)&&obstacle->obstacleID!=3&&obstacle->obstacleID!=4&&obstacle->obstacleID!=11)
						{
							if(obstacle->visible==true)
							{
								unit->vx=0;
							}
						}
						if((Collision(unit,obstacle)==3)&&(unit->direction==1)&&obstacle->obstacleID!=3&&obstacle->obstacleID!=4&&obstacle->obstacleID!=11)
						{
							unit->vx=0;
						}
						if((Collision(unit,obstacle)==4||Collision(unit,obstacle)==5)&&obstacle->obstacleID!=3&&obstacle->obstacleID!=4&&obstacle->obstacleID!=11)
						{
							if(unit->vy<0)
							{
							unit->vy=0;
							}
							if(obstacle->obstacleID==21)
							{
								obstacles[15]->visible=true;
							}
							if(obstacle->obstacleID==20&&showscreens[2]->visible==false)
							{
								props[2]->visible=true;
							}
						}
 						if(unit->x>=(7.8)*63&&unit->x<=(8.6)*63&&unit->y>=3*63&&unit->y<=7*63)//梯子检测
						{
							 unit->state=UNIT_STATE_CLIMB;
						}
							if(unit->x>=(14.8)*63&&unit->x<=(15.3)*63&&unit->y>=3*63&&unit->y<=7*63)//梯子检测
						{
							 unit->state=UNIT_STATE_CLIMB;
						}
								if(unit->x>=(21.8)*63&&unit->x<=(22.3)*63&&unit->y>=4*63&&unit->y<=7*63)//梯子检测
						{
							 unit->state=UNIT_STATE_CLIMB;
						}
		}
}
}
void Monsterdealing(HWND hWnd,Unit*unit)
{
	for(int i=0;i<monsters.size();i++)
	{
		Monster*monster=monsters[i];
						if((Touch(unit,monster)==1)&&(unit->direction==0))
						{	
								unit->vx=0;
						}
						if((Touch(unit,monster)==3)&&(unit->direction==1))
						{
							unit->vx=0;
						}
						if((Touch(unit,monster)==2))
						{
							if(unit->vy>0)
							{
							unit->vy=0;
							}
						}
						if(Touch(unit,monster)==4)
						{
							if(unit->vx>0&&unit->vy>0)
							{
							unit->vx=0;
							unit->vy=0;
							}
						}
						if(Touch(unit,monster)==5)
						{
							if(unit->vx<0&&unit->vy>0)
							{
							unit->vx=0;
							unit->vy=0;
							}
						}
 						
}
}
void Boundarytest_TWO(Unit*unit)
{
	//边界检测
	if(unit->x<0)
	{
		unit->x=0;
		unit->y+=unit->vy;
		
	}
	else if(unit->x>2468)
	{
		    unit->x=2468;
		 unit->y+=unit->vy;
	}
	else if(unit->x>=0&&unit->x<=2468)
	{
			unit->y=unit->y+unit->vy;
			unit->x+=unit->vx;
	}
}
void UnitBehaviour_TWO_1(HWND hWnd,Unit* unit) 
{
	//判断当前状态, 以及判断是否需要状态变化
	int next_state = unit->state;
	switch (unit->state) {
	case UNIT_STATE_HOLD:
		if(keyDDown==true)
	    {
			unit->direction = UNIT_DIRECT_RIGHT;
			next_state=UNIT_STATE_RIGHTWALK;
	    }
		else if(keyADown==true)
		{
			unit->direction=UNIT_DIRECT_LEFT;
			next_state=UNIT_STATE_LEFTWALK;
		}
		else if(keyKDown==true)
		{
			next_state=UNIT_STATE_ATTACK;
		}
		break;
	case UNIT_STATE_LEFTWALK:
		if (keyADown==false&&keyspaceDown==false)
		{
			next_state = UNIT_STATE_HOLD;
		}
		else if(keyDDown==true)
		{
			unit->direction = UNIT_DIRECT_RIGHT;
			next_state=UNIT_STATE_RIGHTWALK;
		}
		else if(keyKDown==true)
		{
			next_state=UNIT_STATE_ATTACK;
		}
		break;
	case UNIT_STATE_RIGHTWALK:
		if(keyDDown==false&&keyADown==false)
		{
			next_state=UNIT_STATE_HOLD;
		}
		else if(keyADown==true)
		{
			unit->direction = UNIT_DIRECT_LEFT;
			next_state=UNIT_STATE_LEFTWALK;;
		}
		else if(keyKDown==true)
		{
			next_state=UNIT_STATE_ATTACK;
		}
		break;
	case UNIT_STATE_CLIMB:
		if(unit->x<21*63)
		{
						if(keyDDown==true&&unit->y<=4*63)
						{
							unit->direction = UNIT_DIRECT_RIGHT;
							next_state=UNIT_STATE_RIGHTWALK;
						}
						if(keyADown==true&&unit->y<=4*63)
						{
							unit->direction = UNIT_DIRECT_LEFT;
							next_state=UNIT_STATE_LEFTWALK;
						}
						if(unit->y>6*63&&unit->y<=(7*63+2)&&keyDDown==true)
						{
					
							unit->direction = UNIT_DIRECT_RIGHT;
							next_state=UNIT_STATE_RIGHTWALK;
						}
						if(unit->y>6*63&&unit->y<=(7*63+2)&&keyADown==true)
						{
					
							unit->direction = UNIT_DIRECT_LEFT;
							next_state=UNIT_STATE_LEFTWALK;
						}
						else if(unit->y<3*63)
						{
							next_state=UNIT_STATE_HOLD;
						}
						else if(unit->y>7*63)
						{
							unit->frame_row=2;
							unit->frame_sequence=FRAMES_CLIMB;
							unit->frame_count=FRAMES_CLIMB_COUNT;
							unit->y=WINDOW_HEIGHT-3*63-2;
						}
						else
						{
							unit->frame_row=2;
							unit->frame_sequence=FRAMES_CLIMB;
							unit->frame_count=FRAMES_CLIMB_COUNT;
							unit->vx=0;
							if(keyWDown==true)
							{
								unit->vy=-4;
							}
							if(keySDown==true)
							{
								unit->vy=4;
							}
			
							else if(keyWDown!=true&&keySDown!=true)
							{
								unit->vy=0;
							}
						}
		}
		else if(unit->x>21*63)
		{
			         if(keyDDown==true&&unit->y<=(4.5)*63)
						{
							unit->direction = UNIT_DIRECT_RIGHT;
							next_state=UNIT_STATE_RIGHTWALK;
						}
						if(keyADown==true&&unit->y<=(4.5)*63)
						{
							unit->direction = UNIT_DIRECT_LEFT;
							next_state=UNIT_STATE_LEFTWALK;
						}
						if(unit->y>6*63&&unit->y<=(7*63+2)&&keyDDown==true)
						{
					
							unit->direction = UNIT_DIRECT_RIGHT;
							next_state=UNIT_STATE_RIGHTWALK;
						}
						if(unit->y>6*63&&unit->y<=(7*63+2)&&keyADown==true)
						{
					
							unit->direction = UNIT_DIRECT_LEFT;
							next_state=UNIT_STATE_LEFTWALK;
						}
						else if(unit->y<4*63)
						{
							next_state=UNIT_STATE_HOLD;
						}
						else if(unit->y>7*63)
						{
							unit->frame_row=2;
							unit->frame_sequence=FRAMES_CLIMB;
							unit->frame_count=FRAMES_CLIMB_COUNT;
							unit->y=WINDOW_HEIGHT-3*63-2;
						}
						else
						{
							unit->frame_row=2;
							unit->frame_sequence=FRAMES_CLIMB;
							unit->frame_count=FRAMES_CLIMB_COUNT;
							unit->vx=0;
							if(keyWDown==true)
							{
								unit->vy=-4;
							}
							if(keySDown==true)
							{
								unit->vy=4;
							}
			
							else if(keyWDown!=true&&keySDown!=true)
							{
								unit->vy=0;
							}
						}
		}
		
		break;
	case UNIT_STATE_ATTACK:
		if(keyKDown==false)
		{
			next_state=UNIT_STATE_HOLD;
		}
		double dirX =unit2->x - unit->x;
		double dirY = unit2->y- unit->y;
		double dirLen = sqrt(dirX * dirX + dirY * dirY) + 0.0001;
		timecount1++;
		if(dirLen<32&&timecount1>=10)
		{
			units[1]->health-=17;
			timecount1=0;
		}
	};

	if (next_state != unit->state) {
		//状态变化
		unit->state = next_state;
		unit->frame_id = -1;

		switch (unit->state) {
		case UNIT_STATE_HOLD:
			unit->frame_row=3;
			unit->frame_sequence = FRAMES_HOLD;
			unit->frame_count = FRAMES_HOLD_COUNT;
			unit->vx = 0;
			break;
		case UNIT_STATE_RIGHTWALK:
			unit->frame_row=3;
			unit->frame_sequence = FRAMES_WALK;
			unit->frame_count = FRAMES_WALK_COUNT;
			unit->vx = UNIT_SPEED;
			break;
		case UNIT_STATE_LEFTWALK:
			unit->frame_row=3;
			unit->frame_sequence = FRAMES_WALK;
			unit->frame_count = FRAMES_WALK_COUNT;
			unit->vx = -UNIT_SPEED;
			break;
		case UNIT_STATE_ATTACK:
			unit->frame_row=4;
			unit->frame_sequence = FRAMES_ATTACK;
			unit->frame_count = FRAMES_ATTACK_COUNT;
			unit->vx = 0;
			break;
		};
	}
		
		//修复BUG
	if(keyADown==false&&keyDDown==false&&unit->vx!=0)
	{
		unit->vx=0;
	}
	if(Collision(unit,obstacles[17])==5||Collision(unit,obstacles[18])==5||Collision(unit,obstacles[7])==5||Collision(unit,obstacles[8])==5||Collision(unit,obstacles[19])==5||Collision(unit,obstacles[17])==4||Collision(unit,obstacles[18])==4||Collision(unit,obstacles[7])==4||Collision(unit,obstacles[8])==4||Collision(unit,obstacles[19])==4||Collision(unit,obstacles[20])==4||Collision(unit,obstacles[20])==5)
	{
		unit->vy=-unit->vy/2;
	}
	Blockdealing_TWO(hWnd,unit);
	Jumpdealing_TWO(unit);
	Propdealing_TWO(unit);
	Monsterdealing(hWnd,unit);
	for(int i=0;i<monsters.size();i++)
	{
		Monster*monster=monsters[i];
		if(Touch(unit,monster)!=0&&monsters1==false)
		{
			unit->health-=15;
			monsters1=true;
		}
	}
	for(int i=0;i<monsters.size();i++)
	{
		Monster*monster=monsters[i];
		if(Touch(unit,monster)==0)
		{
			num3++;
		}
	}
	if(num3==monsters.size())
	{
		monsters1=false;
	}
	num3=0;
	Healthtest(unit);
	//闪现技能
	if(unit->x<=11*63)
	{
		if(unit->y<5*63)
		{
			if(keyFDown==true&&keyADown==true&&flash==true)
			{
				unit->x-=126;
				unit->vy=0;
				flash=false;
			}
			if(keyFDown==true&&keyDDown==true&&flash==true)
			{
				unit->x+=126;
				unit->vy=0;
				flash=false;
			}
		}
		else
		{
				if(keyFDown==true&&keyADown==true&&flash==true)
			{
				unit->x-=126;
				unit->vy=0;
				flash=false;
			}
			if(keyFDown==true&&keyDDown==true&&flash==true)
			{
				if(unit->x<=9*63)
				{
					unit->x+=126;
				}
				else 
				{
					unit->x=11*63;
				}
				unit->vy=0;
				flash=false;
			}
				

		}
	}
	if(unit->x>11*63&&unit->x<16*63)
	{
		  if(keyFDown==true&&keyADown==true&&flash==true)
			{
				unit->x=12*63;
				unit->vy=0;
				flash=false;
			}
			if(keyFDown==true&&keyDDown==true&&flash==true)
			{
				unit->x=13*63+10;
				unit->vy=0;
				flash=false;
			}
	}
	Boundarytest_TWO(unit);
	

	//失败条件判断
	if(unit->y>10*63||showscreens[10]->visible==true)
	{
		FailStage(hWnd);
	}
	//通关条件判断
	if(showscreens[3]->visible==true&&showscreens[2]->visible==true&&showscreens[1]->visible==true&&showscreens[0]->visible==true)
	{
		InitStage(hWnd,STAGE_victory);
		stage=STAGE_victory;
	}
		//动画运行到下一帧
	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;
	int column = unit->frame_sequence[unit->frame_id];
	unit->frame_column = column + unit->direction * (UNIT_LAST_FRAME - 2 * column);
}
void MonsterBehavior_1(HWND hWnd,Monster*monster)
{
	//判断当前状态, 以及判断是否需要状态变化
	int next_state1 = monster->state;
	switch (monster->state) {
	case MONSTER_STATE_HOLD:
		timecount3++;
		if(timecount3>50&&monster->x<17.5*63)
		{
			next_state1=MONSTER_STATE_RIGHTWALK;
		}
		if(timecount3>50&&monster->x>17.5*63)
		{
			next_state1=MONSTER_STATE_LEFTWALK;
		}
		break;
	case MONSTER_STATE_RIGHTWALK:
		if (monster->x>=18.5*63)
		{
			next_state1 = UNIT_STATE_HOLD;
		}
		break;
	case MONSTER_STATE_LEFTWALK:
		if (monster->x<=16.5*63)
		{
			next_state1 = UNIT_STATE_HOLD;
		}
		break;
	}
	if (next_state1 != monster->state) {
		//状态变化
		monster->state = next_state1;
		switch (monster->state) {
		case MONSTER_STATE_HOLD:
			monster->vx = 0;
			timecount3++;
			break;
		case MONSTER_STATE_RIGHTWALK:
			monster->vx = UNIT_SPEED/2+2;
			timecount3=0;
			break;
		case MONSTER_STATE_LEFTWALK:
			monster->vx = -UNIT_SPEED/2-2;
			timecount3=0;
			break;
		};
	}
	monster->x+=monster->vx;

}
void MonsterBehavior_2(HWND hWnd,Monster*monster)
{
	//判断当前状态, 以及判断是否需要状态变化
	int next_state1 = monster->state;
	switch (monster->state) {
	case MONSTER_STATE_HOLD:
		timecount4++;
		if(timecount4>50&&monster->x<21.5*63)
		{
			next_state1=MONSTER_STATE_RIGHTWALK;
		}
		if(timecount4>50&&monster->x>21.5*63)
		{
			next_state1=MONSTER_STATE_LEFTWALK;
		}
		break;
	case MONSTER_STATE_RIGHTWALK:
		if (monster->x>=22.5*63)
		{
			next_state1 = UNIT_STATE_HOLD;
		}
		break;
	case MONSTER_STATE_LEFTWALK:
		if (monster->x<=20.5*63)
		{
			next_state1 = UNIT_STATE_HOLD;
		}
		break;
	}
	if (next_state1 != monster->state) {
		//状态变化
		monster->state = next_state1;
		switch (monster->state) {
		case MONSTER_STATE_HOLD:
			monster->vx = 0;
			timecount4++;
			break;
		case MONSTER_STATE_RIGHTWALK:
			monster->vx = UNIT_SPEED/2;
			timecount4=0;
			break;
		case MONSTER_STATE_LEFTWALK:
			monster->vx = -UNIT_SPEED/2;
			timecount4=0;
			break;
		};
	}
	monster->x+=monster->vx;

}
void MonsterBehavior_3(HWND hWnd,Monster*monster)
{
	//判断当前状态, 以及判断是否需要状态变化
	int next_state1 = monster->state;
	switch (monster->state) {
	case MONSTER_STATE_HOLD:
		timecount5++;
		if(timecount5>50&&monster->x<29.5*63)
		{
			next_state1=MONSTER_STATE_RIGHTWALK;
		}
		if(timecount5>50&&monster->x>29.5*63)
		{
			next_state1=MONSTER_STATE_LEFTWALK;
		}
		break;
	case MONSTER_STATE_RIGHTWALK:
		if (monster->x>=30.5*63)
		{
			next_state1 = UNIT_STATE_HOLD;
		}
		break;
	case MONSTER_STATE_LEFTWALK:
		if (monster->x<=28.5*63)
		{
			next_state1 = UNIT_STATE_HOLD;
		}
		break;
	}
	if (next_state1 != monster->state) {
		//状态变化
		monster->state = next_state1;
		switch (monster->state) {
		case MONSTER_STATE_HOLD:
			monster->vx = 0;
			timecount5++;
			break;
		case MONSTER_STATE_RIGHTWALK:
			monster->vx = UNIT_SPEED;
			timecount5=0;
			break;
		case MONSTER_STATE_LEFTWALK:
			monster->vx = -UNIT_SPEED;
			timecount5=0;
			break;
		};
	}
	monster->x+=monster->vx;

}

#pragma endregion


#pragma region 绘图函数
// 绘图函数
void Paint(HWND hWnd)
{

	PAINTSTRUCT ps;
	HDC hdc_window = BeginPaint(hWnd, &ps);//选定窗口作为画板
	HDC hdc_screen=GetDC(0);
	HDC hdc_screen1=CreateCompatibleDC(hdc_screen);
	HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);//创建一个和窗口相兼容的设备上下文环境
	HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);

	//初始化缓存
	HBITMAP	blankBmp = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);//创建一个和窗口等大的画纸
	SelectObject(hdc_memBuffer, blankBmp);//将大缓冲换为画纸；
	 //SelectObject(hdc_loadBmp, currentStage->bg);
	


	

	// 按场景分类绘制内容到缓存
	if (currentStage->stageID == STAGE_STARTMENU||currentStage->stageID == STAGE_HELP||currentStage->stageID == STAGE_PAUSE||currentStage->stageID == STAGE_SELECT||currentStage->stageID == STAGE_caozuo||currentStage->stageID == STAGE_gonglue||currentStage->stageID == STAGE_victory||currentStage->stageID == STAGE_acknowledge) 
	{
				// 绘制背景到缓存
				SelectObject(hdc_loadBmp, currentStage->bg);//将背景放到小缓冲
				BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);//将小缓冲当中的背景放到大缓冲当中
	}

	 if (currentStage->stageID == STAGE_1 ) 
	{
				SelectObject(hdc_screen1,bmp_ONE);//将背景放到小缓冲
				angle=units[0]->x-WINDOW_WIDTH/2;
				if(angle<0)
				{
					angle=0;
				}
				else if(angle+WINDOW_WIDTH>1890)
				{
					angle=1890-WINDOW_WIDTH;
				}
				BitBlt(hdc_memBuffer,0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_screen1,angle, 0, SRCCOPY);//将小缓冲当中的背景放到大缓冲
				
				// 绘制障碍物到缓存

			for (int i = 0; i < obstacles.size(); i++)
			{
				Obstacle* obstacle = obstacles[i];
				if(obstacle->img!=NULL&&obstacle->visible==true)
				{
					SelectObject(hdc_screen1, obstacle->img);
					TransparentBlt(
						hdc_memBuffer, obstacle->x-angle, obstacle->y,
						obstacle->width, obstacle->height,
						hdc_screen1, 0, 0, obstacle->width, obstacle->height,
						RGB(255, 255, 255)//将障碍物放到大缓冲当中
					);
				}
			}
			//绘制道具
			for (int i = 0; i < props.size(); i++)
			{
				Prop* prop = props[i];
				if(prop->visible==true)
				{
					SelectObject(hdc_screen1, prop->img);
					TransparentBlt(
						hdc_memBuffer, prop->x-angle, prop->y,
						prop->width, prop->length,
						hdc_screen1, 0, 0, prop->width, prop->length,
						RGB(255, 255, 255)//将障碍物放到大缓冲当中
					);
				}
			}
	
			// 绘制单位到缓存
				for (int i = 0; i < units.size(); i++)
				{
					Unit* unit = units[i];
					if(unit->visible)
					{
					SelectObject(hdc_screen1, unit->img);
					TransparentBlt(
						hdc_memBuffer, unit->x-angle-6, unit->y,
						UNIT_SIZE_X, UNIT_SIZE_Y,
						hdc_screen1, UNIT_SIZE_X * unit->frame_column, UNIT_SIZE_Y * unit->frame_row, UNIT_SIZE_X, UNIT_SIZE_Y,
						RGB(255, 255, 255)//将士兵放到大缓冲当中
			
					);
					}
				}

	 }	
	 if (currentStage->stageID == STAGE_2 ) 
	{
				SelectObject(hdc_screen1,bmp_TWO);//将背景放到小缓冲
				angle=units[0]->x-WINDOW_WIDTH/2;
				if(angle<0)
				{
					angle=0;
				}
				else if(angle+WINDOW_WIDTH>2520)
				{
					angle=2520-WINDOW_WIDTH;
				}
				BitBlt(hdc_memBuffer,0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_screen1,angle, 0, SRCCOPY);//将小缓冲当中的背景放到大缓冲
				
			
				//绘制道具
			for (int i = 0; i < props.size(); i++)
			{
				Prop* prop = props[i];
				if(prop->visible==true)
				{
					SelectObject(hdc_screen1, prop->img);
					TransparentBlt(
						hdc_memBuffer, prop->x-angle, prop->y,
						prop->width, prop->length,
						hdc_screen1, 0, 0, prop->width, prop->length,
						RGB(255, 255, 255)
					);
				}
			}
				// 绘制障碍物到缓存

			for (int i = 0; i < obstacles.size(); i++)
			{
				Obstacle* obstacle = obstacles[i];
				if(obstacle->img!=NULL&&obstacle->visible==true)
				{
					SelectObject(hdc_screen1, obstacle->img);
					TransparentBlt(
						hdc_memBuffer, obstacle->x-angle, obstacle->y,
						obstacle->width, obstacle->height,
						hdc_screen1, 0, 0, obstacle->width, obstacle->height,
						RGB(255, 255, 255)
					);
				}
			}
				// 绘制怪物到缓存
				for (int i = 0; i < monsters.size(); i++)
				{
					Monster* monster = monsters[i];
					SelectObject(hdc_screen1, monster->img);
					TransparentBlt(
						hdc_memBuffer, monster->x-angle-6, monster->y-21,
						42, 42,
						hdc_screen1,0 , 0 , UNIT_SIZE_X, UNIT_SIZE_Y,
						RGB(255, 255, 255)//将00士兵放到大缓冲当中
			
					);
					
				}

			// 绘制单位到缓存
				for (int i = 0; i < units.size(); i++)
				{
					Unit* unit = units[i];
					if(unit->visible)
					{
					SelectObject(hdc_screen1, unit->img);
					TransparentBlt(
						hdc_memBuffer, unit->x-angle-6, unit->y,
						UNIT_SIZE_X, UNIT_SIZE_Y,
						hdc_screen1, UNIT_SIZE_X * unit->frame_column, UNIT_SIZE_Y * unit->frame_row, UNIT_SIZE_X, UNIT_SIZE_Y,
						RGB(255, 255, 255)//将士兵放到大缓冲当中
			
					);
					}
				}

	 }		

	  if(currentStage->stageID == STAGE_1 ||currentStage->stageID == STAGE_2)
	  {
		//屏幕显示
			for (int i = 0; i < showscreens.size(); i++)
			{
				Showscreen* showscreen = showscreens[i];
				if(showscreens[i]->visible==true)
				{
					SelectObject(hdc_screen1, showscreen->img);
					TransparentBlt(
						hdc_memBuffer, showscreen->x, showscreen->y,
						showscreen->width, showscreen->length,
						hdc_screen1, 0, 0, showscreen->width, showscreen->length,
						RGB(255, 255, 255)
					);
				}
			}
	  }
	// 绘制按钮到缓存

	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->visible)
		{
			SelectObject(hdc_loadBmp, button->img);
			TransparentBlt(
				hdc_memBuffer, button->x, button->y,
				button->width, button->height,
				hdc_loadBmp, 0, 0, button->width, button->height,
				RGB(255, 255, 255)
			);
		}
	}

	 

	


	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存（非常重要）
	DeleteObject(blankBmp);
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);
	DeleteDC(hdc_screen);
	DeleteDC(hdc_screen1);
	DeleteDC(hdc_window);
	// 结束绘制
	EndPaint(hWnd, &ps);
}


#pragma endregion