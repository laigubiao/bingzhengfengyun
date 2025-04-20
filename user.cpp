#include "user.h"
#include <iostream>
using namespace std;
vector<vector<chess*>>simple1 = { {nullptr,new infantry,nullptr,nullptr,nullptr},{new infantry,nullptr,new cavalrty,nullptr,nullptr},{nullptr,nullptr,nullptr,nullptr,nullptr} ,{nullptr,nullptr,nullptr,new bowman,nullptr} ,{nullptr,nullptr,new cavalrty,nullptr,nullptr} };
vector<vector<chess*>>goal1= { {nullptr,nullptr,nullptr,nullptr,nullptr},{new infantry,new infantry,new cavalrty,nullptr,nullptr},{nullptr,nullptr,nullptr,nullptr,nullptr} ,{nullptr,nullptr,nullptr,new bowman,nullptr} ,{nullptr,nullptr,new cavalrty,nullptr,nullptr} };
vector<vector<chess*>>simple2;
vector<vector<chess*>>goal2;
vector<vector<chess*>>ord1;
vector<vector<chess*>>ogoal1;
vector<vector<chess*>>ord2;
vector<vector<chess*>>ogoal2;
vector<vector<chess*>>hard1;
vector<vector<chess*>>hgoal1;
user::user()
{
	id = "0";
	password = "0";
	movecounter = 0;
	selection = 0;
}
void user::setaccount(string& recordpassword, string& recordid,ofstream &ofs)
{
	cout << "输入你的账户名称:";
	cin >> id;
	recordid = id;
	ofs << id<<" ";
	cout << '\n' << "输入你的账户密码:";
	cin >> password;
	recordpassword = password;
	ofs << password;
}
void user::loginaccount(string& recordpassword, string& recordid,ifstream &ifs, ofstream& ofs)
{
	ifs >> id >> password;
	if (id == "0" || password == "0")
	{
		setaccount(recordpassword, recordid,ofs);
		return;
	}
	else
	{
		ifs.seekg(0,ios::beg);
		ifs >> recordid>>recordpassword;
		cout << "请输入你的账户和id:";
		cin >> id>>password;
		if (id != recordid)
		{
			cout << "账户名不存在" << endl;
			exit(1);
		}
		else
		{
			if (password != recordpassword)
			{
				cout << "密码错误！" << endl;
				exit(1);
			}
			else 
			{ 
				cout << "欢迎" << id << "游玩兵阵风云" << endl;
				return;
			}
		}
	}
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
		if (selection == 3)
		{
			system("pause");
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

}
void user::customizedgame()
{

}
void user::game(chessboard game)
{
	game.useroperate();
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
