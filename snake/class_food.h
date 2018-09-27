#include <stdlib.h>
#include <time.h>

#define W 66
#define H 19

//x = 70
//y = 20

using namespace std;

vector <int> set_pos(){
	
	int x = rand() % (W - 4) + 4;
	int y = rand() % (H - 4) + 4;
	
	vector <int> pos;
	pos.push_back(x);
	pos.push_back(y);
	
	return pos;
}

class Food{
	
	private:
		
		int posX;
		int posY;
		
	public:
		
		Food();
		void new_pos();
		vector <int> get_pos();
};

Food::Food(){
	
	vector <int> pos = set_pos();
	
	this->posX = pos[0];
	this->posY = pos[1];
}

vector <int> Food::get_pos(){
	
	vector <int> pos;
	pos.push_back(this->posX);
	pos.push_back(this->posY);
	
	return pos;
}

void Food::new_pos(){
	
	vector <int> pos = set_pos();
	
	this->posX = pos[0];
	this->posY = pos[1];
}
