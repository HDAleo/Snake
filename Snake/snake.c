#include "snake.h"

/*全局变量定义*/
Snake snake;	//定义蛇结构体变量
Food food;		//定义食物结构体变量
Block block[100];    //定义障碍物结构体变量
char now_Dir = RIGHT;	//当前蛇头方向
char direction = RIGHT; //预期蛇头方向
int block_num; //预期墙体数量
int food_type; //食物种类

/*主菜单实现*/
int Menu() {
	GotoXY(40, 12); 			     //定位光标位置
	printf("欢迎来到贪吃蛇小游戏");
	GotoXY(43, 14);
	printf("1.开始游戏");
	GotoXY(43, 16);
	printf("2 排行榜");
	GotoXY(43, 18);
	printf("3.帮助");
	GotoXY(43, 20);
	printf("4.关于");
	GotoXY(43, 22);
	printf("其他任意键退出游戏");
	Hide();	                       //隐藏光标
	char ch;
	int result = 0;
	ch = _getch();   			    //接收用户输入的菜单选项
	switch (ch) {				//根据选项设置返回结果值
		case '1': result = 1; break;
		case '2': result = 2; break; //新增排行榜界面
		case '3': result = 3; break;
		case '4': result = 4; break;
	}
	system("cls");  				//调用系统命令cls完成清屏操作
	return result;
}

//光标定位函数，将光标定位到(x,y)坐标位置  
void GotoXY(int x, int y) {
	HANDLE hout;
	COORD cor;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cor.X = x;
	cor.Y = y;
	SetConsoleCursorPosition(hout, cor);
}

/*新增更改局部颜色的代码,用于区分墙,食物,蛇*/
void SetColor(UINT uFore, UINT uBack) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, uFore + uBack * 0x10);
}

/*隐藏光标*/
void Hide() {
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cor_info = { 1, 0 };
	SetConsoleCursorInfo(hout, &cor_info);
}

/*音乐模块*/
void Music(int i) {      //音乐设置,根据传递参数播放不同的音乐;
	switch (i) {
	case 1:
		mciSendString("open 1.mp3", NULL, 0, NULL);
		mciSendString("play 1.mp3 repeat", NULL, 0, NULL);
		mciSendString("setaudio 1.mp3 volume to 200", NULL, 0, NULL);
		break;
	case 2:
		mciSendString("close 2.mp3", NULL, 0, NULL);
		mciSendString("open 2.mp3", NULL, 0, NULL);
		mciSendString("play 2.mp3 ", NULL, 0, NULL);
		mciSendString("setaudio 2.mp3 volume to 300", NULL, 0, NULL);
		break;
	case 3:
		mciSendString("close 3.mp3", NULL, 0, NULL);
		mciSendString("open 3.mp3", NULL, 0, NULL);
		mciSendString("play 3.mp3 ", NULL, 0, NULL);
		mciSendString("setaudio 3.mp3 volume to 300", NULL, 0, NULL);
		break;
	case 4:
		mciSendString("close 4.mp3", NULL, 0, NULL);
		mciSendString("open 4.mp3", NULL, 0, NULL);
		mciSendString("play 4.mp3 ", NULL, 0, NULL);
		mciSendString("setaudio 4.mp3 volume to 300", NULL, 0, NULL);
		break;
	}
}

//开始游戏后进入选关界面的实现
void Setting() { 
	GotoXY(40, 10);
	printf("请选择难度:默认简单难度");
	GotoXY(43, 12);
	printf("1.简单难度,只有10个障碍物");
	GotoXY(43, 14);
	printf("2 中等难度,20个障碍物");
	GotoXY(43, 16);
	printf("3.困难难度,40个障碍物");
	GotoXY(43, 18);
	printf("4.挑战一下,50个障碍物");
	Hide();
	char ch;
	int result = 0;
	ch = _getch();
	switch (ch) {
	case '1': block_num = 10; break;
	case '2': block_num = 20; break;
	case '3': block_num = 40; break;
	case '4': block_num = 50; break;
	default: block_num = 10;
	}
	system("cls");
}

