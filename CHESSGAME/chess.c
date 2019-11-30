#include <stdio.h>
#include <termio.h>
#include <stdlib.h>
#include <string.h>

void print_chess();
void titleDraw();
void menuDraw();
void howtouse();
void whowin();
void astoin();
int getch();
void Dis();
void input_loc();
void Rook();
void Knight();
void Bishop();
void King();
void Queen();
void Pawn();
void rook();
void knight();
void bishop();
void king();
void queen();
void pawn();

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
const char ind[8][8][3]={
                        {"A1","A2","A3","A4","A5","A6","A7","A8"},
                        {"B1","B2","B3","B4","B5","B6","B7","B8"},
                        {"C1","C2","C3","C4","C5","C6","C7","C8"},
                        {"D1","D2","D3","D4","D5","D6","D7","D8"},
                        {"E1","E2","E3","E4","E5","E6","E7","E8"},
                        {"F1","F2","F3","F4","F5","F6","F7","F8"},
                        {"G1","G2","G3","G4","G5","G6","G7","G8"},
                        {"H1","H2","H3","H4","H5","H6","H7","H8"}
                        };
int blcwht[8][8]={
		  {1,1,1,1,1,1,1,1},
		  {1,1,1,1,1,1,1,1},
		  {0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0},
		  {2,2,2,2,2,2,2,2},
		  {2,2,2,2,2,2,2,2}
		 };
char K[2][2] = {"k","K"}; // 킹 문자열
char Q[2][2] = {"q","Q"}; // 퀸 문자열
char B[2][2] = {"b","B"};  // 비숍 문자열
char N[2][2] = {"n", "N"};  //나이트 문자열
char R[2][2] = {"r", "R"};  //룩 문자열
char P[2][2] = {"p", "P"};  //폰 문자열
char E[2] = "."; //비어있는 곳을 나타내는 문자열

char HEIGHT[8] = "ABCDEFGH";

char *p_before,*p_after;  // 현재 흑백말 위치와 이동하고 싶은 말의 위치
int before_x,before_y,after_x,after_y; //좌표를 숫자로 바꾼 변수

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
  	  input_loc();
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

void input_loc() {
    printf("좌표 입력 : ");
    scanf("%s %s", &p_before, &p_after);
    astoin();
    if((before_x==after_x)&&(before_y==after_y)){
		printf("같은 좌표를 입력하셨습니다.\n");
		input_loc();
	}
    Dis();
}

void print_chess() {
    printf("\t      1     2     3     4     5     6     7     8\n");
    for (int i = 0; i < 8; i++) {
        printf("\t   -------------------------------------------------\n");
        printf("\t   |#####|     |#####|     |#####|     |#####|     |\n");
        printf("\t %c |# %s #|  %s  |# %s #|  %s  |# %s #|  %s  |# %s #|  %s  |\n", HEIGHT[i], chessboard[i][0], chessboard[i][1], chessboard[i][2],
            chessboard[i][3], chessboard[i][4], chessboard[i][5], chessboard[i][6], chessboard[i][7]);
        printf("\t   |#####|     |#####|     |#####|     |#####|     |\n");
        printf("\t   -------------------------------------------------\n");
        i++;
        printf("\t   |     |#####|     |#####|     |#####|     |#####|\n");
        printf("\t %c |  %s  |# %s #|  %s  |# %s #|  %s  |# %s #|  %s  |# %s #|\n", HEIGHT[i], chessboard[i][0], chessboard[i][1],
            chessboard[i][2], chessboard[i][3], chessboard[i][4], chessboard[i][5], chessboard[i][6], chessboard[i][7]);
        printf("\t   |     |#####|     |#####|     |#####|     |#####|\n");
    }
    printf("\t   -------------------------------------------------\n");
}

void Dis()                      //입력한 자리에 위치한 말 판별
{
        if (strcmp(chessboard[before_x][before_y], "R")==0)
        Rook();
	else if (strcmp(chessboard[before_x][before_y], "N")==0)
        Knight();
        else if (strcmp(chessboard[before_x][before_y], "B")==0)
        Bishop();
        else if (strcmp(chessboard[before_x][before_y], "Q")==0)
        Queen();
        else if (strcmp(chessboard[before_x][before_y], "K")==0)
        King();
        else if (strcmp(chessboard[before_x][before_y], "P")==0)
        Pawn();
        else if (strcmp(chessboard[before_x][before_y], "r")==0)
        rook();
        else if (strcmp(chessboard[before_x][before_y], "n")==0)
        knight();
        else if (strcmp(chessboard[before_x][before_y], "b")==0)
        bishop();
        else if (strcmp(chessboard[before_x][before_y], "q")==0)
        queen();
	else if (strcmp(chessboard[before_x][before_y], "k")==0)
        king();
        else if (strcmp(chessboard[before_x][before_y], "p")==0)
        pawn();
	else  //잘못 선택하였을 
	printf("다시 입력해주세요");	
}

