#ifndef USER_H
#define USER_H
#include <string>
#include <fstream>
using namespace std;
class user
{
private:
	string id;
	string password;
	int movecounter;
	int selection;
public:
	user();
	void setaccount(string &recordpassword,string &recordid,ofstream &ofs);
	void loginaccount(string &recordpassword,string& recordid,ifstream &ifs, ofstream& ofs);
	int select();
	void interface();
	void playgame();
	void reset();
	void information();
};
#endif
