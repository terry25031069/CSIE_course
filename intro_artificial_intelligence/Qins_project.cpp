#include<bits/stdc++.h>
#define F first
#define S second
#define MP make_pair
using namespace std;
struct state_node{
	public:
		bool has_f = 1;
		int board[16][16] = {};
		int f_board[16][16] = {};
		vector<state_node> childs;
		int step = 0;
		int h = 0;
		bool operator<(const state_node &x)const{
			return step<x.step;
		}
};
int n, d1, ch, maxstate;
int is_goal(state_node x){
	int queen_num = 0;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (x.board[i][j]==1) queen_num++;
	if (queen_num==n) return 1;
	return 0;
}
void expend(state_node *rt){
	int can_board[16][16] = {};
	int can_num = 0;
	state_node child;
	child.step = rt->step+1;
	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++){
			child.board[i][j] = rt->board[i][j];
			child.f_board[i][j] = rt->board[i][j];
			if (rt->board[i][j]==1){
				for (int k=0;k<n;k++){
					can_board[i][k] = can_board[k][j] = 1;
					if (i+k<n&&j+k<n) can_board[i+k][j+k] = 1;
					if (i+k<n&&j-k>=0) can_board[i+k][j-k] = 1;
					if (i-k>=0&&j+k<n) can_board[i-k][j+k] = 1;
					if (i-k>=0&&j-k>=0) can_board[i-k][j-k] = 1;
				}
			}
		}
	}
	int bo=0; 
	for (int i=0;i<n;i++){
		bo=0;
		for (int j=0;j<n;j++)
			if (child.board[i][j]) bo=1;
		if (bo==0){
			for (int j=0;j<n;j++){
				if (can_board[i][j] == 0){
					child.board[i][j] = 1;
					rt->childs.push_back(child);
					child.board[i][j] = 0;
				}
			}
			break;
		}
	}
	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++){
			if (can_board[i][j] == 0) can_num++;
			if (rt->board[i][j] == 1) can_num+=8;
		}
	}
//	能放皇后的地方越多，h就越小 
	if (rt->childs.empty()) rt->h = 0;
	else {
		rt->h = (n*n)-can_num;
		if (rt->h == 0) rt->h = 1e9+9;
	}
//		rt->h = can_num;
}
int DLS(state_node rt, int li){
	int re=0;
	if (li==0) return 0;
	if (is_goal(rt)) return 1;
	expend(&rt);
	if (rt.childs.empty()) return 0;
	for (auto i:rt.childs){
		re += DLS(i, li-1);
		if (re) return re;
	}
	return re;
}
int IDS(state_node rt, int li){
	maxstate = 0;
	for (int i=0;i<=li;i++){
		if(DLS(rt, i)) return i-1;
	}
	return -1;
}
int UCS(state_node rt){
	queue<state_node> q;
	q.push(rt);
	maxstate = 0;
	while(q.size()){
		maxstate = max((int)q.size(), maxstate);
		state_node now_state = q.front();
		q.pop();
		if (is_goal(now_state)) return now_state.step;
		expend(&now_state);
		for (auto i:now_state.childs){
			q.push(i);
		}
	}
	return -1;
}
typedef pair<int, state_node> pis_n;

int GBFS(state_node rt){
	maxstate = 0;
	priority_queue<pis_n, vector<pis_n>, greater<pis_n> > pq;
	expend(&rt);
	pq.push(MP(rt.h, rt));
	while(pq.size()){
		maxstate = max((int)pq.size(), maxstate);
		state_node now_state = pq.top().S;
		pq.pop();
		if (is_goal(now_state)) return now_state.step;
		for (auto i:now_state.childs){
			expend(&i);
			pq.push(MP(i.h, i));
		}
	}
	return -1;
}

