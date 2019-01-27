#include <iostream>
#include <CoreWindow.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
using namespace std;

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13
#define SPACE 32

/*
1��ī�� -> ��
2��ī�� -> ��
3��ī�� -> ��
4��ī�� -> ��
5��ī�� -> ��
6��ī�� -> ��
*/
int reco_x = 0;
int reco_y = 0;
int index1 = 0;
int index2 = 0;
int Cx = 1;
int Cy = 1;
int Fc = 0;
int PT = 0;
void set_visual()
{
	//// Ŀ�� ���ֱ�
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = 0; // ���̴°�
	ConsoleCursor.dwSize = 1; //Ŀ�� ������

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
	//â ũ������
	system("mode con cols=65 lines=40");
}

void cout_gotoxy(int x, int y, int image) /// int�� cout gotoxy
{
	COORD Cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
	cout << image;

}

void cout_gotoxy(int x, int y, char *image) // char�� cout gotoxy
{
	COORD Cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
	cout << image;
}

class Card
{
public:
	int mycard[12];
	int card_state[12];
	Card()
	{
		//cout << "������ ȣ��";
		for (int i = 0; i < 12; i = i + 2)
		{
			mycard[i] = (i / 2) + 1;
			mycard[i + 1] = (i / 2) + 1;
			//cout << mycard[i] << endl;
			//cout << mycard[i + 1] << endl;
		}

		for (int i = 0; i < 12; i++)
		{
			card_state[i] = 0;
		}
	}
	void show_card_value()
	{
		cout << "show ������ ȣ��";
		for (int i = 0; i < 12; i++)
		{
			cout << mycard[i] << endl;
		}
	}
	void shuffle()
	{
		srand(time(NULL));

		for (int i = 0; i < 300; i++)
		{
			int temp_a = rand() % 12;
			int temp_b = rand() % 12;
			swap(mycard[temp_a], mycard[temp_b]);
		}
	}
};
Card a;
class UI{
public:
	void Draw_cards(int loc_x, int loc_y, int kind_in_number)
	{
		cout_gotoxy(5 + loc_x, 5 + loc_y, "��");
		cout_gotoxy(7 + loc_x, 5 + loc_y, "��");
		cout_gotoxy(9 + loc_x, 5 + loc_y, "��");
		cout_gotoxy(11 + loc_x, 5 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 5 + loc_y, "��");
		/////////////////////////// ���� ù�� �ϼ�
		cout_gotoxy(5 + loc_x, 6 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 6 + loc_y, "��");
		////////////////////// 2��
		cout_gotoxy(5 + loc_x, 7 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 7 + loc_y, "��");
		////////////////////////3��
		cout_gotoxy(5 + loc_x, 8 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 8 + loc_y, "��");
		//////////////////////////////4��
		cout_gotoxy(5 + loc_x, 9 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 9 + loc_y, "��");
		///////////////////////////////5��
		cout_gotoxy(5 + loc_x, 10 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 10 + loc_y, "��");
		////////////////////////////////////////6��
		cout_gotoxy(5 + loc_x, 11 + loc_y, "��");
		cout_gotoxy(7 + loc_x, 11 + loc_y, "��");
		cout_gotoxy(9 + loc_x, 11 + loc_y, "��");
		cout_gotoxy(11 + loc_x, 11 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 11 + loc_y, "��");
		/////////////////////////////////////����
		char boksa[3];
		if (kind_in_number == 1)
			strcpy(boksa, "��");
		else if (kind_in_number == 2)
			strcpy(boksa, "��");
		else if (kind_in_number == 3)
			strcpy(boksa, "��");
		else if (kind_in_number == 4)
			strcpy(boksa, "��");
		else if (kind_in_number == 5)
			strcpy(boksa, "��");
		else if (kind_in_number == 6)
			strcpy(boksa, "��");

		cout_gotoxy(7 + loc_x, 6 + loc_y, boksa);
		cout_gotoxy(11 + loc_x, 6 + loc_y, boksa);
		//////////////////////////////ù�� �̹���
		cout_gotoxy(9 + loc_x, 8 + loc_y, boksa);
		//////////////////////////////����� �̹���
		cout_gotoxy(7 + loc_x, 10 + loc_y, boksa);
		cout_gotoxy(11 + loc_x, 10 + loc_y, boksa);

	}   // ��üīƮ �����ѷ��ֱ�

