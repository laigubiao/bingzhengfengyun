#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "chess.h"
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;
class chessboard
{
private:
	int width;
	int height;
	int incoordinate[5][2];
	int bocoordinate[3][2];
	int cacoordinate[5][2];
	int winincoordinate[5][2];
	int winbocoordinate[3][2];
	int wincacoordinate[5][2];
	vector<vector<chess*>>winposi;
	vector<vector<chess*>>initialposit;
	vector<vector<chess*>>board;
	int movecounter;
	chrono::steady_clock::time_point startTime;
	chrono::steady_clock::time_point endTime;
	int innum;
	int bownum;
	int cavnum;
public:
	chessboard() 
	{
		width = 5;
		height = 5;
		for (int i = 0; i < 8; i++)
		{
			winposi.push_back({ nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr });
		}
		for (int i = 0; i < 8; i++)
		{
			board.push_back({ nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr });
		}
		for (int i = 0; i < 8; i++)
		{
			initialposit.push_back({ nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr });
		}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				incoordinate[i][j] = 0;
				cacoordinate[i][j] = 0;
				winincoordinate[i][j] = 0;
				wincacoordinate[i][j] = 0;
			}
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				bocoordinate[i][j] = 0;
				winbocoordinate[i][j] = 0;
			}
		}
		movecounter = 0;
		innum = 2;
		bownum = 1;
		cavnum = 2;
	};
	chessboard(const vector<vector<chess*>>&initialposi,const vector<vector<chess*>>&inwinposi);
	chessboard(const int &h,const int &w,const vector<vector<chess*>>& initialposi,const vector<vector<chess*>>& inwinposi, const int& in, const int& bn, const int& cn);
	void loadwithfile(const string& file, const string& wfile);
	void wincondition();
	void getwincoor();
	void printboard();
	bool checksuccess();
	void startGame();
	void endGame();
	void reset();
	void getcoor();
	void useroperate();
	~chessboard()
	{
		for (int i = 0; i < 8; i++)
		{
			for (int t = 0; t < 8; t++)
			{
				if(winposi[i][t]!=nullptr)delete winposi[i][t];
			}
		}
		for (int i = 0; i < 8; i++)
		{
			for (int t = 0; t < 8; t++)
			{
				if (board[i][t] != nullptr)delete board[i][t];
			}
		}
		for (int i = 0; i < 8; i++)
		{
			for (int t = 0; t < 8; t++)
			{
				if (initialposit[i][t] != nullptr)delete initialposit[i][t];
			}
		}
	}
};
#endif
