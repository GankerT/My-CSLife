#include"Button.h"
#include <windows.h>
#include<fstream>
#include<conio.h>
#include<string>
#include<iostream>
//#include<bits/stdc++.h>
#include<mmsystem.h>
#pragma comment(lib,"WINMM.LIB")
#pragma comment( lib, "MSIMG32.LIB")
using namespace std;
#define enemy_Num 99 //��������
#define bullet_Num 500 //�ӵ�����
#define enemybullet0_Num 500 //С�͵���0�ӵ�����
#define enemybullet1_Num 100 //���͵���1�ӵ�����
#define bossbullet_Num 5 //boss�ӵ�����
#define height 650 //ҳ����
#define width 765

IMAGE Bullet;//����ӵ�
IMAGE role;//�����ͼ
IMAGE enemyimg[2];//������ͼ
IMAGE Enemybullet[2];//���ֵ��˵��ӵ�
IMAGE _background;//��Ϸ���汳��
IMAGE lose_background;//ʧ�ܱ���
IMAGE win_background;//ʤ������
IMAGE bossimg;//boss��ͼ
IMAGE bossbulletimg;//boss�ӵ���ͼ
IMAGE stopimg;//��ͣ��ͼ
IMAGE stopbackground;//��ͣ����
IMAGE changediff;//�����Ѷȱ���
IMAGE record_background;//�鿴��¼����



//��¼��˵����ֵ�����

//�û��ṹ��(����)
struct User
{
	char name[20];
	char password[20];
	//char passback_answer[3][10];��ȫ������ʱ�ò���
	int point;
	struct User* next;
};
User* p = NULL, * p1 = NULL, * p2 = NULL, * head = NULL;//��ȡ�û���ϢҪ�õ�
int n = 0;//�û�������

//����ͼƬ�زĵĳ�ʼ��  (�д�����)
IMAGE register_background;//ע�ᱳ��
IMAGE login_background;//��¼����
IMAGE menu_background;//��Ϸ���˵�����
IMAGE Producerlistimg;//����������

string title;//��Ϸ������
char username[20] = "";// ȫ�ֱ��������ڱ����˺ŵ�����
char password[20] = "";// ȫ�ֱ��������ڱ������������
char username1[20] = "";// ȫ�ֱ��������ڱ����˺ŵ�����
char password1[20] = "";// ȫ�ֱ��������ڱ������������
char password2[20] = "";// ȫ�ֱ��������ڱ������������
const int INPUT_LAYER_ID = 1; // �ı������ڵĲ㼶ID

int ms;//���˳��ּ��
int bullet_ms; //�ӵ����
int score = 0;//��Ϸ�÷�
//ģ�͵��ƶ���λ�ٶ�
int rank;//����,�Ѷ�
int speed;//�ӵ��ƶ��ٶ�
int enemybulletspeed;//�����ӵ��ƶ��ٶ�
int boss_spawn;
bool b_boosMusic;//boss���ֵĲ����ж�

int playerhp = 100;//���Ѫ��
//�ɻ��Լ�������ɫ�Ľṹ���ʼ��
struct plane {
	int x;//�����x����
	int y;//�����y����
	bool live;//�Ƿ����Һ͵��ˣ����Ƿ���ڣ����ӵ��Ļ���
	int hp;//����ֵ
	int enemywidth;//���˵�λ��
	int enemyheight;//���˵�λ��
	int bossheight;//boss��
	int bosswidth;//boss��


	int type;//�л����� С ��
}enemy[enemy_Num], player, boss, bullet[bullet_Num], enemybullet0[enemybullet0_Num], enemybullet1[enemybullet1_Num], bossbullet[3][bossbullet_Num];


//��¼ע��

void drawInputBox(int, int, int, int, char*);//�������
void login();//��¼����
void login_action(char[], char[]);//�����¼��������ĺ���
int  login_state(char[], char[]);//��¼״̬�жϺ���
void registered();//ע�ắ��
int file_size();//�ļ���Ϣ�жϺ���
void file_read();//��ȡ�ļ���Ϣ����
void do_free();//�ͷŶ�̬�ڴ溯��
void add();//����û�
void registered_action();//����ע���������ĺ���
void file_save();//��Ϣ�����ļ�����
void GameMenuView();//��Ϸ���˵�����
void ChangeDifficult();//�ı��Ѷ�
void ProducerlistView();//����������
void check_score();//�鿴��¼


//��Ϸ��

void GameInit();//��Ϸ��ʼ��
void PlayerMove();//��ҵ��ƶ�
void LoadGameImg();//������Ϸ��ͼ
void Gamedraw();//��Ϸ��λ����ͼ
void PlayGame();//��Ϸ�߼�����
void CreateBullet();//�����ӵ�
void enemyhp(int i);//������������
void CreateEnemy();//��������
void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg);//͸������
void ctrlFps(int start_time);//z֡�ʵ���
void BossMove();//boss���ƶ�
void GameOverview();//��Ϸ����
void GameWinview();//��Ϸʤ��



void drawInputBox(int x, int y, int inwidth, int inheight, char* text) {
	setfillcolor(WHITE);
	solidrectangle(x, y, x + inwidth, y + inheight);
	settextcolor(BLACK);
	rectangle(x, y, x + inwidth, y + inheight);
	settextcolor(BLACK);
	outtextxy(x + 5, y + 5, text);
	if (msg.message == WM_LBUTTONDOWN && inArea(x, y, msg.x, msg.y, inwidth, inheight)) {
		InputBox(text, 100, "������", "�����");
	}
}

