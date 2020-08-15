/*
 * @Author: zsw 
 * @Date: 2020-05-20 16:41:29 
 * @Last Modified by:   mikey.zhaopeng 
 * @Last Modified time: 2020-05-20 16:41:29 
 */
#include <cmath>
#include <cstdio>
#include <iostream>

typedef long long ll;

using namespace std;

int N = 100;                //总项数
int B = 10;                  //总桶数
int L = N/B;                //总链数

double Echain = 0;          //预期访问内存次数

int main(){
    Echain = 1.0 + L/2;
    printf("Echain = %lf\n", Echain);
    return 0;
}