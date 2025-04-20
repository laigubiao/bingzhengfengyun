#ifndef CHESS_H
#define CHESS_H
#include <vector>
enum direction
{down=1,left=2,up=3,right=4};
class chess
{
protected:
	int x;
	int y;
	direction heading;
public:
	chess();
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
	virtual void shoot(direction option, std::vector<std::vector<chess*>>& board) {};
	virtual void dirdecide(bool decision){};
	void inspin();
	void bowspin();
	void setx(int i);
	void sety(int i);
	void setdir(direction set);
	int returnx();
	int returny();
	direction returndir();
	virtual ~chess() {};
};
class infantry:public chess
{
public:
	infantry() { chess(); };
	void walk(int i, std::vector<std::vector<chess*>>& board)override;
	~infantry()override {};
};
class bowman :public chess
{
public:
	bowman() { chess(); };
	void shoot(direction option, std::vector<std::vector<chess*>>& board)override;
	~bowman()override {};
};
class cavalrty :public chess
{
public:
	cavalrty() { chess(); };
	void dirdecide(bool decision)override
	{
		if (decision == 1)bowspin();
		else return;
	}
	void walk(int i, std::vector<std::vector<chess*>>& board)override;
	~cavalrty()override {};
};
#endif
