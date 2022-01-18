#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second
typedef pair<int, int> pii;

int len = 8, ans, maxstatus;

struct node{
	int board[16][16] = {};
	int pboard[16][16] = {};
	int step = 0;
	int hvalue = 0;
	vector<node>child;
	bool operator < (const node &b)const{
		if(step != b.step)return step > b.step;
	}
};

void print(int a[16][16]){
	for(int i = 0; i < len; i++){
		for(int j = 0; j < len; j++){
			cout << a[i][j] << " \n"[j == len - 1];
		}
	}
	cout << endl;
}

bool checkgoal(node tmpnode){
	int tmp = 0;
	for(int i = 0; i < len; i++){
		for(int j = 0; j < len; j++){
			tmp += (tmpnode.board[i][j]);	
		}
	}
	return (tmp == len);
}

void expand(node *a){
	int tmpboard[16][16] = {};
	int cnt = 0;
	node child; child.step = a->step + 1;
	for (int i = 0; i < len; i++){
		for (int j = 0; j < len; j++){
			child.board[i][j] = child.pboard[i][j] = a->board[i][j];
			if (a->board[i][j]){
				for (int k = 0; k < len; k++){
					tmpboard[i][k] = tmpboard[k][j] = 1;
					if (i + k < len && j + k < len) tmpboard[i+k][j+k] = 1;
					if (i + k < len && j - k > -1) tmpboard[i+k][j-k] = 1;
					if (i - k > -1 && j + k < len) tmpboard[i-k][j+k] = 1;
					if (i - k >- 1 && j - k > -1) tmpboard[i-k][j-k] = 1;
				}
			}
		}
	}
	for (int i = 0; i < len; i++){
		for (int j = 0; j < len; j++){
			if(tmpboard[i][j] == 0){
				child.board[i][j] = 1;
				a->child.push_back(child);
				child.board[i][j] = 0;
				cnt++;
			}
			if(a->board[i][j] == 1) cnt += 8;
		}
	}
	if (a->child.empty()) a->hvalue = 0;
	else {
		//maybe has bug
		a->hvalue = len * len - cnt + (!a->hvalue) * 1e9;
	}
}

int DLS(node a, int limit){
	int ans = 0, ii;
	if(limit == 0) return 0;
	if(checkgoal(a) == 1){
		print(a.board); return 1;
	}
	//if not use pointer, then the result will only save into the local variable. 
	expand(&a);
	int result = 0;
	//cout << "The node has " << a.child.size() << " childs!\n";
	for(auto i:a.child){
		result |= DLS(i, limit - 1);
		if(result)break;
	}
	return result;
}

int IDS(node a){
	for(int limit = 8; limit < 30; limit++){
		cout << "Current limit is " << limit << endl;
		int result = DLS(a, limit);
		maxstatus = limit + 1;
		if(result == 1) return limit;
	}
	return -1;
}

int BFS(node a){
	// push the initial status
	queue<node>status;
	status.push(a);
	//BFS algorithm
	while(!status.empty()){
		node top = status.front(); status.pop();
		if(checkgoal(top)){
			print(top.board); return 1;
		}
		expand(&top);
		for(auto i: top.child) status.push(i);
		maxstatus = max(maxstatus, (int)status.size());
	}
	return -1;
}

int GBFS(node a, int mode){
	//combine GBFS and Astar in same function
	//if mode == 3, then GBFS, if mode == 4, then Astar.
	priority_queue<node> status;
	expand(&a);
	a.hvalue += (mode == 4) * a.step;
	status.push(a); 
	//BFS algorithm with priority queue sorted by hvalue
	while(!status.empty()){
		node top = status.top(); status.pop();
		if(checkgoal(top)){
			print(top.board); return 1;
		}
		for(auto i: top.child){
			expand(&i);
			i.hvalue += (mode == 4) * i.step;
			status.push(i);
		}
		maxstatus = max(maxstatus, (int)status.size());
	}
	return -1;
}

