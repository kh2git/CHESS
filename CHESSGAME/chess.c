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
void w_pro();
void b_pro();
void black();
void white();
int check();
int Check();
	
int player = 1, x, y, m, n;
int an_x=0;
int an_y=0;
int An_x=0;
int An_y=0;
char w, b;
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
   int keyCode, turn;
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

	if (player == 1)
	{
		printf("백의 턴입니다.(소문자)\n");
		check();//소문자진영
		input_loc();
		white();
		player++;
	}
		 
	else if (player == 2)
	{
		printf("흑의 턴입니다.(대문자)\n");
		Check();//대문자진영
		input_loc();
		black();
		player--;
	}
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
		printf("잘못된 입력입니다.\n");
		input_loc();
	}
    if(blcwht[before_x][before_y]==blcwht[after_x][after_y]){
	    	printf("아군을 공격할 수 없습니다.\n");
	    	input_loc();
	}
    
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

void black()           //검은말 이동           
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
	else
	printf("다시 입력해주세요\n");
}
void white()
{
        if (strcmp(chessboard[before_x][before_y], "r")==0)
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
	printf("다시 입력해주세요\n");
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
    if ( ((before_x - after_x <= 1) && (before_x - after_x >= -1)) && ((before_y - after_y <= 1) && (before_y - after_y >= -1))) {           // 상하좌우 or 대각선 한칸
                strcpy(chessboard[after_x][after_y], "k");
        strcpy(chessboard[before_x][before_y], ".");
        blcwht[after_x][after_y]=2;
        blcwht[before_x][before_y]=0;
    }
    else
        printf("이동할 수 없습니다.\n");
}

void King() {                    // 검은색 왕 이동코드
	if (((before_x - after_x <= 1) && (before_x - after_x >= -1)) && ((before_y - after_y <= 1) && (before_y - after_y >= -1))){       // 상하좌우 or 대각선 한칸
        		strcpy(chessboard[after_x][after_y], "K");
			strcpy(chessboard[before_x][before_y], ".");
        		blcwht[after_x][after_y]=1;
        		blcwht[before_x][before_y]=0;
	}
	else
		printf("이동할 수 없습니다.\n");
}

void queen() {                     // 흰색 퀸 이동코드
	if ( (((before_x - after_x == 0) && (before_y - after_y != 0)) || ((before_x - after_x != 0) && (before_y - after_y == 0))) ||  ((before_x - after_x) + (before_y - after_y) == 0) || ( ((before_x - after_x) - (before_y - after_y) == 0)) )      {              // 상하좌우대각선
		strcpy(chessboard[after_x][after_y], "q");
		strcpy(chessboard[before_x][before_y], ".");
        	blcwht[after_x][after_y]=2;
        	blcwht[before_x][before_y]=0;
	}
	else
		printf("이동할 수 없습니다.\n");
}

void Queen() {                      //검은색 퀸 이동코드
	if ( (((before_x - after_x == 0) && (before_y - after_y != 0)) || ((before_x - after_x != 0) && (before_y - after_y == 0))) ||  ((before_x - after_x) + (before_y - after_y) == 0) || ( ((before_x - after_x) - (before_y - after_y) == 0)) )                  //상하좌우대각선 
	{
		strcpy(chessboard[after_x][after_y], "Q");
		strcpy(chessboard[before_x][before_y], ".");
        	blcwht[after_x][after_y]=1;
        	blcwht[before_x][before_y]=0;
	}
	else
		printf("이동할 수 없습니다.\n");
}

void rook() {                           // 흰색 룩 이동코드
	if ( ((before_x - after_x == 0) && (before_y - after_y != 0)) || ((before_x - after_x != 0) && (before_y - after_y == 0)) ){                  // 상하좌우
		strcpy(chessboard[after_x][after_y], "r");
		strcpy(chessboard[before_x][before_y], ".");
       		blcwht[after_x][after_y]=2;
        	blcwht[before_x][before_y]=0;
	}
	else
		printf("이동할 수 없습니다.\n");
}

