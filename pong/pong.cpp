#include <stdio.h>
#include <windows.h>
#include <vector>

#define WIDTH 600
#define HIGH 400

using namespace std;

void gotoxy(int x, int y){
  
  COORD coord;
  
  coord.X = x;
  coord.Y = y;
  
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
  
}

void console_config(){
	
	//Resize console
	
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	
	MoveWindow(console, r.left + 350, r.top + 50, WIDTH, HIGH, TRUE);
	
	//Hide cursor
	
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;
	 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	 
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;
	 
	SetConsoleCursorInfo(hOut, &ConCurInf);
}

void draw_map(){
	
	//draw vertical and horizontal walls
	
	for (int i = 4; i < 67; i++){
		
		gotoxy(i, 3); printf("%c", 205);
		
	}
	
	for (int i = 4; i < 20; i++){
		
		gotoxy(3, i); printf("%c", 186);
	}
	
	for (int i = 4; i < 20; i++){
		
		gotoxy(67, i); printf("%c", 186);
	}
	
	for (int i = 4; i < 67; i++){
		
		gotoxy(i, 20); printf("%c", 205);
	}
	
	//draw corners
	
	gotoxy(3, 3); printf("%c", 201);
	gotoxy(67, 3); printf("%c", 187);
	gotoxy(67, 20); printf("%c", 188);
	gotoxy(3, 20); printf("%c", 200);
	
}

int main(){
	
	console_config();
	
	draw_map();
	Ball ball = Ball(35, 13);
	Player player1 = Player(3);
	
	while(1){
		
		ball.draw();
		
		if (GetAsyncKeyState(VK_UP)){
						
		}else if (GetAsyncKeyState(VK_DOWN)){
			
					
		}
		
		Sleep(50);
	}
	
	system("pause>null");
	
	return 0;
}