//��¼
void login() {
	HWND hnd = GetHWnd();
	initgraph(1024, 576);
	setbkmode(TRANSPARENT);
	cleardevice();
	mciSendString("open menu1.mp3", NULL, 0, NULL);
	mciSendString("play menu1.mp3 repeat", NULL, 0, NULL);
	//mciSendString("setaudio music volume to 8", 0, 0, 0);
	loadimage(&login_background, "res\\login\\login_background.png", 1024, 576);
	putimage(0, 0, &login_background);
	setfillcolor(LIGHTGRAY);
	char arr[] = "������ս";
	char arr1[] = "�˺�";
	char arr2[] = "����";
	settextstyle(100, 0, "����");
	settextcolor(GREEN);
	// ��������
	int loginwidth = 1024 / 2 - textwidth(arr) / 2;
	int loginheight = 0;
	outtextxy(loginwidth, loginheight + 30, arr);
	char text1[] = "��Ϊikun";
	char text2[] = "ikun��¼";
	char text3[] = "�˳���Ϸ";

	while (1) {
		if (peekmessage(&msg, EX_MOUSE)) {
			if (button(340, 400, 150, 50, text1)) {
				// ��Ϊikun �����
				//�رյ�ǰ����
				//��ע�����
				closegraph();
				registered();
				break;
				cout << "��Ϊikun �����" << endl;
			}
			else if (button(540, 400, 150, 50, text2)) {
				// ikun��¼ �����
				login_action(username, password);
				cout << "ikun��¼ �����" << endl;
			}
			else if (button(440, 475, 150, 50, text3)) {
				// �˳���Ϸ �����
				cout << "�˳���Ϸ �����" << endl;
				exit(0);
				break;
			}
		}
		settextstyle(50, 0, "����");
		settextcolor(BLACK);
		outtextxy(200, 200, arr1);
		outtextxy(200, 300, arr2);
		drawInputBox(300, 200, 450, 50, username);
		drawInputBox(300, 300, 450, 50, password);
		FlushBatchDraw();
		BeginBatchDraw();
	}
	
	getchar();
	closegraph();
}

//ʵ�ֵ�¼����Ĺ��ܵĺ���
void login_action(char name[], char password[]) {
	int flag = login_state(name, password);
	switch (flag) {
	case 0:
		cout << "��¼�ɹ�!" << endl;
		cleardevice();
		GameMenuView();
		break;
	case 1: {
		cout << "���˺Ų�����" << endl;
		//��ȡ���ھ��
		HWND hnd = GetHWnd();
		//�������ڣ���ʾ�û�����
		int ok = MessageBox(hnd, "�˺���ϢΪ�ջ��˺Ų�����,�Ƿ�ȥע��", "��ʾ", MB_OKCANCEL);
		if (ok == 1) {
			cleardevice();
			registered();
		}
		break;
	}
	case 2: {
		HWND hnd = GetHWnd();
		//�������ڣ���ʾ�û�����
		int ok = MessageBox(hnd, "����Ϊ�ջ����������������������", "��ʾ", MB_OKCANCEL);
		cout << "�������" << endl;
	}
	}
}

//ע��
void registered() {
	initgraph(1024, 576);
	setbkmode(TRANSPARENT);
	cleardevice();
	// ��������
	loadimage(&register_background, "res\\registered\\registered_background.png", 1024, 576);
	putimage(0, 0, &register_background);
	char text1[] = "���ص�¼";
	char text2[] = "ȷ��ע��";
	char arr1[] = "�˺�";
	char arr2[] = "����";
	char arr3[] = "ȷ������";
	while (1) {

		BeginBatchDraw();
		if (peekmessage(&msg, EX_MOUSE)) {
			if (button(350, 450, 150, 50, text1)) {
				// ���ص�¼ �����
				closegraph();
				login();
				break;
			}
			else if (button(550, 450, 150, 50, text2)) {
				// ȷ��ע�� �����
				registered_action();
				//closegraph();
				//���˵�����
				cout << "��ť�������" << endl;

			}
		}
		settextstyle(50, 0, "����");
		settextcolor(BLACK);
		outtextxy(200, 150, arr1);
		outtextxy(200, 250, arr2);
		outtextxy(100, 350, arr3);
		drawInputBox(300, 150, 450, 50, username1);
		drawInputBox(300, 250, 450, 50, password1);
		drawInputBox(300, 350, 450, 50, password2);
		FlushBatchDraw();
	}
	getchar();
	closegraph();
}

//����ע��Ĺ��ܵĺ���
void registered_action() {
	if (strlen(password1) < 6) {
		HWND hnd = GetHWnd();
		//�������ڣ���ʾ�û�����
		int ok = MessageBox(hnd, "�������", "��ʾ", MB_OKCANCEL);
	}
	else if (strcmp(password1, password2) != 0) {
		HWND hnd = GetHWnd();
		//�������ڣ���ʾ�û�����
		int ok = MessageBox(hnd, "���벻һ��", "��ʾ", MB_OKCANCEL);
	}
	else {
		add();
		file_save();
		do_free();
		login();
	}
}

//�ļ���Ϣ�жϺ���
int file_size()
{
	FILE* p = fopen("user.txt", "r");
	int size = 0;
	fseek(p, 0, 2);  //��Χ��0��ʼλ��ĩβ
	size = ftell(p);  //�ж��ļ���С,��Ϊ�գ�size=0 
	fclose(p);
	return size;
}