//int RBFS(node a){
//	priority_queue<pir, vector<pir>, greater<pir> >status;
//	node ptmp; ptmp.c = 0, ptmp.st = a;
//	status.push({mdis(a, goal), ptmp});
//	visit[khash(a)] = mdis(a, goal);
//	
//	while(!status.empty()){
//		maxstatus = max(maxstatus, (int)status.size());
//		auto tmp = status.top(); status.pop();
//		visit.erase(khash(tmp.S.st));
//		if(khash(tmp.S.st) == khash(goal)) return tmp.S.c;
//		vector<int> cur_node = tmp.S.st, f_node = tmp.S.f;
//		pii min_child; min_child.F = 1e9;
//		if(!f_node.empty()){
//			for(int i = 0; i < f_node.size(); i++){
//				if(f_node[i] == 0) tmpcoord = i;
//			}
//			for(auto move: op[f_node.size()][tmpcoord]){
//				vector<int>b = f_node;
//				swap(b[tmpcoord], b[move]);
//				if(khash(b) == khash(cur_node)) continue;
//				if(visit[khash(b)] == 0) visit[khash(b)] = mdis(b, goal) + tmp.S.c + 1;
//				if(visit[khash(b)] < min_child.F) min_child = {visit[khash(b)], khash(b)};
//			}
//			if(status.empty() || status.top().F >= min_child.F){
//				ptmp.c = tmp.S.c, ptmp.f = tmp.S.f, ptmp.st = rkhash(min_child.S, a.size());
//				status.push({min_child.F, ptmp});
//			}
//		}
//		min_child.F = 1e9;
//		for(int i = 0; i < cur_node.size(); i++){
//			if(cur_node[i] == 0) tmpcoord = i;
//		}
//		for(auto move: op[cur_node.size()][tmpcoord]){
//			vector<int>b = cur_node;
//			swap(b[tmpcoord], b[move]);
//			if(khash(b) == khash(cur_node)) continue;
//			if(visit[khash(b)] == 0) visit[khash(b)] = mdis(b, goal) + tmp.S.c + 1;
//			if(visit[khash(b)] < min_child.F) min_child = {visit[khash(b)], khash(b)};
//		}
//		if(status.empty() || status.top().F >= min_child.F){
//			ptmp.c = tmp.S.c + 1, ptmp.f = tmp.S.st, ptmp.st = rkhash(min_child.S, a.size());
//			status.push({min_child.F, ptmp});
//		}else visit[khash(cur_node)] = min_child.F;
//	}
//	return -1;
//}

int main(){
	// init
	int qnum, qtmpr, qtmpc;
	node start;
	cout << "Plz enter the number of queen:\n";
	// main UI
	while(1){
		cin >> qnum;
		if(qnum < 0 || qnum > 8){
			cout << "The number of queen is not correct, plz re-enter the number!\n";		
		}else{
			int tc;
			cout << "Plz enter the location of queens respectivity:\n";
			for(int i = 0; i < qnum; i++){
				cin >> qtmpr >> qtmpc;
				start.board[qtmpr][qtmpc] = 1;
			}
			print(start.board);
			cout << "Choose a algorithm to execute the answer.\n";
			cout << "(1). Iterative-Deepening Search(IDS)\n";
			cout << "(2). Uniform-Cost Search\n";
			cout << "(3). Greedy Best-First Search\n";
			cout << "(4). A* Search\n";
			cout << "(5). Recursive Best-First Search(RBFS)\n";
			while(cin >> tc){
				if(tc == 1){
					ans = IDS(start);
				}else if(tc == 2){
					ans = BFS(start);
				}else if(tc == 3 || tc == 4){
					ans = GBFS(start, tc);
				}else{
					//ans = RBFS(start);
				}
				if(ans >= 0)cout << "Total moves: " << ans << endl;
				else cout << "The puzzle is not solvable!\n";
				cout << "The maximum number of states during the process is: " << maxstatus << endl;
				break;
			}
		}
	}
}