int ASTAR(state_node rt){
	maxstate = 0;
	priority_queue<pis_n, vector<pis_n>, greater<pis_n> > pq;
	expend(&rt);
	pq.push(MP(rt.h+rt.step, rt));
	while(pq.size()){
		maxstate = max((int)pq.size(), maxstate);
		state_node now_state = pq.top().S;
		pq.pop();
		if (is_goal(now_state)) return now_state.step;
		for (auto i:now_state.childs){
			expend(&i);
			pq.push(MP(i.h+i.step, i));
		}
	}
	return -1;
}
int RBFS(state_node rt){
	maxstate = 0;
	priority_queue<pis_n, vector<pis_n>, greater<pis_n> > q;
	expend(&rt);
	q.push(MP(rt.h, rt));
	while(q.size()){
		maxstate = max(maxstate, (int)q.size());
		auto now_node = q.top();
		q.pop();
		if (is_goal(now_node.S)) return now_node.S.step;
		pis_n min_son;
		min_son.F = 1e9+7;
		if (now_node.S.has_f){
			state_node f_node;
			for (int i=0;i<n;i++)
				for (int j=0;j<n;j++)
					f_node.board[i][j] = now_node.S.f_board[i][j];
			f_node.step = now_node.S.step-1;
			expend(&f_node);
			for (state_node i:f_node.childs){
				int boo = 1;
				for (int j=0;j<n;j++)
					for (int k=0;k<n;k++)
						if(i.board[j][k]!=now_node.S.board[j][k]) boo = 0;
				if(boo) continue;
				if(i.h<min_son.F) min_son = MP(i.h, i);
			}
			if (min_son.F!=1e9+7&&(q.empty()||q.top().F<=min_son.F)){
				q.push(min_son);
			}
		}
		min_son.F = 1e9+7;
		expend(&now_node.S);
		for (auto i:now_node.S.childs){
			if(i.h<min_son.F) min_son = MP(i.h, i);
		}
		if(min_son.F!=1e9+7&&(q.empty()||q.top().F<=min_son.F)){
			q.push(min_son);
		}
		else now_node.S.h = min_son.F;
	}
	return -1;
}

int main(){
	cout << "請輸入 8 or 15\n";
	cin >> n;
	cout << "請輸入初始棋盤\n";
	state_node rt;
	rt.has_f = 0;
	for (int i=0;i<n;i++){
		cin >> d1;
		for (int j=0;j<n;j++){
			if (d1&&j==d1-1) rt.board[i][j]=1;
			else rt.board[i][j]=0;
		}
	}
	cout << "請輸入搜尋方法。\n"
		<< "1. Iterative-Deepening Search (IDS)\n"
		<< "2. Uniform-Cost Search\n"
		<< "3. Greedy Best-First Search\n"
		<< "4. A* search\n"
		<< "5. Recursive Best-First Search (RBFS)\n";
	cin >> ch;
	if (ch==1){
		cout << "請輸入IDS的最大深度。\n";
		int li; cin >> li;
		int tmp = IDS(rt, li+1);
		if (tmp==-1) cout << "Can't achieve goal with maximun limit is " << li << "\n";
		else cout << "The number of movements： " << tmp << "\n";
		cout << "The maximum number of states： " << tmp+1 << "\n";
	}
	else if (ch==2){
		int tmp = UCS(rt);
		if (tmp==-1) cout << "Can't achieve goal\n";
		else cout << "The number of movements： " << tmp << "\n";
		cout << "The maximum number of states： " << maxstate << "\n";
	}
	else if (ch==3){
		int tmp = GBFS(rt);
		if (tmp==-1) cout << "Can't achieve goal\n";
		else cout << "The number of movements： " << tmp << "\n";
		cout << "The maximum number of states： " << maxstate << "\n";
	}
	else if (ch==4){
		int tmp = ASTAR(rt);
		if (tmp==-1) cout << "Can't achieve goal\n";
		else cout << "The number of movements： " << tmp << "\n";
		cout << "The maximum number of states： " << maxstate << "\n";
	}
	else if (ch==5){
		int tmp = RBFS(rt);
		if (tmp==-1) cout << "Can't achieve goal\n";
		else cout << "The number of movements： " << tmp << "\n";
		cout << "The maximum number of states： " << maxstate << "\n";
	}
} 

/*
8
4
1
3
6
2
7
0
*/
