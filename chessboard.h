#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "chess.h"
#include <vector>
#include <fstream>
using namespace std;
class chessboard
{
private:
	int width;
	int height;
	int incoordinate[2][2];
	int bocoordinate[2];
	int cacoordinate[2][2];
	vector<vector<chess*>>winposi;
	vector<vector<chess*>>initialposit;
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
		for (int i = 0; i < 5; i++)
		{
			initialposit.push_back({ nullptr,nullptr,nullptr,nullptr,nullptr });
		}
		for (int i = 0; i < 2; i++)
		{
			bocoordinate[i] = 0;
			for (int j = 0; j < 2; j++)
			{
				incoordinate[i][j] = 0;
				cacoordinate[i][j] = 0;
			}
		}
	};
	chessboard(vector<vector<chess*>>&initialposi, vector<vector<chess*>>&inwinposi);
	void loadwithfile(ifstream& ifs);
	void wincondition();
	void printboard();
	bool checksuccess();
	void reset();
	void getcoor();
	void useroperate();
	~chessboard() {};
};
#endif