//��ȡ�ļ���Ϣ����
void file_read()
{
	if (file_size())
	{
		FILE* fp;
		if ((fp = fopen("./user.txt", "rb")) == NULL)
		{
			printf("�޷����ļ�!");
			exit(0);
		}
		do
		{
			p1 = (struct User*)malloc(sizeof(struct User));
			if (n == 0)
				head = p1;
			else
				p2->next = p1;
			fread(p1, sizeof(struct User), 1, fp);//���ļ���������p1=NULL
			p2 = p1;
			n += 1;
		} while (p2->next != NULL);
		fclose(fp);
		printf("��ȡ���!\n");

	}

}

//��Ϣ�����ļ�����
void file_save()
{
	FILE* fp;
	struct User* p;
	if ((fp = fopen("./user.txt", "wb")) == NULL)
		printf("�޷����ļ�!");
	p = head;
	while (p != NULL)
	{
		if (fwrite(p, sizeof(struct User), 1, fp) != 1)
		{
			printf("д�����ݳ���\n");
			fclose(fp);
			break;
		}
		p = p->next;
	}
	fclose(fp);
	printf("�洢���\n");
}




int login_state(char username[], char pass[])
{
	if (file_size() == 0)
		return 1;
	file_read();
	p = head;
	while (p != NULL)
	{
		if (strcmp(p->name, username) == 0)
		{
			if (strcmp(p->password, pass) != 0)
			{
				do_free();
				return 2;//�������
			}
			else {
				do_free();
				return 0;
			}//��¼�ɹ�
		}
		p = p->next;
	}
	do_free();
	return 1;//�˺Ų�����
}


void add()//����û�
{
	file_read();
	p1 = (struct User*)malloc(sizeof(struct User));
	if (n == 0)
		head = p1;
	else
		p2->next = p1;
	strcpy_s(p1->name, username1);
	strcpy_s(p1->password, password1);
	p1->next = NULL;
	p2 = p1;
	printf("��ӳɹ�");
}

//�ͷŶ�̬�ڴ溯��
void do_free()
{
	struct User* f;
	do
	{
		f = head;
		head = head->next;
		free(f);
	} while (head != NULL);
	n = 0;
	printf("������");
}




void save_score(int mark)//�������溯��
{
	file_read();
	p = head;
	while (p != NULL)
	{
		if (strcmp(p->name, username) == 0)
		{
			if (p->point < mark)
			{
				p->point = mark;
				file_save();
			}
			break;
		}
		else p = p->next;
	}
	do_free();
}

//��ѯ��¼
void check_score()
{
	initgraph(1024, 768);
	loadimage(&record_background, "./record_background.png", 1024, 768);
	putimage(0, 0, &record_background);
	setbkmode(TRANSPARENT);

	int nowuser_score = 0;
	file_read();//��ȡ�ļ����ݻ�÷���
	p = head;
	while (p != NULL)
	{
		if (strcmp(p->name, username) == 0) {
			if(p->point>=0)
			nowuser_score = p->point;//��¼��ǰ�û�����ߵ÷�
		}
		p = p->next;
	}
	do_free();
	string str = to_string(nowuser_score);
	char s[15];//����������ַ���
	strcpy(s, str.c_str());


	setbkmode(TRANSPARENT);
	settextstyle(50, 0, "MicroSoft YaHei");
	settextcolor(BLACK);
	outtextxy(750, 250, "��������߷�:");




	//settextcolor(BLUE);
	settextstyle(50, 50, "����");
	//setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 29, 29));
	outtextxy(750, 320, s);

	while (true) {   //����ж�
		if (peekmessage(&msg, EX_MOUSE)) {}//��ȡ�����Ϣ
		BeginBatchDraw();
		//���������ֱ�ӷ��ص���Ϸ���˵�
		if (button(320, 500, 200, 60, "���ز˵�"))
		{
			return GameMenuView();
		}
		EndBatchDraw();
		msg.message = 0; // ѭ��������ȫ�ֱ���msg����
	}

}

int hard = 1;//�Ѷ�Ĭ��1
void ChangeDifficult()
{
	//�˺���������ֵ��������Ҫ��һ��ȫ�ֱ���hard,�������Ѷȣ���1,2,3�����������ѶȺ󣬻ص����˵�
	//closegraph();
	initgraph(1024, 576);
	loadimage(&changediff, "./changediff.png");
	putimage(0, 0, &changediff);
	HWND hnd = GetHWnd();
	
	int wide = 300;
	int hight = 100;
	setbkmode(TRANSPARENT);
	setbkmode(TRANSPARENT);
	settextstyle(25, 0, "MicroSoft YaHei");
	settextcolor(BLACK);
	outtextxy(618, 500, "��סWASD�����������������ƶ�����K��������" );
	outtextxy(618, 520, "���ܿ����� ���ɻ����Ϸʤ��");
	//������gamemenuview�������Ѿ�ʹ��Beginbatchdraw�������˴�Ҳ����ʹ��
	while (1)
	{
		if (peekmessage(&msg, EX_MOUSE))
		{
			BeginBatchDraw();
			if (button((1024 - wide), 50, wide, hight, "��"))
			{
				hard = 1;
				break;
			}
			else if (button((1024 - wide), 50 + hight + 50, wide, hight, "��ͨ"))
			{
				hard = 2;
				break;
			}
			else if (button((1024 - wide), 50 + hight + 50 + hight + 50, wide, hight, "����"))
			{
				hard = 3;
				break;
			}
			EndBatchDraw();
		}
	}
	return GameMenuView();
}

