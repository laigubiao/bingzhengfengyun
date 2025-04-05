#include <iostream>
#include "chess.h"
void chess::walk(int i, std::vector<std::vector<chess*>>& board){}
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
	board[x][y] = nullptr;
	std::cout << "infantry turn" << std::endl;
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
			newy = newy - 1;
			break;
		case (left):
			newx = newx - 1;
			break;
		case(up):
			newy = newy + 1;
			break;
		case(right):
			newx = newx + 1;
			break;
		}
		if (board[newx][newy] != nullptr)
		{
			board[newx][newy]->inspin();
			x = newx;
			y = newy;
			switch (heading)
			{
			case(down):
				y = y + 1;
				break;
			case(left):
				x = x + 1;
			case(up):
				y = y - 1;
			case(right):
				x = x - 1;
			}
			board[x][y] = this;
			return;
		}
	}
	board[newx][newy] = this;
	return;
}
void bowman::shoot(direction option, std::vector<std::vector<chess*>>& board)
{
	heading = option;
	int newx = x;
	int newy = y;
	board[x][y] = nullptr;
	std::cout << "bowman turn" << std::endl;
	for (;newx<=5&&newy<=5;)
	{
		if (newx > 5 && newy > 5)
		{
			std::cout << "wrong operation,please reoperate" << std::endl;
			return;
		}
		switch (heading)
		{
		case (down):
			newy = newy - 1;
			break;
		case (left):
			newx = newx - 1;
			break;
		case(up):
			newy = newy + 1;
			break;
		case(right):
			newx = newx + 1;
			break;
		}
		if (board[newx][newy] != nullptr)
		{
			switch (heading)
			{
			case (down):
				if (board[newx - 1][newy] == nullptr)
				{
					board[newx - 1][newy] = board[newx][newy];
					board[newx - 1][newy]->bowspin();
					board[newx][newy] = nullptr;
				}
				else
				{
					if (board[newx + 1][newy] == nullptr)
					{
						board[newx + 1][newy] = board[newx][newy];
						board[newx + 1][newy]->bowspin();
						board[newx][newy] = nullptr;
					}
					else board[newx][newy]->bowspin();
				}
				break;
			case (left):
				if (board[newx][newy+1] == nullptr)
				{
					board[newx][newy+1] = board[newx][newy];
					board[newx][newy+1]->bowspin();
					board[newx][newy] = nullptr;
				}
				else
				{
					if (board[newx][newy-1] == nullptr)
					{
						board[newx][newy-1] = board[newx][newy];
						board[newx][newy-1]->bowspin();
						board[newx][newy] = nullptr;
					}
					else board[newx][newy]->bowspin();
				}
				break;
			case(up):
				if (board[newx + 1][newy] == nullptr)
				{
					board[newx + 1][newy] = board[newx][newy];
					board[newx + 1][newy]->bowspin();
					board[newx][newy] = nullptr;
				}
				else
				{
					if (board[newx - 1][newy] == nullptr)
					{
						board[newx - 1][newy] = board[newx][newy];
						board[newx - 1][newy]->bowspin();
						board[newx][newy] = nullptr;
					}
					else board[newx][newy]->bowspin();
				}
				break;
			case(right):
				if (board[newx][newy - 1] == nullptr)
				{
					board[newx][newy - 1] = board[newx][newy];
					board[newx][newy - 1]->bowspin();
					board[newx][newy] = nullptr;
				}
				else
				{
					if (board[newx][newy + 1] == nullptr)
					{
						board[newx][newy + 1] = board[newx][newy];
						board[newx][newy + 1]->bowspin();
						board[newx][newy] = nullptr;
					}
					else board[newx][newy]->bowspin();
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
	board[x][y] = nullptr;
	std::cout << "cavalty turn" << std::endl;
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
			newy = newy - 1;
			break;
		case (left):
			newx = newx - 1;
			break;
		case(up):
			newy = newy + 1;
			break;
		case(right):
			newx = newx + 1;
			break;
		}
		if (board[newx][newy] != nullptr)
		{
			switch (heading)
			{
			case (down):
				board[newx][newy - 1] = board[newx][newy];
				board[newx][newy] = nullptr;
				break;
			case (left):
				board[newx - 1][newy] = board[newx][newy];
				board[newx][newy] = nullptr;
				break;
			case(up):
				board[newx][newy + 1] = board[newx][newy];
				board[newx][newy] = nullptr;
				break;
			case(right):
				board[newx + 1][newy] = board[newx][newy];
				board[newx][newy] = nullptr;
				break;
			}
		}
		board[newx][newy] = this;
		return;
	}
	return;
}

