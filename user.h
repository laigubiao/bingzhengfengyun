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
	void setaccount(string &recordpassword,string &recordid,const string file);
	void loginaccount(string &recordpassword,string& recordid,const string file);
	int select();
	void interface();
	void playgame();
	void game(const chessboard game);
	void cust(const int &i);
	void playcust(const int& i);
	void customizedgame();
	void autogame();
	void reset();
	void information();
	~user() {};
};
#endif