void ProducerlistView() {
	initgraph(797, 800);
	loadimage(&Producerlistimg, "./Producerlistimg.png");
	//��ջ���
	putimage(0, 0, &Producerlistimg);
	//���ر���ͼƬ
		while (true) {   //����ж�
			if (peekmessage(&msg, EX_MOUSE)) {}//��ȡ�����Ϣ
			BeginBatchDraw();
			//���������ֱ�ӷ��ص���Ϸ���˵�
			if (button(0, 400, 250, 60, "���ز˵�"))
			{
				return GameMenuView();
			}
			EndBatchDraw();
			msg.message = 0; // ѭ��������ȫ�ֱ���msg����
		}
	
	

}







//��Ϸ���˵�����
void GameMenuView() {
	initgraph(1024, 768, 0);
	loadimage(&menu_background, "res\\game_menu\\game_menu_background.jpg", getwidth(), getheight());
	putimage(0, 0, &menu_background);
	setbkmode(TRANSPARENT);
	settextcolor(BLUE);
	settextstyle(150, 80, "����");
	setbkmode(TRANSPARENT);
	settextcolor(RGB(172, 172, 172));
	outtextxy(100, 56, "�̵�");

	while (true)
	{
		peekmessage(&msg, EX_MOUSE);
		BeginBatchDraw();
		if (button(700, 100, 200, 60, "��ʼ��Ϸ"))
		{
			mciSendString("close menu1.mp3", NULL, 0, NULL);
			LoadGameImg();
			PlayGame();
			
		}
		if (button(700, 200, 200, 60, "�޸��Ѷ�"))
		{
			cout << "ChangeDifficult()" << endl;
			ChangeDifficult();
		}
		if (button(700, 300, 200, 60, "�鿴��¼"))
		{
			cout << "CheckRecording()" << endl;
				check_score();
		}
		if (button(700, 400, 200, 60, "������"))
		{
			cout << "ProducerlistView()" << endl;
			ProducerlistView();
		}
		if (button(700, 500, 200, 60, "�˳���Ϸ"))
		{
			exit(0);
		}
		EndBatchDraw();
		msg.message = 0;
	}
	cleardevice();
	getchar();
}







void GameOverview() {

	initgraph(1024, 768);	//�������ں͵��ԣ����ϵ�ʱ���ɾ
	//��ջ���
	cleardevice();
	//���ر���ͼƬ
	loadimage(&lose_background, "./lose.jpg", 1024, 768);
	putimage(0, 0, &lose_background);
	//���ֲ���
	settextstyle(72, 0, "����");	//�ı���ʽ��(�߶ȣ����<����Ӧ����0>������)
	settextcolor(RED);//�ı���ɫ
	setbkmode(TRANSPARENT);//�ı�����ģʽ��͸��
	outtextxy(30, 100, "��սʧ��");
	settextcolor(BLACK);
	settextstyle(30, 0, "΢���ź�");
	outtextxy(35, 200, "��������ϰʱ�����������");
	settextcolor(RED);
	outtextxy(35, 270, "���۾�ժ��");
	settextcolor(BLACK);
	outtextxy(140, 270, "ЪһЪ���ԣ�");
	outtextxy(36, 520, "����...");
	PlaySound("gamefail.wav", NULL, SND_FILENAME | SND_ASYNC);
	//��ť����
	while (true) {//����ж�
		if (peekmessage(&msg, EX_MOUSE)) {}//��ȡ�����Ϣ
		//˫�����ͼ���Ƶ��ˢ�����⣺
		BeginBatchDraw();

		if (button(35, 330, 280, 60, "���ز˵�"))
		{//������ز˵�����ת���˵�����
			mciSendString("open menu1.mp3", NULL, 0, NULL);
			mciSendString("play menu1.mp3 repeat", NULL, 0, NULL);
			mciSendString("setaudio music volume to 8", 0, 0, 0);
			GameMenuView();    
		}

		if (button(35, 420, 280, 60, "���¿�ʼ"))
		{//������¿�ʼ����ת����Ϸ�������Ȼ��ʼ��Ϸ
			Gamedraw();
			PlayGame();
		}

		if (button(36, 550, 280, 60, "ԭ�ظ��"))
		{//��������Ի���
			HWND hnd = GetHWnd();
			//MessageBox(hnd, "ԭ�����ǲ����Ե�~\n���Ǽ�����Ը��V hali 50��Ҳ���ǲ�������С��...", "����ԭ�ظ�����", MB_OKCANCEL);
			if (MessageBox(NULL, ("ԭ�����ǲ����Ե�~\n���Ǽ�����Ը��V hali 50��Ҳ���ǲ�������С��..."), ("����ԭ�ظ�����"), MB_YESNO | MB_ICONINFORMATION) == IDYES) {//�жϵ���İ�ť�ǲ��� "��"
				MessageBox(hnd, "��Ҳ����~", "�ٺ�", MB_OKCANCEL);
			}
			else MessageBox(hnd, "��ʵ�����Ը����Ҳû�취������", "�ٺ�", MB_OKCANCEL);
		}
		
		EndBatchDraw();
		//����ͼ���̷�����������֮��
		msg.message = 0;//ѭ��������ȫ�ֱ���msg����
	}
}


