#include <cmath>
#include <cstdio>
#include <iostream>

typedef long long ll;

using namespace std;

int N = 10000000;                    //总项数
double theta = 1;                  //偏度因子

double sum = 0;                 //频率之和
double last_sum = 0;            

ll qpow(ll n, ll p){
    ll res = 1;
    ll base = n;
    while(p){
        if(p&1) res *= base;
        p = p >> 1;
        base = base * base;
    }
    return res;
}
double f(int x){
    static double denominator = 0;     //分母
    if(denominator == 0){
        //计算分母，避免重复计算
        for(int i = 1; i <= N; ++i){
            denominator += 1.0/qpow(i, theta);
        }
    }
    double res = (1.0/qpow(x, theta)) / denominator;
    return res;
}
int main(){
    int div = N/100;
    for(int i = 1; i <= N; ++i){
        double percent = f(i)*100;
        sum += percent;
        if(i % div == 0){
            printf("%3dth=%8.5lf%% ", i/div,  (sum - last_sum));
            last_sum = sum;
        }
            
        if(i % (div*10) == 0) puts("");
    }
    printf("%lf%%\n", sum);
    return 0;
}