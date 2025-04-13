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
	cout << "��������˻�����:";
	cin >> id;
	recordid = id;
	ofs << id<<" ";
	cout << '\n' << "��������˻�����:";
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
		cout << "����������˻���id:";
		cin >> id>>password;
		if (id != recordid)
		{
			cout << "�˻���������" << endl;
			exit(1);
		}
		else
		{
			if (password != recordpassword)
			{
				cout << "�������" << endl;
				exit(1);
			}
			else 
			{ 
				cout << "��ӭ" << id << "����������" << endl;
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
		cout << "----------------1.��ʼ��Ϸ--------------------";
		cout << "----------------2.������Ϣ--------------------";
		cout << "----------------3.������Ϸ--------------------";
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
	cout << "�˻�����:" << id << endl;
	cout << "��ü�¼:"<<endl;
	cout << "����1���޸ĸ�����Ϣ������0���뿪��ҳ��" << endl;
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
	cout << "----------------0.�뿪ҳ��--------------------";
	cout << "--------------1.�޸��˻�����------------------";
	cout << "--------------2.�޸��˻�����------------------";
	cout << "----------------------------------------------";
	select();
	switch (selection)
	{
	case 0:
		interface();
		break;
	case 1:
		cout << "----------------------------------------------";
		cout << "�������˻�������:";
		cin >> id;
		cout << "----------------------------------------------";
		reset();
		break;
	case2:
		cout << "----------------------------------------------";
		for (int t=1;;t++)
		{
			string newpassword;
			cout << "������ԭ����:";
			cin >> newpassword;
			if (newpassword != password)
			{
				cout << "ԭ�������" << endl;
				if (t <= 5)
				{
					continue;
				}
				else
				{
					cout << "�����������Σ�" << endl;
					reset();
				}
			}
			else
			{
				cout << "������������";
				cin >> password;
				cout << "�������޸����";
				reset();
			}
		}
		break;
	}
}
void user::playgame()
{

}