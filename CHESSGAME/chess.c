#include <stdio.h>
#include <termio.h>
#include <stdlib.h>

void titleDraw();
void menuDraw();
void howtouse();
int getch();

int main(){
   system("clear");
   menuDraw();
   int keyCode;
   scanf("%d",&keyCode);
   switch(keyCode){
      case 1:
         break;
      case 2:
         howtouse();
         break;
      case 3:
         break;
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