/*排行榜前置选项*/
void SettingRanking() {
	GotoXY(20, 10);
	printf("请选择对应难度的排行榜");
	GotoXY(43, 12);
	printf("1.简单难度");
	GotoXY(43, 14);
	printf("2 中等难度");
	GotoXY(43, 16);
	printf("3.困难难度");
	GotoXY(43, 18);
	printf("4.挑战难度");
	Hide();
	char ch;
	int result = 0;
	ch = _getch();
	switch (ch) {
	case '1': block_num = 10; break;
	case '2': block_num = 20; break;
	case '3': block_num = 40; break;
	case '4': block_num = 50; break;
	}
	system("cls");
}

/*排行榜菜单的实现*/
void PrintRanking()   //排行榜显示
{
	system("cls");
	int i = 0;
	FILE* fp;
	record gdata[1000];
	if (block_num == 10) {
		fp = fopen("out1.txt", "rb"); //通过读写不同的文件来实现不同排行榜的显示
	}
	else if (block_num == 20) {
		fp = fopen("out2.txt", "rb");
	}
	else if (block_num == 40) {
		fp = fopen("out3.txt", "rb");
	}
	else if (block_num == 50) {
		fp = fopen("out4.txt", "rb");
	}
	else{
		GotoXY(56, 12);
		printf("暂无记录");
		Hide();
		return;
	}
	rewind(fp);
	while (!feof(fp))                           //feof检查文件是否结束，遇到结束符，返回非零
	{
		fread(&gdata[i], sizeof(struct record), 1, fp);
		i++;
	}
	qsort(gdata, i-1, sizeof(record), Cmpfunc);       //按得分排序
	GotoXY(52, 3);
	printf("排行榜");
	GotoXY(42, 5);
	printf("得分\t\t\t时间\n");
	int ret = (i - 1) > 5 ? 5 : (i-1);
	for (int j = 0; j < ret; j++)                     //显示前i-1条或者5条的得分,防止排行榜溢出
	{
		GotoXY(43, 7 + j * 2); //打印得分
		printf("%d\t\t", gdata[j].fraction);
		printf("%d/%02d/%02d ", gdata[j].year + 1900, gdata[j].mon + 1, gdata[j].day);
		printf("%02d:%02d:%02d", gdata[j].hour, gdata[j].min, gdata[j].sec);
	}
	fclose(fp);                               //删除文件指针
	Hide();
	char ch = _getch();
	system("cls");
}

/*关于菜单实现*/
void About() {
	GotoXY(39, 12);
	printf("23050514程世超老师班第三小组小组作业");
	GotoXY(43, 14);
	printf("贪吃蛇-控制台游戏");
	GotoXY(43, 16);
	printf("按任意键返回上级菜单");
	Hide();		//隐藏光标
	char ch = _getch();
	system("cls");
}

/*帮助菜单实现*/
void Help() {
	GotoXY(40, 11);
	printf("wasd 控制上下左右");
	GotoXY(40, 13);
	printf("当蛇撞到撞墙或障碍物时游戏结束时");
	GotoXY(40, 15);
	printf("绿色$生长一格,紫色$生长两格,黄色$生长三格");
	GotoXY(40, 17);
	printf("撞尾不会立即死亡,而是失去自己的尾巴");
	GotoXY(45, 22);
	printf("按任意键返回上级菜单");
	Hide();		//隐藏光标
	char ch = _getch();
	system("cls");
}

