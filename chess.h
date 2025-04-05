#ifndef CHESS_H
#define CHESS_H
#include <vector>
enum direction
{down,left,up,right};
class chess
{
public:
	direction heading;
	int x;
	int y;
	void autoload(direction given, int givenx,int giveny)
	{
		heading = given;
		x=givenx;
		y = giveny;
	}
	void customizedload(direction custgiven, int custgivenx,int custgiveny)
	{
		heading = custgiven;
		x=custgivenx;
		y = custgiveny;
	}
	virtual void walk(int i, std::vector<std::vector<chess*>>& board);
	void inspin();
	void bowspin();
};
class infantry:public chess
{
public:
	void walk(int i, std::vector<std::vector<chess*>>& board)override;
	
};
class bowman :public chess
{
	void shoot(direction option, std::vector<std::vector<chess*>>& board);
};
class cavalrty :public chess
{
	void dirdecide(bool decision)
	{
		if (decision == 1)bowspin();
		else return;
	}
	void walk(int i, std::vector<std::vector<chess*>>& board)override;
};
#endif