void Rook() {                               //검은색 룩 이동코드
	if ( ((before_x - after_x == 0) && (before_y - after_y != 0)) || ((before_x - after_x != 0) && (before_y - after_y == 0)) ){                // 상하좌우
		strcpy(chessboard[after_x][after_y], "R");
		strcpy(chessboard[before_x][before_y], ".");
       		blcwht[after_x][after_y]=1;
        	blcwht[before_x][before_y]=0;
	}
	else
		printf("이동할 수 없습니다.\n");
}

void bishop() {                           // 흰색 비숍 이동코드
	if ( ((before_x - after_x) + (before_y - after_y) == 0) || ( ((before_x - after_x) - (before_y - after_y) == 0)) )                 // 대각선
	{
		strcpy(chessboard[after_x][after_y], "b");
		strcpy(chessboard[before_x][before_y], ".");
        	blcwht[after_x][after_y]=2;
        	blcwht[before_x][before_y]=0;
	}

	else
		printf("이동할 수 없습니다.\n");
}

void Bishop() {                      // 검은색 비숍 이동코드
	if ( ((before_x - after_x) + (before_y - after_y) == 0) || ( ((before_x - after_x) - (before_y - after_y) == 0)) )  {              // 대각선
		strcpy(chessboard[after_x][after_y], "B");
		strcpy(chessboard[before_x][before_y], ".");
        	blcwht[after_x][after_y]=1;
        	blcwht[before_x][before_y]=0;
	}
	else
		printf("이동할 수 없습니다.\n");
}

void knight() {                                                                       // 흰색 나이트 이동코드  미완성
	if ( (((before_x - after_x == -1) && (before_y - after_y == 2) || (before_x - after_x == 1) && (before_y - after_y == 2)) || ((before_x - after_x == -1) && (before_y - after_y == -2) || (before_x - after_x == 1) && (before_y - after_y == -2))) || (((before_x - after_x == -2) && (before_y - after_y == 1) || (before_x - after_x == 2) && (before_y - after_y == 1)) || ((before_x - after_x == -2) && (before_y - after_y == -1) || (before_x - after_x == 2) && (before_y - after_y == -1))) )                                                    
	{
		strcpy(chessboard[after_x][after_y], "n");
		strcpy(chessboard[before_x][before_y], ".");
        	blcwht[after_x][after_y]=2;
        	blcwht[before_x][before_y]=0;
	}
	else
		printf("이동할 수 없습니다.\n");
}
 
void Knight() {                                                                       // 검은색 나이트 이동코드 미완성
	if ( (((before_x - after_x == -1) && (before_y - after_y == 2) || (before_x - after_x == 1) && (before_y - after_y == 2)) || ((before_x - after_x == -1) && (before_y - after_y == -2) || (before_x - after_x == 1) && (before_y - after_y == -2))) || (((before_x - after_x == -2) && (before_y - after_y == 1) || (before_x - after_x == 2) && (before_y - after_y == 1)) || ((before_x - after_x == -2) && (before_y - after_y == -1) || (before_x - after_x == 2) && (before_y - after_y == -1))) )
	{
		strcpy(chessboard[after_x][after_y], "N");
		strcpy(chessboard[before_x][before_y], ".");
        	blcwht[after_x][after_y]=1;
        	blcwht[before_x][before_y]=0;
	}
	else
		printf("이동할 수 없습니다.\n");
}

