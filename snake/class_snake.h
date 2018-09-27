#include <vector>

using namespace std;

class Snake{
	
	private:
		
		vector < vector <int> > body;
		int score;
		
	public:
		
		Snake();
		int size();
		void update_info();
		int get_info();
		vector < vector <int> > get_body();
		void update(vector < vector <int> > new_body);
		
};

Snake::Snake(){

	int x = 36;
	int y = 13;
	
	this->score = 0;
	
	vector <int> pos;
	
	for (int i = 0; i < 4; i++){
		
		pos.push_back(x);
		pos.push_back(y);
		
		this->body.push_back(pos);
		
		pos.pop_back();
		pos.pop_back();
		
		x -= 1;
		
	}
}

vector < vector <int> > Snake::get_body(){

	return this->body;
	
}

void Snake::update(vector < vector <int> > new_body){
	
	this->body = new_body;
	
}

int Snake::get_info(){
	
	return this->score;
}

void Snake::update_info(){
	
	this->score += 1;
}

int Snake::size(){
	
	return body.size();
}
