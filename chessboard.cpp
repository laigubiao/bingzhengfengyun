#include "chessboard.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <functional>
#include <cstdlib>
#include <random>
int winx = 0, winy = 0;
struct CompareState 
{
	bool operator()(const std::pair<int, State>& a, const std::pair<int, State>& b) 
	{
		return a.first > b.first;
	}
};
int heuristic(const State& state) 
{
	int cost = 0;
	pair<int, int> goalPositions = { winx,winy};
		cost += std::abs(state.Positions.first - goalPositions.first) +
			std::abs(state.Positions.second - goalPositions.second);
	return cost;
}
bool isGoalState(const State& state) 
{
	pair<int, int> goalPositions = { winx,winy };
	for (size_t i = 0; i < state.board0.size(); ++i) 
	{
		for (size_t j = 0; j < state.board0[i].size(); ++j) 
		{
			if (state.board0[i][j] != nullptr && dynamic_cast<infantry*>(state.board0[i][j])) 
			{
				if (i != goalPositions.second|| j != goalPositions.first) 
				{
						return false;
				}
			}
		}
	}
	return true;
}
State ingetNextStates(const State& state) 
{
	State nextStates;
	int x = state.Positions.first;
	int y = state.Positions.second;
	int heading = state.board0[y][x]->getdir(); 
	int newX = x, newY = y;
	switch (heading) 
	{
		case 1:
			newY = y + 1;
			break;
		case 2:
			newX = x - 1;
			break;
		case 3:
			newY = y - 1;
			break;
		case 4:
			newX = x + 1;
			break;
	}
	if (newX >= 0 && newX < state.board0.size() && newY >= 0 && newY < state.board0.size() && state.board0[newY][newX] == nullptr) 
	{
		std::vector<std::vector<chess*>> newBoard = state.board0;
		newBoard[newY][newX] = newBoard[y][x];
		newBoard[y][x] = nullptr;
		pair<int, int> newInfantryPositions = state.Positions;
		newInfantryPositions = { newX, newY };
		nextStates=State(newBoard, state.moveCount + 1, newInfantryPositions);
	}
	return nextStates;
}
vector<State> inaStarSearch(const State& initialState)
{
	std::priority_queue<std::pair<int, State>, std::vector<std::pair<int, State>>, CompareState> pq;
	queue < std::pair<int, State>, std::vector<std::pair<int, State>>> rpq;
	std::vector<State> visited;
	pq.push({ heuristic(initialState), initialState });
	visited.push_back(initialState);
	while (!pq.empty())
	{
		State currentState = pq.top().second;
		pq.pop();
		if (isGoalState(currentState))
		{
			return { currentState };
		}
		State nextStates = ingetNextStates(currentState);
		if (std::find(visited.begin(), visited.end(), nextStates) != visited.end())
		{
			visited.push_back(nextStates);
			pq.push({ heuristic(nextStates) + nextStates.moveCount, nextStates });
		}
	}
		return visited;
}
void ingiveHint(const State& initialState) 
{
	std::vector<State> path = inaStarSearch(initialState);
	State r = path[0];
	int rm = path[0].moveCount;
	int mark = 0;
	for (int t = 1; t < path.size(); t++)
	{
		if (path[t].moveCount < rm)
		{
			rm = path[t].moveCount;
			mark = t;
		}
	}
	path[0] = path[mark];
	path[mark] = r;
	if (!path.empty()) 
	{
		State firstMove = path[0]; 
		if (initialState.Positions != firstMove.Positions) 
		{
			std::cout << "提示：移动步兵 " 
				<< " 从 (" << initialState.Positions.first << ", " << initialState.Positions.second
				<< ") 到 (" << firstMove.Positions.first << ", " << firstMove.Positions.second << ")" << std::endl;
			return;
		}
	}
	else 
	{
		std::cout << "没有可用的提示。" << std::endl;
	}
}
vector<State> cagetNextStates(const State& state) 
{
	vector<State> nextStates;
	int x = state.Positions.first;
	int y = state.Positions.second;
	int heading = state.board0[y][x]->getdir(); 
	int newX = x, newY = y;
	switch (heading) 
	{
	case 1:
		newY = y + 1;
		break;
	case 2:
		newX = x - 1;
		break;
	case 3:
		newY = y - 1;
		break;
	case 4:
		newX = x + 1;
		break;
	}
	if (newX >= 0 && newX < state.board0.size() && newY >= 0 && newY < state.board0.size() && state.board0[newY][newX] == nullptr) 
	{
		std::vector<std::vector<chess*>> newBoard = state.board0;
		newBoard[newY][newX] = newBoard[y][x];
		newBoard[y][x] = nullptr;
		pair<int, int> newCavalryPositions = state.Positions;
		newCavalryPositions = { newX, newY };
		nextStates.push_back(State(newBoard, state.moveCount + 1, newCavalryPositions));
	}
	int newHeading=0;
	switch (heading) 
	{
	case 1:
		newHeading = 3;
		break;
	case 2:
		newHeading = 4;
		break;
	case 3:
		newHeading = 1;
		break;
	case 4:
		newHeading = 2;
		break;
	}
	newX = x, newY = y;
	switch (newHeading) 
	{
	case 1:
		newY = y + 1;
		break;
	case 2:
		newX = x - 1;
		break;
	case 3:
		newY = y - 1;
		break;
	case 4:
		newX = x + 1;
		break;
	}
	if (newX >= 0 && newX < state.board0.size() && newY >= 0 && newY < state.board0.size() && state.board0[newY][newX] == nullptr) 
	{
		std::vector<std::vector<chess*>> newBoard = state.board0;
		newBoard[newY][newX] = newBoard[y][x];
		newBoard[y][x] = nullptr;
		pair<int, int> newCavalryPositions = state.Positions;
		newCavalryPositions = { newX, newY };
		nextStates.push_back(State(newBoard, state.moveCount + 1, newCavalryPositions));
	}
	return nextStates;
}
std::vector<State> caaStarSearch(const State& initialState) 
{
	std::priority_queue<std::pair<int, State>, std::vector<std::pair<int, State>>, CompareState> pq;
	std::vector<State> visited;
	pq.push({ heuristic(initialState), initialState });
	visited.push_back(initialState);
	while (!pq.empty()) 
	{
		State currentState = pq.top().second;
		pq.pop();
		if (isGoalState(currentState)) 
		{
			return { currentState }; 
		}
		State nextStates1 = cagetNextStates(currentState)[0];
		State nextStates2 = cagetNextStates(currentState)[1];
		if (std::find(visited.begin(), visited.end(), nextStates1) == visited.end()) 
		{
			visited.push_back(nextStates1);
			pq.push({ heuristic(nextStates1) + nextStates1.moveCount, nextStates1 });
		}
		if (std::find(visited.begin(), visited.end(), nextStates2) == visited.end())
		{
			visited.push_back(nextStates2);
			pq.push({ heuristic(nextStates2) + nextStates2.moveCount, nextStates2 });
		}
	}
	return visited;
}
void cagiveHint(const State& initialState) 
{
	std::vector<State> path = caaStarSearch(initialState);
	State r = path[0];
	int rm = path[0].moveCount;
	int mark = 0;
	for (int t = 1; t < path.size(); t++)
	{
		if (path[t].moveCount < rm)
		{
			rm = path[t].moveCount;
			mark = t;
		}
	}
	path[0] = path[mark];
	path[mark] = r;
	if (!path.empty()) 
	{
		State firstMove = path[0];
		if (initialState.Positions != firstMove.Positions)
		{
			std::cout << "提示：移动骑兵 " 
				<< " 从 (" << initialState.Positions.first << ", " << initialState.Positions.second
				<< ") 到 (" << firstMove.Positions.first << ", " << firstMove.Positions.second << ")" << std::endl;
			return;
		}
	}
	else 
	{
		std::cout << "没有可用的提示。" << std::endl;
	}
}
chessboard::chessboard(const vector<vector<chess*>>& initialposi,const vector<vector<chess*>>& inwinposi) :board(initialposi), winposi(inwinposi), initialposit(initialposi)
{
	height = 5;
	width = 5;
	getcoor();
	getwincoor();
	instate1 = State(board, 0,{incoordinate[0][1],incoordinate[0][0]});
	instate2 = State(board, 0,{incoordinate[1][1],incoordinate[1][0]});
	castate1 = State(board, 0,{cacoordinate[0][1],cacoordinate[0][0]});
	castate2 = State(board, 0,{cacoordinate[1][1],cacoordinate[1][0]});
	movecounter = 0;
}
chessboard::chessboard(const int &h,const int &w,const vector<vector<chess*>>& initialposi,const vector<vector<chess*>>& inwinposi) :height(h),width(w),board(initialposi), winposi(inwinposi), initialposit(initialposi)
{
	getcoor();
	getwincoor();
	instate1 = State(board, 0, { incoordinate[0][1],incoordinate[0][0] });
	instate2 = State(board, 0, { incoordinate[1][1],incoordinate[1][0] });
	castate1 = State(board, 0, { cacoordinate[0][1],cacoordinate[0][0] });
	castate2 = State(board, 0, { cacoordinate[1][1],cacoordinate[1][0] });
	movecounter = 0;
}
void chessboard::loadwithfile(const string &file,const string &wfile)
{
	ifstream ifs;
	ifstream wifs;
	ifs.open(file);
	wifs.open(wfile);
	int h = 0, w = 0;
	ifs >> h >> w;
	height = h;
	width = w;
	string in;
	int nx = 0, ny = 0;
	int d = 0;
	int j = 0,p=0,q=0;
	for (int i = 0; i < 5; i++)
	{
			ifs >>in>> nx >>ny>> d;
			if (in == "I")
			{
				board[ny][nx] = new infantry(nx,ny,d);
				incoordinate[j][0] = nx;
				incoordinate[j][1] = ny;
				j++;
			}
			if (in == "B")
			{
				board[ny][nx] = new bowman(nx,ny,d);
				bocoordinate[p] = nx;
				bocoordinate[p + 1] = ny;
			}
			if (in == "C")
			{
				board[ny][nx] = new cavalrty(nx,ny,d);
				cacoordinate[q][0] = nx;
				cacoordinate[q][1] = ny;
				q++;
			}
	}
	int wj = 0, wp = 0, wq = 0;
	for (int i = 0; i < 5; i++)
	{
		ifs >> in >> nx >> ny >> d;
		if (in == "I")
		{
			winposi[ny][nx] = new infantry(nx, ny, d);
			winincoordinate[j][0] = nx;
			winincoordinate[j][1] = ny;
			wj++;
		}
		if (in == "B")
		{
			winposi[ny][nx] = new bowman(nx, ny, d);
			winbocoordinate[p] = nx;
			winbocoordinate[p + 1] = ny;
		}
		if (in == "C")
		{
			winposi[ny][nx] = new cavalrty(nx, ny, d);
			wincacoordinate[q][0] = nx;
			wincacoordinate[q][1] = ny;
			wq++;
		}
	}
	initialposit = board;
	ifs.close();
	wifs.close();
}
void chessboard::wincondition()
{
	cout << "----------------------------------------------" << endl;
	for (int i = 0; i < height; i++)
	{
		for (int t = 0; t < width; t++)
		{
			if (winposi[i][t] == nullptr)cout << "*"<<" ";
			if (dynamic_cast<infantry*>(winposi[i][t]))cout << "I"<<" ";
			if (dynamic_cast<bowman*>(winposi[i][t]))cout << "B"<<" ";
			if (dynamic_cast<cavalrty*>(winposi[i][t]))cout << "C"<<" ";
		}
		cout << endl;
	}
}
void chessboard::getwincoor()
{
	int j = 0, p = 0, q = 0;
	for (int i = 0; i < height; i++)
	{
		for (int t = 0; t < width; t++)
		{
			if (winposi[i][t] == nullptr){}
			else if (dynamic_cast<infantry*>(winposi[i][t]))
			{
				winincoordinate[j][0] = t;
				winincoordinate[j][1] = i;
				j++;
			}
			else if (dynamic_cast<bowman*>(winposi[i][t]))
			{
				winbocoordinate[p] = t;
				winbocoordinate[p + 1] = i;
			}
			else if (dynamic_cast<cavalrty*>(winposi[i][t]))
			{
				wincacoordinate[q][0] = t;
				wincacoordinate[q][1] = i;
				q++;
			}
		}
	}
}
void chessboard::printboard()
{
	cout << "----------------------------------------------"<<endl;
	for (int i = 0; i < height; i++)
	{
		for (int t = 0; t < width; t++)
		{
			if (board[i][t] == nullptr)cout << "*"<<" ";
			if (dynamic_cast<infantry*>(board[i][t]))cout << "I"<<" ";
			if (dynamic_cast<bowman*>(board[i][t]))cout << "B"<<" ";
			if (dynamic_cast<cavalrty*>(board[i][t]))cout << "C"<<" ";
		}
		cout << endl;
	}
}
bool chessboard::checksuccess()
{
	for (int i = 0; i < height; i++)
	{
		for (int t = 1; t < width; t++)
		{
			if (board[i][t] == nullptr && winposi[i][t] == nullptr)continue;
			else if (board[i][t] != nullptr && winposi[i][t] != nullptr)
			{
					if (dynamic_cast<infantry*>(board[i][t]) && dynamic_cast<infantry*>(winposi[i][t]))continue;
					else if (dynamic_cast<bowman*>(board[i][t]) && dynamic_cast<bowman*>(winposi[i][t]))continue;
					else if (dynamic_cast<cavalrty*>(board[i][t]) && dynamic_cast<cavalrty*>(winposi[i][t]))continue;
					else return 1;
			}
			else return 1;
		}
	}
	return 0;
}
void chessboard::reset()
{
	board = initialposit;
	getcoor();
}
void chessboard::getcoor()
{
	int j = 0, p = 0, q = 0;
	for (int i = 0; i < height; i++)
	{
		for (int t = 0; t < width; t++)
		{
			if (dynamic_cast<infantry*>(board[i][t]))
			{
				incoordinate[j][0] = t;
				incoordinate[j][1] = i;
				j++;
			}
			else if (dynamic_cast<bowman*>(board[i][t]))
			{
				bocoordinate[p] = t;
				bocoordinate[p + 1] = i;
			}
			else if (dynamic_cast<cavalrty*>(board[i][t]))
			{
				cacoordinate[q][0] = t;
				cacoordinate[q][1] = i;
				q++;
			}
		}
	}
}
void chessboard::useroperate()
{
	cout << "目标棋盘为:" << endl;
	wincondition();
	int i = 1;
	while (checksuccess())
	{
		getcoor();
		instate1 = State(board, 0, { incoordinate[0][1],incoordinate[0][0] });
		instate2 = State(board, 0, { incoordinate[1][1],incoordinate[1][0] });
		castate1 = State(board, 0, { cacoordinate[0][1],cacoordinate[0][0] });
		castate2 = State(board, 0, { cacoordinate[1][1],cacoordinate[1][0] });
		board[incoordinate[1][1]][incoordinate[1][0]]->setx(incoordinate[1][0]);
		board[incoordinate[1][1]][incoordinate[1][0]]->sety(incoordinate[1][1]);
		board[incoordinate[0][1]][incoordinate[0][0]]->setx(incoordinate[0][0]);
		board[incoordinate[0][1]][incoordinate[0][0]]->sety(incoordinate[0][1]);
		board[bocoordinate[1]][bocoordinate[0]]->setx(bocoordinate[0]);
		board[bocoordinate[1]][bocoordinate[0]]->sety(bocoordinate[1]);
		board[cacoordinate[1][1]][cacoordinate[1][0]]->setx(cacoordinate[1][0]);
		board[cacoordinate[1][1]][cacoordinate[1][0]]->sety(cacoordinate[1][1]);
		board[cacoordinate[0][1]][cacoordinate[0][0]]->setx(cacoordinate[0][0]);
		board[cacoordinate[0][1]][cacoordinate[0][0]]->sety(cacoordinate[0][1]);
		int num;
		int whichob=0;
		printboard();
		cout << "----------------------------------------------" << endl;
		if (i == 1)
		{
			cout << "此时两个步兵的坐标分别为:(" << incoordinate[0][0] << "," << incoordinate[0][1] << "),(" << incoordinate[1][0] << "," << incoordinate[1][1] << ")";
			cout << endl;
			cout << "此时两个步兵的前进方向分别为:" << board[incoordinate[0][1]][incoordinate[0][0]]->returndir() << "," << board[incoordinate[1][1]][incoordinate[1][0]]->returndir();
			cout << endl;
			cout << "请输入你要操作的步兵对象(1为第一个坐标表示的步兵，2为第二个坐标表示的步兵, 5为跳过本回合操作，0为重置游戏):";
			cin >> whichob;
			if (whichob==2)
			{
				cout << "是否需要提示?(1为需要，2为不需要)";
				cin >> whichob;
				if (whichob == 1)
				{
					winx = winincoordinate[1][0];
					winy = winincoordinate[1][1];
					ingiveHint(instate2);
				}
				cout << "请输入该步兵前进的步数:";
				cin >> num;
				board[incoordinate[1][1]][incoordinate[1][0]]->walk(height,width,num, board);
			}
			else if(whichob==1)
			{
				cout << "是否需要提示?(1为需要，2为不需要)";
				cin >> whichob;
				if (whichob == 1)
				{
					winx = winincoordinate[0][0];
					winy = winincoordinate[0][1];
					ingiveHint(instate1);
				}
				cout << "请输入该步兵前进的步数:";
				cin >> num;
				board[incoordinate[0][1]][incoordinate[0][0]]->walk(height, width, num, board);
			}
			else if (whichob == 0)
			{
				reset();
				i = 1;
				continue;
			}
			i=2;
			movecounter++;
			continue;
		}
		if (i == 2)
		{
			int t = 0;
			int option = 1;
			cout << "此时弓箭手的坐标为:(" << bocoordinate[0] << "," << bocoordinate[1] << ")";
			cout << endl;
			cout << "此时弓箭手的面向方向为:" << board[bocoordinate[1]][bocoordinate[0]]->returndir();
			cout << endl;
			cout << "请输入你想弓箭手所射击的方向（1为往下,2为往左,3为往上,4为往右,5为跳过本回合操作,6为给予提示，0为重置游戏):";
			cin >> t;
			switch (t)
			{
			case 1:
				option = 1;
				break;
			case 2:
				option = 2;
				break;
			case 3:
				option = 3;
				break;
			case 4:
				option = 4;
				break;
			case 5:
				break;
			default:
				cout << "错误的输入！请重新输入";
				i = 1;
				break;
			}
			if (t == 1 || t == 2 || t == 3 || t == 4)
			{
				board[bocoordinate[1]][bocoordinate[0]]->shoot(height,width,option, board);
			}
			else if (t == 0)
			{
				reset();
				i = 1;
				continue;
			}
			else if(t==5)
			{
				i = 3;
				continue;
			}
			else if (t == 6)
			{
				cout << "弓箭手射击暂无提示，请自行决定是否射击与射击方向" << endl;
				i = 2;
				continue;
			}
			i=3;
			movecounter++;
			continue;
		}
		if (i == 3)
		{
			cout << "此时两个骑兵的坐标分别为:(" << cacoordinate[0][0] << "," << cacoordinate[0][1] << "),(" << cacoordinate[1][0] << "," << cacoordinate[1][1] << ")";
			cout << endl;
			cout << "此时两个骑兵的前进方向分别为:" << board[cacoordinate[0][1]][cacoordinate[0][0]]->returndir() << "," << board[cacoordinate[1][1]][cacoordinate[1][0]]->returndir();
			cout << endl;
			cout << "请输入你要操作的骑兵对象(1为第一个坐标表示的步兵，2为第二个坐标表示的步兵, 5为跳过本回合操作，6为给予提示，0为重置游戏):";
			cin >> whichob;
			cout << "是否需要该骑兵转向?(0为不转向,1为转向):";
			bool decision = 0;
			cin >> decision;
			if (whichob == 2)
			{
				cout << "是否需要提示?(1为需要，2为不需要)";
				cin >> whichob;
				if (whichob == 1)
				{
					winx = wincacoordinate[1][0];
					winy = wincacoordinate[1][1];
					cagiveHint(castate2);
				}
				cout << "请输入该骑兵前进的步数";
				cin >> num;
				board[cacoordinate[1][1]][cacoordinate[1][0]]->dirdecide(decision);
				board[cacoordinate[1][1]][cacoordinate[1][0]]->walk(height, width, num, board);
			}
			else if (whichob == 1)
			{
				cout << "是否需要提示?(1为需要，2为不需要)";
				cin >> whichob;
				if (whichob == 1)
				{
					winx = wincacoordinate[0][0];
					winy = wincacoordinate[0][1];
					cagiveHint(castate1);
				}
				cout << "请输入该骑兵前进的步数";
				cin >> num;
				board[cacoordinate[0][1]][cacoordinate[0][0]]->dirdecide(decision);
				board[cacoordinate[0][1]][cacoordinate[0][0]]->walk(height, width, num, board);
			}
			else if (whichob == 0)
			{
				reset();
				i = 1;
				continue;
			}
			i=1;
			movecounter++;
			continue;
		}
	}
	cout << "你赢了！" << endl;
	cout << "此次所用步数为:" << movecounter << endl;
}