void pawn()             // 흰색 폰 이동코드
{
	if (An_x!=0) //앙파상 하는 상황이라면
        {       if ((after_y==An_y)&&(after_x==An_x-1)) //옮길 위치가 상대체스말 위라면(앙파상 실행 조건)
                {
                        strcpy(chessboard[An_x][An_y], ".");
                        strcpy(chessboard[before_x][before_y], ".");
                        strcpy(chessboard[after_x][after_y], "p");
                        An_x=0;
                        An_y=0;

                }

        }
        if ( before_x == 6 )            // 처음 움직일때 (흰 말)
        {
                 if ( (after_y == before_y) && (after_x == before_x-1) )                // 한칸만 이동하면
                {
                        if (blcwht[after_x][after_y] == 0) {
                                strcpy(chessboard[after_x][after_y], "p");
                                strcpy(chessboard[before_x][before_y], ".");
                                blcwht[after_x][after_y]=2;
                                blcwht[before_x][before_y]=0;
                                w_pro();
                        }
                    }
                 else if ( (after_y == before_y) && (after_x== before_x-2) )            // 첫수에 두칸 이동하면
                {
                        if (blcwht[after_x][after_y] == 0) {                                    //옮길 장소가 비어있다면
                                strcpy(chessboard[after_x][after_y], "p");                      //두칸 앞으로 옮긴다
                                strcpy(chessboard[before_x][before_y], ".");
                                blcwht[after_x][after_y]=2;
                                blcwht[before_x][before_y]=0;
                                w_pro();
                        	
                                if((strcmp(chessboard[after_x][after_y+1], "P")==0 || (strcmp(chessboard[after_x][after_y-1], "P")== 0))) //왼쪽 또는 오른쪽에 상대폰이 있다면
                                {
                                        an_x=after_x;                                                           //앙파상 대상이 되는 폰의 위치 저장
                                        an_y=after_y;
                                }
                    	}
                        else
                                printf("이동할 수 없습니다. \n");
                }
            
                else if ( (((after_y == before_y-1) && (after_y == before_y+1)) || (after_x == before_x-1)) )           // 공격하는 상황이면
                {
                        if (blcwht[after_x][after_y] == 1) {
                                strcpy(chessboard[after_x][after_y], "p");
                                strcpy(chessboard[before_x][before_y], ".");
                                        blcwht[after_x][after_y]=2;
                                blcwht[before_x][before_y]=0;
                                w_pro();
                        }
                        else
                                printf("이동할 수 없습니다. \n");
                }
                else
                        printf("이동할 수 없습니다. \n");
        }
        else            // 처음 움직이는게 아니라면 (흰 말)
        {
                if ( (after_y == before_y) && (after_x == before_x-1) )         // 공격하지 않고 이동만 하면
                {
                        if (blcwht[after_x][after_y] == 0) {
                                strcpy(chessboard[after_x][after_y], "p");
                                strcpy(chessboard[before_x][before_y], ".");
                                        blcwht[after_x][after_y]=2;
                                blcwht[before_x][before_y]=0;
                                w_pro();
                        }
                        else
                                printf("이동할 수 없습니다. \n");
                }
                else if ( (((after_y == before_y-1) && (after_y == before_y+1)) || (after_x == before_x-1)) )           //공격하는 상황이면
                {
                        if (blcwht[after_x][after_y] == 1) {
                                strcpy(chessboard[after_x][after_y], "p");
                                strcpy(chessboard[before_x][before_y], ".");
                                        blcwht[after_x][after_y]=2;
                                blcwht[before_x][before_y]=0;
                                w_pro();
                        }
                        else
                                printf("이동할 수 없습니다. \n");
                }
                else
                        printf("이동할 수 없습니다. \n");
        }
}

