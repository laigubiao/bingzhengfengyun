#include "chess.h"
#include "user.h"
#include "chessboard.h"
static string recordpassword;
static string recordid;
ofstream ofs("user.txt");
ifstream ifs("user.txt");
int main()
{
	user comup;
	comup.loginaccount(recordpassword,recordid,ifs,ofs);
	comup.interface();
}