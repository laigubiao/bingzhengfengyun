#include <iostream>
#include "chess.h"
chess::chess()
{
	x = 0;
	y = 0;
	heading = down;
}
void chess::walk(int i, std::vector<std::vector<chess*>>& board){}
void chess::setx(int i) { x = i; }
void chess::sety(int i) { y = i; }
void chess::setdir(direction set) { heading = set; }
int chess::returnx() { return x; }
int chess::returny() { return y; }
direction chess::returndir() { return heading; }
void chess::inspin()
{
	switch (heading)
	{
	case(down):
		heading = left;
		break;
	case(left):
		heading = up;
		break;
	case(up):
		heading = right;
		break;
	case(right):
		heading = down;
		break;
	}
	return;
}
void chess::bowspin()
{
	switch (heading)
	{
	case(down):
		heading = up;
		break;
	case(left):
		heading = right;
		break;
	case(up):
		heading = down;
		break;
	case(right):
		heading = left;
		break;
	}
	return;
}
void infantry::walk(int i, std::vector<std::vector<chess*>>& board)
{
	int newx = x;
	int newy = y;
	for (int t = 1; t <= i; t++)
	{
		if (newx > 5 && newy > 5)
		{
			std::cout << "wrong operation,please reoperate" << std::endl;
			return;
		}
		switch (heading)
		{
		case (down):
			newy = newy + 1;
			break;
		case (left):
			newx = newx - 1;
			break;
		case(up):
			newy = newy - 1;
			break;
		case(right):
			newx = newx + 1;
			break;
		}
		if (board[newy][newx] != nullptr)
		{
			board[newy][newx]->inspin();
			switch (heading)
			{
			case(down):
				newy = newy - 1;
				break;
			case(left):
				newx = newx + 1;
			case(up):
				newy = newy + 1;
			case(right):
				newx = newx - 1;
			}
			board[newy][newx] = board[y][x];
			return;
		}
	}
	board[newy][newx] = board[y][x];
	y = newy;
	x = newx;
	board[y][x] = nullptr;
	return;
}
void bowman::shoot(direction option, std::vector<std::vector<chess*>>& board)
{
	heading = option;
	int newx = x;
	int newy = y;
	for (; newx <= 5 && newy <= 5;)
	{
		if (newx > 5 && newy > 5)
		{
			std::cout << "wrong operation,please reoperate" << std::endl;
			return;
		}
		switch (heading)
		{
		case (down):
			newy = newy + 1;
			break;
		case (left):
			newx = newx - 1;
			break;
		case(up):
			newy = newy - 1;
			break;
		case(right):
			newx = newx + 1;
			break;
		}
		if (board[newy][newx] != nullptr)
		{
			switch (heading)
			{
			case (down):
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
			case (left):
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
			case(up):
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
			case(right):
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
		}
		return;
	}
	return;
}
void cavalrty::walk(int i, std::vector<std::vector<chess*>>& board)
{
	int newx = x;
	int newy = y;
	for (int t = 1; t <= i; t++)
	{
		if (newx > 5 && newy > 5)
		{
			std::cout << "wrong operation,please reoperate" << std::endl;
			return;
		}
		switch (heading)
		{
		case (down):
			newy = newy + 1;
			break;
		case (left):
			newx = newx - 1;
			break;
		case(up):
			newy = newy - 1;
			break;
		case(right):
			newx = newx + 1;
			break;
		}
		if (board[newy][newx] != nullptr)
		{
			switch (heading)
			{
			case (down):
				board[newy+1][newx] = board[newy][newx];
				board[newy+1][newx]->setx(newx);
				board[newy+1][newx]->sety(newy+1);
				board[newy][newx] = board[y][x];
				if (t >= 2)
				{
					board[newy-1][newx] = nullptr;
				}
				break;
			case (left):
				board[newy][newx-1] = board[newy][newx];
				board[newy][newx] = board[y][x];
				board[newy][newx-1]->setx(newx-1);
				board[newy][newx-1]->sety(newy);
				if (t >= 2)
				{
					board[newy][newx + 1] = nullptr;
				}
				break;
			case(up):
				board[newy-1][newx] = board[newy][newx];
				board[newy][newx] = board[y][x];
				board[newy-1][newx]->setx(newx);
				board[newy-1][newx]->sety(newy-1);
				if (t >= 2)
				{
					board[newy+1][newx] = nullptr;
				}
				break;
			case(right):
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
	x = newx;
	y = newy;
	board[y][x] = nullptr;
	return;
}

