/*引入必要的头文件*/
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib") //引入音乐播放相关API
#pragma warning(disable : 4996)  //禁用4996警告,真阴间

/*宏定义*/
#define MAP_HEIGHT 20	//定义地图高度
#define MAP_WIDTH 40	//定义地图宽度
#define UP 'w'			//定义上移键
#define DOWN 's'		//定义下移键
#define LEFT 'a'		//定义左移键
#define RIGHT 'd'		//定义右移键

/*结构体定义*/
typedef struct		//定义食物和蛇节点位置的结构体
{
	int x;			//x坐标位置
	int y;	        //y坐标位置
}Food, Snakenode,Block;

typedef struct		//定义蛇的结构体
{
	Snakenode snakeNode[1000];   //蛇长最多包含1000个节点
	int length;                  //蛇长度
	int speed;					 //蛇移动速度
}Snake;

typedef struct record    //记录排行榜用结构体
{
	int fraction;        //分数
	int hour;
	int min;
	int sec;
	int year;
	int mon;
	int day;
}record;

/*函数定义*/
void GotoXY(int, int);	//光标定位函数
void Hide();			//隐藏光标函数
int Menu();				//主菜单函数
void Help();			//帮助信息
void About();			//关于信息
void InitMap();			//地图初始化
void PrintFood();		//生成食物
int MoveSnake();		//蛇移动
int IsCorrect();		//自撞或撞墙检测
void SpeedControl();	//速度控制
void Setting();         //设置信息
void Music(int);        //音乐设置
void PrintRanking();    //排名打印函数
void SettingRanking();  //排行榜前置界面
void Recordeddata();    //排名存储函数
int Cmpfunc(const void*, const void*); //排序函数