void Pawn()             // 검은색 폰 이동코드
{
        if (an_x!=0) //앙파상 하는 상황이라면
        {       if ((after_y==an_y)&&(after_x==an_x+1)) //옮길 위치가 상대체스말 아래라면(앙파상 실행 조건)
                {
                        strcpy(chessboard[an_x][an_y], ".");
                        strcpy(chessboard[before_x][before_y], ".");
                        strcpy(chessboard[after_x][after_y], "P");
                        an_x=0;
                        an_y=0;

                }
                

        }
        else if ( before_x == 1 )            // 처음 움직일때 (검은 말)
        {
                 if ( (after_y == before_y) && (after_x == before_x+1) )                // 한칸만 이동하면
                {
                        if (blcwht[after_x][after_y] == 0) {
                                strcpy(chessboard[after_x][after_y], "P");
                                strcpy(chessboard[before_x][before_y], ".");
                                blcwht[after_x][after_y]=1;
                                blcwht[before_x][before_y]=0;
                                b_pro();
                        }
                    }
                 else if ( (after_y == before_y) && (after_x== before_x+2) )            // 첫수에 두칸 이동하면
                {
                        if (blcwht[after_x][after_y] == 0) {                                    //옮길 장소가 비어있다면
                                strcpy(chessboard[after_x][after_y], "P");                      //두칸 앞으로 옮긴다
                                strcpy(chessboard[before_x][before_y], ".");
                                blcwht[after_x][after_y]=1;
                                blcwht[before_x][before_y]=0;
                                b_pro();
                        	
                                if((strcmp(chessboard[after_x][after_y+1], "P")==0 || (strcmp(chessboard[after_x][after_y-1], "p")== 0))) //왼쪽 또는 오른쪽에 상대폰이 있다면
                                {
                                        An_x=after_x;                                                           //앙파상 대상이 되는 폰의 위치 저장
                                        An_y=after_y;
                                }
                    	}
                        else
                                printf("이동할 수 없습니다. \n");
                }
                else if ( (after_y == before_y) && (after_x == before_x+2) )            // 공격하지 않고 이동만 하면
                {
                        if(blcwht[after_x][after_y] == 0) {
                                strcpy(chessboard[after_x][after_y], "P");
                                strcpy(chessboard[before_x][before_y], ".");
                                        blcwht[after_x][after_y]=1;
                                blcwht[before_x][before_y]=0;
                                b_pro();
                        }
                        else
                                printf("이동할 수 없습니다. \n");
                }
                else if ( (((after_y == before_y-1) && (after_y == before_y+1)) || (after_x == before_x+1)) )           // 공격하는 상황이면
                {
                        if (blcwht[after_x][after_y] == 2) {
                                strcpy(chessboard[after_x][after_y], "P");
                                strcpy(chessboard[before_x][before_y], ".");
                                        blcwht[after_x][after_y]=1;
                                blcwht[before_x][before_y]=0;
                                b_pro();
                        }
                        else
                                printf("이동할 수 없습니다. \n");
                }
                else
                        printf("이동할 수 없습니다. \n");
        }
        else            // 처음 움직이는게 아니라면 (검은 말)
        {
                if ( (after_y == before_y) && (after_x == before_x+1) )         //공격하지 않고 이동만 하면
                {
                        if(blcwht[after_x][after_y] == 0) {
                                strcpy(chessboard[after_x][after_y], "P");
                                strcpy(chessboard[before_x][before_y], ".");
                                        blcwht[after_x][after_y]=1;
                                blcwht[before_x][before_y]=0;
                                b_pro();
                        }
                        else
                                printf("이동할 수 없습니다. \n");
                }
                else if ( (((after_y == before_y-1) && (after_y == before_y+1)) || (after_x == before_x+1)) )           //공격하는 상황이면
                {
                        if (blcwht[after_x][after_y] == 2) {
                                strcpy(chessboard[after_x][after_y], "P");
                                strcpy(chessboard[before_x][before_y], ".");
                                        blcwht[after_x][after_y]=1;
                                blcwht[before_x][before_y]=0;
                                b_pro();
                        }
                        else
                                printf("이동할 수 없습니다. \n");
                }

                else
                        printf("이동할 수 없습니다. \n");
        }
}
void w_pro() {
	if (after_x == 0) {
		printf("q, n, r, b 중 승격할 말을 선택 : ");
		scanf(" %c", &w);
		switch (w) {
		case 'q':
			strcpy(chessboard[after_x][after_y], "q");
			break;
		case 'n':
			strcpy(chessboard[after_x][after_y], "n");
			break;
		case 'r':
			strcpy(chessboard[after_x][after_y], "r");
			break;
		case 'b':
			strcpy(chessboard[after_x][after_y], "b");
			break;
		default: 
			printf("잘못된 입력입니다.\n");
			w_pro();
		}
	}
}

