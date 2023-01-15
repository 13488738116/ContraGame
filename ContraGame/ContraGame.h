#pragma once

#pragma region 头文件引用

// Windows 头文件: 
#include <windows.h>
#include<d3d9.h>
// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>


// 资源头文件
#include "resource.h"
#pragma comment(lib, "Msimg32.lib")			//图象处理的函数接口，例如：透明色的位图的绘制TransparentBlt函数


// TODO:  在此处引用程序需要的其他头文件
#include <vector>
#include <math.h>


#pragma endregion


#pragma region 宏定义

#define WINDOW_TITLEBARHEIGHT	32			//标题栏高度
#define WINDOW_WIDTH			1050		//游戏窗口宽度
#define WINDOW_HEIGHT			630	//游戏窗口高度



#define STAGE_STARTMENU			0		//开始画面的ID
#define STAGE_1					1		//第一个游戏场景的ID
#define STAGE_HELP              2       //帮助界面
#define STAGE_PAUSE				3		//暂停界面
#define STAGE_2                 4        //关卡2
#define STAGE_SELECT            5
#define STAGE_caozuo            6
#define STAGE_gonglue            7
#define STAGE_victory            8
#define STAGE_acknowledge           9

#define UNIT_SIZE_X				63		//单位的宽度
#define UNIT_SIZE_Y				63		//单位的高度
#define UNIT_LAST_FRAME			11		//单位的动画帧最大值

//单位阵营定义
#define UNIT_SIDE_RED			10000	//红方
#define UNIT_SIDE_BLUE			10001	//蓝方


//单位类型定义
#define UNIT_TYPE_LEAP		0		//跳跃
#define UNIT_TYPE_JINENG		1		//技能
#define UNIT_TYPE_CLIMB			2		//爬行
#define UNIT_TYPE_WALK		3		//行走
#define UNIT_TYPE_ATTACK		4		//攻击
//怪物状态定义
#define MONSTER_STATE_HOLD      0
#define MONSTER_STATE_LEFTWALK      1
#define MONSTER_STATE_RIGHTWALK     2

//单位状态定义
#define UNIT_STATE_HOLD			0		//静止
#define UNIT_STATE_LEFTWALK		2		//向左行走
#define UNIT_STATE_ATTACK		1		//攻击
#define UNIT_STATE_RIGHTWALK    3       //向右行走
#define UNIT_STATE_LEAP         4       //跳跃
#define UNIT_STATE_CLIMB        5        //爬梯子
#define UNIT_STATE_SKY          6        //空中

//单位方向定义
#define UNIT_DIRECT_RIGHT		0		//向右
#define UNIT_DIRECT_LEFT		1		//向左
//怪物方向定义
#define MONSTER_DIRECT_RIGHT    0
#define MONSTER_DIRECT_LEFT     1

//背景
#define BG_SRC_COUNT			6		//背景资源数量
#define BG_COLUMNS				16		//背景列数
#define BG_ROWS					12		//背景行数
#define BG_ROWS_SKY				3		//背景天空行数
#define BG_ROWS_LAND			9		//背景地面行数
#define BG_CELL_WIDTH			64		//背景单格宽度
#define BG_CELL_HEIGHT			64		//背景单格高度

//其它定义
#define BUTTON_STARTGAME			1001	//开始游戏按钮ID
#define BUTTON_STARTGAME_WIDTH		240		//开始游戏按钮宽度
#define BUTTON_STARTGAME_HEIGHT		64		//开始游戏按钮高度
#define BUTTON_HELP                 1002    //帮助按钮ID
#define BUTTON_HELP_WIDTH          239       //帮助按钮宽度
#define BUTTON_HELP_HEIGHT          62      //帮助按钮高度
#define BUTTON_RETURN               1003    //返回按钮
#define BUTTON_RETURN_WIDTH          110       //帮助按钮宽度
#define BUTTON_RETURN_HEIGHT          61      //帮助按钮高度
#define BUTTON_RESTART               1004   //重新开始按钮
#define BUTTON_RESTART_WIDTH          337       //宽度
#define BUTTON_RESTART_HEIGHT          59      //高度
#define BUTTON_RETURN1               1005    //返回按钮
#define BUTTON_RETURN1_WIDTH          342       //宽度
#define BUTTON_RETURN1_HEIGHT          55      //高度
#define BUTTON_RESUME              1006   //恢复按钮
#define BUTTON_RESUME_WIDTH          339      //宽度
#define BUTTON_RESUME_HEIGHT          59     //高度
#define BUTTON_NEXT               1007       //下一关
#define BUTTON_NEXT_WIDTH          337      //宽度
#define BUTTON_NEXT_HEIGHT          61     //高度
#define BUTTON_FIRST              1008
#define BUTTON_SECOND           1010
#define BUTTON_LEFT           1011
#define BUTTON_RIGHT           1012