void GameWinview() {

	//�������ں͵��ԣ����ϵ�ʱ���ɾ
	initgraph(1024, 768);
	//mciSendString("close song", NULL, 0, NULL);
	PlaySound("gamewin.wav", NULL, SND_FILENAME | SND_ASYNC);
	//��ջ���
	cleardevice();
	//���ر���ͼƬ
	loadimage(&win_background, "./win.png", 1024, 768);
	putimage(0, 0, &win_background);
	//���ֲ���
	settextstyle(90, 0, "����");	//�ı���ʽ��(�߶ȣ����<����Ӧ����0>������)
	settextcolor(RED);//�ı���ɫ
	setbkmode(TRANSPARENT);//�ı�����ģʽ��͸��
	outtextxy(750, 70, "WIN!!!!");//
	settextstyle(40, 0, "����");
	outtextxy(840, 170, "�÷�");
	outtextxy(755, 225, "114514");
	//������ʾ��
	setfillcolor(WHITE);//�����ɫ
	solidrectangle(750, 220, 1000, 290);//�ޱ߿��ʵ�ľ���

	string winbkg_score = "test";//�����ַ������Խ��ռƷֵ�����
	outtextxy(755, 235, ("����:" + to_string(score)).data());//������ʾλ��
	settextcolor(RGB(184, 134, 248));
	settextstyle(30, 0, "΢���ź�");
	outtextxy(785, 295, "���Ϊ�� �ʣ� о��");
	//��ť����
	while (true) {//����ж�
		if (peekmessage(&msg, EX_MOUSE)) {}//��ȡ�����Ϣ
		//˫�����ͼ���Ƶ��ˢ�����⣺
		BeginBatchDraw();

		if (button(750, 355, 250, 60, "���ز˵�"))
		{//������ز˵�����ת���˵�����
			save_score(score);
			mciSendString("open menu1.mp3", NULL, 0, NULL);
			mciSendString("play menu1.mp3 repeat", NULL, 0, NULL);
			mciSendString("setaudio music volume to 8", 0, 0, 0);
			GameMenuView();  //����û����,��ע����
		}

		if (button(750, 425, 250, 60, "���¿�ʼ"))
		{//������¿�ʼ����ת����Ϸ�������Ȼ��ʼ��Ϸ
			Gamedraw();
			PlayGame();
		}
		EndBatchDraw();
		//����ͼ���̷�����������֮��
		msg.message = 0;//ѭ��������ȫ�ֱ���msg����
	}

}


//��ͣ����
void Stopview() {
	initgraph(1024, 768);
	//��ջ���
	cleardevice();
	//mciSendString("pause battle1.mp3", NULL, 0, NULL);
	if (b_boosMusic) {
		//system("pause");
		mciSendString("pause battle1.mp3", NULL, 0, NULL);
	}
	else {
		//system("pause");
		mciSendString("pause boss.mp3", NULL, 0, NULL);
	}
	//mciSendString("close song", NULL, 0, NULL);
	//���ر���ͼƬ
	while (1) {
		putimage(0, 0, &stopbackground);
		
		while (true) {   //����ж�
			if (peekmessage(&msg, EX_MOUSE)) {}//��ȡ�����Ϣ

			BeginBatchDraw();

			//��������Իص���ǰ��Ϸ
			if (button(750, 220, 250, 60, "������Ϸ"))
			{
				if (b_boosMusic) {
					mciSendString("resume battle1.mp3", NULL, 0, NULL);
					initgraph(height, width);// �ص�ԭ����Ϸ�ķֱ���
					return;
				}
				else {
					mciSendString("resume boss.mp3", NULL, 0, NULL);
					initgraph(height, width);// �ص�ԭ����Ϸ�ķֱ���
					return;
				}
				
			}

			//���������ֱ�ӷ��ص���Ϸ���˵�
			if (button(0, 220, 250, 60, "���ز˵�"))
			{
				mciSendString("close battle1.mp3", NULL, 0, NULL);
				mciSendString("open menu1.mp3", NULL, 0, NULL);
				mciSendString("play menu1.mp3 repeat", NULL, 0, NULL);
				mciSendString("setaudio music volume to 8", 0, 0, 0);
				return GameMenuView();
			}
			EndBatchDraw();
			msg.message = 0; // ѭ��������ȫ�ֱ���msg����
		}
	}
}







void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg) //ʵ��͸����ͼ
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

void GameInit() {
	player.x = width / 2;
	player.y = height - 65;
	player.live = true;
	playerhp = 100;
	score = 0;
	enemybulletspeed = 5;
	//��ʼ����ҵ�ÿ���ӵ���λ��
	for (int i = 0; i < bullet_Num; i++) {
		bullet[i].x = 0;
		bullet[i].y = 0;
		bullet[i].live = false;
	}

	//��ʼ������״̬
	for (int i = 0; i < enemy_Num; i++) {
		enemy[i].live = false;
		enemyhp(i);
	}
	//��ʼ�����˵�ÿ���ӵ���״̬
	
	for (int i = 0; i < enemybullet0_Num; i++) {
		enemybullet0[i].x = 0;
		enemybullet0[i].y = 0;
		enemybullet0[i].live = false;
	}

	for (int i = 0; i < enemybullet1_Num; i++) {
		enemybullet1[i].x = 0;
		enemybullet1[i].y = 0;
		enemybullet1[i].live = false;
	}

	//��ʼ��boss��ÿ���ӵ���״̬
	for (int i = 0; i < bossbullet_Num; i++) {
		for (int j = 0; j < 3; j++) {
			bossbullet[j][i].x = 0;
			bossbullet[j][i].y = 0;
			bossbullet[j][i].live = false;
		}
}
	//��ʼ��boss

	boss.live = true;
	boss.x = 300;
	boss.y = -210;
	boss.hp = 100;
	boss.bossheight = 250;
	boss.bosswidth = 210;
	b_boosMusic = true;

	
	/*����
	enemybullet[0].live = true;
	enemybullet[0].x = 50;
	enemybullet[0].y = 50;
	*/
}

