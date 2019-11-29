#include <stdio.h>
#include <termio.h>
#include <stdlib.h>
#include <string.h>

void print_chess();
void titleDraw();
void menuDraw();
void howtouse();
int getch();
int p1 = 1, p2 = 1, x, y, m, n;
char chessboard[8][8][2]= { 
                            {"R","N","B","Q","K","B","N","R"},
                            {"P","P","P","P","P","P","P","P"},
                            {".",".",".",".",".",".",".","."},
                            {".",".",".",".",".",".",".","."},
                            {".",".",".",".",".",".",".","."},
                            {".",".",".",".",".",".",".","."},
                            {"p","p","p","p","p","p","p","p"},
                            {"r","n","b","q","k","b","n","r"}
                            };
const char ind[8][8][3]=
                        {
                        {"A1","A2","A3","A4","A5","A6","A7","A8"},
                        {"B1","B2","B3","B4","B5","B6","B7","B8"},
                        {"C1","C2","C3","C4","C5","C6","C7","C8"},
                        {"D1","D2","D3","D4","D5","D6","D7","D8"},
                        {"E1","E2","E3","E4","E5","E6","E7","E8"},
                        {"F1","F2","F3","F4","F5","F6","F7","F8"},
                        {"G1","G2","G3","G4","G5","G6","G7","G8"},
                        {"H1","H2","H3","H4","H5","H6","H7","H8"},
                        };

char King[1][3] = {"k","K"}; // 킹 문자열
char Queen[1][3] = {"q","Q"}; // 퀸 문자열
char Bishop[1][3] = {"b","B"};  // 비숍 문자열
char Knight[1][3] = {"n", "N"};  //나이트 문자열
char Rook[1][3] = {"r", "R"};  //룩 문자열
char pawn[1][3] = {"p", "P"};  //폰 문자열
char Empty[3] = "."; //비어있는 곳을 나타내는 문자열

char* white_loc = "W1";  // 단순 배열 초기화
char* black_loc = "B1";  // 단순 배열 초기화
char *w_now, *b_now, *w_input, *b_input;  // 현재 흑백말 위치와 이동하고 싶은 말의 위치

