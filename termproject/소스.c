#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <stralign.h>
#include <time.h>

#define kbhit _kbhit
#define getch _getch
#define width 90
#define height 32
#define maxword 5
#define KEY_ENTER '\r'
#define number 30 
#define space_word 5
#define line 26
#define enter 13
#define backspace 8
#define ESC 0x1b
#define BLACK   0
#define BLUE1   1
#define GREEN1   2
#define CYAN1   3
#define RED1   4
#define MAGENTA1 5
#define YELLOW1   6
#define GRAY1   7
#define GRAY2   8
#define BLUE2   9
#define GREEN2   10
#define CYAN2   11
#define RED2   12
#define MAGENTA2 13
#define YELLOW2   14
#define WHITE   15

int frame_count = 0;
int score = 0;
int idx = 0;
int j = 0;
int life = 3;
int wordinterval = 2;
int iteminterval = 10;
int item2interval = 7;
int return_menu = 0;


void CursorView(char show)//커서숨기기 0이면 숨김, 1이면 보임
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void cls(int bg_color, int text_color)
{
    char cmd[100];
    system("cls");
    sprintf(cmd, "COLOR %x%x", bg_color, text_color);
    system(cmd);

}

void SetColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void textcolor(int fg_color, int bg_color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}
void Console_Size() //콘솔 사이즈 설정
{
    char temp[50];
    sprintf(temp, "Mode con cols=%d lines=%d", width, height);
    /*system(temp);*/
}


void gotoxy(int x, int y) //내가 원하는 위치로 커서 이동
{
    COORD pos; // Windows.h 에 정의
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


char words[100][30] = { "apple","banana","orange","melon","kiwi", "watermelon", "grape", "peach", "tomato","cherry",
"grapefruit", "tangerine", "plum", "coconut","meat","bean","onion","garlic","beef","rice",
"provide", "develop", "service", "inform", "improve", "require", "advise","social", "amount", "behave",
"employ", "ability", "expense", "local", "stress", "ride", "person","burn" , "cave", "cross",
"kick", "spill", "simple", "spark", "lecture", "sunset" , "able" , "simple","care", "tail",
"stand", "excite", "erase", "relax", "stand", "soon", "floor", "sing", "dance", "magic",
"bill", "center", "host", "evil","fat", "each", "deaf", "wing", "still", "sheet",
"old", "all", "bubble", "little", "move","joke", "ocean", "new", "fire", "easy" ,
"math", "music", "move", "gold" , "afraid", "sport", "listen", "change", "time","city",
"idea", "noise", "nose", "eye", "ear", "year", "cold", "king", "queen", "road" };

char word2[10][30] = {
    "splendid","greatness","superb","celestial","tranquility","supernova","splendent",
    "magnificent","confidence","sublimity" };

char word3[10][30] = {
    "comfort","tradition","schedule","pollution","machine","respect","candle","solution",
    "teenager","increase" };

typedef struct {
    int x; //x좌표
    int y; //y좌표

    char word[30]; //단어 저장 공간
}rain;

rain rains[30];  //문자열을 보관하는 배열
rain item1[30]; //아이템 문자열을 보관하는 배열
rain item2[30];
char input[20]; //단어 입력받을 배열


int startmenu() { //첫 화면


    SetColor(9, 0);
    gotoxy(0, 1); printf("       ■         ■■■■    ■■■■■    ■■■■      ");
    gotoxy(0, 2); printf("     ■  ■      ■       ■      ■        ■      ■");
    gotoxy(0, 3); printf("    ■    ■     ■               ■        ■       ■");
    gotoxy(0, 4); printf("   ■■■■■    ■               ■        ■        ■   ");
    gotoxy(0, 5); printf("  ■        ■   ■               ■        ■       ■");
    gotoxy(0, 6); printf("  ■        ■   ■       ■      ■        ■      ■");
    gotoxy(0, 7); printf("  ■        ■    ■■■■    ■■■■■    ■■■■ ");

    SetColor(8, 0);
    gotoxy(30, 10); printf(" ■■■■            ■         ■■■■■    ■■       ■");
    gotoxy(30, 11); printf(" ■      ■        ■  ■           ■        ■ ■      ■");
    gotoxy(30, 12); printf(" ■      ■       ■    ■          ■        ■  ■     ■");
    gotoxy(30, 13); printf(" ■■■■        ■■■■■         ■        ■   ■    ■");
    gotoxy(30, 14); printf(" ■     ■      ■        ■        ■        ■    ■   ■");
    gotoxy(30, 15); printf(" ■      ■     ■        ■        ■        ■     ■  ■");
    gotoxy(30, 16); printf(" ■       ■    ■        ■    ■■■■■    ■       ■■");
    SetColor(15, 0);

    SetColor(YELLOW2, 0);
    gotoxy(40, 23);
    printf("게임시작\n");
    gotoxy(40, 26);
    printf("게임방법\n");
    gotoxy(40, 29);
    printf("게임종료\n");
    gotoxy(50, 23);
    SetColor(15, 0);
    printf("◀");

    int return_menu = 0;
    while (1) //키보드 움직임
    {
        int key;
        if (kbhit())
        {
            key = getch();
            if (key == 224 || key == 0)
            {
                key = getch();
                switch (key)
                {
                case 72: //상
                    gotoxy(50, 23 + return_menu);
                    printf("  ");
                    return_menu -= 3;
                    if (return_menu < 0) return_menu = 0;
                    gotoxy(50, 23 + return_menu);
                    printf("◀");
                    break;
                case 80: //하
                    gotoxy(50, 23 + return_menu);
                    printf("  ");
                    return_menu += 3;
                    if (return_menu > 6) return_menu = 6;
                    gotoxy(50, 23 + return_menu);
                    printf("◀");
                    break;
                default:
                    break;
                }
            }
            else
                if (key == 13)//엔터
                    return return_menu;
        }
    }
}

void init_word() { //배열 초기화
    for (int i = 0; i < 30; i++) {
        rains[i].x = 0;
        strcpy(rains[i].word, " ");
    }
    for (int i = 0; i < 30; i++) {
        item1[i].x = 0;
        strcpy(rains[i].word, " ");
    }
    for (int i = 0; i < 30; i++) {
        item2[i].x = 0;
        strcpy(rains[i].word, " ");
    }
    
}
void draw_map() { //맵 그림

    gotoxy(0, 26);
    printf("－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－\n");
    gotoxy(0, 28);
    printf("------------------------------------------------------------------------------------------\n");
    gotoxy(0, 29);
    printf(" 입력:%s",input);
    gotoxy(0, 1);

}

void show_score() {
    gotoxy(0, 1);
    textcolor(RED2, YELLOW2);
    printf("점수:%d", score);
    textcolor(15, 0);
}

int kx = 6, ky = 29;
void input_key() { //사용자 키 입력받는 함수

    char ch;



    if (kbhit()) {
        //gotoxy(kx + j, ky);
        ch = _getch();


        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            input[j] = ch;
            gotoxy(kx + j, ky);
            putchar(ch);
            j++;
        }
        else if (ch == backspace) {
            if (j > 0) {
                j--;
                input[strlen(input) - 1] = NULL;

            }
        }
        else if (ch == enter) {
            for (int i = 0; i < 30; i++) {
                if (strcmp(item1[i].word, input) == 0) {
                    score += 50;
                    strcpy(item1[i].word, " ");
                }
                else if (strcmp(rains[i].word, input) == 0) {
                    score += 10;
                    strcpy(rains[i].word, " ");
                }
                else if (strcmp(item2[i].word, input) == 0) {
                    score += 10;
                    Sleep(1000);
                    strcpy(item2[i].word, " ");
                }

            }
            memset(input, 0, 20);//enter 눌렀을때 문자열 초기화 
            j = 0;
        }
        gotoxy(7, 29);
        /*printf("%s", input);*/
    }
}