void b_pro() {
	if (after_x == 7) {
		printf("q, n, r, b 중 승격할 말을 선택 : ");
		scanf(" %c", &b);
		if (b == 'q')
			strcpy(chessboard[after_x][after_y], "Q");
		else if (b == 'n')
			strcpy(chessboard[after_x][after_y], "N");
		else if (b == 'r')
			strcpy(chessboard[after_x][after_y], "R");
		else if (b == 'b')
			strcpy(chessboard[after_x][after_y], "B");
		else {
			printf("잘못된 입력입니다.\n");
			b_pro();
		}
	}
}

int check()//소문자의 체크 판별
{
	int king_x,king_y,check_cnt=0;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(strcmp(chessboard[i][j],"k")==0){
				king_x=i;
				king_y=j;
			}
		}
	}
	for(int i=-1;i<2;i++){
		for(int j=-1;j<2;j++){
			if(strcmp(chessboard[king_x+i][king_y+j],"K")==0){
				check_cnt++;
			}
		}
	}
	if(strcmp(chessboard[king_x-1][king_y-1],"P")==0){
		check_cnt++;
	}
	if(strcmp(chessboard[king_x-1][king_y+1],"P")==0){
		check_cnt++;
	}
	if(strcmp(chessboard[king_x+1][king_y+2],"N")==0){
		check_cnt++;
	}
	if(strcmp(chessboard[king_x-1][king_y+2],"N")==0){
		check_cnt++;
	}
	if(strcmp(chessboard[king_x+1][king_y-2],"N")==0){
		check_cnt++;
	}
	if(strcmp(chessboard[king_x-1][king_y-2],"N")==0){
		check_cnt++;
	}
	if(strcmp(chessboard[king_x+2][king_y+1],"N")==0){
		check_cnt++;
	}
	if(strcmp(chessboard[king_x-2][king_y+1],"N")==0){
		check_cnt++;
	}
	if(strcmp(chessboard[king_x+2][king_y-1],"N")==0){
		check_cnt++;
	}
	if(strcmp(chessboard[king_x-2][king_y-1],"N")==0){
		check_cnt++;
	}
	for(int i=king_x;i<8;i++){
			if(strcmp(chessboard[i][king_y],"R")==0){
				check_cnt++;
				break;
			}
			if(strcmp(chessboard[i][king_y],"Q")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][king_y],"k")!=0){
				if(blcwht[i][king_y]!=0){
					break;
				}
			}
	}
	for(int i=king_x;i>-1;i--){
			if(strcmp(chessboard[i][king_y],"R")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][king_y],"Q")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][king_y],"k")!=0){
				if(blcwht[i][king_y]!=0){
					break;
				}
			}
	}
	for(int j=king_y;j<8;j++){
			if(strcmp(chessboard[king_x][j],"R")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[king_x][j],"Q")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[king_x][j],"k")!=0){
				if(blcwht[king_x][j]!=0){
					break;
				}
			}
	}
	for(int j=king_y;j>-1;j--){
			if(strcmp(chessboard[king_x][j],"R")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[king_x][j],"Q")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[king_x][j],"k")!=0){
				if(blcwht[king_x][j]!=0){
					break;
				}
			}
	}
	for(int i=king_x,j=king_y;i<8&&j<8;i++,j++){
			if(strcmp(chessboard[i][j],"B")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][j],"Q")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][j],"k")!=0){
				if(blcwht[i][j]!=0){
					break;
				}
			}
	}
	for(int i=king_x,j=king_y;i>-1&&j<8;i--,j++){
			if(strcmp(chessboard[i][j],"B")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][j],"Q")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][j],"k")!=0){
				if(blcwht[i][j]!=0){
					break;
				}
			}
			
	}
	for(int i=king_x,j=king_y;i<8&&j>-1;i++,j--){
			if(strcmp(chessboard[i][j],"B")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][j],"Q")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][j],"k")!=0){
				if(blcwht[i][j]!=0){
					break;
				}
			}
	}
	for(int i=king_x,j=king_y;i>-1&&j>-1;i--,j--){
			if(strcmp(chessboard[i][j],"B")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][j],"Q")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][j],"k")!=0){
				if(blcwht[i][j]!=0){
					break;
				}
			}
	}
	
	if(check_cnt>0){
		printf("체크!\n");
	}
}