/*初始化地图函数*/
void InitMap() {
	Music(2);
	Hide();	   				//隐藏光标
	//设置蛇头位置在地图中心
	snake.snakeNode[0].x = MAP_WIDTH / 2 - 1;
	snake.snakeNode[0].y = MAP_HEIGHT / 2 - 1;
	GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y); 	  //将光标移动到蛇头位置
	SetColor(3, 0);
	printf("@"); 				//打印蛇头
	SetColor(7, 0);
	snake.length = 3;   		//设置蛇长初始值为3节
	snake.speed = 250;  		//设置蛇初始移动速度为250
	now_Dir = RIGHT;            //当前蛇头方向
	//显示蛇身
	for (int i = 1; i < snake.length; i++) {
		//设置蛇身的纵坐标位置和蛇头位置相同
		snake.snakeNode[i].y = snake.snakeNode[i - 1].y;
		//设置蛇身的横坐标位置，蛇身在蛇头的左边,所以横坐标依次减1
		snake.snakeNode[i].x = snake.snakeNode[i - 1].x - 1;
		GotoXY(snake.snakeNode[i].x, snake.snakeNode[i].y); 	//移动光标到蛇身位置
		SetColor(3, 0);
		printf("o");   		//打印蛇身
		SetColor(7, 0);
	}
	//生成地图上下边界
	for (int i = 0; i < MAP_WIDTH; i++) {
		GotoXY(i, 0);
		printf("-");
		GotoXY(i, MAP_HEIGHT - 1);
		printf("-");
	}
	//生成地图左右边界
	for (int i = 1; i < MAP_HEIGHT - 1; i++) {
		GotoXY(0, i);
		printf("|");
		GotoXY(MAP_WIDTH - 1,i);
		printf("|");
	}
	//根据预先设定的数量生成障碍物
	int num = block_num;
	int flag;
	while (num>0) {
		block[num].x = rand() % (MAP_WIDTH - 2) + 1;
		block[num].y = rand() % (MAP_HEIGHT - 2) + 1;
		flag = 1;
		for (int k = 0; k <= snake.length - 1; k++) {
			if (snake.snakeNode[k].x == block[num].x && snake.snakeNode[k].y == block[num].y) { //判定不与蛇重叠
				flag = 0;
				break;
			}
		}
		if (flag == 1) {
			GotoXY(block[num].x, block[num].y);
			printf("#");
			num--;
		}
	}
	//生成食物
	PrintFood();
	//得分说明
	GotoXY(50, 5);
	printf("当前得分: 0 ");
}

/*生成食物函数*/
void PrintFood() {
	int flag_food = 1 ;
	int percent;
	while (flag_food)
	{
		flag_food = 0;
		//设置随机的食物坐标位置
		food.x = rand() % (MAP_WIDTH - 2) + 1;
		food.y = rand() % (MAP_HEIGHT - 2) + 1;
		//循环判断食物位置是否和蛇的位置重叠，如果重叠则需要重新设置食物位置
		for (int k = 0; k <= snake.length - 1; k++) {
			if (snake.snakeNode[k].x == food.x && snake.snakeNode[k].y == food.y) {
				flag_food = 1;  				//位置有重叠，需要继续循环
				break;
			}
		}
		//循环判断食物位置是否和障碍物的位置重叠,如果重叠则需要重新设置食物位置
		for (int i = 1; i <= block_num; i++) {
			if (food.x == block[i].x && food.y == block[i].y) {
				flag_food = 1; //位置重叠,需要继续循环
				break;
			}
		}
		if (flag_food == 0) { //只有能进入循环且该位置不重叠时才能生成食物(原代码好像没有?)
			GotoXY(food.x, food.y);
			percent = rand() % 3; //将三种食物概率均等生成,snake_length+=food_type实现生长速度的不同.
			switch (percent) {
			case 0:
				food_type = 1;
				SetColor(2, 0);
				printf("$");
				SetColor(7, 0);
				break;
			case 1:
				food_type = 2;
				SetColor(5, 0);
				printf("$");
				SetColor(7, 0);
				break;
			default:
				food_type = 3;
				SetColor(6, 0);
				printf("$");
				SetColor(7, 0);
				break;
			}
		}
	}
}