void remove_word() { 


    if (rains[0].y == 26) {
        for (int j = 0; j < 29; j++) {
            rains[j] = rains[j + 1];
        }
        strcpy(rains[29].word, words[rand() % 100]);
        rains[29].x = rand() % 70;
        rains[29].y = 0;
    }
    else if (item1[0].y == 26) {
        for (int k = 0; k < 9; k++) {
            item1[k] = item1[k + 1];
        }
    }
    else if (item2[0].y == 26) {
        for (int l = 0; l < 9; l++) {
            item2[l] = item2[l + 1];
        }
    }
    

}


void show_time(int remain_time) {
    gotoxy(0, 0);
    textcolor(RED2, YELLOW2);
    printf("남은시간 : %02d", remain_time);
    textcolor(WHITE, BLACK);
}


void print_word() { 


    system("cls");
    draw_map();
    for (int i = 0; i < 30; i++) 
    {
        gotoxy(rains[i].x, rains[i].y);
        printf("%s\n", rains[i].word);
        rains[i].y++;
    }


}

void print_itemword() { 

    draw_map();
    for (int i = 0; i < 30; i++) 
    {

        gotoxy(item1[i].x, item1[i].y);
        SetColor(10);
        printf("%s", item1[i].word);
        SetColor(15);
        item1[i].y++;
    }

}

void print_itemword2() {

    draw_map();
    for (int i = 0; i < 30; i++) 
    {

        gotoxy(item2[i].x, item2[i].y);
        SetColor(RED2);
        printf("%s", item2[i].word);
        SetColor(15);
        item2[i].y++;
    }

}


