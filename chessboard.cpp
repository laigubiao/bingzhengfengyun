#include "chessboard.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <functional>
int winx1 = 0, winy1 = 0, winx2 = 0, winy2 = 0;
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
	std::vector<std::pair<int, int>> goalPositions = { {4, 4}, {3, 4} };
	for (size_t i = 0; i < state.Positions.size(); ++i) {
		cost += std::abs(state.Positions[i].first - goalPositions[i].first) +
			std::abs(state.Positions[i].second - goalPositions[i].second);
	}
	return cost;
}
bool isGoalState(const State& state) 
{
	std::vector<std::pair<int, int>> goalPositions = { {winx1,winy1}, {winx2, winy2} };
	for (size_t i = 0; i < state.board0.size(); ++i) 
	{
		for (size_t j = 0; j < state.board0[i].size(); ++j) 
		{
			if (state.board0[i][j] != nullptr && dynamic_cast<infantry*>(state.board0[i][j])) 
			{
				if (i != goalPositions[0].first || j != goalPositions[0].second) 
				{
					return false;
				}
			}
		}
	}
	return true;
}
std::vector<State> ingetNextStates(const State& state) 
{
	std::vector<State> nextStates;
	for (size_t i = 0; i < state.Positions.size(); ++i) 
	{
		int x = state.Positions[i].first;
		int y = state.Positions[i].second;
		direction heading = state.board0[y][x]->getdir(); 
		int newX = x, newY = y;
		switch (heading) {
		case direction::down:
			newY = y + 1;
			break;
		case direction::left:
			newX = x - 1;
			break;
		case direction::up:
			newY = y - 1;
			break;
		case direction::right:
			newX = x + 1;
			break;
		}
		if (newX >= 0 && newX < state.board0.size() && newY >= 0 && newY < state.board0.size() && state.board0[newY][newX] == nullptr) {
			std::vector<std::vector<chess*>> newBoard = state.board0;
			newBoard[newY][newX] = newBoard[y][x];
			newBoard[y][x] = nullptr;
			std::vector<std::pair<int, int>> newInfantryPositions = state.Positions;
			newInfantryPositions[i] = { newX, newY };
			nextStates.push_back(State(newBoard, state.moveCount + 1, newInfantryPositions));
		}
	}
	return nextStates;
}
std::vector<State> inaStarSearch(const State& initialState) 
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
		std::vector<State> nextStates = ingetNextStates(currentState);
		for (const auto& nextState : nextStates) 
		{
			if (std::find(visited.begin(), visited.end(), nextState) == visited.end()) 
			{
				visited.push_back(nextState);
				pq.push({ heuristic(nextState) + nextState.moveCount, nextState });
			}
		}
	}
	return {};
}
void ingiveHint(const State& initialState) 
{
	std::vector<State> path = inaStarSearch(initialState);
	if (!path.empty()) {
		State firstMove = path[0]; 
		for (size_t i = 0; i < initialState.Positions.size(); ++i) 
		{
			if (initialState.Positions[i] != firstMove.Positions[i]) 
			{
				std::cout << "提示：移动步兵 " << i + 1
					<< " 从 (" << initialState.Positions[i].first << ", " << initialState.Positions[i].second
					<< ") 到 (" << firstMove.Positions[i].first << ", " << firstMove.Positions[i].second << ")" << std::endl;
				return;
			}
		}
	}
	else {
		std::cout << "没有可用的提示。" << std::endl;
	}
}
std::vector<State> cagetNextStates(const State& state) {
	std::vector<State> nextStates;
	for (size_t i = 0; i < state.Positions.size(); ++i) {
		int x = state.Positions[i].first;
		int y = state.Positions[i].second;
		direction heading = state.board0[y][x]->getdir(); 
		int newX = x, newY = y;
		switch (heading) {
		case direction::down:
			newY = y + 1;
			break;
		case direction::left:
			newX = x - 1;
			break;
		case direction::up:
			newY = y - 1;
			break;
		case direction::right:
			newX = x + 1;
			break;
		}
		if (newX >= 0 && newX < state.board0.size() && newY >= 0 && newY < state.board0.size() && state.board0[newY][newX] == nullptr) {
			// 创建新状态
			std::vector<std::vector<chess*>> newBoard = state.board0;
			newBoard[newY][newX] = newBoard[y][x];
			newBoard[y][x] = nullptr;
			std::vector<std::pair<int, int>> newCavalryPositions = state.Positions;
			newCavalryPositions[i] = { newX, newY };
			nextStates.push_back(State(newBoard, state.moveCount + 1, newCavalryPositions));
		}
		direction newHeading;
		switch (heading) {
		case direction::down:
			newHeading = direction::up;
			break;
		case direction::left:
			newHeading = direction::right;
			break;
		case direction::up:
			newHeading = direction::down;
			break;
		case direction::right:
			newHeading = direction::left;
			break;
		}

		newX = x, newY = y;
		switch (newHeading) {
		case direction::down:
			newY = y + 1;
			break;
		case direction::left:
			newX = x - 1;
			break;
		case direction::up:
			newY = y - 1;
			break;
		case direction::right:
			newX = x + 1;
			break;
		}
		if (newX >= 0 && newX < state.board0.size() && newY >= 0 && newY < state.board0.size() && state.board0[newY][newX] == nullptr) {
			// 创建新状态
			std::vector<std::vector<chess*>> newBoard = state.board0;
			newBoard[newY][newX] = newBoard[y][x];
			newBoard[y][x] = nullptr;
			std::vector<std::pair<int, int>> newCavalryPositions = state.Positions;
			newCavalryPositions[i] = { newX, newY };
			nextStates.push_back(State(newBoard, state.moveCount + 1, newCavalryPositions));
		}
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
		std::vector<State> nextStates = cagetNextStates(currentState);
		for (const auto& nextState : nextStates) {
			if (std::find(visited.begin(), visited.end(), nextState) == visited.end()) {
				visited.push_back(nextState);
				pq.push({ heuristic(nextState) + nextState.moveCount, nextState });
			}
		}
	}
	return {};
}
void cagiveHint(const State& initialState) 
{
	std::vector<State> path = caaStarSearch(initialState);
	if (!path.empty()) 
	{
		State firstMove = path[0];
		for (size_t i = 0; i < initialState.Positions.size(); ++i) 
		{
			if (initialState.Positions[i] != firstMove.Positions[i])
			{
				std::cout << "提示：移动骑兵 " << i + 1
					<< " 从 (" << initialState.Positions[i].first << ", " << initialState.Positions[i].second
					<< ") 到 (" << firstMove.Positions[i].first << ", " << firstMove.Positions[i].second << ")" << std::endl;
				return;
			}
		}
	}
	else 
	{
		std::cout << "没有可用的提示。" << std::endl;
	}
}
chessboard::chessboard(vector<vector<chess*>>& initialposi, vector<vector<chess*>>& inwinposi) :board(initialposi), winposi(inwinposi), initialposit(initialposi)
{
	getcoor();
	getwincoor();
	instate = State(board, 0, { {incoordinate[0][1],incoordinate[0][0]},{incoordinate[1][1],incoordinate[1][0]} });
	castate = State(board, 0, { {cacoordinate[0][1],cacoordinate[0][0]},{cacoordinate[1][1],cacoordinate[1][0]} });
}
void chessboard::loadwithfile(ifstream& ifs)
{
	string in;
	int j = 0,p=0,q=0;
	for (int i = 0; i < 5; i++)
	{
		for (int t = 0; t < 5; t++)
		{
			ifs >> in;
			if (in == "*")board[i][t] = nullptr;
			if (in == "I")
			{
				board[i][t] = new infantry;
				board[i][t]->setx(t);
				board[i][t]->sety(i);
				incoordinate[j][0] = t;
				incoordinate[j][1] = i;
				j++;
			}
			if (in == "B")
			{
				board[i][t] = new bowman;
				board[i][t]->setx(t);
				board[i][t]->sety(i);
				bocoordinate[p] = t;
				bocoordinate[p + 1] = i;
			}
			if (in == "C")
			{
				board[i][t] = new cavalrty;
				board[i][t]->setx(t);
				board[i][t]->sety(i);
				cacoordinate[q][0] = t;
				cacoordinate[q][1] = i;
				q++;
			}
		}
	}
	initialposit = board;
}
void chessboard::wincondition()
{
	cout << "----------------------------------------------" << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int t = 0; t < 5; t++)
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
	for (int i = 0; i < 5; i++)
	{
		for (int t = 0; t < 5; t++)
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
	for (int i = 0; i < 5; i++)
	{
		for (int t = 0; t < 5; t++)
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
	for (int i = 0; i < 5; i++)
	{
		for (int t = 1; t < 5; t++)
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
	for (int i = 0; i < 5; i++)
	{
		for (int t = 0; t < 5; t++)
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
			cout << "请输入你要操作的步兵对象(1为第一个坐标表示的步兵，2为第二个坐标表示的步兵, 5为跳过本回合操作，6为给予提示，0为重置游戏):";
			cin >> whichob;
			cout << "请输入该步兵前进的步数:";
			cin >> num;
			if (whichob==2)
			{
				board[incoordinate[1][1]][incoordinate[1][0]]->walk(num, board);
			}
			else if(whichob==1)
			{
				board[incoordinate[0][1]][incoordinate[0][0]]->walk(num, board);
			}
			else if (whichob == 0)
			{
				reset();
				i = 1;
				continue;
			}
			else if (whichob == 6)
			{
				winx1 = winincoordinate[0][0];
				winy1 = winincoordinate[0][1];
				winx2 = winincoordinate[1][0];
				winy2 = winincoordinate[1][1];
				ingiveHint(instate);
			}
			i++;
			continue;
		}
		if (i == 2)
		{
			int t = 0;
			direction option = down;
			cout << "此时弓箭手的坐标为:(" << bocoordinate[0] << "," << bocoordinate[1] << ")";
			cout << endl;
			cout << "此时弓箭手的面向方向为:" << board[bocoordinate[1]][bocoordinate[0]]->returndir();
			cout << endl;
			cout << "请输入你想弓箭手所射击的方向（1为往下,2为往左,3为往上,4为往右,5为跳过本回合操作,6为给予提示，0为重置游戏):";
			cin >> t;
			switch (t)
			{
			case 1:
				option = down;
				break;
			case 2:
				option = direction::left;
				break;
			case 3:
				option = up;
				break;
			case 4:
				option = direction::right;
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
				board[bocoordinate[1]][bocoordinate[0]]->shoot(option, board);
			}
			else if (t == 5)
			{
				reset();
				i = 1;
				continue;
			}
			else if (t == 6)
			{
				cout << "弓箭手射击暂无提示，请自行决定是否射击与射击方向" << endl;
			}
			i++;
		}
		if (i == 1)
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
			cout << "请输入该骑兵前进的步数";
			cin >> num;
			if (whichob == 2)
			{
				board[cacoordinate[1][1]][cacoordinate[1][0]]->dirdecide(decision);
				board[cacoordinate[1][1]][cacoordinate[1][0]]->walk(num, board);
			}
			else if (whichob == 1)
			{
				board[cacoordinate[0][1]][cacoordinate[0][0]]->dirdecide(decision);
				board[cacoordinate[0][1]][cacoordinate[0][0]]->walk(num, board);
			}
			else if (whichob == 0)
			{
				reset();
				i = 1;
				continue;
			}
			else if (whichob == 6)
			{
				winx1 = wincacoordinate[0][0];
				winy1 = wincacoordinate[0][1];
				winx2 = wincacoordinate[1][0];
				winy2 = wincacoordinate[1][1];
				cagiveHint(castate);
			}
			i=1;
		}
	}
	cout << "你赢了！" << endl;
}


