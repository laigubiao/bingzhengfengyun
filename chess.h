#ifndef CHESS_H
#define CHESS_H
#include <vector>
#include <string>
class chess
{
protected:
	int x;
	int y;
	int heading;
public:
	chess();
	chess(int x, int y, int dir);
	chess(int given);
	virtual void walk(const int &h,const int &w,const int &i, std::vector<std::vector<chess*>>& board);
	virtual void shoot(const int& h, const int& w,const int &option, std::vector<std::vector<chess*>>& board) {};
	virtual void dirdecide(bool decision){};
	void inspin();
	void bowspin();
	void setx(int i);
	void sety(int i);
	void setdir(int set);
	int returnx();
	int returny();
	int getdir();
	std::string returndir();
	virtual ~chess() {};
};
class infantry:public chess
{
public:
	infantry() { chess(); };
	infantry(int x, int y, int dir) :chess(x, y, dir){}
	void walk(const int& h, const int& w, const int& i, std::vector<std::vector<chess*>>& board)override;
	~infantry()override {};
};
class bowman :public chess
{
public:
	bowman() { chess(); };
	bowman(int x, int y, int dir) :chess(x, y, dir) {}
	void shoot(const int& h, const int& w, const int& option, std::vector<std::vector<chess*>>& board)override;
	~bowman()override {};
};
class cavalrty :public chess
{
public:
	cavalrty() { chess(); };
	cavalrty(int x, int y, int dir) :chess(x, y, dir) {}
	void dirdecide(bool decision)override
	{
		if (decision == 1)bowspin();
		else return;
	}
	void walk(const int& h, const int& w, const int& i, std::vector<std::vector<chess*>>& board)override;
	~cavalrty()override {};
};
#endif
