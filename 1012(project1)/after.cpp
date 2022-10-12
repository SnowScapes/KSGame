#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define box_length 15 //게임의 영역(좌우 길이) 
#define box_height 15 //바닥의 높이(상하 길이) 

void intro_game(void);
void game_difficulty(void);
void practice_game(void);
void game_control(void);
void gotoxy(int x, int y);
int left_right_move(bool practice);
void move_down(int x);
void draw_rectangle(int c, int r);
int max_block(void);
int difficulty;

int block_stack[box_length*2+1]={0}; //해당위치의 값을 0으로 초기화

int main(void)
{
	intro_game();
	gotoxy(1, box_height+3);
	printf("game이 종료되었습니다.                 \n");
	return 0;
}

void intro_game(void)
{
	system("cls");
	for (int i=0; i<32; i++)
		block_stack[i]=0; //연습게임을 했을 경우 블록 스택 초기 
	printf("블록 쌓기 \n\n");
	printf("블록이 좌우로 움직일때 스페이스키를 누르면\n");
	printf("블록이 떨어져 바닥에 쌓입니다.\n\n");
	printf("1. 게임 시작\n");
	printf("2. 연습 게임\n");
	printf("3. 게임 종료\n");
	char key = getch();
	switch(key) {
		case '1' :
			game_difficulty();
			game_control();
			break;
		case '2' :
			difficulty=2;
			practice_game();
			gotoxy(1, box_height+3);
			printf("연습게임이 종료되었습니다.                 \n");
			Sleep(2000);
			intro_game();
			break;화 
		case '3' :
			exit(0);
			break;
	}
	Sleep(2000);
}
void game_difficulty(void) {
	system("cls");
	printf("게임의 난이도를 정할 수 있습니다.\n\n");
	printf("쉬움 : 블록이 좌우로 움직이는 속도가 느림\n");
	printf("보통 : 블록이 좌우로 움직이는 속도가 보통\n");
	printf("어려움 : 블록이 좌우로 움직이는 속도가 빠름\n");
	printf("매우 어려움 : 블록이 좌우로 움직이는 속도가 랜덤\n\n");
	printf("원하는 난이도에 해당하는 숫자키를 눌러주세요.\n\n");
	printf("1.쉬움	2.보통	3.어려움  4.매우 어려움\n\n");
	char key = getch();
	switch(key) {
		case '1' :
			difficulty = 1;
			printf("쉬움 난이도로 설정되었습니다.");
			break;
		case '2' :
			difficulty = 2;
			printf("보통 난이도로 설정되었습니다.");
			break;
		case '3' :
			difficulty = 3;
			printf("어려움 난이도로 설정되었습니다.");
			break;
		case '4' :
			difficulty = 4;
			printf("매우 어려움 난이도로 설정되었습니다.");
			break;
	}
	Sleep(2000);
}
void practice_game(void) {
	int x, count=0;
	system("cls");
	draw_rectangle(box_length, box_height);
	gotoxy(box_length*2+5,3);
	printf("블록의 개수: %2d", box_height);
	gotoxy(1, box_height+3);
	printf("방향키 아래를 누르면 블록이 떨어지고\n");
	printf("바닥에 쌓입니다. \n");
	printf("15층을 쌓거나 ESC키를 누르면 종료됩니다.\n");
	Sleep(3000);
	while(max_block()<box_height)
	{
		gotoxy(box_length*2+5,4);
		printf("시도한 횟수: %2d", count+1);
		gotoxy(box_length*2+5,5);
		printf("쌓인 블록수: %2d", max_block());
		x=left_right_move(true);
		if(x == -1)
			break;
		else {
			move_down(x);
			count++;
		}
	}
}
void game_control(void)
{
	int x, count=0;
	system("cls");
	draw_rectangle(box_length, box_height);
	gotoxy(box_length*2+5,3);
	printf("블록의 개수: %2d", box_height);
	gotoxy(1, box_height+3);
	printf("스페이스키를 누르면 블록이 떨어지고\n");
	printf("바닥에 쌓입니다. \n");
	Sleep(3000);
	while(count<box_height)
	{
		gotoxy(box_length*2+5,4);
		printf("시도한 횟수: %2d", count+1);
		gotoxy(box_length*2+5,5);
		printf("쌓인 블록수: %2d", max_block());
		x=left_right_move(false);
		move_down(x);
		count++;
	}

}
void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
int random_speed() {
	int speed[3] = {20,50,100};
	int num = rand() % 3;
	return speed[num];
}
int set_speed() {
	int speed;
	switch(difficulty) {
		case 1 :
			speed = 100;
			break;
		case 2 :
			speed = 50;
			break;
		case 3 :
			speed = 20;
			break;
		case 4 :
			speed = random_speed();
			break;
	}
	return speed;
}
int left_right_move(bool practice)
{
	int key = 0;
	int x=3, y=2, temp=2;
	bool n = true;
	int speed = set_speed();
	do
	{
		x+=temp;
		if (x>(box_length*2)) //x방향 최대값 설정
			temp=-2;
		if (x<3)
		{
			x=3;
			temp=2;
		}

		gotoxy(x, y);
		printf("□");
		Sleep(speed); //블록이 좌우로 움직이는 속도를 조절
		gotoxy(x, y);
		printf("  ");
		if(kbhit()) {
			key = getch();
			if (key == 27 && practice) {
				n = false;
				break;
			}
		}
	}while(key!=80);
	if(n) {
		block_stack[x]+=1;
		return x;
	}
	else
		return -1;
}
void move_down(int x)
{
	int y;
	for(y=2;y<box_height+2-block_stack[x];y+=1)
	{
		gotoxy(x, y);
		printf("□");
		Sleep(20);
		gotoxy(x, y);
		printf("  ");
		Sleep(10);
	}
	gotoxy(x,box_height+2-block_stack[x]);
	printf("□");
}
void draw_rectangle(int c, int r)
{
    int i, j;
    unsigned char a=0xa6;
    unsigned char b[7]; 
    for(i=1;i<7;i++)
   		b[i]=0xa0+i;

    printf("%c%c",a, b[3]);
    for(i=0;i<c*2+1;i++)
		printf("%c%c", a, b[1]);
    printf("%c%c", a, b[4]);
    printf("\n");
    for(i=0;i<r;i++)
    {
		printf("%c%c", a, b[2]);
		for(j=0;j<c*2+1;j++)
			printf(" ");
		printf("%c%c",a, b[2]);
		printf("\n");
    }
    printf("%c%c", a, b[6]);
    for(i=0;i<c*2+1;i++)
		printf("%c%c", a, b[1]);
    printf("%c%c", a, b[5]);
    printf("\n");
}
int max_block(void)
{
	int i, max=0;
	for(i=1;i<box_height*2+1;i++)
	{
		if (max<=block_stack[i])
			max=block_stack[i];
	}
	return max;
}
