#ifndef CHESS_H
#define CHESS_H
#include <vector>
#include <string>
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
	chess(int x, int y, direction dir);
	chess(direction given);
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
	direction getdir();
	std::string returndir();
	virtual ~chess() {};
};
class infantry:public chess
{
public:
	infantry() { chess(); };
	infantry(int x, int y, direction dir) :chess(x, y, dir){}
	void walk(int i, std::vector<std::vector<chess*>>& board)override;
	~infantry()override {};
};
class bowman :public chess
{
public:
	bowman() { chess(); };
	bowman(int x, int y, direction dir) :chess(x, y, dir) {}
	void shoot(direction option, std::vector<std::vector<chess*>>& board)override;
	~bowman()override {};
};
class cavalrty :public chess
{
public:
	cavalrty() { chess(); };
	cavalrty(int x, int y, direction dir) :chess(x, y, dir) {}
	void dirdecide(bool decision)override
	{
		if (decision == 1)bowspin();
		else return;
	}
	void walk(int i, std::vector<std::vector<chess*>>& board)override;
	~cavalrty()override {};
};
#endif