int main(){
   
   int keyCode;
   while(1){
   system("clear");
   menuDraw();
   printf("메뉴를 선택하세요 : ");
   scanf("%d",&keyCode);
   switch(keyCode){
      case 1:
         while(1){
	  system("clear");
          print_chess();
         }
         break;
      case 2:
         howtouse();
         break;
      case 3:
         exit(0);
         break;
   }
   }

void player()  // 어떤 플레이어 차례인지

switch(p1) 
    {
    case 1:
        {
            p1++; // 이전에 p1차례였을 경우, 다음은 p2 차례
            p2--; // player 변수의 상대방이 되는 변수
        }
        break;

    case 2:
        {
            p1--; // 이전에 p2차례였을 겨우, 다음은 p1 차례
            p2++;
        }
        break;
}

        printf(" %d의 차례입니다. 움직일 말을 선택해주세요.", player);
	if((1<=x && x<=8)&&(1<=y && y<=8)) //옳은 자리 선택
        Dis();

        else
        {
                system("");
                printf("잘못된 선택입니다.");
                switch(p1)
        {
        case 1:
        {
                p1++;
                p2--;
        }
        break;

        case 2:
        {
                p1--;
                p2++;
        }
        break;
        }
}

Victory = 0; // 승패 여부를 확인 0이면 게임 끝 1이면 계속

for(m=0; m<8; m++)
{
        for(n=0; n<8; n++)
        {
                if(strcmp(chessboard[m][n], king[p2-1]==0)
                Victory=1;
        }
}

if(Victory==0)
{
        printf("%d플레이어의 승리입니다!", p1);
        }

printf("체스게임 종료");

Lost = 0;  // 승패 여부를 확인 0이면 게임 끝 1이면 계속

for(m=0; m<8; m++)
{
        for(n=0l n<8; n++)
        {
                if(strcmp(chessboard[m][n], king[p1-1]==0)
                Lost = 1;
        }
}

if(Lost==0)
{
        printf("%플레이어의 승리입니다 !", p2);
        }

printf("체스게임 종료");	
	
   return 0;
}

void menuDraw(){
   printf("  1. 게임 시작\n");
   printf("  2. 조작 방법 안내\n");
   printf("  3. 종료\n"); 
}

void howtouse(){
   system("clear");
         printf("==========조작 방법 안내==========\n");
        printf("기물이 위치한 칸을 먼저 입력하고 원하고자 하는 위치를 입력한다.\n");
        printf(" Ex - B1칸의 나이트를 A3칸에 옮기고 싶다.\n");
        printf(" B1 A3 입력 \n\n\n ");


        printf("u를 다시 입력하면 체스 게임 화면으로 돌아갑니다\n");
        int use = getch();
        if(use == 'u')
                return;
        while(use != 'u')
        {
                use = getch();
                if(use == 'u')
                        return;
        }
   
}

int getch(void)

{
        int ch;


        struct termios buf;

        struct termios save;


        tcgetattr(0, &save);

        buf = save;


        buf.c_lflag &= ~(ICANON | ECHO);

        buf.c_cc[VMIN] = 1;

        buf.c_cc[VTIME] = 0;
       tcsetattr(0, TCSAFLUSH, &buf);


        ch = getchar();

        tcsetattr(0, TCSAFLUSH, &save);


        return ch;
}

void input_loc_w() {
    printf("흰색 입력 : ");
    scanf("%s %s", &w_now, &w_input);
    white_loc = &w_input;
}

void input_loc_b(){
    printf("검은색 입력 : ");
    scanf("%s %s", &b_now, &b_input);
    black_loc = &b_input;
}

void print_chess() {
    printf("\t      A     B     C     D     E     F     G     H\n");
    for (int i = 0; i < 8; i++) {
        printf("\t   -------------------------------------------------\n");
        printf("\t   |#####|     |#####|     |#####|     |#####|     |\n");
        printf("\t %d |# %s #|  %s  |# %s #|  %s  |# %s #|  %s  |# %s #|  %s  |\n", 8 - i, chessboard[i][0], chessboard[i][1], chessboard[i][2],
            chessboard[i][3], chessboard[i][4], chessboard[i][5], chessboard[i][6], chessboard[i][7]);
        printf("\t   |#####|     |#####|     |#####|     |#####|     |\n");
        printf("\t   -------------------------------------------------\n");
        i++;
        printf("\t   |     |#####|     |#####|     |#####|     |#####|\n");
        printf("\t %d |  %s  |# %s #|  %s  |# %s #|  %s  |# %s #|  %s  |# %s #|\n", 8 - i, chessboard[i][0], chessboard[i][1],
            chessboard[i][2], chessboard[i][3], chessboard[i][4], chessboard[i][5], chessboard[i][6], chessboard[i][7]);
        printf("\t   |     |#####|     |#####|     |#####|     |#####|\n");
    }
    printf("\t   -------------------------------------------------\n");
}

void Dis()                      //입력한 자리에 위치한 말 판별
{
        if strcmp(chessboard[loc_x][loc_y], "R")
        Rook();
	else if strcmp(chessboard[loc_x][loc_y], "N")
        Knight();
        else if strcmp(chessboard[loc_x][loc_y], "B")
        Bishop();
        else if strcmp(chessboard[loc_x][loc_y], "Q")
        Queen();
        else if strcmp(chessboard[loc_x][loc_y], "K")
        King();
        else if strcmp(chessboard[loc_x][loc_y], "P")
        Pawn();
        else if strcmp(chessboard[loc_x][loc_y], "r")
        rook();
        else if strcmp(chessboard[loc_x][loc_y], "n")
        knight();
        else if strcmp(chessboard[loc_x][loc_y], "b")
        bishop();
        else if strcmp(chessboard[loc_x][loc_y], "q")
        queen();
	else if strcmp(chessboard[loc_x][loc_y], "k")
        king();
        else if strcmp(chessboard[loc_x][loc_y], "p")
        pawn();
	else  //잘못 선택하였을 때
	{
	printf("다시 입력해주세요");

	switch(p1)
        {
        case 1:
                {
                        p1++;
                        p2--;
                }
                        break;
        case 2:
                {
                        p1--;
                        p2++;
                }
                        break;

                }
	}
}

 


		   