	void Move_cards(int kind_in_number, int card_state) //// 
	{
		int key;
		key = getch();
		if (key == 224)
		{
			key = getch();
			if (key == UP)
			{
				Draw_cs(UP);
			}
			if (key == DOWN)
			{
				Draw_cs(DOWN);
			}
			if (key == LEFT)
			{
				Draw_cs(LEFT);
			}
			if (key == RIGHT)
			{
				Draw_cs(RIGHT);
			}
		}
		else if (key == ENTER || key == SPACE)
		{
			if (Fc == 0)  //ó��ī�� ����������
			{
				index1 = Cx - 1 + (Cy - 1) * 4;
				if (a.card_state[index1] != 2)
				{
					Flip_one(kind_in_number, card_state);
					reco_x = Cx;
					reco_y = Cy;
					//ù��° ������ ī���� xy ��ǥ ����
					if (a.card_state[index1] == 1)
						a.card_state[index1] == 0;
					else
						a.card_state[index1] == 1;
					Fc++;
				}
			}

			else if (Fc == 1) // �ι�°ī�� ����������
			{
				index2 = Cx - 1 + (Cy - 1) * 4;
				if (a.card_state[index2] != 2)
				{
					if (index1 != index2) // �� ī��� �ι� ����� �� ����
					{
						Flip_one(kind_in_number, card_state);
						if (a.card_state[index2] == 1)
							a.card_state[index2] == 0;
						else
							a.card_state[index2] == 1;
						Fc = 0;
						if (a.mycard[index1] == a.mycard[index2])
						{
							//������ī�� 2���� ������ 
							//a. index 1 �� index 2 ���� ��ȯ
							//Ȳ��ī��� ������� �Ұ��ϳ� Ȳ��ī�带 ���� �ٸ� ī��� ��ȯ�����ϰ�.
							a.card_state[index1] = 2;
							a.card_state[index2] = 2;
							Flip_one(index1, a.card_state[index1]);
							int tempx = Cx;
							int tempy = Cy;
							Cx = reco_x;
							Cy = reco_y;
							Flip_one(index2, a.card_state[index2]);
							Cx = tempx;
							Cy = tempy;
							cout_gotoxy(0, 0, "�� ī�尡 �����ϴ�. ���� 2�� �߰�!");
							Sleep(1500);
							cout_gotoxy(0, 0, "                                         ");
							// �� ī�尡 �����ϱ� ���� +2��
							PT += 2;

						}
						else
						{
							// �� ī�尡 �ٸ��� ����Ʈ -2��
							PT -= 2;
							cout_gotoxy(0, 0, "�� ī�尡 �ٸ��ϴ�. ���� 2�� ������");
							Sleep(1500);
							cout_gotoxy(0, 0, "                                               ");
							//������ī�� 2���� �ٸ��� �Ѵ� �����·� ������
							//index1 ,2 ������ Flipone����
							//index1 ,2�� ���� state 0����

							Flip_one(a.mycard[index2], 1);
							a.card_state[index2] = 0;
							int tempx = Cx;
							int tempy = Cy;
							Cx = reco_x;
							Cy = reco_y;
							Flip_one(a.mycard[index1], 1);
							Cx = tempx;
							Cy = tempy;
						}
					}
					else // �� ī�尡 2�� ���������� �õ�
					{
						cout_gotoxy(0, 0, "�̹� ������ ī���Դϴ�.            ");
						Sleep(1500);
						cout_gotoxy(0, 0, "                                       ");
					}
				}
				else
				{
					cout_gotoxy(0, 0, "�̹� Ȳ��ī���Դϴ�.                  ");
					Sleep(1500);
					cout_gotoxy(0, 0, "                                                ");
				}

			}
			else
			{
				cout << "���� Fc�� ����" << endl;
			}
		}
	}