void enemyhp(int i) {

	int randflag = rand() % 10;
	
	//randflag�����趨����
	if (randflag==4) {
		enemy[i].type = 1;//����
		enemy[i].hp = 3;//����ֵ
		enemy[i].enemyheight = 115;
		enemy[i].enemywidth = 106;
	}
	else {
		enemy[i].type = 0;//С��
		enemy[i].hp = 1;//����ֵ
		enemy[i].enemyheight = 49;
		enemy[i].enemywidth = 70;
	}
}



//����ӵ�����
void CreateBullet() {
	for(int i=0;i<bullet_Num;i++){
		if(bullet[i].live==false){
		bullet[i].x=player.x+35;
		bullet[i].y=player.y;
		bullet[i].live=true;
		break;
		}
	}
}

//�����ӵ�����
void CreateEnemyBullet() {

	for (int j = 0; j < enemy_Num; j++) {
		if (enemy[j].live == true) {
			if (enemy[j].type == 1) {
				for (int i = 0; i < enemybullet1_Num; i++) {
					if (enemybullet1[i].live == false) {
						enemybullet1[i].x = enemy[j].x ;
						enemybullet1[i].y = enemy[j].y;
						enemybullet1[i].live = true;
						break;
					}
				}
			}

			if (enemy[j].type == 0) {
				for (int i = 0; i < enemybullet0_Num; i++) {
					if (enemybullet0[i].live == false) {
						enemybullet0[i].x = enemy[j].x + 35;
						enemybullet0[i].y = enemy[j].y;
						enemybullet0[i].live = true;
						break;
					}
				}
			}

		}
	}
}

//����boss���ӵ�
void CreateBossBullet() {
	
	if (boss.live == true) {
		for (int i = 0; i < bossbullet_Num; i++) {
			for (int j = 0; j < 3; j++) {
				if (bossbullet[j][i].live == false) {
					bossbullet[j][i].x = boss.x + 35;
					bossbullet[j][i].y = boss.y;
					bossbullet[j][i].live = true;
				}
			}
		}
	}
}


void BulletMove() {//�ӵ��ƶ�

	for (int i = 0; i < bullet_Num; i++) {
		if (bullet[i].live == true) {
			bullet[i].y -= 15;//�ӵ�ֻ�����µ��ƶ�
				if (bullet[i].y < 0) {//�ӵ�������
					bullet[i].live = false;//�ӵ�û��
				}
		}
	}
}


void EnemyBulletMove() {//�����ӵ��ƶ�
	//���͵���
	for (int i = 0; i < enemybullet1_Num; i++) {
		if (enemybullet1[i].live == true) {
			enemybullet1[i].y += enemybulletspeed;;//�ӵ�ֻ�����µ��ƶ�
			if (enemybullet1[i].y > width) {//�ӵ�������
				enemybullet1[i].live = false;//�ӵ�û��
			}
		}
	}

	//С�͵���
	for (int i = 0; i < enemybullet0_Num; i++) {
		if (enemybullet0[i].live == true) {
			enemybullet0[i].y += enemybulletspeed;//�ӵ�ֻ�����µ��ƶ�
			if (enemybullet0[i].y > width) {//�ӵ�������
				enemybullet0[i].live = false;//�ӵ�û��
			}
		}
	}
	
}

void BossBulletMove() {

	//��һ�� ������
	for (int i = 0; i < bossbullet_Num; i++) {
		if (bossbullet[0][i].live == true) {
			bossbullet[0][i].y += enemybulletspeed;//�ӵ�ֻ���µ��ƶ�
			if (bossbullet[0][i].y > width) {//�ӵ�������
				bossbullet[0][i].live = false;//�ӵ�û��
			}
		}
	}

	//�ڶ��� ��������
	for (int i = 0; i < bossbullet_Num; i++) {
		if (bossbullet[1][i].live == true) {
			bossbullet[1][i].y += enemybulletspeed;
			bossbullet[1][i].x -= 5;//�ӵ�ֻ���µ��ƶ�
			if (bossbullet[1][i].y > width) {//�ӵ�������
				bossbullet[1][i].live = false;//�ӵ�û��
			}
		}
	}

	//������ ��������
	for (int i = 0; i < bossbullet_Num; i++) {
		if (bossbullet[2][i].live == true) {
			bossbullet[2][i].y += enemybulletspeed;
			bossbullet[2][i].x += 5;//�ӵ�ֻ���µ��ƶ�
			if (bossbullet[2][i].y > width) {//�ӵ�������
				bossbullet[2][i].live = false;//�ӵ�û��
			}
		}
	}


}

