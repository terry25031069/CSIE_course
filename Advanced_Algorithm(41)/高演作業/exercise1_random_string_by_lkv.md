## 因為不想 fork 所以開 Issues(?

## 程式碼 (盡力修了 code style，但經驗還是不足，還有待加強)

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<double> memo;

// handle suffix *= p
// mode control whether to modify zero_cnt
void multiplyP(double &suffix, int &zero_cnt, double p, int mode = 0) {
    if (p != 0) {
        suffix *= p;
    }
    else if (mode) {
        zero_cnt++;
    }
}

// handle p * suffix
double multiplySuffix(double suffix, int zero_cnt, double p) {
    if (zero_cnt) {
        return 0;
    }
    return suffix * p;
}

// handle suffix / p
void divideP(double &suffix, int &zero_cnt, double p) {
    if (p != 0) {
        suffix /= p;
    }
    else {
        zero_cnt--;
    }
}

double R(vector<double> &p, int n, int k) {
    if (n < k) return 1;
    if (memo[n] != -1) return memo[n];
    double res = 0, suffix = 1;
    for (int i = n - 1; i >= n - k && i >= 0; i--) {
        res += suffix * (1 - p[i]) * R(p, i, k);
        suffix *= p[i];
    }
    return memo[n] = res;
}

// O(nk)
void memorization(vector<double> &p, int n, int k) {
    memo.clear(), memo.resize(n + 1);
    fill(memo.begin(), memo.end(), -1);
    cout << fixed << setprecision(5) << R(p, n, k) << endl;
}

// O(n)
void dynamic_programming(vector<double> &p, int n, int k) {
    vector<double> dp(n);
    double sum = 0;
    double suffix = 1;
    int zero_cnt = 0;
    for (int i = 0; i < k - 1; i++) {
        dp[i] = 1;
        multiplyP(suffix, zero_cnt, p[i], 1);
        multiplyP(sum, zero_cnt, p[i]);
        sum += (1 - p[i]);
    }
    for (int i = k - 1; i < n; i++) {
        divideP(suffix, zero_cnt, p[i - k + 1]);
        multiplyP(suffix, zero_cnt, p[i], 1);
        multiplyP(sum, zero_cnt, p[i]);
        sum += (1 - p[i]) * dp[i - 1];
        dp[i] = sum;
        if (i - k >= 0) {
            sum -= multiplySuffix(suffix, zero_cnt, (1 - p[i - k + 1]) * dp[i - k]);
        }
        else {
            sum -= multiplySuffix(suffix, zero_cnt, (1 - p[i - k + 1]));
        }
    }
    cout << fixed << setprecision(5) << dp[n - 1] << endl;
}

// O(n)
void dynamic_programming_2(vector<double> &p, int n, int k) {
    vector<double> dp(n);
    double suffix = 1;
    int zero_cnt = 0;
    for (int i = 0; i < k + 1; i++) {
        if (i - k >= 0) {
            divideP(suffix, zero_cnt, p[i - k]);
        }
        multiplyP(suffix, zero_cnt, p[i], 1);
        if (i < k - 1) {
            dp[i] = 1;
        }
        else if (i == k - 1) {  // initialize special case : i == k - 1
            dp[i] = zero_cnt ? 1 : 1 - suffix;
        }
        else {  // initialize special case : i == k
            dp[i] = 1 - (zero_cnt ? 0 : suffix + (1 - p[i]) * (1 - dp[i - 1]));
        }
    }
    for (int i = k + 1; i < n; i++) {
        multiplyP(suffix, zero_cnt, p[i], 1);
        divideP(suffix, zero_cnt, p[i - k]);
        dp[i] = dp[i - 1] - (1 - p[i - k]) * suffix * dp[i - k - 1];
    }
    cout << fixed << setprecision(5) << dp[n - 1] << endl;
}

void solve(int n) {
    int k;
    cin >> k;
    vector<double> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    dynamic_programming(p, n, k);
    memorization(p, n, k);
    dynamic_programming_2(p, n, k);
}

int main() {
    int n;
    while (cin >> n, n) {
        solve(n);
    }
    system("pause");
    return 0;
}
```

## 複雜度分析(隨便寫的)

## Memorization

- R(n, k) : 在前 n 個 bits 中，不存在連續 k 個 1 的機率
- R(n, k) = 1 if n < k
- R(n, k) = $\sum_{i=n-k}^{n-1}q_{i} \times p_{i+1} \times ...  \times p_{n-1} \times R(i,k)$

### 實作細節

- 利用 memo[n] 紀錄 R(n, k)，每個值只計算一次
- 利用 suffix 計算 $\prod_{i=n-k+1}^{n-1}p_i$，避免重複計算
- 每個 memo[n] 都需要 k 次運算來 $\sum_{i=n-k}^{n-1}$，所以時間複雜度為O(nk)
- 時間複雜度為O(nk)

## Dynamic Programming 1

- R(n, k) = $\sum_{i=n-k}^{n-1} q_i \times p_{i+1} \times ... \times p_{n-1} \times R(i, k)$
- R(n + 1, k) = $\sum_{i=n-k+1}^{n} q_i \times p_{i+1} \times ... \times p_{n} \times R(i, k)$
- R(n + 1, k) = $R(n, k) \times p_{n}-q_{n-k} \times p_{n-k+1} \times ... \times p_{n} \times R(n-k,k)+p_n \times R(n, k)$
- 大概寫寫而已，反正 R(n + 1, k) 可以透過 $R(n, k)  \times  p_n$ 並扣掉首項 i=n-k 加上末項 i=n 進行轉移

### 實作細節

- 利用 dp 來記錄 R(n, k)
- 利用 sum 來計算正在求的 R(n, k)
- 利用 suffix 求 $\prod_{i=n-k+1}^{n} p_i$
- 值得注意的是 suffix 的連乘中若有遇到 $p_i$ = 0，需要額外用 zero_cnt 處理，否則 0 乘下去不可逆，遇到除法也可能發生 divide by zero
- 我維持一個大小為 k - 1 的 window，每次 slide 時都讓右界先進來，算好結果後，再放左界出去
- 每個 dp[n] 都可以透過 $sum \times p_i + (1 - p_i)  \times  dp[i-1] - (1 - p[i-k+1])  \times  dp[n-k+1]  \times  suffix$ O(1) 計算及轉移
- 時間複雜度為 O(n)

## Dynamic Programming 2

- 基本上和 Dynamic Programming 1 沒兩樣
- 轉移式使用了高演期中110 第三題的 (b) 轉移式
- 轉移更輕鬆，但同時因為要用到 dp[i] 會call dp[i - k - 1]，所以需要自己初始化 dp[k - 1], dp[k]