	void Flip_one(int kind_in_number, int card_state)
	{
		if (card_state == 0)
		{
			int loc_x = 15 * (Cx - 1);
			int loc_y = 10 * (Cy - 1);

			char boksa[3];
			if (kind_in_number == 1)
				strcpy(boksa, "��");
			////////1��6�� ���ֱ�
			else if (kind_in_number == 2)
				strcpy(boksa, "��");
			else if (kind_in_number == 3)
				strcpy(boksa, "��");
			else if (kind_in_number == 4)
				strcpy(boksa, "��");
			else if (kind_in_number == 5)
				strcpy(boksa, "��");
			else if (kind_in_number == 6)
				strcpy(boksa, "��");

			cout_gotoxy(7 + loc_x, 6 + loc_y, boksa);
			cout_gotoxy(11 + loc_x, 6 + loc_y, boksa);
			//////////////////////////////ù�� �̹���
			cout_gotoxy(9 + loc_x, 8 + loc_y, boksa);
			//////////////////////////////����� �̹���
			cout_gotoxy(7 + loc_x, 10 + loc_y, boksa);
			cout_gotoxy(11 + loc_x, 10 + loc_y, boksa);
		}
		else if (card_state == 1)
		{
			int loc_x = 15 * (Cx - 1);
			int loc_y = 10 * (Cy - 1);

			cout_gotoxy(7 + loc_x, 6 + loc_y, "��");
			cout_gotoxy(11 + loc_x, 6 + loc_y, "��");
			//////////////////////////////ù�� �̹���
			cout_gotoxy(9 + loc_x, 8 + loc_y, "��");
			//////////////////////////////����� �̹���
			cout_gotoxy(7 + loc_x, 10 + loc_y, "��");
			cout_gotoxy(11 + loc_x, 10 + loc_y, "��");
		}
		else if (card_state == 2) // Ȳ��ī��
		{
			int loc_x = 15 * (Cx - 1);
			int loc_y = 10 * (Cy - 1);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF6);
			cout_gotoxy(7 + loc_x, 6 + loc_y, "��");
			cout_gotoxy(11 + loc_x, 6 + loc_y, "��");
			//////////////////////////////ù�� �̹���
			cout_gotoxy(9 + loc_x, 8 + loc_y, "��");
			//////////////////////////////����� �̹���
			cout_gotoxy(7 + loc_x, 10 + loc_y, "��");
			cout_gotoxy(11 + loc_x, 10 + loc_y, "��");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0);
		}
	}
	void Flip_AC()   // FLIP ALL CARD
	{
		int tempx = Cx;
		int tempy = Cy;
		for (tempx = Cx; tempx < 5; tempx++)
		{
			for (tempy = Cy; tempy < 4; tempy++)
			{
				int loc_x = 15 * (tempx - 1);
				int loc_y = 10 * (tempy - 1);

				cout_gotoxy(7 + loc_x, 6 + loc_y, "��");
				cout_gotoxy(11 + loc_x, 6 + loc_y, "��");
				//////////////////////////////ù�� �̹���
				cout_gotoxy(9 + loc_x, 8 + loc_y, "��");
				//////////////////////////////����� �̹���
				cout_gotoxy(7 + loc_x, 10 + loc_y, "��");
				cout_gotoxy(11 + loc_x, 10 + loc_y, "��");

			}
		}
	}
	void Draw_cs(int a)
	{/////////##���� ���� ����
		int loc_x = 15 * (Cx - 1);
		int loc_y = 10 * (Cy - 1);

		cout_gotoxy(5 + loc_x, 5 + loc_y, "��");
		cout_gotoxy(7 + loc_x, 5 + loc_y, "��");
		cout_gotoxy(9 + loc_x, 5 + loc_y, "��");
		cout_gotoxy(11 + loc_x, 5 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 5 + loc_y, "��");
		/////////////////////////// ���� ù�� �ϼ�
		cout_gotoxy(5 + loc_x, 6 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 6 + loc_y, "��");
		////////////////////// 2��
		cout_gotoxy(5 + loc_x, 7 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 7 + loc_y, "��");
		////////////////////////3��
		cout_gotoxy(5 + loc_x, 8 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 8 + loc_y, "��");
		//////////////////////////////4��
		cout_gotoxy(5 + loc_x, 9 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 9 + loc_y, "��");
		///////////////////////////////5��
		cout_gotoxy(5 + loc_x, 10 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 10 + loc_y, "��");
		////////////////////////////////////////6��
		cout_gotoxy(5 + loc_x, 11 + loc_y, "��");
		cout_gotoxy(7 + loc_x, 11 + loc_y, "��");
		cout_gotoxy(9 + loc_x, 11 + loc_y, "��");
		cout_gotoxy(11 + loc_x, 11 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 11 + loc_y, "��");
		/////////////////////////////////////����
		if (a == RIGHT && Cx <= 3)
		{
			Cx++;
		}
		if (a == LEFT&& Cx >= 2)
		{
			Cx--;
		}
		if (a == UP && Cy >= 2)
		{
			Cy--;
		}
		if (a == DOWN && Cy <= 2)
		{
			Cy++;
		}

		loc_x = 15 * (Cx - 1);
		loc_y = 10 * (Cy - 1);
		/////
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0);
		////
		cout_gotoxy(5 + loc_x, 5 + loc_y, "��");
		cout_gotoxy(7 + loc_x, 5 + loc_y, "��");
		cout_gotoxy(9 + loc_x, 5 + loc_y, "��");
		cout_gotoxy(11 + loc_x, 5 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 5 + loc_y, "��");
		/////////////////////////// ���� ù�� �ϼ�
		cout_gotoxy(5 + loc_x, 6 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 6 + loc_y, "��");
		////////////////////// 2��
		cout_gotoxy(5 + loc_x, 7 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 7 + loc_y, "��");
		////////////////////////3��
		cout_gotoxy(5 + loc_x, 8 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 8 + loc_y, "��");
		//////////////////////////////4��
		cout_gotoxy(5 + loc_x, 9 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 9 + loc_y, "��");
		///////////////////////////////5��
		cout_gotoxy(5 + loc_x, 10 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 10 + loc_y, "��");
		////////////////////////////////////////6��
		cout_gotoxy(5 + loc_x, 11 + loc_y, "��");
		cout_gotoxy(7 + loc_x, 11 + loc_y, "��");
		cout_gotoxy(9 + loc_x, 11 + loc_y, "��");
		cout_gotoxy(11 + loc_x, 11 + loc_y, "��");
		cout_gotoxy(13 + loc_x, 11 + loc_y, "��");
		/////////////////////////////////////����
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0);
	}
	void Main_Sc()
	{
		/////1�� 13�ϱ��� �޴��Լ� ����
		///// Draw.io �� ��Ʈ�������� �׷����� �׷�����.
		/*
		1. ���ӽ���
		2. ���Ӽ���
		3. ���Ӽ���
		4. ���Ӽ���
		*/

	}
};
int main()
{
	system("color F0");

	a.shuffle();
	set_visual();

	UI myUI;
	for (int i = 0; i < 4; i++)
	{
		myUI.Draw_cards(15 * i, 0, a.mycard[i]);
	}
	for (int i = 4; i < 8; i++)
	{
		myUI.Draw_cards(15 * (i - 4), 10, a.mycard[i]);
	}
	for (int i = 8; i < 12; i++)
	{
		myUI.Draw_cards(15 * (i - 8), 20, a.mycard[i]);
	}
	Sleep(1500);
	///////////////// ó�� 0.5�� �����ֱ�
	myUI.Flip_AC();  /// �� ������
	myUI.Draw_cs(0); // ��ó��Ŀ�� 

	while (1)
	{
		myUI.Move_cards(a.mycard[Cx - 1 + (Cy - 1) * 4], a.card_state[Cx - 1 + (Cy - 1) * 4]);
		
	}







	COORD Cur = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);

}