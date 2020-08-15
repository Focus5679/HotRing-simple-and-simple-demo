#include <cmath>
#include <cstdio>
#include <iostream>

typedef long long ll;

using namespace std;

int N = 10000000;           //总项数
int B = 1000;                  //总桶数
int L = N/B;                 //总链数
double theta = 1;            //偏度因子

double Echain = 0;          //传统冲突链表访问内存的预期次数
double Eideal = 0;          //应用热点感知后理想访问内存的预期次数

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
double F(int k){
    double res = 0;
    for(int i = (k-1)*B+1; i <= k*B; ++i){
        res += f(i);
    }
    return res;
}
int main(){
    Echain = 1.0 + L/2;
    Eideal = 1.0;
    for(int k = 1; k <= L; ++k){
        Eideal += F(k)*k;
    }
    printf("Echain = %lf Eideal = %lf\n", Echain, Eideal);
    return 0;
}