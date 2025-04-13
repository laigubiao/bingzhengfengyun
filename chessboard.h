#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "chess.h"
#include <vector>
using namespace std;
class chessboard
{
private:
	int width;
	int height;
	vector<vector<chess*>>winposi;
	vector<vector<chess*>>board;
public:
	chessboard() 
	{
		width = 5;
		height = 5;
		for (int i = 0; i < 5; i++)
		{
			winposi.push_back({ nullptr,nullptr,nullptr,nullptr,nullptr });
		}
		for (int i = 0; i < 5; i++)
		{
			board.push_back({ nullptr,nullptr,nullptr,nullptr,nullptr });
		}
	};
	chessboard(vector<vector<chess*>>&initialposi, vector<vector<chess*>>&inwinposi);
	void loadwithfile(ifstream& ifs);
	void wincondition();
	void printboard();
	void useroperate();
	bool checksuccess();
};
#endif