#define TIMER_GAMETIMER				1		//游戏的默认计时器ID
#define TIMER_GAMETIMER_ELAPSE		20		//默认计时器刷新间隔的毫秒数
#define UNIT_SPEED					6.0		//单位行走速度	
#define LEAP_SPEED					20.0		//单位跳跃速度

#pragma endregion


#pragma region 结构体声明

// 场景结构体
struct Stage
{
	int stageID;		//场景编号
	HBITMAP bg;			//背景图片
	int timeCountDown;	//游戏时间倒计时
	bool timerOn;		//计时器是否运行（游戏是否被暂停）

};


// 按钮结构体
struct Button
{
	int buttonID;	//按钮编号
	bool visible;	//按钮是否可见
	HBITMAP img;	//图片
	int x;			//坐标x
	int y;			//坐标y
	int width;		//宽度
	int height;		//高度
};

// 单位结构体
struct Unit
{
	HBITMAP img;	//图片

	int frame_row;			//当前显示的是图像的第几行
	int frame_column;		//当前显示的是图像的第几列

	int* frame_sequence;		//当前的帧序列
	int frame_count;		//帧序列的长度
	int frame_id;			//当前显示的是帧序列的第几个


	int side;		//单位阵营
	int type;		//单位类型
	int state;		//单位状态
	int direction;	//单位方向

	int x;			//坐标x
	int y;			//坐标y
	int width;		//宽度
	int length;		//长度
	double vx;		//速度x
	double vy;		//速度y
	bool visible;    //是否可见
	int health;		//生命值
	bool sky;       //是否在空中
};
struct Monster
{
	HBITMAP img;	//图片
	int ID;		//单位ID
	int state;		//单位状态
	int direction;	//单位方向

	int x;			//坐标x
	int y;			//坐标y
	int r;		//半径
	double vx;		//速度x
	double vy;		//速度y
};

struct Obstacle
{
	int obstacleID;
	HBITMAP img;	//图片
	int x;          //坐标x
	int y;          //坐标y
	int width;      //宽度
	int height;		//长度
	bool visible;   //是否可见

};
struct Prop
{
	int propID;
	HBITMAP img;
	int x;
	int y;
	int width;
	int length;
	bool visible;

};
struct Showscreen
{
	int showscreenID;
	HBITMAP img;
	int x;
	int y;
	int width;
	int length;
	bool visible;
};
//TODO: 添加游戏需要的更多种数据（地物、砖块等）


#pragma endregion


#pragma region 事件处理函数声明


// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);

#pragma endregion


#pragma region 其它游戏状态处理函数声明

// 添加按钮函数
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y);

// 添加单位函数
Unit* CreateUnit(int side, int type, int x, int y, int health);
//添加障碍函数
Obstacle* CreatObstacle(int obstacleID,HBITMAP img,int x,int y,int width,int length);
Prop* CreatProp(int propID,HBITMAP img,int x,int y,int width,int length,bool visible);
Showscreen*CreatShowscreen(int showscreenID,HBITMAP img,int x,int y,int width,int length,bool visible);

int RestartStage(HWND hWnd,int stageID);
void FailStage(HWND hWnd);
void CongratulationStage(HWND hWnd);
// 初始化场景函数
void InitStage(HWND hWnd, int stageID);
// 刷新单位状态函数
void UpdateUnits(HWND hWnd);
int Collision(Unit *unit,Obstacle*obstacle);
int Getprop(Unit*unit,Prop*prop);
void Blockdealing(HWND hWnd,Unit*unit);
void Propdealing(Unit*unit);
void Jumpdealing(Unit*unit);
void Boundarytest(Unit*unit);
void Healthtest(Unit*unit);

//单位行为函数
void UnitBehaviour_ONE_1(HWND hWnd,Unit* unit);
void UnitBehaviour_ONE_2(Unit* unit);
void UnitBehaviour_TWO_1(HWND hWnd,Unit* unit);
void MonsterBehavior_1(HWND hWnd,Monster*monster);
void MonsterBehavior_2(HWND hWnd,Monster*monster);
void MonsterBehavior_3(HWND hWnd,Monster*monster);
//TODO: 添加游戏需要的更多函数


#pragma endregion 


#pragma region 绘图函数声明

// 绘图函数
void Paint(HWND hWnd);

// 初始化背景函数
HBITMAP InitBackGround(HWND hWnd, HBITMAP bmp_src);

#pragma endregion