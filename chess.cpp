#include <iostream>
#include "chess.h"
chess::chess()
{
	x = 0;
	y = 0;
	heading = 1;
}
chess::chess(int x, int y, int dir):x(x),y(y),heading(dir){}
chess::chess(int given)
{
	x = 0;
	y = 0;
	heading = given;
}
void chess::walk(const int& h, const int& w, const int& i, std::vector<std::vector<chess*>>& board){}
void chess::setx(int i) { x = i; }
void chess::sety(int i) { y = i; }
void chess::setdir(int set) { heading = set; }
int chess::returnx() { return x; }
int chess::returny() { return y; }
int chess::getdir()
{
	return heading;
}
std::string chess::returndir()
{
	switch (heading)
	{
	case 0:
		return "0";
		break;
	case 1:
		return "down";
		break;
	case 2:
		return "left";
		break;
	case3:
		return "up";
		break;
	case 4:
		return "right";
		break;
	default:
		return "up";
		break;
	}
}
void chess::inspin()
{
	switch (heading)
	{
	case(1):
		heading = 2;
		break;
	case(2):
		heading = 3;
		break;
	case(3):
		heading = 4;
		break;
	case(4):
		heading = 1;
		break;
	}
	return;
}
void chess::bowspin()
{
	switch (heading)
	{
	case(1):
		heading = 3;
		break;
	case(2):
		heading = 4;
		break;
	case(3):
		heading = 1;
		break;
	case(4):
		heading = 2;
		break;
	}
	return;
}
infantry::infantry(int given):chess(given){}
void infantry::walk(const int& h, const int& w, const int& i, std::vector<std::vector<chess*>>& board)
{
	if (i == 0)return;
	int newx = x;
	int newy = y;
	for (int t = 1; t <= i; t+=1)
	{
		if (newx > w || newy > h||newx<0||newy<0)
		{
			std::cout << "wrong operation,please reoperate" << std::endl;
			return;
		}
		switch (heading)
		{
		case (1):
			newy = newy + 1;
			break;
		case (2):
			newx = newx - 1;
			break;
		case(3):
			newy = newy - 1;
			break;
		case(4):
			newx = newx + 1;
			break;
		}
		if (board[newy][newx] != nullptr)
		{
			board[newy][newx]->inspin();
			switch (heading)
			{
			case(1):
				board[newy-1][newx] = new infantry(newx,newy-1,board[y][x]->getdir());
				board[newy-1][newx]->setx(newx);
				board[newy-1][newx]->sety(newy-1);
				if (t!=1)
				{
					board[y][x] = nullptr;
				}
				break;
			case(2):
				board[newy][newx+1] = new infantry(newx+1, newy, board[y][x]->getdir());
				board[newy][newx+1]->setx(newx+1);
				board[newy][newx+1]->sety(newy);
				if (t!=1)
				{
					board[y][x] = nullptr;
				}
				break;
			case(3):
				board[newy+1][newx] = new infantry(newx, newy + 1, board[y][x]->getdir());
				board[newy+1][newx]->setx(newx);
				board[newy+1][newx]->sety(newy+1);
				if (t!=1)
				{
					board[y][x] = nullptr;
				}
				break;
			case(4):
				board[newy][newx-1] = new infantry(newx-1, newy, board[y][x]->getdir());
				board[newy][newx-1]->setx(newx-1);
				board[newy][newx-1]->sety(newy);
				if (t!=1)
				{
					board[y][x] = nullptr;
				}
				break;
			}
			return;
		}
	}
	board[newy][newx] = new infantry(newx, newy, board[y][x]->getdir());
	board[newy][newx]->setx(newx);
	board[newy][newx]->sety(newy);
	board[y][x] = nullptr;
	return;
}
bowman::bowman(int given) :chess(given) {}
void bowman::shoot(const int& h, const int& w, const int& option, std::vector<std::vector<chess*>>& board)
{
	if (option != 4 && option != 1 && option != 2 && option != 3)
	{
		std::cout << "请勿输入错误方向" << std::endl;
		return;
	}
	heading = option;
	int newx = x;
	int newy = y;
	for (; newx <=w && newy <= h;)
	{
		switch (option)
		{
		case (1):
			newy = newy + 1;
			break;
		case (2):
			newx = newx - 1;
			break;
		case(3):
			newy = newy - 1;
			break;
		case(4):
			newx = newx + 1;
			break;
		}
		if (board[newy][newx] != nullptr)
		{
			switch (option)
			{
			case (1):
				if (board[newy][newx-1] == nullptr)
				{
					board[newy][newx-1] = board[newy][newx];
					board[newy][newx-1]->bowspin();
					board[newy][newx - 1]->setx(newx - 1);
					board[newy][newx - 1]->sety(newy);
					board[newy][newx] = nullptr;
				}
				else
				{
					if (board[newy][newx+1] == nullptr)
					{
						board[newy][newx+1] = board[newy][newx];
						board[newy][newx+1]->bowspin();
						board[newy][newx + 1]->setx(newx + 1);
						board[newy][newx + 1]->sety(newy);
						board[newy][newx] = nullptr;
					}
					else board[newy][newx]->bowspin();
				}
				break;
			case (2):
				if (board[newy-1][newx] == nullptr)
				{
					board[newy-1][newx] = board[newy][newx];
					board[newy-1][newx]->bowspin();
					board[newy-1][newx]->setx(newx);
					board[newy-1][newx]->sety(newy-1);
					board[newy][newx] = nullptr;
				}
				else
				{
					if (board[newy+1][newx] == nullptr)
					{
						board[newy+1][newx] = board[newy][newx];
						board[newy+1][newx]->bowspin();
						board[newy+1][newx]->setx(newx);
						board[newy+1][newx]->sety(newy+1);
						board[newy][newx] = nullptr;
					}
					else board[newy][newx]->bowspin();
				}
				break;
			case(3):
				if (board[newy][newx+1] == nullptr)
				{
					board[newy][newx+1] = board[newy][newx];
					board[newy][newx+1]->bowspin();
					board[newy][newx+1]->setx(newx+1);
					board[newy][newx+1]->sety(newy);
					board[newy][newx] = nullptr;
				}
				else
				{
					if (board[newy][newx-1] == nullptr)
					{
						board[newy][newx-1] = board[newy][newx];
						board[newy][newx-1]->bowspin();
						board[newy][newx - 1]->setx(newx - 1);
						board[newy][newx - 1]->sety(newy);
						board[newy][newx] = nullptr;
					}
					else board[newy][newx]->bowspin();
				}
				break;
			case(4):
				if (board[newy+1][newx] == nullptr)
				{
					board[newy+1][newx] = board[newy][newx];
					board[newy+1][newx]->bowspin();
					board[newy+1][newx]->setx(newx);
					board[newy+1][newx]->sety(newy+1);
					board[newy][newx] = nullptr;
				}
				else
				{
					if (board[newy-1][newx] == nullptr)
					{
						board[newy-1][newx] = board[newy][newx];
						board[newy-1][newx]->bowspin();
						board[newy-1][newx]->setx(newx);
						board[newy-1][newx]->sety(newy-1);
						board[newy][newx] = nullptr;
					}
					else board[newy][newx]->bowspin();
				}
				break;
			}
			break;
		}
	}
	return;
}
cavalrty::cavalrty(int given) :chess(given) {}
void cavalrty::walk(const int& h, const int& w, const int& i, std::vector<std::vector<chess*>>& board)
{
	if (i == 0)return;
	int newx = x;
	int newy = y;
	for (int t = 1; t <= i; t++)
	{
		if (newx > w || newy > h || newx < 0 || newy < 0)
		{
			std::cout << "wrong operation,please reoperate" << std::endl;
			return;
		}
		switch (heading)
		{
		case (1):
			newy = newy + 1;
			break;
		case (2):
			newx = newx - 1;
			break;
		case(3):
			newy = newy - 1;
			break;
		case(4):
			newx = newx + 1;
			break;
		}
		if (board[newy][newx] != nullptr)
		{
			switch (heading)
			{
			case (1):
				board[newy+1][newx] = board[newy][newx];
				board[newy+1][newx]->setx(newx);
				board[newy+1][newx]->sety(newy+1);
				board[newy][newx] = board[y][x];
				if (t >= 2)
				{
					board[newy-1][newx] = nullptr;
				}
				break;
			case (2):
				board[newy][newx-1] = board[newy][newx];
				board[newy][newx] = board[y][x];
				board[newy][newx-1]->setx(newx-1);
				board[newy][newx-1]->sety(newy);
				if (t >= 2)
				{
					board[newy][newx + 1] = nullptr;
				}
				break;
			case(3):
				board[newy-1][newx] = board[newy][newx];
				board[newy][newx] = board[y][x];
				board[newy-1][newx]->setx(newx);
				board[newy-1][newx]->sety(newy-1);
				if (t >= 2)
				{
					board[newy+1][newx] = nullptr;
				}
				break;
			case(4):
				board[newy][newx+1] = board[newy][newx];
				board[newy][newx] = board[y][x];
				board[newy][newx + 1]->setx(newx + 1);
				board[newy][newx + 1]->sety(newy);
				if (t >= 2)
				{
					board[newy][newx -1] = nullptr;
				}
				break;
			}
		}
	}
	board[newy][newx] = board[y][x];
	board[y][x] = nullptr;
	return;
}

