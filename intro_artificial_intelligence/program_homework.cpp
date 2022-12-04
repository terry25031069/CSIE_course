#include<bits/stdc++.h>
using namespace std;
#define int long long
#define F first
#define S second
typedef pair<int, int> pii;

int fac[17] = {1, 1}, maxstatus = 0, tmpcoord;
map<int, int> visit;
vector<int> goal;
vector<vector<int>> op[17]; 

struct node{
	int c;
	vector<int>st, f;
	bool operator < (const node &x) const{
		return x.c < c;
	}	
};
typedef pair<int, node> pir;

void print(vector<int> a){
	for(auto i: a)cout << i << ' ';
	cout << endl;
}

int khash(vector<int>a){
	int t, sum = 0, n = a.size();
	for(int i = 0; i < n; i++){
		t = 0;
		for(int j = i + 1; j < n; j++) t += (a[i] > a[j]);
		sum += t * fac[n - i - 1];
	}
	return sum;
}

int mdis(vector<int>a, vector<int>b){
	int dis = 0;
	for(int i = 0; i < a.size(); i++){
		int coorda, coordb;
		for(int j = 0; j < a.size(); j++){
			if(a[j] == i) coorda = j;
			if(b[j] == i) coordb = j;
			
		} 
		dis += abs(coorda / 3 - coordb / 3) + abs(coorda % 3 - coordb % 3);
	}
	return dis;
}

vector<int> rkhash(int num, int vsize){
	vector<int>a, ans;
	for(int i = 0; i <= vsize - 1; i++)a.push_back(i);
	for(int i = vsize - 1; i > 0; i--){
		int r = num % fac[i], t = num / fac[i];
		num = r;
		ans.push_back(a[t]);
		a.erase(a.begin() + t);
	}
	ans.push_back(a[0]);
	return ans;
}

int DLS(vector<int>a, int parent, int coord, int limit){
	int ans = 0, ii;
	if(khash(goal) == khash(a))return 1;
	//recursive
	for(auto move: op[a.size()][coord]){
		vector<int>b = a;
		swap(b[coord], b[move]);
		if(khash(b) != parent && limit > 0){
			ans = max(ans, DLS(b, khash(a), move, limit - 1));
		}
		if(ans == 1) return 1;
	}
	return ans;
}

int IDS(vector<int>a, int coord){
	for(int limit = 0; limit < 30; limit++){
		cout << "Current limit is " << limit << endl;
		int result = DLS(a, khash(a), coord, limit);
		maxstatus = limit + 1;
		if(result == 1) return limit;
	}
	return -1;
}

int BFS(vector<int>a, int coord){
	// push the initial status
	queue<pii>status; status.push({coord, khash(a)}); visit[khash(a)] = 1;
	if(khash(a) == khash(goal)) return visit[khash(a)] - 1;
	//BFS algorithm
	while(!status.empty()){
		vector<int>top = rkhash(status.front().S, a.size());
		tmpcoord = 0;
		for(int i = 0; i < top.size(); i++){
			if(top[i] == 0) tmpcoord = i;
		}
		for(auto move: op[top.size()][tmpcoord]){
			vector<int>b = top;
			swap(b[status.front().F], b[move]);
			if(!visit[khash(b)]){
				status.push({move, khash(b)});
				visit[khash(b)] = visit[khash(top)] + 1;
				if(khash(b) == khash(goal))return visit[khash(b)] - 1;
 			}
		}
		status.pop();
		maxstatus = max(maxstatus, (int)visit.size());
	}
	return -1;
}

int GBFS(vector<int>a, int mode){
	//combine GBFS and Astar in same function
	//if mode == 3, then GBFS, if mode == 4, then Astar.
	priority_queue<pii, vector<pii>, greater<pii> > status;
	status.push({mdis(a, goal) + (mode == 4) * 1, khash(a)}); 
	visit[khash(a)] = 1;
	//BFS algorithm with priority queue sorted by manhattan distance
	while(!status.empty()){
		vector<int>top = rkhash(status.top().S, a.size());
		status.pop();
		for(int i = 0; i < top.size(); i++){
			if(top[i] == 0) tmpcoord = i;
		}
		for(auto move: op[top.size()][tmpcoord]){
			vector<int>b = top;
			swap(b[tmpcoord], b[move]);
			if(!visit[khash(b)]){
				visit[khash(b)] = visit[khash(top)] + 1;
				status.push({mdis(b, goal) + visit[khash(b)] * (mode == 4), khash(b)});
				if(khash(b) == khash(goal))return visit[khash(b)] - 1;
 			}
		}
		maxstatus = max(maxstatus, (int)visit.size());
	}
	return -1;
}