/*蛇移动函数实现,返回值为1表示继续移动，为0表示停止移动*/
int MoveSnake() {
	Snakenode temp;
	int flag = 0;
	temp = snake.snakeNode[snake.length - 1]; 			//记录蛇尾
	for (int i = snake.length - 1; i >= 1; i--)
		snake.snakeNode[i] = snake.snakeNode[i - 1];	//将所有蛇身向前移动一个位置
	GotoXY(snake.snakeNode[1].x, snake.snakeNode[1].y);
	SetColor(3, 0);
	printf("o");  			//前进方向打印一节蛇身，其他蛇身不需要打印
	SetColor(7, 0);
	//响应键盘修改
	if (_kbhit()) {			//键盘输入返回1，非键盘输入返回0
		direction = _getch();
		switch (direction) {
		case UP:  //按下w键
			if (now_Dir != DOWN)		//如果蛇头向下，按向上移动的键w时不起作用
				now_Dir = direction;
			break;
		case DOWN:  //按下s键
			if (now_Dir != UP)			//如果蛇头向上，按向下移动的键s时不起作用
				now_Dir = direction;
			break;
		case LEFT:  //按下a键
			if (now_Dir != RIGHT)		//如果蛇头向右，按向左移动的键a时不起作用
				now_Dir = direction;
			break;
		case RIGHT:  //按下d键
			if (now_Dir != LEFT)		//如果蛇头向左，按向右移动的键d时不起作用
				now_Dir = direction;
			break;
		}
	}
	switch (now_Dir) {   					//根据现在的方向修改蛇头的位置
	case UP:snake.snakeNode[0].y--; break;		//向上移动
	case DOWN:snake.snakeNode[0].y++; break;		//向下移动
	case LEFT:snake.snakeNode[0].x--; break;		//向左移动
	case RIGHT:snake.snakeNode[0].x++; break;	//向右移动
	}
	//打印蛇头
	GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);
	SetColor(3, 0);
	printf("@");
	SetColor(7, 0);
	//判断是否吃到食物，如果蛇头的位置和食物的位置相同表示吃到食物
	if (snake.snakeNode[0].x == food.x && snake.snakeNode[0].y == food.y) {
		Music(4);
		snake.length+=food_type;  		//吃到食物加长长度取决于food_type变量.
		flag = 1;        		//flag为1表示吃到食物，为0表示没有吃到食物
		snake.snakeNode[snake.length - 1] = temp;	//吃到食物，蛇尾加一节
	}
	//输出蛇此时状态
	//没吃到食物时，在原来的蛇尾打印一个空格，去掉原来的蛇尾
	if (!flag) {
		GotoXY(temp.x, temp.y);
		printf(" ");
	}
	else {			//吃到食物，则需要在地图上重新更新一个食物
		PrintFood();
		GotoXY(50, 5);
		printf("当前得分: %d ", snake.length - 3);  	//打印得分，得分为蛇长减原始长度3 ----tips:修改得分显示效果,加入空格避免出现十位数退回个位数导致的显示错误.
	}
	//判断是否死亡
	if (!IsCorrect()) { 	 	//如果自撞或撞墙，则清楚屏幕，打印最终得分，游戏结束
		Recordeddata();
		Music(3);
		system("cls");
		GotoXY(45, 14);
		printf("最终得分：%d ", snake.length - 3);
		GotoXY(45, 16);
		printf("你输了！");
		GotoXY(45, 18);
		printf("按任意键返回主菜单");
		char c = _getch();
		system("cls");
		return 0;
	}
	//调整速度
	SpeedControl();
	Sleep(snake.speed);		//把进程挂起一段时间，用于控制蛇移动的速度
	return 1;
}