int Check()//대문자의 체크 판별
{
	int king_x,king_y,check_cnt=0;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(strcmp(chessboard[i][j],"K")==0){
				king_x=i;
				king_y=j;
			}
		}
	}
	for(int i=-1;i<2;i++){
		for(int j=-1;j<2;j++){
			if(strcmp(chessboard[king_x+i][king_y+j],"k")==0){
				check_cnt++;
			}
		}
	}
	if(strcmp(chessboard[king_x-1][king_y-1],"p")==0){
		check_cnt++;
	}
	if(strcmp(chessboard[king_x-1][king_y+1],"p")==0){
		check_cnt++;
	}
	if(strcmp(chessboard[king_x+1][king_y+2],"n")==0){
		check_cnt++;
	}
	if(strcmp(chessboard[king_x-1][king_y+2],"n")==0){
		check_cnt++;
	}
	if(strcmp(chessboard[king_x+1][king_y-2],"n")==0){
		check_cnt++;
	}
	if(strcmp(chessboard[king_x-1][king_y-2],"n")==0){
		check_cnt++;
	}
	if(strcmp(chessboard[king_x+2][king_y+1],"n")==0){
		check_cnt++;
	}
	if(strcmp(chessboard[king_x-2][king_y+1],"n")==0){
		check_cnt++;
	}
	if(strcmp(chessboard[king_x+2][king_y-1],"n")==0){
		check_cnt++;
	}
	if(strcmp(chessboard[king_x-2][king_y-1],"n")==0){
		check_cnt++;
	}
	for(int i=king_x;i<8;i++){
			if(strcmp(chessboard[i][king_y],"r")==0){
				check_cnt++;
				break;
			}
			if(strcmp(chessboard[i][king_y],"q")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][king_y],"K")!=0){
				if(blcwht[i][king_y]!=0){
					break;
				}
			}
	}
	for(int i=king_x;i>-1;i--){
			if(strcmp(chessboard[i][king_y],"r")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][king_y],"q")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][king_y],"K")!=0){
				if(blcwht[i][king_y]!=0){
					break;
				}
			}
	}
	for(int j=king_y;j<8;j++){
			if(strcmp(chessboard[king_x][j],"r")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[king_x][j],"q")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[king_x][j],"K")!=0){
				if(blcwht[king_x][j]!=0){
					break;
				}
			}
	}
	for(int j=king_y;j>-1;j--){
			if(strcmp(chessboard[king_x][j],"r")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[king_x][j],"q")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[king_x][j],"K")!=0){
				if(blcwht[king_x][j]!=0){
					break;
				}
			}
	}
	for(int i=king_x,j=king_y;i<8&&j<8;i++,j++){
			if(strcmp(chessboard[i][j],"b")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][j],"q")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][j],"K")!=0){
				if(blcwht[i][j]!=0){
					break;
				}
			}
	}
	for(int i=king_x,j=king_y;i>-1&&j<8;i--,j++){
			if(strcmp(chessboard[i][j],"b")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][j],"q")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][j],"K")!=0){
				if(blcwht[i][j]!=0){
					break;
				}
			}
			
	}
	for(int i=king_x,j=king_y;i<8&&j>-1;i++,j--){
			if(strcmp(chessboard[i][j],"b")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][j],"q")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][j],"K")!=0){
				if(blcwht[i][j]!=0){
					break;
				}
			}
	}
	for(int i=king_x,j=king_y;i>-1&&j>-1;i--,j--){
			if(strcmp(chessboard[i][j],"b")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][j],"q")==0){
				check_cnt++;
			}
			if(strcmp(chessboard[i][j],"K")!=0){
				if(blcwht[i][j]!=0){
					break;
				}
			}
	}
	
	if(check_cnt>0){
		printf("체크!\n");
	}
}
