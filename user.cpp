#include "user.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
vector<vector<chess*>>simple1 = 
{ 
	{nullptr,new infantry,nullptr,nullptr,nullptr},
	{new infantry,nullptr,new cavalrty,nullptr,nullptr},
	{nullptr,nullptr,nullptr,nullptr,nullptr} ,
	{nullptr,nullptr,nullptr,new bowman,nullptr} ,
	{nullptr,nullptr,new cavalrty,nullptr,nullptr}
};
vector<vector<chess*>>goal1= 
{
	{nullptr,nullptr,nullptr,nullptr,nullptr},
	{new infantry,new infantry,new cavalrty,nullptr,nullptr},
	{nullptr,nullptr,nullptr,nullptr,nullptr} ,
	{nullptr,nullptr,nullptr,new bowman,nullptr} ,
	{nullptr,nullptr,new cavalrty,nullptr,nullptr} 
};
vector<vector<chess*>>simple2;
vector<vector<chess*>>goal2;
vector<vector<chess*>>ord1;
vector<vector<chess*>>ogoal1;
vector<vector<chess*>>ord2;
vector<vector<chess*>>ogoal2;
vector<vector<chess*>>hard1;
vector<vector<chess*>>hgoal1;
static const string customizedfile[5] = { "customized1.txt","customized2.txt","customized3.txt","customized4.txt" ,"customized5.txt" };
static const string wincondition[5] = { "wincondition1.txt","wincondition2.txt" ,"wincondition3.txt" ,"wincondition4.txt" ,"wincondition5.txt" };
ifstream ifs[5];
ofstream ofs[5];
ifstream wifs[5];
ofstream wofs[5];
user::user()
{
	id = "0";
	password = "0";
	selection = 0;
}
void user::setaccount(string& recordpassword, string& recordid,const string file)
{
	ofstream ofs;
	ofs.open(file);
	cout << "输入你的账户名称:";
	cin >> id;
	recordid = id;
	ofs << id<<" ";
	cout << '\n' << "输入你的账户密码:";
	cin >> password;
	recordpassword = password;
	ofs << password;
	ofs.close();
}
void user::loginaccount(string& recordpassword, string& recordid,const string file)
{
	ifstream ifs;
	ifs.open(file);
	ifs >> id >> password;
	if (id == "0" || password == "0")
	{
		setaccount(recordpassword, recordid,file);
		return;
	}
	else
	{
		recordid = id;
		recordpassword = password;
		cout << "请输入你的账户和密码:";
		cin >> id>>password;
		if (id != recordid)
		{
			cout << "账户名不存在" << endl;
			loginaccount(recordpassword, recordid, file);
		}
		else
		{
			if (password != recordpassword)
			{
				cout << "密码错误！" << endl;
				loginaccount(recordpassword, recordid, file);
			}
			else 
			{ 
				cout << "欢迎" << id << "游玩兵阵风云" << endl;
				return;
			}
		}
	}
	ifs.close();
}
int user::select()
{
	cin >> selection;
	return selection;
}
void user::interface()
{
	for (;;)
	{
		cout << "----------------------------------------------"<<endl;
		cout << "----------------1.开始游戏--------------------" << endl;
		cout << "----------------2.个人信息--------------------" << endl;
		cout << "----------------0.结束游戏--------------------" << endl;
		cout << "----------------------------------------------" << endl;
		select();
		if (selection == 2)
		{
			information();
		}
		if (selection == 0)
		{
			system("pause");
			exit(0);
		}
		if (selection == 1)
		{
			playgame();
		}
	}
}
void user::information()
{
	cout << "----------------------------------------------" << endl;
	cout << "账户名称:" << id << endl;
	cout << "最好记录:"<<endl;
	cout << "输入1可修改个人信息，输入0可离开此页面" << endl;
	cout << "----------------------------------------------" << endl;
	select();
	switch (selection)
	{
		case 1:
			reset();
			break;
		case 0:
			interface();
			break;
	}
	return;
}
void user::reset()
{
	cout << "----------------------------------------------" << endl;
	cout << "----------------0.离开页面--------------------" << endl;
	cout << "--------------1.修改账户名称------------------" << endl;
	cout << "--------------2.修改账户密码------------------" << endl;
	cout << "----------------------------------------------" << endl;
	select();
	switch (selection)
	{
	case 0:
		interface();
		break;
	case 1:
		cout << "----------------------------------------------" << endl;
		cout << "请输入账户新名称:";
		cin >> id;
		cout << "----------------------------------------------" << endl;
		reset();
		break;
	case2:
		{
			cout << "----------------------------------------------" << endl;
			for (int t = 1;; t++)
			{
				string newpassword;
				cout << "请输入原密码:";
				cin >> newpassword;
				if (newpassword != password)
				{
					cout << "原密码错误！" << endl;
					if (t <= 5)
					{
						continue;
					}
					else
					{
						cout << "错误操作过多次！" << endl;
						reset();
					}
				}
				else
				{
					cout << "请输入新密码";
					cin >> password;
					cout << "密码已修改完成";
					reset();
				}
			}
			break;
		}
	}
}
void user::autogame()
{
	cout << "----------------------------------------------" << endl;
	cout << "想玩多大的棋盘?请输入棋盘高度和宽度（至多为8*8）" << endl;
	int h = 0, w = 0;
	for (;;)
	{
		cin >> h >> w;
		if (h > 8 || w > 8)
		{
			cout << "棋盘太大了!请重新输入" << endl;

		}
		else break;
	}
	vector<vector<chess*>>aboard;
	vector<vector<chess*>>winaboard;
	vector<pair<int, int>> positions;
	vector<pair<int, int>> wpositions;
	for (int i = 0; i < h; ++i) 
	{
		aboard.push_back({ nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr });
		winaboard.push_back({ nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr });
		for (int j = 0; j < w; ++j) 
		{
			positions.emplace_back(i, j);
			wpositions.emplace_back(i, j);
		}
	}
	srand(time(0));
	std::random_shuffle(positions.begin(), positions.end());
	std::random_shuffle(wpositions.begin(),wpositions.end());
	int index1 = 0;
	int index2 = 0;
	for (int i = 0; i < 2; ++i) 
	{
		int y = positions[index1].first;
		int x = positions[index1].second;
		int wy = wpositions[index2].first;
		int wx = wpositions[index2].second;
		int heading; 
		heading = (int)rand() % 4 + 1;
		int wheading;
		wheading = (int)rand() % 4 + 1;
		aboard[y][x] = new infantry(x,y,heading);
		winaboard[wy][wx] = new infantry(x, y, wheading);
		index1++;
		index2++;
	}
	for (int i = 0; i < 1; ++i) 
	{
		int y = positions[index1].first;
		int x = positions[index1].second;
		int wy = wpositions[index2].first;
		int wx = wpositions[index2].second;
		int heading;
		heading= (int)rand()%4+1;
		int wheading;
		wheading = (int)rand() % 4 + 1;
		aboard[y][x] = new bowman(x, y, heading);
		winaboard[wy][wx] = new bowman(x, y, wheading);
		index1++;
		index2++;
	}
	for (int i = 0; i < 2; ++i) 
	{
		int y = positions[index1].first;
		int x = positions[index1].second;
		int wy = wpositions[index2].first;
		int wx = wpositions[index2].second;
		int heading;
		heading = (int)rand() % 4 + 1;
		int wheading;
		wheading = (int)rand() % 4 + 1;
		aboard[y][x] = new cavalrty(x, y, heading);
		winaboard[wy][wx] = new cavalrty(x, y, wheading);
		index1++;
		index2++;
	}
	chessboard b(h,w,aboard, winaboard);
	game(b);
}
void user::cust(const int& i)
{
	ofs[i].open(customizedfile[i]);
	wofs[i].open(wincondition[i]);
	int h = 0, w = 0;
	cout << "----------------------------------------------" << endl;
	cout << "输入棋盘的高和宽:" << endl;
	cin >> h >> w;
	ofs[i] << h << " " << w << " ";
	wofs[i] << h << " " << w << " ";
	pair<int, int>cor[5];
	int dir[5];
	string sym;
	cout << "请输入初始棋盘中棋子的坐标以及方向（其中I代表步兵,B代表弓箭手,C代表骑兵）（方向中1代表下,2代表左,3代表上,4代表右）" << endl;
	cout << "比如输入 I 4 5 2,代表设置一个骑兵位于（4,5）的位置，且其方向向左" << endl;
	for (int r = 0; r < 5; r++)
	{
		cin >> sym >> cor[r].first >> cor[r].second >> dir[r];
		ofs[i] << sym << " " << cor[r].first << " " << cor[r].second << " " << dir[r];
	}
	cout << "请输入目标棋盘中棋子的坐标以及方向:" << endl;
	for (int r = 0; r < 5; r++)
	{
		cin >> sym >> cor[r].first >> cor[r].second >> dir[r];
		wofs[i] << sym << " " << cor[r].first << " " << cor[r].second << " " << dir[r];
	}
	ofs[i].close();
	wofs[i].close();
}
void user::playcust(const int& i)
{
	ifs[i].open(customizedfile[i]);
	wifs[i].open(wincondition[i]);
	int yesorno1 = 0,yesorno2=0;
	ifs[i] >> yesorno1;
	wifs[i] >> yesorno2;
	if (yesorno1 == 0||yesorno2==0)
	{
		cout << "该棋盘还未自定义!无法游玩" << endl;
		customizedgame();
	}
	else
	{
		chessboard c;
		c.loadwithfile(customizedfile[i], wincondition[i]);
		game(c);
	}
}
void user::customizedgame()
{
	cout << "----------------------------------------------" << endl;
	cout << "------------------选择模式:-------------------" << endl;
	cout << "---------------1.游玩已定义棋盘---------------" << endl;
	cout << "----------------2.自定义棋盘------------------" << endl;
	cout << "----------------0.返回上一页------------------" << endl;
	select();
	if (selection == 1)
	{
		cout << "----------------------------------------------" << endl;
		cout << "------------------选择地图:-------------------" << endl;
		cout << "-------------------1.地图1--------------------" << endl;
		cout << "-------------------2.地图2--------------------" << endl;
		cout << "-------------------3.地图3--------------------" << endl;
		cout << "-------------------4.地图4--------------------" << endl;
		cout << "-------------------5.地图5--------------------" << endl;
		cout << "----------------0.返回上一页------------------" << endl;
		select();
		if (selection == 0)
		{
			customizedgame();
		}
		else if (selection == 1)
		{
			playcust(0);
		}
		else if (selection == 2)
		{
			playcust(1);
		}
		else if (selection == 3)
		{
			playcust(2);
		}
		else if (selection == 4)
		{
			playcust(3);
		}
		else if (selection == 5)
		{
			playcust(4);
		}
	}
	else if (selection == 2)
	{
		cout << "----------------------------------------------" << endl;
		cout << "------------------选择地图:-------------------" << endl;
		cout << "-------------------1.地图1--------------------" << endl;
		cout << "-------------------2.地图2--------------------" << endl;
		cout << "-------------------3.地图3--------------------" << endl;
		cout << "-------------------4.地图4--------------------" << endl;
		cout << "-------------------5.地图5--------------------" << endl;
		cout << "----------------0.返回上一页------------------" << endl;
		select();
		if (selection == 0)
		{
			customizedgame();
		}
		else if (selection == 1)
		{
			cust(0);
		}
		else if (selection == 2)
		{
			cust(1);
		}
		else if (selection == 3)
		{
			cust(2);
		}
		else if (selection == 4)
		{
			cust(3);
		}
		else if (selection == 5)
		{
			cust(4);
		}
	}
	else if (selection == 0)
	{
		interface();
	}
}
void user::game(chessboard game)
{
	game.useroperate();
	playgame();
}
void user::playgame()
{
	cout << "----------------------------------------------" << endl;
	cout << "------------------选择模式:-------------------" << endl;
	cout << "---------------1.固定棋盘模式-----------------" << endl;
	cout << "--------------2.非固定棋盘模式----------------" << endl;
	cout << "----------------3.自定义模式------------------" << endl;
	cout << "----------------0.返回主菜单------------------" << endl;
	select();
	if (selection == 0)
	{
		interface();
	}
	if (selection == 1)
	{
		cout << "----------------------------------------------" << endl;
		cout << "------------------选择模式:-------------------" << endl;
		cout << "-----------------1.简单模式-------------------" << endl;
		cout << "-----------------2.普通模式-------------------" << endl;
		cout << "-----------------3.困难模式-------------------" << endl;
		cout << "----------------0.返回上一页------------------" << endl;
		select();
		if (selection == 1)
		{
			cout << "----------------------------------------------" << endl;
			cout << "------------------选择地图:-------------------" << endl;
			cout << "-------------------1.地图1--------------------" << endl;
			cout << "-------------------2.地图2--------------------" << endl;
			cout << "----------------0.返回上一页------------------" << endl;
			select();
			switch (selection)
			{
			case 0:
				playgame();
				break;
			case 1:
			{
				chessboard s1(simple1, goal1);
				game(s1);
				break;
			}
			case 2:
			{
				chessboard s2(simple2, goal2);
				game(s2);
				break;
			}
			default:
				cout << "错误的输入！已自动跳转至上一页" << endl;
				playgame();
				break;
			}
		}
		if (selection == 2)
		{
			cout << "----------------------------------------------" << endl;
			cout << "------------------选择地图:-------------------" << endl;
			cout << "-------------------1.地图1--------------------" << endl;
			cout << "-------------------2.地图2--------------------" << endl;
			cout << "----------------0.返回上一页------------------" << endl;
			select();
			switch (selection)
			{
			case 0:
				playgame();
				break;
			case 1:
			{
				chessboard o1(ord1, ogoal1);
				game(o1);
				break;
			}
			case 2:
			{
				chessboard o2(ord2, ogoal2);
				game(o2);
				break;
			}
			default:
				cout << "错误的输入！已自动跳转至上一页" << endl;
				playgame();
				break;
			}
		}
		if (selection == 3)
		{
			cout << "----------------------------------------------" << endl;
			cout << "------------------选择地图:-------------------" << endl;
			cout << "-------------------1.地图1--------------------" << endl;
			cout << "----------------0.返回上一页------------------" << endl;
			select();
			switch (selection)
			{
			case 0:
				playgame();
				break;
			case 1:
			{
				chessboard h1(hard1, hgoal1);
				game(h1);
				break;
			}
			default:
				cout << "错误的输入！已自动跳转至上一页" << endl;
				playgame();
				break;
			}
		}
	}
	if (selection == 2)
	{
		autogame();
	}
	if (selection == 3)
	{
		customizedgame();
	}
}