void PlayerMove()
{

	speed = 10;
	if (GetAsyncKeyState('A')) {
		if (player.x > 0)
			player.x -= speed;
	}//����
	if (GetAsyncKeyState('D')) {
		if (player.x + 175 < width)
			player.x += speed;
	}//����

	if (GetAsyncKeyState('W')) {
		if (player.y > 0)
			player.y -= speed;
	}//����

	if (GetAsyncKeyState('S')) {
		if (player.y - 50 < height)
			player.y += speed;
	}//����


	static DWORD t1 = 0, t2 = 0;
	if (GetAsyncKeyState('K') && t2-t1 > 100) {
		PlaySound("shoot1_01.wav", NULL, SND_FILENAME | SND_ASYNC);
		CreateBullet();
		t1 = t2;
		//�ӵ�����ļ��ʵ��
	}//��k�����ӵ�
	t2 = GetTickCount();
}



//����ͼƬ
void LoadGameImg() {
	loadimage(&_background, "./beijing.png");
	loadimage(&role, "./player1.png");
	loadimage(&Bullet, "./bullet.png");
	loadimage(&enemyimg[0], "./enemy0.png");
	loadimage(&enemyimg[1], "./enemy1.png");
	loadimage(&Enemybullet[0], "./enemybullet0.png");
	loadimage(&Enemybullet[1], "./enemybullet1.png");
	loadimage(&bossimg, "./boss.png");
	loadimage(&bossbulletimg, "./bossbullet.png");
	loadimage(&stopimg, "./stop.png");
	loadimage(&stopbackground, "./stopbackground.png",1024,768);
	
}


void Gamedraw() {

	BeginBatchDraw();
	putimage(0, 0, &_background);
	//��ͣ����ʾ
	
	transparentimage3(NULL, 560, 40, &stopimg);
	//������ʾ
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, "MicroSoft YaHei");
	settextcolor(BLACK);
	outtextxy(0, 0, ("����:" + to_string(score)).data());

	//���������ʾ
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, "MicroSoft YaHei");
	settextcolor(RED);
	outtextxy(525, 0, ("HP:" + to_string(playerhp)).data());
	

	//putimage(player.x, player.y, &role);
	transparentimage3(NULL, player.x, player.y, &role);

	//�ӵ�����
	
	//���
	for (int i = 0; i < bullet_Num; i++) {
		if (bullet[i].live == true) {
			transparentimage3(NULL, bullet[i].x, bullet[i].y, &Bullet);
		}
	}


	//����
	
	//���͵���
			for (int i = 0; i < enemybullet1_Num; i++) {
				if (enemybullet1[i].live == true&&enemy[i].type==1) {
					transparentimage3(NULL, enemybullet1[i].x, enemybullet1[i].y, &Enemybullet[1]);
				}
			}
		

	//С�͵���
			for(int i = 0; i < enemybullet0_Num; i++) {
				if (enemybullet0[i].live == true&&enemy[i].type==0) {
					transparentimage3(NULL, enemybullet0[i].x, enemybullet0[i].y, &Enemybullet[0]);
				}
			}
		
		
     //boss
			


	//���˻���
	for (int i = 0; i < enemy_Num; i++) {
		if (enemy[i].live == true) {
			if (enemy[i].type == 1) {//���͵�
				transparentimage3(NULL, enemy[i].x, enemy[i].y, &enemyimg[1]);
			}

			if (enemy[i].type == 0) {//С�͵�
				transparentimage3(NULL, enemy[i].x, enemy[i].y, &enemyimg[0]);
			}

		}
		
	}
	 

	//boss�Ļ���+�ӵ��Ļ���
	if (score >= boss_spawn && boss.live == true) {
		
		transparentimage3(NULL, boss.x, boss.y, &bossimg);
		CreateBossBullet();
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < bossbullet_Num; i++) {
				if (bossbullet[j][i].live == true) {
					transparentimage3(NULL, bossbullet[j][i].x, bossbullet[j][i].y, &bossbulletimg);
				}
			}
		}
		BossBulletMove();
		BossMove();

	}
	
	if (boss.y > -210 && b_boosMusic)
	{
		b_boosMusic = false;
		mciSendString("close battle1.mp3", NULL, 0, NULL);
		mciSendString("open boss.mp3", NULL, 0, NULL);
		mciSendString("play boss.mp3 repeat", NULL, 0, NULL);
	}

	EndBatchDraw();
			
}

void CreateEnemy() {//��������
	for (int i = 0; i < enemy_Num; i++) {
		if (enemy[i].live == false) {
			enemy[i].live = true;
			enemy[i].x = rand() % (width);
			enemy[i].y = 0;
			enemyhp(i);

			static DWORD t5 = 0, t6 = 0;
			if (t6 - t5 > bullet_ms) {
				t5 = t6;
				CreateEnemyBullet();
			}

			t6 = clock();
			break;
		}
	}
}




void ctrlFps(int start_time) //����֡��
{
	clock_t running_time = clock() - start_time;
	if ((13 - running_time) >= 0)//��ֹ˯�ߺ���ʹ�ø���
		Sleep(13 - running_time);//��̬˯��

	int FPS = 1000 / (clock() - start_time);
	
	settextcolor(0xFFA500);
	settextstyle(30, 0, TEXT("΢���ź�"));
	
}


void EnemyMove() {
		int speed = 1;
		for (int i = 0; i < enemy_Num; i++) {
			if (enemy[i].live == true) {
				enemy[i].y += speed;//����ֻ�����µ��ƶ� ���ٶ�
				if (enemy[i].y > height) {//���˳�����
					enemy[i].live = false;//����û��
				}

				//�������˵���ײ�ж�
				if (player.x > enemy[i].x && player.x < enemy[i].x + enemy[i].enemywidth
					&& player.y>enemy[i].y && player.y < enemy[i].y + enemy[i].enemyheight) {
					enemy[i].live = false;
					if(enemy[i].type==0)//����С�͵���
					playerhp -= 10;
					if (enemy[i].type == 1)//�������͵���
					playerhp -= 20;
				}
			}
		}
	
}

