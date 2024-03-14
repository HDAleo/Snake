#include "snake.h"

/*ȫ�ֱ�������*/
Snake snake;	//�����߽ṹ�����
Food food;		//����ʳ��ṹ�����
Block block[100];    //�����ϰ���ṹ�����
char now_Dir = RIGHT;	//��ǰ��ͷ����
char direction = RIGHT; //Ԥ����ͷ����
int block_num; //Ԥ��ǽ������
int food_type; //ʳ������

/*���˵�ʵ��*/
int Menu() {
	GotoXY(40, 12); 			     //��λ���λ��
	printf("��ӭ����̰����С��Ϸ");
	GotoXY(43, 14);
	printf("1.��ʼ��Ϸ");
	GotoXY(43, 16);
	printf("2 ���а�");
	GotoXY(43, 18);
	printf("3.����");
	GotoXY(43, 20);
	printf("4.����");
	GotoXY(43, 22);
	printf("����������˳���Ϸ");
	Hide();	                       //���ع��
	char ch;
	int result = 0;
	ch = _getch();   			    //�����û�����Ĳ˵�ѡ��
	switch (ch) {				//����ѡ�����÷��ؽ��ֵ
		case '1': result = 1; break;
		case '2': result = 2; break; //�������а����
		case '3': result = 3; break;
		case '4': result = 4; break;
	}
	system("cls");  				//����ϵͳ����cls�����������
	return result;
}

//��궨λ����������궨λ��(x,y)����λ��  
void GotoXY(int x, int y) {
	HANDLE hout;
	COORD cor;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cor.X = x;
	cor.Y = y;
	SetConsoleCursorPosition(hout, cor);
}

/*�������ľֲ���ɫ�Ĵ���,��������ǽ,ʳ��,��*/
void SetColor(UINT uFore, UINT uBack) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, uFore + uBack * 0x10);
}

/*���ع��*/
void Hide() {
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cor_info = { 1, 0 };
	SetConsoleCursorInfo(hout, &cor_info);
}