int RBFS(vector<int>a){
	priority_queue<pir, vector<pir>, greater<pir> >status;
	node ptmp; ptmp.c = 0, ptmp.st = a;
	status.push({mdis(a, goal), ptmp});
	visit[khash(a)] = mdis(a, goal);
	
	while(!status.empty()){
		maxstatus = max(maxstatus, (int)status.size());
		auto tmp = status.top(); status.pop();
		visit.erase(khash(tmp.S.st));
		if(khash(tmp.S.st) == khash(goal)) return tmp.S.c;
		vector<int> cur_node = tmp.S.st, f_node = tmp.S.f;
		pii min_child; min_child.F = 1e9;
		if(!f_node.empty()){
			for(int i = 0; i < f_node.size(); i++){
				if(f_node[i] == 0) tmpcoord = i;
			}
			for(auto move: op[f_node.size()][tmpcoord]){
				vector<int>b = f_node;
				swap(b[tmpcoord], b[move]);
				if(khash(b) == khash(cur_node)) continue;
				if(visit[khash(b)] == 0) visit[khash(b)] = mdis(b, goal) + tmp.S.c + 1;
				if(visit[khash(b)] < min_child.F) min_child = {visit[khash(b)], khash(b)};
			}
			if(status.empty() || status.top().F >= min_child.F){
				ptmp.c = tmp.S.c, ptmp.f = tmp.S.f, ptmp.st = rkhash(min_child.S, a.size());
				status.push({min_child.F, ptmp});
			}
		}
		min_child.F = 1e9;
		for(int i = 0; i < cur_node.size(); i++){
			if(cur_node[i] == 0) tmpcoord = i;
		}
		for(auto move: op[cur_node.size()][tmpcoord]){
			vector<int>b = cur_node;
			swap(b[tmpcoord], b[move]);
			if(khash(b) == khash(cur_node)) continue;
			if(visit[khash(b)] == 0) visit[khash(b)] = mdis(b, goal) + tmp.S.c + 1;
			if(visit[khash(b)] < min_child.F) min_child = {visit[khash(b)], khash(b)};
		}
		if(status.empty() || status.top().F >= min_child.F){
			ptmp.c = tmp.S.c + 1, ptmp.f = tmp.S.st, ptmp.st = rkhash(min_child.S, a.size());
			status.push({min_child.F, ptmp});
		}else visit[khash(cur_node)] = min_child.F;
	}
	return -1;
}

int32_t main(){
	// init
	int tc, tmpinput;
	string s;
	for(int i = 2; i < 16; i++) fac[i] = fac[i-1] * i;
	//opeartions for 8-puzzles
	op[9].resize(9);
	op[9] =  {{1, 3}, {0, 2, 4}, {1, 5}, {0, 4, 6}, {1, 3, 5, 7}, {2, 4, 8}, {3, 7}, {4, 6, 8}, {5, 7}};
	//opeartions for 15-puzzles
	op[16].resize(16);
	op[16] = {{1, 4}, {0, 2, 5}, {1, 3, 6}, {2, 7}, {0, 5, 8}, {1, 4, 6, 9}, 
	 {2, 5, 7, 10},{3, 6, 11}, {4, 9, 12}, {5, 8, 10, 13}, {6, 9, 11, 14}, 
	 {7, 10, 15}, {8, 13}, {9, 12, 14}, {10, 13, 15}, {11, 14}};	
	
	// main UI
	while(getline(cin, s)){
		vector<int>a, b;
		visit.clear(); 
		stringstream ss; ss.str(s); 
		while(ss >> tmpinput) a.push_back(tmpinput);
		b = a; sort(b.begin(), b.end());
		int tmpsum = 0;
		for(auto i: b)tmpsum += i;
		if(!((b.size() == 9 || b.size() == 16) && (b[0] == 0) && (b[b.size() - 1] == b.size() - 1)
			&& (tmpsum == b.size() * (b.size() - 1) / 2))){
			cout << "The puzzle format is not correct, plz re-enter the puzzle!\n";		
		}else{
			if(a.size() == 9) goal = {5, 8, 6, 0, 7, 4, 2, 3, 1};
			else goal = {7, 14, 11, 5, 8, 12, 13, 10, 2, 0, 4, 15, 6, 3, 9, 1};
			cout << "Choose a algorithm to execute the puzzle.\n";
			cout << "(1). Iterative-Deepening Search(IDS)\n";
			cout << "(2). Uniform-Cost Search\n";
			cout << "(3). Greedy Best-First Search\n";
			cout << "(4). A* Search\n";
			cout << "(5). Recursive Best-First Search(RBFS)\n";
			while(cin >> tc){
				getline(cin, s);
				//init before each algorithm
				maxstatus = -1;
				visit.clear();
				for(int i = 0; i < a.size(); i++){
					if(a[i] == 0) tmpcoord = i;
				}
				
				//each algorithm
				if(tc < 0 || tc > 5){
					cout << "The command is invaild, plz enter the correct command.";
					continue;
				}else{
					int ans;
					if(tc == 1){
						ans = IDS(a, tmpcoord);
					}else if(tc == 2){
						ans = BFS(a, tmpcoord);
					}else if(tc == 3 || tc == 4){
						ans = GBFS(a, tc);
					}else{
						ans = RBFS(a);
					}
					if(ans >= 0)cout << "Total moves: " << ans << endl;
					else cout << "The puzzle is not solvable!\n";
					cout << "The maximum number of states during the process is: " << maxstatus << endl;
					break;
				}
			}
		}
	}
}