/*判断是否自撞或撞墙,返回值为0表示自撞或撞墙，否则为1*/
int IsCorrect() {
	if (snake.snakeNode[0].x == 0 || snake.snakeNode[0].y == 0 || snake.snakeNode[0].x == MAP_WIDTH - 1 || snake.snakeNode[0].y == MAP_HEIGHT - 1) //判断蛇头是否撞墙
		return 0;
	for (int i = 1; i < block_num; i++) {
		if (snake.snakeNode[0].x == block[i].x && snake.snakeNode[0].y == block[i].y)
			return 0;
	}
	for (int i = 1; i < snake.length; i++)   //判断蛇头是否和蛇身重叠，重叠表示自撞
		if (snake.snakeNode[0].x == snake.snakeNode[i].x && snake.snakeNode[0].y == snake.snakeNode[i].y) {
			//自撞时先显示蛇头位置,避免看不到蛇头.
			GotoXY(snake.snakeNode[i].x, snake.snakeNode[i].y);
			SetColor(3, 0);
			printf("@");
			SetColor(7, 0);
			//遍历撞到的蛇身后面的节点,清空并退回蛇身长度.
			int length = snake.length;
			for (int j=i+1; j < length; j++) {
				GotoXY(snake.snakeNode[j].x, snake.snakeNode[j].y);
				printf(" ");
				snake.length--;
			}
		}
	//及时刷新积分板,不加该行会导致得分刷新不及时.
	GotoXY(50, 5);
	printf("当前得分: %d ", snake.length - 3);
	return 1;
}

/*速度调整函数*/
void SpeedControl() {
	switch (snake.length) {  		//根据蛇长调整蛇的移动速度
	case 6:snake.speed = 200; break;
	case 9:snake.speed = 180; break;
	case 12:snake.speed = 160; break;
	case 15:snake.speed = 140; break;
	case 18:snake.speed = 120; break;
	case 21:snake.speed = 100; break;
	case 24:snake.speed = 80; break;
	case 27:snake.speed = 60; break;
	case 30:snake.speed = 40; break;
	default:break;
	}
}

/*保存成绩函数*/
void Recordeddata() 
{
	time_t timep;
	struct tm* ti;
	time(&timep);
	ti = localtime(&timep);              //获取系统时间
	record* gdata = (record*)malloc(sizeof(record));
	gdata->year = ti->tm_year;//年
	gdata->mon = ti->tm_mon;  //月
	gdata->day = ti->tm_mday; //日
	gdata->hour = ti->tm_hour;//时
	gdata->min = ti->tm_min;  //分
	gdata->sec = ti->tm_sec;  //秒
	gdata->fraction = snake.length - 3;
	/*根据难度不同保存到不同的文件中, 创建多个排行榜*/
	switch (block_num) {  
	case 10:
	{FILE* fp1 = fopen("out1.txt", "ab");
	if (fp1 == NULL)
		fp1 = fopen("out1.txt", "wb");
	fwrite(gdata, sizeof(record), 1, fp1);
	fclose(fp1);       
	free(gdata);
	break;
	}
	case 20:
	{FILE* fp2 = fopen("out2.txt", "ab");
	if (fp2 == NULL)
		fp2 = fopen("out2.txt", "wb");
	fwrite(gdata, sizeof(record), 1, fp2);
	fclose(fp2);       
	free(gdata);
	break;
	}
	case 40:
	{FILE* fp3 = fopen("out3.txt", "ab");
	if (fp3 == NULL)
		fp3 = fopen("out3.txt", "wb");
	fwrite(gdata, sizeof(record), 1, fp3);
	fclose(fp3);       
	free(gdata);
	break;
	}
	case 50:
	{FILE* fp4 = fopen("out4.txt", "ab");
	if (fp4 == NULL)
		fp4 = fopen("out4.txt", "wb");
	fwrite(gdata, sizeof(record), 1, fp4);
	fclose(fp4);         
	free(gdata);
	break;
	}
	}
}

/*降序排序函数*/
int Cmpfunc(const void* a, const void* b) //排序函数,使用嵌套实现排行榜的排序
{
	return(*(int*)b - *(int*)a);
}