/*����ģ��*/
void Music(int i) {      //��������,���ݴ��ݲ������Ų�ͬ������;
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

//��ʼ��Ϸ�����ѡ�ؽ����ʵ��
void Setting() { 
	GotoXY(40, 10);
	printf("��ѡ���Ѷ�:Ĭ�ϼ��Ѷ�");
	GotoXY(43, 12);
	printf("1.���Ѷ�,ֻ��10���ϰ���");
	GotoXY(43, 14);
	printf("2 �е��Ѷ�,20���ϰ���");
	GotoXY(43, 16);
	printf("3.�����Ѷ�,40���ϰ���");
	GotoXY(43, 18);
	printf("4.��սһ��,50���ϰ���");
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

/*���а�ǰ��ѡ��*/
void SettingRanking() {
	GotoXY(20, 10);
	printf("��ѡ���Ӧ�Ѷȵ����а�");
	GotoXY(43, 12);
	printf("1.���Ѷ�");
	GotoXY(43, 14);
	printf("2 �е��Ѷ�");
	GotoXY(43, 16);
	printf("3.�����Ѷ�");
	GotoXY(43, 18);
	printf("4.��ս�Ѷ�");
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

/*���а�˵���ʵ��*/
void PrintRanking()   //���а���ʾ
{
	system("cls");
	int i = 0;
	FILE* fp;
	record gdata[1000];
	if (block_num == 10) {
		fp = fopen("out1.txt", "rb"); //ͨ����д��ͬ���ļ���ʵ�ֲ�ͬ���а����ʾ
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
		printf("���޼�¼");
		Hide();
		return;
	}
	rewind(fp);
	while (!feof(fp))                           //feof����ļ��Ƿ���������������������ط���
	{
		fread(&gdata[i], sizeof(struct record), 1, fp);
		i++;
	}
	qsort(gdata, i-1, sizeof(record), Cmpfunc);       //���÷�����
	GotoXY(52, 3);
	printf("���а�");
	GotoXY(42, 5);
	printf("�÷�\t\t\tʱ��\n");
	int ret = (i - 1) > 5 ? 5 : (i-1);
	for (int j = 0; j < ret; j++)                     //��ʾǰi-1������5���ĵ÷�,��ֹ���а����
	{
		GotoXY(43, 7 + j * 2); //��ӡ�÷�
		printf("%d\t\t", gdata[j].fraction);
		printf("%d/%02d/%02d ", gdata[j].year + 1900, gdata[j].mon + 1, gdata[j].day);
		printf("%02d:%02d:%02d", gdata[j].hour, gdata[j].min, gdata[j].sec);
	}
	fclose(fp);                               //ɾ���ļ�ָ��
	Hide();
	char ch = _getch();
	system("cls");
}

/*���ڲ˵�ʵ��*/
void About() {
	GotoXY(39, 12);
	printf("23050514��������ʦ�����С��С����ҵ");
	GotoXY(43, 14);
	printf("̰����-����̨��Ϸ");
	GotoXY(43, 16);
	printf("������������ϼ��˵�");
	Hide();		//���ع��
	char ch = _getch();
	system("cls");
}

/*�����˵�ʵ��*/
void Help() {
	GotoXY(40, 11);
	printf("wasd ������������");
	GotoXY(40, 13);
	printf("����ײ��ײǽ���ϰ���ʱ��Ϸ����ʱ");
	GotoXY(40, 15);
	printf("��ɫ$����һ��,��ɫ$��������,��ɫ$��������");
	GotoXY(40, 17);
	printf("ײβ������������,����ʧȥ�Լ���β��");
	GotoXY(45, 22);
	printf("������������ϼ��˵�");
	Hide();		//���ع��
	char ch = _getch();
	system("cls");
}

/*��ʼ����ͼ����*/
void InitMap() {
	Music(2);
	Hide();	   				//���ع��
	//������ͷλ���ڵ�ͼ����
	snake.snakeNode[0].x = MAP_WIDTH / 2 - 1;
	snake.snakeNode[0].y = MAP_HEIGHT / 2 - 1;
	GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y); 	  //������ƶ�����ͷλ��
	SetColor(3, 0);
	printf("@"); 				//��ӡ��ͷ
	SetColor(7, 0);
	snake.length = 3;   		//�����߳���ʼֵΪ3��
	snake.speed = 250;  		//�����߳�ʼ�ƶ��ٶ�Ϊ250
	now_Dir = RIGHT;            //��ǰ��ͷ����
	//��ʾ����
	for (int i = 1; i < snake.length; i++) {
		//���������������λ�ú���ͷλ����ͬ
		snake.snakeNode[i].y = snake.snakeNode[i - 1].y;
		//��������ĺ�����λ�ã���������ͷ�����,���Ժ��������μ�1
		snake.snakeNode[i].x = snake.snakeNode[i - 1].x - 1;
		GotoXY(snake.snakeNode[i].x, snake.snakeNode[i].y); 	//�ƶ���굽����λ��
		SetColor(3, 0);
		printf("o");   		//��ӡ����
		SetColor(7, 0);
	}
	//���ɵ�ͼ���±߽�
	for (int i = 0; i < MAP_WIDTH; i++) {
		GotoXY(i, 0);
		printf("-");
		GotoXY(i, MAP_HEIGHT - 1);
		printf("-");
	}
	//���ɵ�ͼ���ұ߽�
	for (int i = 1; i < MAP_HEIGHT - 1; i++) {
		GotoXY(0, i);
		printf("|");
		GotoXY(MAP_WIDTH - 1,i);
		printf("|");
	}
	//����Ԥ���趨�����������ϰ���
	int num = block_num;
	int flag;
	while (num>0) {
		block[num].x = rand() % (MAP_WIDTH - 2) + 1;
		block[num].y = rand() % (MAP_HEIGHT - 2) + 1;
		flag = 1;
		for (int k = 0; k <= snake.length - 1; k++) {
			if (snake.snakeNode[k].x == block[num].x && snake.snakeNode[k].y == block[num].y) { //�ж��������ص�
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
	//����ʳ��
	PrintFood();
	//�÷�˵��
	GotoXY(50, 5);
	printf("��ǰ�÷�: 0 ");
}

/*����ʳ�ﺯ��*/
void PrintFood() {
	int flag_food = 1 ;
	int percent;
	while (flag_food)
	{
		flag_food = 0;
		//���������ʳ������λ��
		food.x = rand() % (MAP_WIDTH - 2) + 1;
		food.y = rand() % (MAP_HEIGHT - 2) + 1;
		//ѭ���ж�ʳ��λ���Ƿ���ߵ�λ���ص�������ص�����Ҫ��������ʳ��λ��
		for (int k = 0; k <= snake.length - 1; k++) {
			if (snake.snakeNode[k].x == food.x && snake.snakeNode[k].y == food.y) {
				flag_food = 1;  				//λ�����ص�����Ҫ����ѭ��
				break;
			}
		}
		//ѭ���ж�ʳ��λ���Ƿ���ϰ����λ���ص�,����ص�����Ҫ��������ʳ��λ��
		for (int i = 1; i <= block_num; i++) {
			if (food.x == block[i].x && food.y == block[i].y) {
				flag_food = 1; //λ���ص�,��Ҫ����ѭ��
				break;
			}
		}
		if (flag_food == 0) { //ֻ���ܽ���ѭ���Ҹ�λ�ò��ص�ʱ��������ʳ��(ԭ�������û��?)
			GotoXY(food.x, food.y);
			percent = rand() % 3; //������ʳ����ʾ�������,snake_length+=food_typeʵ�������ٶȵĲ�ͬ.
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

/*���ƶ�����ʵ��,����ֵΪ1��ʾ�����ƶ���Ϊ0��ʾֹͣ�ƶ�*/
int MoveSnake() {
	Snakenode temp;
	int flag = 0;
	temp = snake.snakeNode[snake.length - 1]; 			//��¼��β
	for (int i = snake.length - 1; i >= 1; i--)
		snake.snakeNode[i] = snake.snakeNode[i - 1];	//������������ǰ�ƶ�һ��λ��
	GotoXY(snake.snakeNode[1].x, snake.snakeNode[1].y);
	SetColor(3, 0);
	printf("o");  			//ǰ�������ӡһ����������������Ҫ��ӡ
	SetColor(7, 0);
	//��Ӧ�����޸�
	if (_kbhit()) {			//�������뷵��1���Ǽ������뷵��0
		direction = _getch();
		switch (direction) {
		case UP:  //����w��
			if (now_Dir != DOWN)		//�����ͷ���£��������ƶ��ļ�wʱ��������
				now_Dir = direction;
			break;
		case DOWN:  //����s��
			if (now_Dir != UP)			//�����ͷ���ϣ��������ƶ��ļ�sʱ��������
				now_Dir = direction;
			break;
		case LEFT:  //����a��
			if (now_Dir != RIGHT)		//�����ͷ���ң��������ƶ��ļ�aʱ��������
				now_Dir = direction;
			break;
		case RIGHT:  //����d��
			if (now_Dir != LEFT)		//�����ͷ���󣬰������ƶ��ļ�dʱ��������
				now_Dir = direction;
			break;
		}
	}
	switch (now_Dir) {   					//�������ڵķ����޸���ͷ��λ��
	case UP:snake.snakeNode[0].y--; break;		//�����ƶ�
	case DOWN:snake.snakeNode[0].y++; break;		//�����ƶ�
	case LEFT:snake.snakeNode[0].x--; break;		//�����ƶ�
	case RIGHT:snake.snakeNode[0].x++; break;	//�����ƶ�
	}
	//��ӡ��ͷ
	GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);
	SetColor(3, 0);
	printf("@");
	SetColor(7, 0);
	//�ж��Ƿ�Ե�ʳ������ͷ��λ�ú�ʳ���λ����ͬ��ʾ�Ե�ʳ��
	if (snake.snakeNode[0].x == food.x && snake.snakeNode[0].y == food.y) {
		Music(4);
		snake.length+=food_type;  		//�Ե�ʳ��ӳ�����ȡ����food_type����.
		flag = 1;        		//flagΪ1��ʾ�Ե�ʳ�Ϊ0��ʾû�гԵ�ʳ��
		snake.snakeNode[snake.length - 1] = temp;	//�Ե�ʳ���β��һ��
	}
	//����ߴ�ʱ״̬
	//û�Ե�ʳ��ʱ����ԭ������β��ӡһ���ո�ȥ��ԭ������β
	if (!flag) {
		GotoXY(temp.x, temp.y);
		printf(" ");
	}
	else {			//�Ե�ʳ�����Ҫ�ڵ�ͼ�����¸���һ��ʳ��
		PrintFood();
		GotoXY(50, 5);
		printf("��ǰ�÷�: %d ", snake.length - 3);  	//��ӡ�÷֣��÷�Ϊ�߳���ԭʼ����3 ----tips:�޸ĵ÷���ʾЧ��,����ո�������ʮλ���˻ظ�λ�����µ���ʾ����.
	}
	//�ж��Ƿ�����
	if (!IsCorrect()) { 	 	//�����ײ��ײǽ���������Ļ����ӡ���յ÷֣���Ϸ����
		Recordeddata();
		Music(3);
		system("cls");
		GotoXY(45, 14);
		printf("���յ÷֣�%d ", snake.length - 3);
		GotoXY(45, 16);
		printf("�����ˣ�");
		GotoXY(45, 18);
		printf("��������������˵�");
		char c = _getch();
		system("cls");
		return 0;
	}
	//�����ٶ�
	SpeedControl();
	Sleep(snake.speed);		//�ѽ��̹���һ��ʱ�䣬���ڿ������ƶ����ٶ�
	return 1;
}

/*�ж��Ƿ���ײ��ײǽ,����ֵΪ0��ʾ��ײ��ײǽ������Ϊ1*/
int IsCorrect() {
	if (snake.snakeNode[0].x == 0 || snake.snakeNode[0].y == 0 || snake.snakeNode[0].x == MAP_WIDTH - 1 || snake.snakeNode[0].y == MAP_HEIGHT - 1) //�ж���ͷ�Ƿ�ײǽ
		return 0;
	for (int i = 1; i < block_num; i++) {
		if (snake.snakeNode[0].x == block[i].x && snake.snakeNode[0].y == block[i].y)
			return 0;
	}
	for (int i = 1; i < snake.length; i++)   //�ж���ͷ�Ƿ�������ص����ص���ʾ��ײ
		if (snake.snakeNode[0].x == snake.snakeNode[i].x && snake.snakeNode[0].y == snake.snakeNode[i].y) {
			//��ײʱ����ʾ��ͷλ��,���⿴������ͷ.
			GotoXY(snake.snakeNode[i].x, snake.snakeNode[i].y);
			SetColor(3, 0);
			printf("@");
			SetColor(7, 0);
			//����ײ�����������Ľڵ�,��ղ��˻�������.
			int length = snake.length;
			for (int j=i+1; j < length; j++) {
				GotoXY(snake.snakeNode[j].x, snake.snakeNode[j].y);
				printf(" ");
				snake.length--;
			}
		}
	//��ʱˢ�»��ְ�,���Ӹ��лᵼ�µ÷�ˢ�²���ʱ.
	GotoXY(50, 5);
	printf("��ǰ�÷�: %d ", snake.length - 3);
	return 1;
}

/*�ٶȵ�������*/
void SpeedControl() {
	switch (snake.length) {  		//�����߳������ߵ��ƶ��ٶ�
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

/*����ɼ�����*/
void Recordeddata() 
{
	time_t timep;
	struct tm* ti;
	time(&timep);
	ti = localtime(&timep);              //��ȡϵͳʱ��
	record* gdata = (record*)malloc(sizeof(record));
	gdata->year = ti->tm_year;//��
	gdata->mon = ti->tm_mon;  //��
	gdata->day = ti->tm_mday; //��
	gdata->hour = ti->tm_hour;//ʱ
	gdata->min = ti->tm_min;  //��
	gdata->sec = ti->tm_sec;  //��
	gdata->fraction = snake.length - 3;
	/*�����ѶȲ�ͬ���浽��ͬ���ļ���, ����������а�*/
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

/*����������*/
int Cmpfunc(const void* a, const void* b) //������,ʹ��Ƕ��ʵ�����а������
{
	return(*(int*)b - *(int*)a);
}