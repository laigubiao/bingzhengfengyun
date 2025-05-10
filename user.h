#ifndef USER_H
#define USER_H
#include <string>
#include <fstream>
#include "chessboard.h"
using namespace std;
class user
{
private:
	string id;
	string password;
	int selection;
public:
	user();
	void setaccount(string &recordpassword,string &recordid,ofstream &ofs);
	void loginaccount(string &recordpassword,string& recordid,ifstream &ifs, ofstream& ofs);
	int select();
	void interface();
	void playgame();
	void game(chessboard game);
	void customizedgame();
	void autogame();
	void reset();
	void information();
	~user() {};
};
#endif