void make_word(int i) {

  
        strcpy(rains[i].word, words[rand() % 100]);
        rains[i].x = rand() % width - 5; 
        rains[i].y = 2; 
    
}

void make_itemword(int itemIndex) {

    strcpy(item1[itemIndex].word, word2[rand() % 10]);
    item1[itemIndex].x = rand() % width - 5; 
    item1[itemIndex].y = 2; 
}

void make_itemword2(int itemIndex2) {

    strcpy(item2[itemIndex2].word, word3[rand() % 10]);
    item2[itemIndex2].x = rand() % width - 5; 
    item2[itemIndex2].y = 2; 
}


void gamestart() {
    int i, g;


    gotoxy(30, 10); printf("┌────────────────┐");
    gotoxy(30, 11); printf("│                                │");
    gotoxy(30, 12); printf("│                                │");
    gotoxy(30, 13); printf("│      시작하려면 enter키를      │");
    gotoxy(30, 14); printf("│          눌러주세요!           │");
    gotoxy(30, 15); printf("│                                │");
    gotoxy(30, 16); printf("│                                │");
    gotoxy(30, 17); printf("└────────────────┘");

    while (1)
    {
        if (kbhit())
        {
            g = getch();
            if (g == KEY_ENTER)
                break;
        }
    }
}


char c;
void game_over() {
    while (1) {
        int c1, c2;
        do { // 색을 변경하면서 Game Over 출력
            c1 = rand() % 16;
            c2 = rand() % 16;
        } while (c1 == c2);
        textcolor(c1, c2);
        gotoxy(35, 10);
        printf("** Game Over **");

        gotoxy(26, 14);
        printf("메인메뉴로 나가려면 Q를 눌러주세요");
        Sleep(300);
        textcolor(15, 0);
        if (kbhit()) {
            c = getch();
            if (c == 'q') {
                score = 0;
                system("cls");
                return return_menu;
            }
        }

    }
}

void round_clear2() {
    int q;
    while (1) {
        int c1, c2;
        do { // 색을 변경하면서 Game Over 출력
            c1 = rand() % 16;
            c2 = rand() % 16;
        } while (c1 == c2);
        textcolor(c1, c2);
        gotoxy(35, 10);
        printf("★★ 2라운드 클리어 ★★");

        textcolor(YELLOW1, 0);
        gotoxy(29, 14);
        printf("축하합니다! 모든 라운드를 클리어하셨습니다.");
        gotoxy(34, 15);
        printf("메인메뉴로 나가려면 ESC를 누르세요");
        Sleep(300);
        textcolor(15, 0);
        if (kbhit()) {
            q = getch();
            if (q == ESC) {
                system("cls");
                score = 0;
                return return_menu;
            }
        }

    }
}

void round_two() {


    srand((unsigned)time(NULL));
    system("cls");
    CursorView(0);
    gamestart();
    system("cls");

    gotoxy(43, 14); printf("3");
    Sleep(1000);
    gotoxy(43, 14); printf("2");
    Sleep(1000);
    gotoxy(43, 14); printf("1");
    Sleep(1000);
    system("cls");

    int i = 0;
    int k = 1;

    init_word();
    make_word(k);

    draw_map();
    show_score();
    int time_out = 60;
    unsigned char ch;
    int run_time, start_time, remain_time, last_remain_time;
    int print_time;
    print_time = 0;
    start_time = time(NULL);
    last_remain_time = remain_time = time_out;
    show_time(remain_time);
    int status = 0;
    int play = 0;
    int t = 1;
    int itemindex = 0;
    int itemindex2 = 0;

    while (1)
    {
        run_time = time(NULL) - start_time;
        if (run_time > print_time && (run_time % iteminterval == 0)) {

            make_itemword(itemindex);
            itemindex++;
            /*Sleep(500);*/
            print_time = run_time;

        }

        else if (run_time > print_time && (run_time % wordinterval == 0)) {

            make_word(i);
            i++;
            /*Sleep(500);*/
            print_time = run_time;

        }
        else if (run_time > print_time && (run_time % item2interval == 0)) {

            make_itemword2(itemindex2);
            itemindex2++;
            /*Sleep(500);*/
            print_time = run_time;

        }

        remain_time = time_out - run_time;
        show_time(remain_time); //타이머 출력
        last_remain_time = remain_time;

        if (remain_time == 0) { // 시간 종료
            play = 2;
            break;
        }



        input_key();
        Sleep(50);

        if (frame_count % 10 == 0) {
            print_itemword2(itemindex2);
            Sleep(10);
        }
        frame_count++;


        if (frame_count % 10 == 0) {
            draw_map();
            print_word();
            print_itemword(itemindex);
            draw_map();
            show_time(remain_time);
            show_score();
            Sleep(100);
            remove_word();
        }


        if (score >= 200) {
            play = 1;
            break;
        }

    }

    if (play == 1) {
        system("cls");
        round_clear2();
    }
    else if (play == 2) {
        system("cls");
        game_over();
    }
}




