#include<bits/stdc++.h>
using namespace std;

double dis[205][205];

int main(){
	cout<<fixed<<setprecision(3);
	int n,m,a,b;double c;
	while(cin>>n>>m){
		for(int i=1;i<205;i++){
			for(int j=1;j<205;j++){
				if(i!=j)dis[i][j]=100000;
				else dis[i][j]=0;
			}
		}
		for(int i=1;i<=m;i++){
			cin>>a>>b>>c;
			dis[a][b]=min(dis[a][b],c);
		}
		for(int k=1;k<=n;k++){
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++){
					if(dis[i][k]+dis[k][j]<dis[i][j])dis[i][j]=dis[i][k]+dis[k][j];
				}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(dis[i][j]!=100000)cout<<dis[i][j]<<' ';
				else cout<<"N ";
			}
			cout<<endl;
		}
	}
}