void whowin(){
	int w_cnt,b_cnt;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(strcmp(chessboard[i][j],"K")==0){
				w_cnt++;
			}
			else if(strcmp(chessboard[i][j],"k")==0){
				b_cnt++;
			}
		}
	}
	if(w_cnt==0){
		printf("흑이 승리하였습니다!");
	}
	else if(b_cnt==0){
		printf("백이 승리하였습니다!");
	}
}
 
void astoin(){
	int i,j;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(strcmp(ind[i][j],&p_before)==0){
				before_x=i;
				before_y=j;
			}
		}
	}
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(strcmp(ind[i][j],&p_after)==0){
				after_x=i;
				after_y=j;
			}
		}
	}
}



void king() {                      //흰색 왕 이동코드
	if ( ((before_x - after_x <= 1) && (before_x - after_x >= -1)) && ((before_y - after_y <= 1) && (before_y - after_y)))             // 상하좌우 or 대각선 한칸
        		strcpy(chessboard[after_x][after_y], "k");
	else
		printf("이동이 불가합니다");
}

void King() {                    // 검은색 왕 이동코드
	if ( ((before_x - after_x <= 1) && (before_x - after_x >= -1)) && ((before_y - after_y <= 1) && (before_y - after_y)) )         // 상하좌우 or 대각선 한칸
        		strcpy(chessboard[after_x][after_y], "K");
	else
		printf("이동이 불가합니다");
}

void queen() {                     // 흰색 퀸 이동코드
	if ( (((before_x - after_x == 0) && (before_y - after_y != 0)) && ((before_x - after_x != 0) && (before_y - after_y != 0))) && ( ((before_x - after_x != 0) && (before_y - after_y != 0)) && ( ((before_x - after_x) - (before_y - after_y) == 0))))                    // 상하좌우대각선
		strcpy(chessboard[after_x][after_y], "q");

	else
		printf("이동이 불가합니다");
}

void Queen() {                      //검은색 퀸 이동코드
	if ( (((before_x - after_x == 0) && (before_y - after_y != 0)) && ((before_x - after_x != 0) && (before_y - after_y != 0))) && ( ((before_x - after_x != 0) && (before_y - after_y != 0)) && ( ((before_x - after_x) - (before_y - after_y) == 0))))                  //상하좌우대각선 
		strcpy(chessboard[after_x][after_y], "Q");

	else
		printf("이동이 불가합니다");
}

void rook() {                           // 흰색 룩 이동코드
	if ( ((before_x - after_x == 0) && (before_y - after_y != 0)) && ((before_x - after_x != 0) && (before_y - after_y != 0)) )                   // 상하좌우
		strcpy(chessboard[after_x][after_y], "r");
	else
		printf("이동이 불가합니다");
}

void Rook() {                               //검은색 룩 이동코드
	if ( ((before_x - after_x == 0) && (before_y - after_y != 0)) && ((before_x - after_x != 0) && (before_y - after_y != 0)) )                    // 상하좌우
		strcpy(chessboard[after_x][after_y], "R");
	else
		printf("이동이 불가합니다");
}

void bishop() {                           // 흰색 비숍 이동코드
	if ( ((before_x - after_x != 0) && (before_y - after_y != 0)) && ( ((before_x - after_x) - (before_y - after_y) == 0)) )                 // 대각선
		strcpy(chessboard[after_x][after_y], "b");

	else
		printf("이동이 불가합니다");
}

void Bishop() {                      // 검은색 비숍 이동코드
	if ( ((before_x - after_x != 0) && (before_y - after_y != 0)) && ( ((before_x - after_x) - (before_y - after_y) == 0)) )                // 대각선
		strcpy(chessboard[after_x][after_y], "B");
	else
		printf("이동이 불가합니다");
}

void knight() {                                                                       // 흰색 나이트 이동코드  미완성
	if ( (((before_x - after_x == -1) && (before_y - after_y == 2) || (before_x - after_x == 1) && (before_y - after_y == 2)) || ((before_x - after_x == -1) && (before_y - after_y == -2) || (before_x - after_x == 1) && (before_y - after_y == -2))) || (((before_x - after_x == -2) && (before_y - after_y == 1) || (before_x - after_x == 2) && (before_y - after_y == 1)) || ((before_x - after_x == -2) && (before_y - after_y == -1) || (before_x - after_x == 2) && (before_y - after_y == -1))) )                                                    
		strcpy(chessboard[after_x][after_y], "n");
	else
		printf("이동이 불가합니다");
}
 
