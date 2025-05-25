#include "chessboard.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <functional>
#include <cstdlib>
#include <random>
#include <chrono>
#include <thread>
int m = 0;
chessboard::chessboard(const vector<vector<chess*>>& initialposi,const vector<vector<chess*>>& inwinposi) :board(initialposi), winposi(inwinposi), initialposit(initialposi)
{
	height = 5;
	width = 5;
	innum = 2;
	bownum = 1;
	cavnum = 2; 
	getcoor();
	getwincoor();
	movecounter = 0;
}
chessboard::chessboard(const int &h,const int &w,const vector<vector<chess*>>& initialposi,const vector<vector<chess*>>& inwinposi, const int& in, const int& bn, const int& cn) :height(h),width(w),board(initialposi), winposi(inwinposi), initialposit(initialposi),innum(in),bownum(bn),cavnum(cn)
{
	getcoor();
	getwincoor();
	movecounter = 0;
}
void chessboard::loadwithfile(const string &file,const string &wfile)
{
	ifstream ifs;
	ifstream wifs;
	ifs.open(file);
	wifs.open(wfile);
	int h = 0, w = 0;
	ifs >> h >> w;
	height = h;
	width = w;
	int inf = 0, bow = 0, cav = 0;
	ifs >> inf >> bow >> cav;
	innum = inf;
	bownum = bow;
	cavnum = cav;
	string in;
	int nx = 0, ny = 0;
	int d = 0;
	int j = 0,p=0,q=0;
	for (int i = 0; i < inf+bow+cav; i++)
	{
			ifs >>in>> nx >>ny>> d;
			if (in == "I")
			{
				board[ny][nx] = new infantry(nx,ny,d);
				incoordinate[j][0] = nx;
				incoordinate[j][1] = ny;
				j++;
			}
			if (in == "B")
			{
				board[ny][nx] = new bowman(nx,ny,d);
				bocoordinate[p][0] = nx;
				bocoordinate[p][1] = ny;
				p++;
			}
			if (in == "C")
			{
				board[ny][nx] = new cavalrty(nx,ny,d);
				cacoordinate[q][0] = nx;
				cacoordinate[q][1] = ny;
				q++;
			}
	}
	int wj = 0, wp = 0, wq = 0;
	for (int i = 0; i < inf+bow+cav; i++)
	{
		ifs >> in >> nx >> ny >> d;
		if (in == "I")
		{
			winposi[ny][nx] = new infantry(nx, ny, d);
			winincoordinate[wj][0] = nx;
			winincoordinate[wj][1] = ny;
			wj++;
		}
		if (in == "B")
		{
			winposi[ny][nx] = new bowman(nx, ny, d);
			winbocoordinate[wp][0] = nx;
			winbocoordinate[wp][1] = ny;
			wp++;
		}
		if (in == "C")
		{
			winposi[ny][nx] = new cavalrty(nx, ny, d);
			wincacoordinate[wq][0] = nx;
			wincacoordinate[wq][1] = ny;
			wq++;
		}
	}
	initialposit = board;
	ifs.close();
	wifs.close();
}
void chessboard::wincondition()
{
	cout << "----------------------------------------------" << endl;
	for (int i = 0; i < height; i++)
	{
		for (int t = 0; t < width; t++)
		{
			if (winposi[i][t] == nullptr)cout << "*"<<" ";
			if (dynamic_cast<infantry*>(winposi[i][t]))cout << "I"<<" ";
			if (dynamic_cast<bowman*>(winposi[i][t]))cout << "B"<<" ";
			if (dynamic_cast<cavalrty*>(winposi[i][t]))cout << "C"<<" ";
		}
		cout << endl;
	}
}
void chessboard::getwincoor()
{
	int j = 0, p = 0, q = 0;
	for (int i = 0; i < height; i++)
	{
		for (int t = 0; t < width; t++)
		{
			if (winposi[i][t] == nullptr){}
			else if (dynamic_cast<infantry*>(winposi[i][t]))
			{
				winincoordinate[j][0] = t;
				winincoordinate[j][1] = i;
				j++;
			}
			else if (dynamic_cast<bowman*>(winposi[i][t]))
			{
				winbocoordinate[p][0] = t;
				winbocoordinate[p][1] = i;
				p++;
			}
			else if (dynamic_cast<cavalrty*>(winposi[i][t]))
			{
				wincacoordinate[q][0] = t;
				wincacoordinate[q][1] = i;
				q++;
			}
		}
	}
}
void chessboard::printboard()
{
	cout << "----------------------------------------------"<<endl;
	for (int i = 0; i < height; i++)
	{
		for (int t = 0; t < width; t++)
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
	for (int i = 0; i < height; i++)
	{
		for (int t = 1; t < width; t++)
		{
			if (board[i][t] == nullptr && winposi[i][t] == nullptr)continue;
			else if (board[i][t] != nullptr && winposi[i][t] != nullptr)
			{
					if (dynamic_cast<infantry*>(board[i][t]) && dynamic_cast<infantry*>(winposi[i][t]))continue;
					else if (dynamic_cast<bowman*>(board[i][t]) && dynamic_cast<bowman*>(winposi[i][t]))continue;
					else if (dynamic_cast<cavalrty*>(board[i][t]) && dynamic_cast<cavalrty*>(winposi[i][t]))continue;
					else return 1;
			}
			else return 1;
		}
	}
	return 0;
}
void chessboard::startGame() 
{
	startTime = chrono::steady_clock::now();
}
void chessboard::endGame() 
{
	endTime = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();
	cout << "游戏结束！总用时: " << duration << " 秒" << endl;
}
void chessboard::reset()
{
	board = initialposit;
	getcoor();
	startGame();
}
void chessboard::getcoor()
{
	int j = 0, p = 0, q = 0;
	for (int i = 0; i < height; i++)
	{
		for (int t = 0; t < width; t++)
		{
			if (dynamic_cast<infantry*>(board[i][t]))
			{
				incoordinate[j][0] = t;
				incoordinate[j][1] = i;
				j++;
			}
			else if (dynamic_cast<bowman*>(board[i][t]))
			{
				bocoordinate[p][0] = t;
				bocoordinate[p][1] = i;
				p++;
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
	startGame();
	while (checksuccess())
	{
		getcoor();
		cout << 1;
		for (int t = 0; t < innum; t++)
		{
			board[incoordinate[t][1]][incoordinate[t][0]]->setx(incoordinate[t][0]);
			board[incoordinate[t][1]][incoordinate[t][0]]->sety(incoordinate[t][1]);
		}
		for (int t = 0; t < bownum; t++)
		{
			board[bocoordinate[t][1]][bocoordinate[t][0]]->setx(bocoordinate[t][0]);
			board[bocoordinate[t][1]][bocoordinate[t][0]]->sety(bocoordinate[t][1]);
		}
		for (int t = 0; t < cavnum; t++)
		{
			board[cacoordinate[t][1]][cacoordinate[t][0]]->setx(cacoordinate[t][0]);
			board[cacoordinate[t][1]][cacoordinate[t][0]]->sety(cacoordinate[t][1]);
		}
		cout << 2;
		int num;
		int whichob=0;
		printboard();
		cout << "----------------------------------------------" << endl;
		if (i == 1)
		{
			cout << "此时"<<innum<<"个步兵的坐标分别为:";
			cout << endl;
			for (int t = 0; t < innum; t++)
			{
				cout << "(" << incoordinate[t][0] << ", " << incoordinate[t][1] << ")";
			}
			cout << endl;
			cout << "此时"<<innum<<"个步兵的前进方向分别为:";
			cout << endl;
			for (int t = 0; t < innum; t++)
			{
				cout << board[incoordinate[t][1]][incoordinate[t][0]]->returndir();
				if (t != innum - 1)cout << ",";
			}
			cout << endl;
			cout << "请输入你要操作的步兵对象:(";
			for (int t = 0; t < innum; t++)
			{
				cout << t<<"为第"<<t<<"个步兵";
				if (t != innum - 1)cout << ",";
			}
			cout << "6为跳过本回合操作，0为重置游戏)" << endl;
			cin >> whichob;
			if (whichob==2)
			{
				cout << "请输入该步兵前进的步数:";
				cin >> num;
				board[incoordinate[1][1]][incoordinate[1][0]]->walk(height,width,num, board);
			}
			else if (whichob == 3)
			{
				cout << "请输入该步兵前进的步数:";
				cin >> num;
				board[incoordinate[2][1]][incoordinate[2][0]]->walk(height, width, num, board);
			}
			else if (whichob == 4)
			{
				cout << "请输入该步兵前进的步数:";
				cin >> num;
				board[incoordinate[3][1]][incoordinate[3][0]]->walk(height, width, num, board);
			}
			else if (whichob == 5)
			{
				cout << "请输入该步兵前进的步数:";
				cin >> num;
				board[incoordinate[4][1]][incoordinate[4][0]]->walk(height, width, num, board);
			}
			else if(whichob==1)
			{
				cout << "请输入该步兵前进的步数:";
				cin >> num;
				board[incoordinate[0][1]][incoordinate[0][0]]->walk(height, width, num, board);
			}
			else if (whichob == 0)
			{
				reset();
				i = 1;
				continue;
			}
			i=2;
			movecounter++;
			continue;
		}
		if (i == 2)
		{
			int d = 0;
			int option = 1;
			cout << "此时" << bownum << "个弓箭手的坐标分别为:";
			cout << endl;
			for (int t = 0; t < bownum; t++)
			{
				cout<< "(" << bocoordinate[t][0] << ", " << bocoordinate[t][1] << ")";
			}
			cout << "此时"<<bownum<<"个弓箭手的面向方向分别为:";
			cout << endl;
			for (int t = 0; t < bownum; t++)
			{
				cout << board[bocoordinate[t][1]][bocoordinate[t][0]]->returndir();
				if (t != bownum - 1)cout << ",";
			}
			cout << endl;
			cout << "请输入你要操作的弓箭手对象:(";
			for (int t = 0; t < bownum; t++)
			{
				cout << t << "为第" << t << "个弓箭手";
				if (t != bownum - 1)cout << ",";
			}
			cout << "6为跳过本回合操作，0为重置游戏)" << endl;
			cin >> whichob;
			if (whichob == 0)
			{
				reset();
				i = 1;
				continue;
			}
			cout << "请输入你想弓箭手所射击的方向（1为往下,2为往左,3为往上,4为往右,6为跳过本回合操作，0为重置游戏):";
			cin >> d;
			switch (d)
			{
			case 1:
				option = 1;
				break;
			case 2:
				option = 2;
				break;
			case 3:
				option = 3;
				break;
			case 4:
				option = 4;
				break;
			case 6:
				break;
			default:
				cout << "错误的输入！请重新输入";
				i = 1;
				break;
			}
			if (whichob == 1)
			{
				if (d == 1 || d == 2 || d == 3 || d == 4)
				{
					board[bocoordinate[0][1]][bocoordinate[0][0]]->shoot(height, width, option, board);
				}
				else if (d == 6)
				{
					i = 3;
					continue;
				}
				else if (d == 0)
				{
					reset();
					i = 1;
					continue;
				}
			}
			else if (whichob == 2)
			{
				if (d == 1 || d == 2 || d == 3 || d == 4)
				{
					board[bocoordinate[1][1]][bocoordinate[1][0]]->shoot(height, width, option, board);
				}
				else if (d == 6)
				{
					i = 3;
					continue;
				}
				else if (d == 0)
				{
					reset();
					i = 1;
					continue;
				}
			}
			else if (whichob == 3)
			{
				if (d == 1 || d == 2 || d == 3 || d == 4)
				{
					board[bocoordinate[2][1]][bocoordinate[2][0]]->shoot(height, width, option, board);
				}
				else if (d == 6)
				{
					i = 3;
					continue;
				}
				else if (d == 0)
				{
					reset();
					i = 1;
					continue;
				}
			}
			i=3;
			movecounter++;
			continue;
		}
		if (i == 3)
		{
			bool deci = 0;
			cout << "此时" << cavnum << "个骑兵的坐标分别为:";
			cout << endl;
			for (int t = 0; t < innum; t++)
			{
				cout << "(" << cacoordinate[t][0] << ", " << cacoordinate[t][1] << ")";
			}
			cout << endl;
			cout << "此时" << cavnum << "个骑兵的前进方向分别为:";
			cout << endl;
			for (int t = 0; t < cavnum; t++)
			{
				cout << board[cacoordinate[t][1]][cacoordinate[t][0]]->returndir();
				if (t != cavnum - 1)cout << ",";
			}
			cout << endl;
			cout << "请输入你要操作的骑兵对象:(";
			for (int t = 0; t < cavnum; t++)
			{
				cout << t << "为第" << t << "个骑兵";
				if (t != cavnum - 1)cout << ",";
			}
			cout << "6为跳过本回合操作，0为重置游戏)" << endl;
			cin >> whichob;
			if (whichob == 2)
			{
				cout << "是否需要该骑兵转向?(0为不转向，1为转向):";
				cin >> deci;
				board[cacoordinate[1][1]][cacoordinate[1][0]]->dirdecide(deci);
				cout << "请输入该骑兵前进的步数:";
				cin >> num;
				board[cacoordinate[1][1]][cacoordinate[1][0]]->walk(height, width, num, board);
			}
			else if (whichob == 3)
			{
				cout << "是否需要该骑兵转向?(0为不转向，1为转向):";
				cin >> deci;
				board[cacoordinate[2][1]][cacoordinate[2][0]]->dirdecide(deci);
				cout << "请输入该骑兵前进的步数:";
				cin >> num;
				board[cacoordinate[2][1]][cacoordinate[2][0]]->walk(height, width, num, board);
			}
			else if (whichob == 4)
			{
				cout << "是否需要该骑兵转向?(0为不转向，1为转向):";
				cin >> deci;
				board[cacoordinate[3][1]][cacoordinate[3][0]]->dirdecide(deci);
				cout << "请输入该骑兵前进的步数:";
				cin >> num;
				board[cacoordinate[3][1]][cacoordinate[3][0]]->walk(height, width, num, board);
			}
			else if (whichob == 5)
			{
				cout << "是否需要该骑兵转向?(0为不转向，1为转向):";
				cin >> deci;
				board[cacoordinate[4][1]][cacoordinate[4][0]]->dirdecide(deci);
				cout << "请输入该骑兵前进的步数:";
				cin >> num;
				board[cacoordinate[4][1]][cacoordinate[4][0]]->walk(height, width, num, board);
			}
			else if (whichob == 1)
			{
				cout << "是否需要该骑兵转向?(0为不转向，1为转向):";
				cin >> deci;
				board[cacoordinate[0][1]][cacoordinate[0][0]]->dirdecide(deci);
				cout << "请输入该骑兵前进的步数:";
				cin >> num;
				board[cacoordinate[0][1]][cacoordinate[0][0]]->walk(height, width, num, board);
			}
			else if (whichob == 0)
			{
				reset();
				i = 1;
				continue;
			}
			i = 1;
			movecounter++;
			continue;
		}
	}
	cout << "你赢了！" << endl;
	endGame();
	cout << "此次所用步数为:" << movecounter << endl;
}


