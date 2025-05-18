#include "chess.h"
#include "user.h"
#include "chessboard.h"
static string recordpassword;
static string recordid;
static const string filename="user.txt";
int main()
{
	user comup;
	comup.loginaccount(recordpassword,recordid,filename);
	comup.interface();
}