//boss���ƶ�
void BossMove() {
	
	static int bossspeed = 5;
	
		if (boss.y < 0)								//boss��ǰҡ(װ�ƽ���)
		{
			boss.y +=1 ;
		}

		else
		{
			boss.x += bossspeed;						//boss������ҡ��
			if (boss.x + 250 > height || boss.x < 0)
			{
				bossspeed =  - bossspeed;
			}
		}
	

}
void ShootingEnemy() {
	int flag = 0;
	//�����
	for (int i = 0; i < enemy_Num; i++) {
		if (enemy[i].live == false) {
			continue;
		}
		flag = 0;
		for (int j = 0; j < bullet_Num; j++) {
			if (bullet[j].live == false) {
				continue;
			}
			if (bullet[j].x > enemy[i].x && bullet[j].x < enemy[i].x + enemy[i].enemywidth
				&& bullet[j].y>enemy[i].y && bullet[j].y < enemy[i].y + enemy[i].enemyheight) {
				bullet[j].live = false;
				enemy[i].hp--;
				flag = 1;
			}
			if (enemy[i].hp <= 0) {
				if (enemy[i].type == 1&&flag==1)score += 20;
				if (enemy[i].type == 0&&flag==1)score += 10;
				enemy[i].live = false;
			}
		}
	}

	//��boss
	for (int j = 0; j < bullet_Num; j++) {
		if (bullet[j].live == false) {
			continue;
		}
		if (bullet[j].x > boss.x && bullet[j].x < boss.x + boss.bosswidth
			&& bullet[j].y>boss.y && bullet[j].y < boss.y + boss.bossheight) {
			bullet[j].live = false;
			boss.hp--;

		}
		if (boss.hp <= 0) {//boss������Ϸ����
			boss.live = false;
			//gameover();
		}
	}
}
 

//���˹������
void Shootingplayer() {
	//���͵����ж�
	for (int i = 0; i < enemybullet1_Num; i++) {
		if (enemybullet1[i].live == false) continue;
		
		if(enemybullet1[i].x+10>=player.x&& enemybullet1[i].x<=player.x+40&&
			enemybullet1[i].y>=player.y&&enemybullet1[i].y<=player.y+40){
			enemybullet1[i].live = false;
			playerhp-=20;
		
		}
	}

	//С�͵����ж�
	for (int i = 0; i < enemybullet0_Num; i++) {

		if (enemybullet0[i].live == false) continue;

		if (enemybullet0[i].x+10 >= player.x && enemybullet0[i].x <= player.x + 40 &&
			enemybullet0[i].y >= player.y && enemybullet0[i].y <= player.y + 40) {
			enemybullet0[i].live = false;
			playerhp -= 10;
		}
	}

	//boss�ж�
	for (int i = 0; i < bossbullet_Num; i++) {
		for (int j = 0; j < 3; j++) {
			if (bossbullet[j][i].live == false) continue;
			if (bossbullet[j][i].x + 10 >= player.x && bossbullet[j][i].x <= player.x + 40 &&
				bossbullet[j][i].y >= player.y && bossbullet[j][i].y <= player.y + 40) {
				bossbullet[j][i].live = false;
				playerhp -=5 ;
			}
		}
	}



}


//�Ѷ��ж�
void judgedifficulty() {
	
	
	if (hard == 1) {
		ms = 1200;
		bullet_ms = 1000;
		enemybulletspeed = 3;
		boss_spawn = 300;
		boss.hp == 300;
	}
	else if (hard == 2) {
		ms = 1000;
		bullet_ms = 700;
		boss_spawn = 700;
		boss.hp = 500;
		enemybulletspeed = 5;
	}
	else if (hard == 3) {
		ms = 500;
		boss_spawn = 1300;
		boss.hp = 700;
		bullet_ms = 400;
		enemybulletspeed = 7;
	}
}






void PlayGame() {//��Ϸ����

	initgraph(height, width);

	mciSendString("open battle1.mp3", NULL, 0, NULL);
	mciSendString("play battle1.mp3 repeat", NULL, 0, NULL);

	
	GameInit();
	judgedifficulty();
	while (1) {

		if (playerhp <= 0) {
			mciSendString("close battle1.mp3", NULL, 0, NULL);
			mciSendString("close boss.mp3", NULL, 0, NULL);
			GameOverview();//��Ϸʧ��
		}
		if (boss.hp <= 0) {
			mciSendString("close battle1.mp3", NULL, 0, NULL);
			mciSendString("close boss.mp3", NULL, 0, NULL);
			GameWinview();//��Ϸʤ��
		}
		if ((peekmessage(&msg, EX_MOUSE)) && msg.message == WM_LBUTTONDOWN && inArea(560, 40, msg.x, msg.y, 100, 100)) {
				Stopview();
		}//��Ϸ��ͣ

		Gamedraw();
		PlayerMove();
		BulletMove();
		Shootingplayer();
		static DWORD t3 = 0, t4 = 0;
		if (t4 - t3 > ms) {
			t3 = t4;
			CreateEnemy();
		}

		t4 = clock();
		ShootingEnemy();
		EnemyBulletMove();
		EnemyMove();
		int start_time = clock();
		ctrlFps(start_time);
	}
}



int main() {

	login();
	
}