void Knight() {                                                                       // 검은색 나이트 이동코드 미완성
	if ( (((before_x - after_x == -1) && (before_y - after_y == 2) || (before_x - after_x == 1) && (before_y - after_y == 2)) || ((before_x - after_x == -1) && (before_y - after_y == -2) || (before_x - after_x == 1) && (before_y - after_y == -2))) || (((before_x - after_x == -2) && (before_y - after_y == 1) || (before_x - after_x == 2) && (before_y - after_y == 1)) || ((before_x - after_x == -2) && (before_y - after_y == -1) || (before_x - after_x == 2) && (before_y - after_y == -1))) )
		strcpy(chessboard[after_x][after_y], "N");
	else
		printf("이동이 불가합니다");
}

void pawn() {                  // 백색 폰 이동코드          
	if (before_y == 2) {                                                     // 처음 폰을 움직일때 (흰 말)
		if ( (strcmp(chessboard[before_x-1][before_y+1], "P") ==0) || (strcmp(chessboard[before_x+1][before_y+1], "P") == 0) || (strcmp(chessboard[before_x-1][before_y], "P") == 0) || (strcmp(chessboard[before_x+1][before_y], "P") == 0)) {             // 공격하는 상황이면 (앙파상 포함)
			if (((before_x - after_x == -1) || (before_x - after_x == 1)) && (before_y - after_y == -1))               // 대각선으로 한칸 (흰 말) 
				strcpy(chessboard[after_x][after_y], "p");
			else
				printf("이동할 수 없습니다");
		}

		else {                   // 공격하지 않는 상황이면	
			if(((before_y - after_y == -2) || (before_y - after_y == -1)) && (before_x - after_y == 0))   // 위로 두칸 or 한칸
				strcpy(chessboard[after_x][after_y], "p");
			else
				printf("이동할 수 없습니다");
		}
	}

	else {                                                              // 폰을 처음 움직이는게 아니라면 (흰 말)
		if ( (strcmp(chessboard[before_x-1][before_y+1], "P") ==0) || (strcmp(chessboard[before_x+1][before_y+1], "P") == 0) || (strcmp(chessboard[before_x-1][before_y], "P") == 0) || (strcmp(chessboard[before_x+1][before_y], "P") == 0))   {           // 공격하는 상황이면 (앙파상 포함)
			if (((before_x - after_x == -1) || (before_x - after_x ==1)) && (before_y - after_y == -1))               // 대각선으로 한칸 (흰 말) 
				strcpy(chessboard[after_x][after_y], "p");
			else
				printf("이동할 수 없습니다");
		}
		else {             // 공격하지 않는 상황이면
			if ((before_x - after_x == 0) && (before_y - after_y ==-1))          // 위로 한칸
				strcpy(chessboard[after_x][after_y], "p");
			else
				printf("이동할 수 없습니다");
		}
	}			
}

void Pawn() {                 // 검은색 폰 이동코드
	if (before_y == 7) {                                                     // 처음 폰을 움직일때 (검은 말)
		 if ( (strcmp(chessboard[before_x-1][before_y-1], "p") ==0) || (strcmp(chessboard[before_x+1][before_y-1], "p") == 0) || (strcmp(chessboard[before_x-1][before_y], "p") == 0) || (strcmp(chessboard[before_x+1][before_y], "p") == 0)) {                 // 공격하는 상황이면 (앙파상 포함)
			if (((before_x - after_x == -1) || (before_x - after_x == 1)) && (before_y - after_y == 1))               // 대각선으로 한칸 (검은 말)       
				strcpy(chessboard[after_x][after_y], "P");
			else
				printf("이동할 수 없습니다");
		}

		else {                   // 공격하지 않는 상황이면	
			if(((before_y - after_y == 2) || (before_y - after_y == 1)) && (before_x - before_y == 0))   // 아래로 두칸 or 한칸
				strcpy(chessboard[after_x][after_y], "P");
			else
				printf("이동할 수 없습니다");
		}
	}

	else {                                                              // 폰을 처음 움직이는게 아니라면 (검 말)
		if ( (strcmp(chessboard[before_x-1][before_y-1], "p") ==0) || (strcmp(chessboard[before_x+1][before_y-1], "p") == 0) || (strcmp(chessboard[before_x-1][before_y], "p") == 0) || (strcmp(chessboard[before_x+1][before_y], "p") == 0))   {                 // 공격하는 상황이면 (앙파상 포함)
			if (((before_x - after_x == -1) || (before_x - after_x == 1)) && (before_y - after_y == -1))               // 대각선으로 한칸 (검은 말) 
				strcpy(chessboard[after_x][after_y], "P");
			else
				printf("이동할 수 없습니다");
		}
		else {             // 공격하지 않는 상황이면
			if ((before_x - after_x == 0) && (before_y - after_y == 1))          // 아래로 한칸
				strcpy(chessboard[after_x][after_y], "P");
			else
				printf("이동할 수 없습니다");
		}
	}
}
