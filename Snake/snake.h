/*�����Ҫ��ͷ�ļ�*/
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib") //�������ֲ������API
#pragma warning(disable : 4996)  //����4996����,������

/*�궨��*/
#define MAP_HEIGHT 20	//�����ͼ�߶�
#define MAP_WIDTH 40	//�����ͼ���
#define UP 'w'			//�������Ƽ�
#define DOWN 's'		//�������Ƽ�
#define LEFT 'a'		//�������Ƽ�
#define RIGHT 'd'		//�������Ƽ�

/*�ṹ�嶨��*/
typedef struct		//����ʳ����߽ڵ�λ�õĽṹ��
{
	int x;			//x����λ��
	int y;	        //y����λ��
}Food, Snakenode,Block;

typedef struct		//�����ߵĽṹ��
{
	Snakenode snakeNode[1000];   //�߳�������1000���ڵ�
	int length;                  //�߳���
	int speed;					 //���ƶ��ٶ�
}Snake;

typedef struct record    //��¼���а��ýṹ��
{
	int fraction;        //����
	int hour;
	int min;
	int sec;
	int year;
	int mon;
	int day;
}record;

/*��������*/
void GotoXY(int, int);	//��궨λ����
void Hide();			//���ع�꺯��
int Menu();				//���˵�����
void Help();			//������Ϣ
void About();			//������Ϣ
void InitMap();			//��ͼ��ʼ��
void PrintFood();		//����ʳ��
int MoveSnake();		//���ƶ�
int IsCorrect();		//��ײ��ײǽ���
void SpeedControl();	//�ٶȿ���
void Setting();         //������Ϣ
void Music(int);        //��������
void PrintRanking();    //������ӡ����
void SettingRanking();  //���а�ǰ�ý���
void Recordeddata();    //�����洢����
int Cmpfunc(const void*, const void*); //������