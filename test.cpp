#include<iostream>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <time.h>

using namespace std;

#define SCREEN_WIDTH 100  // **
#define SCREEN_HEIGHT 50  // **
#define WIN_HEIGHT 40     // **


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void drawBorder(){ 
	
	for(int i=0; i<SCREEN_WIDTH; i++){
		gotoxy(i,0); cout<<"±";
		gotoxy(i,SCREEN_HEIGHT); cout<<"±";
	}
	
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(0,i); cout<<"±";
		gotoxy(SCREEN_WIDTH,i); cout<<"±";
	}
	for(int i=0; i<SCREEN_WIDTH-2; i++){
		gotoxy(i+1,WIN_HEIGHT); cout<<"±";
	}
}

void setcursor(bool visible, DWORD size) 
{
	if(size == 0)
		size = 10;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

char control()   //เช็คการกดปุ่ม ตอนเล่น
{
	if(kbhit()){
		char ch = getch();
		if(ch=='w') {return 'w' ;}
		if(ch=='a') {return 'a' ;}
		if(ch=='s') {return 's' ;}
		if(ch=='d') {return 'd' ;}
		if(ch==' ') {return ' ' ;}
		if(ch== 27) {return 'x' ;}	//ESC
	}return '-' ;  // non
}

char dookdik[4][5] = {   ' ','_','_','_',' ',
						 '(','o','>','o',')',
						 '/','_','_','_','\\',
						 ' ','l',' ','l',' '  };

//     ___ 
//    (o>o)
// 	  \___/    
//	   l l 
//    
//    dookdik

//     ___ 
//    (o>o)
// 	  /___\   	โดด
//	   l l 
//    
//    dookdik


	int STX = 50 ,  STY = 32 ;	//ตำแหน่ง X Y เริ่ม  ( บนน้อย , ล่างมาก )  **

	int DDposx = STX ; int DDposy = STY ;
	int dx = 0 ;         //ตำแหน่ง X ในอนาคต
	int vx = 2 ;     		//ความเร็ว X  **
	
    
    double dy = DDposy ; 	 //ตำแหน่ง Y ในอนาคต  
	double uy = 3 ;  //ความเร็วต้น Y **
	double vy = -uy ; //ความเร็ว Y
	double ay = 0.5 ; //แรงโน้มถ่วง

	int point = 0;


void drawDD(){
	for(int i=0; i<4; i++){
		for(int j=0; j<5; j++){
			gotoxy(DDposx+j-3,DDposy+i-3); cout<<dookdik[i][j];
		}
	}
	gotoxy(SCREEN_WIDTH,SCREEN_HEIGHT); // กันcursor กระพริบ
}

void eraseDD(){
	for(int i=0; i<4; i++){
		for(int j=0; j<5; j++){
			gotoxy(DDposx+j-3,DDposy+i-3); cout<<' ';
		}
	}
	gotoxy(SCREEN_WIDTH,SCREEN_HEIGHT); // กันcursor กระพริบ
}

class ABCD
{  
	public :
	char CH ;
	int posx;
	double posy;
	bool appear = 1 ;
	void gen(char);
	bool check();
};

void ABCD::gen(char i)
{
	if(i<='Z')
	{
	CH = i ;
	posy = 2 + rand()%6 ;
	posx = rand()%61+20;
	appear = 1;
	}
}

void move(ABCD &f)
{
	if(f.appear)
	{
		f.posy += 0.1 + 0.005*point ;
		gotoxy(f.posx,f.posy-1); cout<< " ";
		gotoxy(f.posx,f.posy); cout<<f.CH;
	}
}

bool gameover = 0 ;

bool ABCD::check()
{
	bool x = ( DDposx >= posx-3) && ( DDposx <= posx+3);
	bool y = ( posy >= DDposy-3 &&  posy <= DDposy);
	bool out = (posy >= 35);
	if(out) gameover=1;
	if(x&&y||out)
	{
		appear = 0;
		gotoxy(posx,posy);
		cout<<" ";
		posx=0;
		posy=0;
		return 1;
	}
	return 0;
}

void ClrPsc(){
	gotoxy(22,43); cout << "                                                            ";
	gotoxy(22,44); cout << "                                                            ";
	gotoxy(22,45); cout << "                                                            ";
	gotoxy(22,46); cout << "                                                            ";
	gotoxy(22,47); cout << "                                                            ";
}

void GainPsc(){
	int G = rand()%3;
	if(G == 0){
		ClrPsc();
		gotoxy(31,43); cout << "  *****  *****   ******     *     ******* "<<endl;
		gotoxy(31,44); cout << " *       *    *  *         * *       *    "<<endl;
		gotoxy(31,45); cout << "*  ***** *****   ******   *   *      *    "<<endl;
		gotoxy(31,46); cout << " *     * *    *  *       *******     *    "<<endl;
		gotoxy(31,47); cout << "  *****  *     * ****** *       *    *    "<<endl;
	}
	if(G == 1){
		ClrPsc();
		gotoxy(37,43); cout << "*     * *******   ***** ****** "<<endl;
		gotoxy(37,44); cout << "* *   *    *     *      *      "<<endl;
		gotoxy(37,45); cout << "*  *  *    *    *       ****** "<<endl;
		gotoxy(37,46); cout << "*   * *    *     *      *      "<<endl;
		gotoxy(37,47); cout << "*     * *******   ***** ****** "<<endl;
	}
	if(G == 2){
		ClrPsc();
		gotoxy(36,43); cout << "  *****   *****   *****  *****   "<<endl;
		gotoxy(36,44); cout << " *       *     * *     * *    *  "<<endl;
		gotoxy(36,45); cout << "*  ***** *     * *     * *     * "<<endl;
		gotoxy(36,46); cout << " *     * *     * *     * *    *  "<<endl;
		gotoxy(36,47); cout << "  *****   *****   *****  *****   "<<endl;
	}
}

void EndScreen()
{		
	system("cls"); drawBorder();
	if(gameover) //loss
	{
		gotoxy(10,6);  cout << " ------------------------------------------------------------------------- "<<endl;
		gotoxy(10,8);  cout << "|    *****      *     *       * ******       ****  *       ****** ****    |"<<endl;
		gotoxy(10,9);  cout << "|   *          * *    * *   * * *           *    *  *     * *     *   *   |"<<endl;
		gotoxy(10,10); cout << "|   *  ****   *   *   *  * *  * *****       *    *   *   *  ****  ****    |"<<endl;
		gotoxy(10,11); cout << "|   *  *  *  *******  *   *   * *           *    *    * *   *     * *     |"<<endl;
		gotoxy(10,12); cout << "|    *****  *       * *       * ******       ****      *    ***** *   *   |"<<endl;
		gotoxy(10,13); cout << " ------------------------------------------------------------------------- "<<endl;
	}else{  //win
		gotoxy(10,7);  cout << " ------------------------------------------------------------------------- "<<endl;
		gotoxy(10,8);  cout << "|    *****      *     *       * ******      *       * ******* *       *   |"<<endl;
		gotoxy(10,9);  cout << "|   *          * *    * *   * * *           *   *   *    *    * *     *   |"<<endl;
		gotoxy(10,10); cout << "|   *  ****   *   *   *  * *  * *****       *  * *  *    *    *   *   *   |"<<endl;
		gotoxy(10,11); cout << "|   *  *  *  *******  *   *   * *           * *   * *    *    *     * *   |"<<endl;
		gotoxy(10,12); cout << "|    *****  *       * *       * ******      *       * ******* *       *   |"<<endl;
		gotoxy(10,13); cout << " ------------------------------------------------------------------------- "<<endl;
		
	}
	gotoxy(10,15); cout<< "POINT = "<< point <<"  ";
	gotoxy(10,17); cout<< "Press x to return to menu  ";
	char op ;
	do{ op = getch();}while(op != 'x');
}

void instructions(){
	system("cls"); drawBorder();
	gotoxy(23,5); cout<<  "     Collecting the alphabets A-Z each gain 1 point"; 
	gotoxy(23,6); cout<<  "          Not depend on order,Max 26 points "; 
	gotoxy(23,7); cout<<  "Every point you gain make the alphabets falling down faster";
	gotoxy(23,9); cout<<  "  If one single alphabet hit the ground the game is over";
	gotoxy(23,12);cout<<  "Press x to return to menu  ";	 
	char op;
	do{ op = getch();}while(op != 'x');
}

void showpoint(char i)
{
	gotoxy(10,36); cout<<"POINT = "<<point;
	gotoxy(10,38); cout<<"GET ==> ";
	gotoxy(18+(i-65)*2,38); cout<<i<<" ";
}

ABCD CH[8];

void play()   
{
	//double fps = 20 , ptime = time(0)-1 ;
	//int countfps = 0 ;

	char i = 'A';
	
	for(int j=0;j<8;j++) CH[j].gen(i++) ;
	bool jump = 0;

	DDposx = STX ; DDposy = STY ;
	dx = 0 ;         //ตำแหน่ง X ในอนาคต
    dy = DDposy ; 	 //ตำแหน่ง Y ในอนาคต  
	vy = -uy ; //ความเร็ว Y

	point = 0;
	showpoint(' ');

	while(!gameover)
	{
		
		char CT = control() ;
		if(CT =='x') { } //exit ( esc )
		if(CT ==' ') { jump=1;}
		if(CT =='w') { jump=1;}
		if(CT =='s') { }
		if(CT =='a') { dx = -vx ; }
		if(CT =='d') { dx =  vx ; }

		//gotoxy(70,46); cout<<" dy= "<< dy <<"  ";
		//gotoxy(70,56); cout<<" vy= "<< vy <<"  ";
		//gotoxy(70,59); cout<<" P= "<< point <<"  ";

		//รอเขียน dy ใหม่
		if(jump)
		{
		dy += vy ;
		vy += ay ;
		if( vy > 0 ) { dookdik[2][0]='\\';dookdik[2][4]='/';}
		else 		 { dookdik[2][0]='/';dookdik[2][4]='\\';}
		if( vy > uy ) {vy = -uy; jump=0;}
		}


		DDposx += dx ;
		DDposy = dy ;

		if(DDposx<7) { DDposx = SCREEN_WIDTH-2 ; }  if(DDposx>SCREEN_WIDTH-2)  { DDposx = 7 ;}  //ชนขอบ X
		if(DDposy<1) { DDposy = 1 ; }  if(DDposy>WIN_HEIGHT-1)    { DDposy = WIN_HEIGHT-1 ; }  //ชนขอบ Y

		//gotoxy(40,45); cout<<"  CT = "<<CT;             //Show data ปุ่มกด wasd-
		//gotoxy(50,45); cout<<"  X = " <<DDposx<<" ";    //Show data DDposX
		//gotoxy(60,45); cout<<"  Y = " <<DDposy<<" ";    //Show data DDposY
	    //gotoxy(10,45); cout<<"  FPS = ";                //Show data FPS

		//if(time(0)-ptime == 1 ) { ptime=time(0) ; gotoxy(18,45); fps = countfps ; cout<<(fps)<<"   " ;  countfps=0 ; }  //update data FPS every 2sec
		//else { countfps++; } 

		for(int i=0;i<8;i++) move(CH[i]);

		for(int j=0;j<8;j++)
		if(CH[j].check())
		{
			point++;
			showpoint(CH[j].CH) ;
			CH[j].gen(i);
			i++;
			GainPsc();
		}

		if( point == 26 ) break;


	//draw
		drawDD();
		Sleep(20); 	
	//erase
		eraseDD();
	

	gotoxy(SCREEN_WIDTH,SCREEN_HEIGHT); // กันcursor กระพริบ
	}
}


int main()
{
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 

    do{
		system("cls");
        drawBorder();
		gotoxy(10,5); cout<<" -------------------------- "; 
		gotoxy(10,6); cout<<" |      Go Go Jump!!!     | "; 
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9);  cout<<"1. Start Game";
		gotoxy(10,10); cout<<"2. Instructions";	 
		gotoxy(10,11); cout<<"3. Quit";
		gotoxy(10,13); cout<<"Select option: ";

		char op = getche();
		     if( op=='1') { system("cls"); drawBorder();  play();   EndScreen();   gameover = 0 ;} //**
		else if( op=='2') { instructions(); }
		else if( op=='3') exit(0);

	}while(1);


	return 0;
}
