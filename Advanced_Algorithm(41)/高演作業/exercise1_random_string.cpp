#include<bits/stdc++.h>
using namespace std;

// CAUTION: the code is just referencial, not totally correct
// it might get wrong answer when the input is too small

int nn, k;
double p[1001], dp[1001], pi[1001];

double re(int n){
	if(dp[n] != -1) return dp[n];
	else{
		double ans = .0;
		for(int i = n-k+1; i <= n; i++){
			double tmp = 1 - p[i];
			for(int j = i + 1; j <= n; j++) tmp *= p[j];
			//ans += re(i-1) * (pi[n] / pi[i] - pi[n] / pi[i-1]);
			ans += re(i-1) * tmp;
		}	
		dp[n] = ans;
		return ans;
	} 
}

int main(){
	while(cin >> nn, nn){
		cin >> k;
		for(int i = 0; i < 1001; i++) dp[i] = -1, pi[i] = 1;
		for(int i = 1; i <= nn; i++) cin >> p[i], pi[i] = pi[i-1] * p[i];
		for(int i = 0; i < k; i++) dp[i] = 1;
		cout << fixed << setprecision(5) << re(nn) << endl;
	}
}
