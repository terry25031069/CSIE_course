#include<bits/stdc++.h>
using namespace std;

string s,command;
vector<string>a,a2;

bool check(){
	for(int i=0;i<a.size();i++){
		for(int j=0;j<a[i].size();j++){
			if(a2[i][j]=='E'){
				if(a[i][j]!='B')return 0;
			}
		}
	}
	return 1;
}

int main(int argc,char **argv){
	fstream file(argv[1],ios::in);
	if(!file){
		cout<<"檔案開啟失敗!";
		
	}
	system("cls");
	int dx[5]={0,-1,0,1,0},dy[5]={0,0,-1,0,1},x,y,ex,ey;
	int flag=0,com=0;stack<int>lcomm;
	map<string,int>comm;
	comm["w"]=1,comm["a"]=2,comm["s"]=3,comm["d"]=4;
	while(file>>s){
		for(int i=0;i<s.size()&&(!flag);i++){
			if(s[i]=='A'){
				x=a.size(),y=i,flag=1;
			}
		}
		a.push_back(s);
	}
	a2=a;
	for(int i=0;i<a.size();i++){
		for(int j=0;j<a[i].size();j++)cout<<a[i][j];
		cout<<endl;
	}
	cout<<endl;
	cout<<"請輸入指令(合法指令只有w(往上),a(往左),s(往下),d(往右)和大寫R(復原))\n";
	cout<<"(復原可以復原到第一步):"; 
	while(cin>>command){
		if(command!="w"&&command!="a"&&command!="s"&&command!="d"&&command!="R"){
			cout<<"輸入錯誤!\n";
		}
		else {
			if(command=="R"){
				if(lcomm.size()){
					int lcom=lcomm.top();lcomm.pop();
					a[x-dx[lcom]][y-dy[lcom]]='A';x-=dx[lcom],y-=dy[lcom];
					if(a[x+2*dx[com]][y+2*dy[com]]=='B'){
						a[x+dx[lcom]][y+dy[lcom]]='B';
						a[x+2*dx[lcom]][y+2*dy[lcom]]='*';
					}
					else{
						a[x+dx[lcom]][y+dy[lcom]]='*';
					}
				}
				else{
					cout<<"已經沒有上一步可以復原了QQ\n";
				}
			}
			else{
				com=comm[command];
				if(a[x+dx[com]][y+dy[com]]=='*'||a[x+dx[com]][y+dy[com]]=='E'){
					a[x][y]='*';
					x+=dx[com],y+=dy[com];
					a[x][y]='A';
					lcomm.push(com);
				}
				else if(a[x+dx[com]][y+dy[com]]=='B'&&(a[x+2*dx[com]][y+2*dy[com]]=='*'||a[x+2*dx[com]][y+2*dy[com]]=='E')){
					a[x+2*dx[com]][y+2*dy[com]]='B',a[x+dx[com]][y+dy[com]]='A';
					a[x][y]='*';x+=dx[com],y+=dy[com];
					lcomm.push(com);
				}
			}
		}
		system("cls");
		for(int i=0;i<a.size();i++){
			for(int j=0;j<a[i].size();j++){
				if(a[i][j]=='*'&&a2[i][j]=='E')a[i][j]=a2[i][j];
				cout<<a[i][j];
			}
			cout<<endl;
		}
		cout<<endl;
		if(check())break;
		cout<<"請輸入指令(合法指令只有w(往上),a(往左),s(往下),d(往右)和大寫R)\n";
		cout<<"(大寫R代表復原最後一個動作):";
	}
	cout<<"CONGRATULATIONS! YOU WIN THE GAME!\n";
}
