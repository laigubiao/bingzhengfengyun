#include "chessboard.h"
#include "chess.h"
#include <vector>
#include <iostream>
#include <fstream>
chessboard::chessboard(vector<vector<chess*>>& initialposi, vector<vector<chess*>>& inwinposi) :board(initialposi), winposi(inwinposi) {};
void chessboard::loadwithfile(ifstream& ifs)
{
	string in;
	for (int i = 0; i < 5; i++)
	{
		for (int t = 0; t < 5; t++)
		{
			ifs >> in;
			if (in == "*")board[i][t] = nullptr;
			if (in == "I")
			{
				board[i][t] = new infantry;
				board[i][t]->setx(t);
				board[i][t]->sety(i);
			}
			if (in == "B")
			{
				board[i][t] = new bowman;
				board[i][t]->setx(t);
				board[i][t]->sety(i);
			}
			if (in == "C")
			{
				board[i][t] = new cavalrty;
				board[i][t]->setx(t);
				board[i][t]->sety(i);
			}
		}
	}
}
void chessboard::wincondition()
{
	for (int i = 0; i < 5; i++)
	{
		for (int t = 0; t < 5; t++)
		{
			if (winposi[i][t] == nullptr)cout << "*";
			if (dynamic_cast<infantry*>(winposi[i][t]))cout << "I";
			if (dynamic_cast<bowman*>(winposi[i][t]))cout << "B";
			if (dynamic_cast<cavalrty*>(winposi[i][t]))cout << "C";
		}
	}
}
void chessboard::printboard()
{
	for (int i = 0; i < 5; i++)
	{
		for (int t = 0; t < 5; t++)
		{
			if (board[i][t] == nullptr)cout << "*";
			if (dynamic_cast<infantry*>(board[i][t]))cout << "I";
			if (dynamic_cast<bowman*>(board[i][t]))cout << "B";
			if (dynamic_cast<cavalrty*>(board[i][t]))cout << "C";
		}
	}
}
bool chessboard::checksuccess()
{
	for (int i = 0; i < 5; i++)
	{
		for (int t = 1; t < 5; t++)
		{
			if (board[i][t] == nullptr && winposi[i][t] == nullptr)continue;
			else if(dynamic_cast<infantry*>(board[i][t]) && dynamic_cast<infantry*>(winposi[i][t]))continue;
			else if (dynamic_cast<bowman*>(board[i][t]) && dynamic_cast<bowman*>(winposi[i][t]))continue;
			else if (dynamic_cast<cavalrty*>(board[i][t]) && dynamic_cast<cavalrty*>(winposi[i][t]))continue;
			else return 1;
		}
	}
	return 0;
}
void chessboard::useroperate()
{
	while (checksuccess())
	{

	}
}


