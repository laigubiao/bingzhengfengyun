#include "chessboard.h"
#include <iostream>
#include <fstream>
chessboard::chessboard(vector<vector<chess*>>& initialposi, vector<vector<chess*>>& inwinposi) :board(initialposi), winposi(inwinposi), initialposit(initialposi)
{
	getcoor();
}
void chessboard::loadwithfile(ifstream& ifs)
{
	string in;
	int j = 0,p=0,q=0;
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
				incoordinate[j][0] = t;
				incoordinate[j][1] = i;
				j++;
			}
			if (in == "B")
			{
				board[i][t] = new bowman;
				board[i][t]->setx(t);
				board[i][t]->sety(i);
				bocoordinate[p] = t;
				bocoordinate[p + 1] = i;
			}
			if (in == "C")
			{
				board[i][t] = new cavalrty;
				board[i][t]->setx(t);
				board[i][t]->sety(i);
				cacoordinate[q][0] = t;
				cacoordinate[q][1] = i;
				q++;
			}
		}
	}
	initialposit = board;
}
void chessboard::wincondition()
{
	cout << "----------------------------------------------" << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int t = 0; t < 5; t++)
		{
			if (winposi[i][t] == nullptr)cout << "*"<<" ";
			if (dynamic_cast<infantry*>(winposi[i][t]))cout << "I"<<" ";
			if (dynamic_cast<bowman*>(winposi[i][t]))cout << "B"<<" ";
			if (dynamic_cast<cavalrty*>(winposi[i][t]))cout << "C"<<" ";
		}
		cout << endl;
	}
}
void chessboard::printboard()
{
	cout << "----------------------------------------------"<<endl;
	for (int i = 0; i < 5; i++)
	{
		for (int t = 0; t < 5; t++)
		{
			if (board[i][t] == nullptr)cout << "*"<<" ";
			if (dynamic_cast<infantry*>(board[i][t]))cout << "I"<<" ";
			if (dynamic_cast<bowman*>(board[i][t]))cout << "B"<<" ";
			if (dynamic_cast<cavalrty*>(board[i][t]))cout << "C"<<" ";
		}
		cout << endl;
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
void chessboard::reset()
{
	board = initialposit;
	getcoor();
}
void chessboard::getcoor()
{
	int j = 0, p = 0, q = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int t = 0; t < 5; t++)
		{
			if (dynamic_cast<infantry*>(board[i][t]))
			{
				incoordinate[j][0] = t;
				incoordinate[j][1] = i;
				j++;
			}
			else if (dynamic_cast<bowman*>(board[i][t]))
			{
				bocoordinate[p] = t;
				bocoordinate[p + 1] = i;
			}
			else if (dynamic_cast<cavalrty*>(board[i][t]))
			{
				cacoordinate[q][0] = t;
				cacoordinate[q][1] = i;
				q++;
			}
		}
	}
}
void chessboard::useroperate()
{
	cout << "目标棋盘为:" << endl;
	wincondition();
	int i = 1;
	while (checksuccess())
	{
		getcoor();
		int num;
		int whichob=0;
		printboard();
		cout << "----------------------------------------------" << endl;
		if (i == 1)
		{
			cout << "此时两个步兵的坐标分别为:(" << incoordinate[0][0] << "," << incoordinate[0][1] << "),(" << incoordinate[1][0] << "," << incoordinate[1][1] << ")";
			cout << endl;
			cout << "此时两个步兵的前进方向分别为:" << board[incoordinate[0][1]][incoordinate[0][0]]->returndir() << "," << board[incoordinate[1][1]][incoordinate[1][0]]->returndir();
			cout << endl;
			cout << "请输入你要操作的步兵对象(1为第一个坐标表示的步兵，2为第二个坐标表示的步兵, 5为跳过本回合操作，0为重置游戏):";
			cin >> whichob;
			cout << "请输入该步兵前进的步数:";
			cin >> num;
			if (whichob==2)
			{
				board[incoordinate[1][1]][incoordinate[1][0]]->walk(num, board);
			}
			else if(whichob==1)
			{
				board[incoordinate[0][1]][incoordinate[0][0]]->walk(num, board);
			}
			else if (whichob == 0)
			{
				reset();
				i = 1;
				continue;
			}
			i++;
			continue;
		}
		if (i == 2)
		{
			int t = 0;
			direction option = down;
			cout << "此时弓箭手的坐标为:(" << bocoordinate[0] << "," << bocoordinate[1] << ")";
			cout << endl;
			cout << "此时弓箭手的面向方向为:" << board[bocoordinate[1]][bocoordinate[0]]->returndir();
			cout << endl;
			cout << "请输入你想弓箭手所射击的方向（1为往下,2为往左,3为往上,4为往右,5为跳过本回合操作,0为重置游戏):";
			cin >> t;
			switch (t)
			{
			case 1:
				option = down;
				break;
			case 2:
				option = direction::left;
				break;
			case 3:
				option = up;
				break;
			case 4:
				option = direction::right;
				break;
			default:
				cout << "错误的输入！请重新输入";
				i = 1;
				break;
			}
			if (t == 1 || t == 2 || t == 3 || t == 4)
			{
				board[bocoordinate[1]][bocoordinate[0]]->shoot(option, board);
			}
			else if (t == 5)
			{
				reset();
				i = 1;
				continue;
			}
			i++;
		}
		if (i == 1)
		{
			cout << "此时两个骑兵的坐标分别为:(" << cacoordinate[0][0] << "," << cacoordinate[0][1] << "),(" << cacoordinate[1][0] << "," << cacoordinate[1][1] << ")";
			cout << endl;
			cout << "此时两个骑兵的前进方向分别为:" << board[cacoordinate[0][1]][cacoordinate[0][0]]->returndir() << "," << board[cacoordinate[1][1]][cacoordinate[1][0]]->returndir();
			cout << endl;
			cout << "请输入你要操作的骑兵对象(1为第一个坐标表示的步兵，2为第二个坐标表示的步兵, 5为跳过本回合操作，0为重置游戏):";
			cin >> whichob;
			cout << "是否需要该骑兵转向?(0为不转向,1为转向):";
			bool decision = 0;
			cin >> decision;
			cout << "请输入该骑兵前进的步数";
			cin >> num;
			if (whichob == 2)
			{
				board[incoordinate[1][1]][incoordinate[1][0]]->dirdecide(decision);
				board[incoordinate[1][1]][incoordinate[1][0]]->walk(num, board);
			}
			else if (whichob == 1)
			{
				board[incoordinate[0][1]][incoordinate[0][0]]->dirdecide(decision);
				board[incoordinate[0][1]][incoordinate[0][0]]->walk(num, board);
			}
			else if (whichob == 0)
			{
				reset();
				i = 1;
				continue;
			}
			i=1;
		}
	}
	cout << "你赢了！";
}


