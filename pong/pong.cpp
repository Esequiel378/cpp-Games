#include <stdio.h>
#include <windows.h>

#define WIDTH 600
#define HIGH 400

using namespace std;

void gotoxy(int x, int y){
  
  COORD coord;
  
  coord.X = x;
  coord.Y = y;
  
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
  
}

class Player{
	
	private:
		
		int posX;
		int posY;
		int size;
		int score;
		
	public:
		
		Player(int dx, int dy, int size);
		void draw(int move);
		int get_pos();
		void set_score(int sc);
		int get_score();
		
};

Player::Player(int dx, int dy, int size){
	
	this->posX = dx;
	this->posY = dy;
	this->size = size;
	this->score = 0;
	
}

int Player::get_pos(){
	
	return this->posY;
}

void Player::set_score(int sc){
	
	this->score += sc;
}

int Player::get_score(){
	
	return this->score;
}

void Player::draw(int move){
	
	
	if (move == 1){
		
		if (this->posY + this->size != 21){
			
			int dy = this->posY;
			this->posY += 1;
			
			for (int i = this->posY; i < this->posY + this->size - 1; i++){
				
				gotoxy(this->posX, i); printf("%c", 219);
			}
			
			gotoxy(this->posX, this->posY - this->size + 2); printf(" ");
			
		}
		
	}else if (move == 0){
		
		if (this->posY - 1 != 3){
			
			this->posY -= 1;
			
			for (int i = this->posY; i < this->posY + this->size - 1; i++){
				
				gotoxy(this->posX, i); printf("%c", 219);
			}
			
			gotoxy(this->posX, this->posY + this->size - 1); printf(" ");
		}
		
		
	}else{
		
		for (int i = this->posY; i < this->posY + this->size - 1; i++){
			
			gotoxy(this->posX, i); printf("%c", 219);
		}
	}
}

class Ball{
	
	private:
		
		float posX;
		float posY;
		float dx;
		float dy;
		
	public:
		
		Ball(int _dx, int _dy);
		int draw(Player p1, Player p2);
};


Ball::Ball(int _dx, int _dy){
	
	this->posX = 34;
	this->posY = 15;
	this->dx = _dx;
	this->dy = _dy;
}

int Ball::draw(Player p1, Player p2){
	
	int posP1 = p1.get_pos();
	int posP2 = p2.get_pos();
	
	gotoxy(this->posX, this->posY); printf("%c", 32);
	
	if (this->posX >= 66){
		
		return 1;
		
	}else if (this->posX <= 5){
	
		return 2;
	}
	
	if (this->posY >= 19 || this->posY <= 4){
		this->dy *= -1;
	}
	
	
	if ( this->posX  == 6 && (this->posY >= posP1 && this->posY <= posP1 + 2)){
		this->dx *= -1;		
		
	}else if ( this->posX  == 64 && (this->posY >= posP2 && this->posY <= posP2 + 2)){
		
		this->dx *= -1;		
	}
	
	this->posX += dx;
	this->posY += dy;
	
	gotoxy(this->posX, this->posY); printf("%c", 248);
	
	return 0;

}

void console_config(){
	
	//RESIZE CONSOLE
	
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	
	MoveWindow(console, r.left + 350, r.top + 50, WIDTH, HIGH, TRUE);
	
	//HIDE CURSOR
	
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;
	 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	 
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;
	 
	SetConsoleCursorInfo(hOut, &ConCurInf);
}

void draw_map(){
	
	//DRAW VERTICAL AND HORIZONTAL WALLS
	
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
	
	//DRAW CORNERS
	
	gotoxy(3, 3); printf("%c", 201);
	gotoxy(67, 3); printf("%c", 187);
	gotoxy(67, 20); printf("%c", 188);
	gotoxy(3, 20); printf("%c", 200);
	
}

void draw_score(Player p1, Player p2){
	
	int score1 = p1.get_score();
	int score2 = p2.get_score();
	
	gotoxy(4, 2); printf("Score: %i", score1);
	gotoxy(58, 2); printf("Score: %i", score2);
}

int main(){
	
	//CONFIGURE CONSOLE
	console_config();
	
	//DRAW MAP
	draw_map();
	
	//CREATE BALL
	Ball ball = Ball(2, 1);
	
	//CREATE PLAYERS
	
	Player p1 = Player(5, 12, 3);
	Player p2 = Player(65, 12, 3);
	
	//PRE-LOAD PLAYERS
	p1.draw(-1);
	p2.draw(-1);
	
	int loop = 0;
	
	while(1){
		
		//DRAW BALL	
		
		if (loop >= 1){
			int point = ball.draw(p1, p2);
			loop = 0;
			
			if (point == 1){
				
				p1.set_score(1);
				ball = Ball(2, -1);
				
			}else if (point == 2){
				
				p2.set_score(1);
				ball = Ball(-2, -1);
				
			}
		}
		
		draw_score(p1, p2);
		
		//PLAYER 1 MOVE
		if (GetAsyncKeyState(0x57)) p1.draw(0); else if (GetAsyncKeyState(0x53)) p1.draw(1);
		
		//PLAYER 2 MOVE
		if (GetAsyncKeyState(VK_UP)) p2.draw(0); else if (GetAsyncKeyState(VK_DOWN)) p2.draw(1);
		
		loop++;		
		Sleep(50);
	}
	
	system("pause>null");
	
	return 0;
}


