#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#define outfile "test5.data"
typedef long long ll;

using namespace std;

const int N = 10000000;           //总访问数
const int M = 8000;               //总项数
const int MOD = 20000;            //取值时
double theta = 1;                 //偏度因子

double sum = 0;                   //频率之和
double last_sum = 0;

int vis[MOD + 50];                //用于保证随机时，key唯一
vector<int> frequency;            //量级N下，各部分请求的频数
vector<pair<string, string> > dta;//表示数据库已有的数据


ll qpow(ll n, ll p) {
    ll res = 1;
    ll base = n;
    while (p) {
        if (p & 1) res *= base;
        p = p >> 1;
        base = base * base;
    }
    return res;
}
double f(int x) {
    static double denominator = 0;     //分母
    if (denominator == 0) {
        //计算分母，避免重复计算
        for (int i = 1; i <= N; ++i) {
            denominator += 1.0 / qpow(i, theta);
        }
    }
    double res = (1.0 / qpow(x, theta)) / denominator;
    return res;
}
//将数组转成字符串
string itos(int x) {
    string res;
    while (x) {
        res.push_back(x % 10 + '0');
        x /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}


int main() {
    int ed = 99;
    int div = N / 100;
    int key, val;
    int r;
    int fre;
    
    //计算当前量级下，访问分布的频数
    for (int i = 1; i <= N; ++i) {
        double percent = f(i);
        sum += percent;
        if (i % div == 0) {
            fre = (sum - last_sum)*N;
            //printf("%3dth=%8d", i / div, fre);
            frequency.push_back(fre);
            last_sum = sum;
        }
        //if (i % (div * 10) == 0) puts("");
    }

    freopen(outfile, "w", stdout);
    srand((unsigned)time(NULL));

    for (int i = 0; i < M; ++i) {
        while (vis[key = rand() % MOD]) {} //去重，得到一个不与其他key值重复的新key值
        vis[key] = 1;
        val = rand() % MOD;
        dta.push_back(pair<string, string>(itos(key), itos(val)));
        printf("%d %d\n", key, val);
    }
    
    //模拟访问请求
    while (frequency[0]) {
        for (int i = 0; i <= ed; ++i) {
            if (frequency[i] > 0) {
                --frequency[i];
                r = rand() % 10;
                printf("%s\n", dta[i * 10 + r].first.c_str());
            }
            else {
                --ed;
            }
        }
    }
    return 0;
}