#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <vector>
#include "class_snake.h"
#include "class_food.h"

#define HIGH 400
#define WIDTH 600
#define BODY 207

using namespace std;

void gotoxy(int x, int y){
  
  COORD coord;
  
  coord.X = x;
  coord.Y = y;
  
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
  
}

void draw_map(){
	
	srand(time(NULL));
	
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

void draw_info(Snake snake, int speed = 10){
	
	int size = snake.size();
	int score = snake.get_info();
	
	//draw info
	
	gotoxy(4, 2); printf("Score: %i", score);
	gotoxy(59, 2); printf("Size: %i", size);
	gotoxy(4, 21); printf("Speed: 1/%i", speed);
	
	gotoxy(0,0);
	
}

vector < vector <int> > draw_snake(Snake snake, int dir, bool fed=false){
	
	vector <int> pos;
	vector < vector <int> > body = snake.get_body();
	int last[2];
	
	for (int i = 0; i < body.size(); i++){
		
		int x = body[i][0];
		int y = body[i][1];
		
		last[0] = x;
		last[1] = y;
		
		gotoxy(x, y); printf("%c", BODY);
		
	}
	
	gotoxy(last[0], last[1]); printf("%c", 00);
	
	gotoxy(0,0);
	
	if (fed == false){
		
		body.pop_back();
	}	
	
	int x = body[0][0];
	int y = body[0][1];
	
	if (dir == 0){
		
		pos.push_back(x);
		pos.push_back(y - 1);

	}else if (dir == 1){
		
		pos.push_back(x - 1);
		pos.push_back(y);
	
	}else if (dir == 2){
		
		pos.push_back(x);
		pos.push_back(y + 1);
		
	}else if (dir == 3){
		
		pos.push_back(x + 1);
		pos.push_back(y);
	}
	
	body.insert(body.begin(), pos);
	
	pos.pop_back();
	pos.pop_back();
	
	return body;

}

int colition(Snake snake, Food food){
	
	vector < vector <int> > body = snake.get_body();
	vector <int> pos = food.get_pos();
	
	int foodX = pos[0];
	int foodY = pos[1];
	
	int headX = body[0][0];
	int headY = body[0][1];
	
	for (int i = body.size() - 1; i > 0 ; i--)	{
		
		int snakeX = body[i][0];
		int snakeY = body[i][1];
		
		if (headX == snakeX && headY == snakeY){
			
			return 1;
		}
	}
	
	if (headX == 67 || headX == 3 || headY == 3 || headY == 20){
		
		return 1;
		
	}else if (headX == foodX && headY == foodY){
		
		return 2;
	}
	
	return 0;
}

void new_egg(Food food, Snake snake){
	
	vector <int> pos = food.get_pos();
	vector < vector <int> > body = snake.get_body();
	
	int x = pos[0];
	int y = pos[1];
	
	for (int i = 0; i < body.size() - 1; i++){
		
		int snakeX = body[i][0];
		int snakeY = body[i][1];
		
		if (x == snakeX && y == snakeY){
			
			food.new_pos();
			new_egg(food, snake);	
			
		}
	}
		
	gotoxy(x, y); printf("%c", 155);
	
}

void dead_message(){
		
	gotoxy(30, 10); printf("Game Over!");
	gotoxy(0,0);
	
}

int main (){
	
    HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	
	MoveWindow(console, r.left + 350, r.top + 50, WIDTH, HIGH, TRUE);
	
	while(!GetAsyncKeyState(VK_ESCAPE)){
		
		draw_map();
			
		Snake snake = Snake();
		
		int dir = 3; // 0-up 1-left 2-down 3-right
		int draw_speed = 0;
		int max_draw_speed = 18;
		
		bool exist_food = true;
		
		draw_info(snake);
		
		Food food = Food();
		new_egg(food, snake);
		
		while(1){
			
			if (draw_speed == max_draw_speed){
			
				int colitions = colition(snake, food);
				
				if (exist_food == false){
					
					food.new_pos();
					new_egg(food, snake);
					exist_food = true;
				}
				
				if (colitions == 0){
					
					vector < vector <int> > body = draw_snake(snake, dir);
					snake.update(body);

					draw_info(snake, max_draw_speed);
					
				}else if (colitions == 2){
					
					vector < vector <int> > body = draw_snake(snake, dir, true);
					snake.update(body);
					snake.update_info();

					exist_food = false;
					draw_info(snake, max_draw_speed);
									
				}else if (colitions == 1){
					
					dead_message();
					system("pause>null");
					break;
				}
			}
			
			if (draw_speed > max_draw_speed){
				
				draw_speed = 0;
			}
				
			if (GetAsyncKeyState(VK_UP)){
				
				if (dir != 2){dir = 0; max_draw_speed = 15;}
			}	
				
			else if (GetAsyncKeyState(VK_LEFT)){
				
				if (dir != 3){dir = 1; max_draw_speed = 10;}
			}
			
			else if (GetAsyncKeyState(VK_DOWN)){
				
				if (dir != 0){dir = 2; max_draw_speed = 15;}
			}
			
			else if (GetAsyncKeyState(VK_RIGHT)){
				
				if (dir != 1){dir = 3; max_draw_speed = 10;}
				
			}else if (GetAsyncKeyState(VK_ESCAPE)){
				
				break;
			}
				
			draw_speed++;
			Sleep(5);
			
		}	
		
		system("cls");
		
	}

    return 0;
}