void round_clear1() {
    int o;
    while (1) {
        int c1, c2;
        do { // 색을 변경하면서 Game Over 출력
            c1 = rand() % 16;
            c2 = rand() % 16;
        } while (c1 == c2);
        textcolor(c1, c2);
        gotoxy(35, 10);
        printf("★★ 1라운드 클리어 ★★");

        textcolor(YELLOW1, 0);
        gotoxy(34, 14);
        printf("2라운드로 가려면 ENTER를");
        gotoxy(29, 15);
        printf("메인메뉴로 나가려면 ESC를 누르세요");
        Sleep(300);
        textcolor(15, 0);
        if (kbhit()) {
            o = getch();
            if (o == 13) {
                score = 0;
                system("cls");
                return round_two();
            }
            else if (o == ESC) {
                system("cls");
                score = 0;
                return return_menu;
            }
        }

    }
    
}


void round_one() {


    srand((unsigned)time(NULL));
    system("cls");
    CursorView(0);
    gamestart();
    system("cls");

    gotoxy(43, 14); printf("3");
    Sleep(1000);
    gotoxy(43, 14); printf("2");
    Sleep(1000);
    gotoxy(43, 14); printf("1");
    Sleep(1000);
    system("cls");

    int i = 0;
    int k = 1;

    init_word();
    make_word(k);

    draw_map();
    show_score();
    int time_out = 60;
    unsigned char ch;
    int run_time, start_time, remain_time, last_remain_time;
    int print_time;
    print_time = 0;
    start_time = time(NULL);
    last_remain_time = remain_time = time_out;
    show_time(remain_time);
    int status = 0;
    int play = 0;
    int t = 1;
    int itemindex = 0;
    int itemindex2 = 0;

    while (1)
    {
        run_time = time(NULL) - start_time;
        if (run_time > print_time && (run_time % iteminterval == 0)) {

            make_itemword(itemindex);
            itemindex++;
            /*Sleep(500);*/
            print_time = run_time;

        }

        else if (run_time > print_time && (run_time % wordinterval == 0)) {

            make_word(i);
            i++;
            /*Sleep(500);*/
            print_time = run_time;

        }
       

        remain_time = time_out - run_time;
        show_time(remain_time); //타이머 출력
        last_remain_time = remain_time;

        if (remain_time == 0) { // 시간 종료
            play = 2;
            break;
        }


        
        input_key();
        Sleep(50);
        
       
        frame_count++;


        if (frame_count % 10 == 0) {
            draw_map();
            print_word();
            print_itemword(itemindex);
            draw_map();
            show_time(remain_time);
            show_score();
            Sleep(400);
            remove_word();
        }


        if (score >= 200) {
            play = 1;
            break;
        }

    }

    if (play == 1) {
        system("cls");
        round_clear1();
    }
    else if (play == 2) {
        system("cls");
        game_over();
    }
}




void Menu_two() {
    system("cls");
    gotoxy(22, 13);
    printf("화면에서 떨어지는 영단어들을 빠르게 쳐야하는");
    gotoxy(22, 14);
    printf("게임입니다. 총 2라운드로 구성되어있으며 라운드가");
    gotoxy(22, 15);
    printf("높아질수록 난이도가 어려워집니다. 기본 점수는 0점으로");
    gotoxy(22, 16);
    printf("시작하고 단어를 정확히 치면 10점, 초록색 단어는 50점이며");
    gotoxy(22, 17);
    printf("빨간색 단어는 일시적인 스턴 효과를 줍니다.");
    gotoxy(24, 20);
    printf("메인메뉴로 돌아가려면 enter키를 눌러주세요!");

    

    while (1)
    {
        int g;
        if (kbhit())
        {
            g = getch();
            if (g == 13)
                system("cls");
            return return_menu;
        }
    }
}

void Menu_three() {
    system("cls");
    gotoxy(30, 10);
    textcolor(12, 0);
    printf("정말 종료하시겠습니까?(Y/N)");
    textcolor(15, 0);
    gotoxy(34, 14);
    printf("종료를 원하시면 Y를");
    gotoxy(24, 15);
    printf("다시 메인메뉴로 돌아가려면 N을 눌러주세요");
    while (1)
    {
        int q;
        if (kbhit())
        {
            q = getch();
            if (q == 'y')
                exit(1);
            else if (q == 'n');
                return startmenu();
        }
    }
}


void main() {
    srand(time(NULL));
    Console_Size();
    CursorView(0);
    while (1) {
        int return_menu = startmenu();
        if (return_menu == 0)round_one();
        else if (return_menu == 3)Menu_two();
        else if (return_menu == 6)Menu_three();
    }
    getch;
}