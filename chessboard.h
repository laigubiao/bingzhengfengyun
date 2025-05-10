#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "chess.h"
#include <vector>
#include <fstream>
using namespace std;
struct State 
{
	std::vector<std::vector<chess*>> board0;
	int moveCount;
	pair<int, int> Positions;
	State() {};
	State(std::vector<std::vector<chess*>> board, int moveCount, pair<int, int> Positions)
		: board0(board), moveCount(moveCount), Positions(Positions) {}
	bool operator==(const State& other) const 
	{
		if (board0.size() != other.board0.size()) return false;
		for (size_t i = 0; i < board0.size(); ++i) 
		{
			if (board0[i].size() != other.board0[i].size()) return false;
			for (size_t j = 0; j < board0[i].size(); ++j)
			{
				if (board0[i][j] != other.board0[i][j]) return false;
			}
		}
		return true;
	}
};
class chessboard
{
private:
	int width;
	int height;
	int incoordinate[2][2];
	int bocoordinate[2];
	int cacoordinate[2][2];
	int winincoordinate[2][2];
	int winbocoordinate[2];
	int wincacoordinate[2][2];
	vector<vector<chess*>>winposi;
	vector<vector<chess*>>initialposit;
	vector<vector<chess*>>board;
	State instate1;
	State instate2;
	State castate1;
	State castate2;
	int movecounter;
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
			winbocoordinate[i] = 0;
			for (int j = 0; j < 2; j++)
			{
				incoordinate[i][j] = 0;
				cacoordinate[i][j] = 0;
				winincoordinate[i][j] = 0;
				wincacoordinate[i][j] = 0;
			}
		}
		instate1 = State(board, 0, {winincoordinate[0][1],winincoordinate[0][0]});
		instate2 = State(board, 0, {winincoordinate[1][1],winincoordinate[1][0]});
		castate1 = State(board, 0, {wincacoordinate[0][1],wincacoordinate[0][0]});
		castate2 = State(board, 0, {wincacoordinate[1][1],wincacoordinate[1][0]});
		movecounter = 0;
	};
	chessboard(vector<vector<chess*>>&initialposi, vector<vector<chess*>>&inwinposi);
	void loadwithfile(ifstream& ifs);
	void wincondition();
	void getwincoor();
	void printboard();
	bool checksuccess();
	void reset();
	void getcoor();
	void useroperate();
	~chessboard() {};
};
#endif
