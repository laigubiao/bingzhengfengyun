#include "user.h"
#include <iostream>
using namespace std;
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
		cout << "----------------------------------------------";
		cout << "----------------1.开始游戏--------------------";
		cout << "----------------2.个人信息--------------------";
		cout << "----------------3.结束游戏--------------------";
		cout << "----------------------------------------------";
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
	cout << "----------------------------------------------";
	cout << "账户名称:" << id << endl;
	cout << "最好记录:"<<endl;
	cout << "输入1可修改个人信息，输入0可离开此页面" << endl;
	cout << "----------------------------------------------";
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
	cout << "----------------------------------------------";
	cout << "----------------0.离开页面--------------------";
	cout << "--------------1.修改账户名称------------------";
	cout << "--------------2.修改账户密码------------------";
	cout << "----------------------------------------------";
	select();
	switch (selection)
	{
	case 0:
		interface();
		break;
	case 1:
		cout << "----------------------------------------------";
		cout << "请输入账户新名称:";
		cin >> id;
		cout << "----------------------------------------------";
		reset();
		break;
	case2:
		cout << "----------------------------------------------";
		for (int t=1;;t++)
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
void user::playgame()
{

}