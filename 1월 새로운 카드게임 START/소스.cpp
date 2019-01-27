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
1번카드 -> ♡
2번카드 -> ♧
3번카드 -> ○
4번카드 -> ☆
5번카드 -> ◐
6번카드 -> ◈
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
	//// 커서 없애기
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = 0; // 보이는거
	ConsoleCursor.dwSize = 1; //커서 사이즈

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
	//창 크기조절
	system("mode con cols=65 lines=40");
}

void cout_gotoxy(int x, int y, int image) /// int형 cout gotoxy
{
	COORD Cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
	cout << image;

}

void cout_gotoxy(int x, int y, char *image) // char형 cout gotoxy
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
		//cout << "생성자 호출";
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
		cout << "show 에서의 호출";
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
		cout_gotoxy(5 + loc_x, 5 + loc_y, "┌");
		cout_gotoxy(7 + loc_x, 5 + loc_y, "─");
		cout_gotoxy(9 + loc_x, 5 + loc_y, "─");
		cout_gotoxy(11 + loc_x, 5 + loc_y, "─");
		cout_gotoxy(13 + loc_x, 5 + loc_y, "┐");
		/////////////////////////// 맨위 첫줄 완성
		cout_gotoxy(5 + loc_x, 6 + loc_y, "│");
		cout_gotoxy(13 + loc_x, 6 + loc_y, "│");
		////////////////////// 2줄
		cout_gotoxy(5 + loc_x, 7 + loc_y, "│");
		cout_gotoxy(13 + loc_x, 7 + loc_y, "│");
		////////////////////////3줄
		cout_gotoxy(5 + loc_x, 8 + loc_y, "│");
		cout_gotoxy(13 + loc_x, 8 + loc_y, "│");
		//////////////////////////////4줄
		cout_gotoxy(5 + loc_x, 9 + loc_y, "│");
		cout_gotoxy(13 + loc_x, 9 + loc_y, "│");
		///////////////////////////////5줄
		cout_gotoxy(5 + loc_x, 10 + loc_y, "│");
		cout_gotoxy(13 + loc_x, 10 + loc_y, "│");
		////////////////////////////////////////6줄
		cout_gotoxy(5 + loc_x, 11 + loc_y, "└");
		cout_gotoxy(7 + loc_x, 11 + loc_y, "─");
		cout_gotoxy(9 + loc_x, 11 + loc_y, "─");
		cout_gotoxy(11 + loc_x, 11 + loc_y, "─");
		cout_gotoxy(13 + loc_x, 11 + loc_y, "┘");
		/////////////////////////////////////막줄
		char boksa[3];
		if (kind_in_number == 1)
			strcpy(boksa, "♥");
		else if (kind_in_number == 2)
			strcpy(boksa, "♧");
		else if (kind_in_number == 3)
			strcpy(boksa, "♣");
		else if (kind_in_number == 4)
			strcpy(boksa, "◆");
		else if (kind_in_number == 5)
			strcpy(boksa, "◐");
		else if (kind_in_number == 6)
			strcpy(boksa, "◈");

		cout_gotoxy(7 + loc_x, 6 + loc_y, boksa);
		cout_gotoxy(11 + loc_x, 6 + loc_y, boksa);
		//////////////////////////////첫줄 이미지
		cout_gotoxy(9 + loc_x, 8 + loc_y, boksa);
		//////////////////////////////가운데줄 이미지
		cout_gotoxy(7 + loc_x, 10 + loc_y, boksa);
		cout_gotoxy(11 + loc_x, 10 + loc_y, boksa);

	}   // 전체카트 먼저뿌려주기

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
			if (Fc == 0)  //처음카드 뒤집었을때
			{
				index1 = Cx - 1 + (Cy - 1) * 4;
				if (a.card_state[index1] != 2)
				{
					Flip_one(kind_in_number, card_state);
					reco_x = Cx;
					reco_y = Cy;
					//첫번째 뒤집은 카드의 xy 좌표 저장
					if (a.card_state[index1] == 1)
						a.card_state[index1] == 0;
					else
						a.card_state[index1] == 1;
					Fc++;
				}
			}

			else if (Fc == 1) // 두번째카드 뒤집었을때
			{
				index2 = Cx - 1 + (Cy - 1) * 4;
				if (a.card_state[index2] != 2)
				{
					if (index1 != index2) // 한 카드로 두번 계산할 수 없게
					{
						Flip_one(kind_in_number, card_state);
						if (a.card_state[index2] == 1)
							a.card_state[index2] == 0;
						else
							a.card_state[index2] == 1;
						Fc = 0;
						if (a.mycard[index1] == a.mycard[index2])
						{
							//뒤집은카드 2개가 같을때 
							//a. index 1 과 index 2 값을 변환
							//황금카드는 뒤집기는 불가하나 황금카드를 통해 다른 카드로 변환가능하게.
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
							cout_gotoxy(0, 0, "두 카드가 같습니다. 점수 2점 추가!");
							Sleep(1500);
							cout_gotoxy(0, 0, "                                         ");
							// 두 카드가 같으니까 점수 +2점
							PT += 2;

						}
						else
						{
							// 두 카드가 다를때 포인트 -2점
							PT -= 2;
							cout_gotoxy(0, 0, "두 카드가 다릅니다. 점수 2점 감점ㅠ");
							Sleep(1500);
							cout_gotoxy(0, 0, "                                               ");
							//뒤집은카드 2개가 다를때 둘다 원상태로 뒤집기
							//index1 ,2 뒤집기 Flipone으로
							//index1 ,2에 대한 state 0으로

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
					else // 한 카드가 2번 뒤집을려고 시도
					{
						cout_gotoxy(0, 0, "이미 뒤집은 카드입니다.            ");
						Sleep(1500);
						cout_gotoxy(0, 0, "                                       ");
					}
				}
				else
				{
					cout_gotoxy(0, 0, "이미 황금카드입니다.                  ");
					Sleep(1500);
					cout_gotoxy(0, 0, "                                                ");
				}

			}
			else
			{
				cout << "오류 Fc값 오류" << endl;
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
				strcpy(boksa, "♥");
			////////1월6일 색넣기
			else if (kind_in_number == 2)
				strcpy(boksa, "♧");
			else if (kind_in_number == 3)
				strcpy(boksa, "♣");
			else if (kind_in_number == 4)
				strcpy(boksa, "◆");
			else if (kind_in_number == 5)
				strcpy(boksa, "◐");
			else if (kind_in_number == 6)
				strcpy(boksa, "◈");

			cout_gotoxy(7 + loc_x, 6 + loc_y, boksa);
			cout_gotoxy(11 + loc_x, 6 + loc_y, boksa);
			//////////////////////////////첫줄 이미지
			cout_gotoxy(9 + loc_x, 8 + loc_y, boksa);
			//////////////////////////////가운데줄 이미지
			cout_gotoxy(7 + loc_x, 10 + loc_y, boksa);
			cout_gotoxy(11 + loc_x, 10 + loc_y, boksa);
		}
		else if (card_state == 1)
		{
			int loc_x = 15 * (Cx - 1);
			int loc_y = 10 * (Cy - 1);

			cout_gotoxy(7 + loc_x, 6 + loc_y, "▩");
			cout_gotoxy(11 + loc_x, 6 + loc_y, "▩");
			//////////////////////////////첫줄 이미지
			cout_gotoxy(9 + loc_x, 8 + loc_y, "▩");
			//////////////////////////////가운데줄 이미지
			cout_gotoxy(7 + loc_x, 10 + loc_y, "▩");
			cout_gotoxy(11 + loc_x, 10 + loc_y, "▩");
		}
		else if (card_state == 2) // 황금카드
		{
			int loc_x = 15 * (Cx - 1);
			int loc_y = 10 * (Cy - 1);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF6);
			cout_gotoxy(7 + loc_x, 6 + loc_y, "★");
			cout_gotoxy(11 + loc_x, 6 + loc_y, "★");
			//////////////////////////////첫줄 이미지
			cout_gotoxy(9 + loc_x, 8 + loc_y, "★");
			//////////////////////////////가운데줄 이미지
			cout_gotoxy(7 + loc_x, 10 + loc_y, "★");
			cout_gotoxy(11 + loc_x, 10 + loc_y, "★");
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

				cout_gotoxy(7 + loc_x, 6 + loc_y, "▩");
				cout_gotoxy(11 + loc_x, 6 + loc_y, "▩");
				//////////////////////////////첫줄 이미지
				cout_gotoxy(9 + loc_x, 8 + loc_y, "▩");
				//////////////////////////////가운데줄 이미지
				cout_gotoxy(7 + loc_x, 10 + loc_y, "▩");
				cout_gotoxy(11 + loc_x, 10 + loc_y, "▩");

			}
		}
	}
	void Draw_cs(int a)
	{/////////##┏┗ ┛━ ┓┃
		int loc_x = 15 * (Cx - 1);
		int loc_y = 10 * (Cy - 1);

		cout_gotoxy(5 + loc_x, 5 + loc_y, "┌");
		cout_gotoxy(7 + loc_x, 5 + loc_y, "─");
		cout_gotoxy(9 + loc_x, 5 + loc_y, "─");
		cout_gotoxy(11 + loc_x, 5 + loc_y, "─");
		cout_gotoxy(13 + loc_x, 5 + loc_y, "┐");
		/////////////////////////// 맨위 첫줄 완성
		cout_gotoxy(5 + loc_x, 6 + loc_y, "│");
		cout_gotoxy(13 + loc_x, 6 + loc_y, "│");
		////////////////////// 2줄
		cout_gotoxy(5 + loc_x, 7 + loc_y, "│");
		cout_gotoxy(13 + loc_x, 7 + loc_y, "│");
		////////////////////////3줄
		cout_gotoxy(5 + loc_x, 8 + loc_y, "│");
		cout_gotoxy(13 + loc_x, 8 + loc_y, "│");
		//////////////////////////////4줄
		cout_gotoxy(5 + loc_x, 9 + loc_y, "│");
		cout_gotoxy(13 + loc_x, 9 + loc_y, "│");
		///////////////////////////////5줄
		cout_gotoxy(5 + loc_x, 10 + loc_y, "│");
		cout_gotoxy(13 + loc_x, 10 + loc_y, "│");
		////////////////////////////////////////6줄
		cout_gotoxy(5 + loc_x, 11 + loc_y, "└");
		cout_gotoxy(7 + loc_x, 11 + loc_y, "─");
		cout_gotoxy(9 + loc_x, 11 + loc_y, "─");
		cout_gotoxy(11 + loc_x, 11 + loc_y, "─");
		cout_gotoxy(13 + loc_x, 11 + loc_y, "┘");
		/////////////////////////////////////막줄
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
		cout_gotoxy(5 + loc_x, 5 + loc_y, "┏");
		cout_gotoxy(7 + loc_x, 5 + loc_y, "━");
		cout_gotoxy(9 + loc_x, 5 + loc_y, "━");
		cout_gotoxy(11 + loc_x, 5 + loc_y, "━");
		cout_gotoxy(13 + loc_x, 5 + loc_y, "┓");
		/////////////////////////// 맨위 첫줄 완성
		cout_gotoxy(5 + loc_x, 6 + loc_y, "┃");
		cout_gotoxy(13 + loc_x, 6 + loc_y, "┃");
		////////////////////// 2줄
		cout_gotoxy(5 + loc_x, 7 + loc_y, "┃");
		cout_gotoxy(13 + loc_x, 7 + loc_y, "┃");
		////////////////////////3줄
		cout_gotoxy(5 + loc_x, 8 + loc_y, "┃");
		cout_gotoxy(13 + loc_x, 8 + loc_y, "┃");
		//////////////////////////////4줄
		cout_gotoxy(5 + loc_x, 9 + loc_y, "┃");
		cout_gotoxy(13 + loc_x, 9 + loc_y, "┃");
		///////////////////////////////5줄
		cout_gotoxy(5 + loc_x, 10 + loc_y, "┃");
		cout_gotoxy(13 + loc_x, 10 + loc_y, "┃");
		////////////////////////////////////////6줄
		cout_gotoxy(5 + loc_x, 11 + loc_y, "┗");
		cout_gotoxy(7 + loc_x, 11 + loc_y, "━");
		cout_gotoxy(9 + loc_x, 11 + loc_y, "━");
		cout_gotoxy(11 + loc_x, 11 + loc_y, "━");
		cout_gotoxy(13 + loc_x, 11 + loc_y, "┛");
		/////////////////////////////////////막줄
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0);
	}
	void Main_Sc()
	{
		/////1월 13일까지 메뉴함수 조절
		///// Draw.io 로 포트폴리오용 그래ㅐ프 그려오기.
		/*
		1. 게임시작
		2. 게임설명
		3. 게임순위
		4. 게임설정
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
	///////////////// 처음 0.5초 보여주기
	myUI.Flip_AC();  /// 다 뒤집기
	myUI.Draw_cs(0); // 맨처음커서 

	while (1)
	{
		myUI.Move_cards(a.mycard[Cx - 1 + (Cy - 1) * 4], a.card_state[Cx - 1 + (Cy - 1) * 4]);
		
	}







	COORD Cur = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);

}