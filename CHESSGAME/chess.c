#include <stdio.h>
#include <termio.h>
#include <stdlib.h>
#include <string.h>

void print_chess();
void titleDraw();
void menuDraw();
void howtouse();
int getch();
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
                printf("u를 다시 입력하면 체스 게임 화면으로 돌아갑니다\n");
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
