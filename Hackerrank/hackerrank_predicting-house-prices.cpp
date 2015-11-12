/*
*
* Regression. Using Gradient Descent.
*/
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h> 
using namespace std;
const double lambda = 0.01;
const int Iter = 50000;
int f, n, t;
double dt[110][15], x[15], y[110], xt[15], nx[15];

double cal(){
    double res = 0;
    for(int i = 0; i <= f; ++ i)
        res += xt[i]*x[i];
    return res;
}

double compute(int id){
    double res = 0;
    for(int i = 0; i <= f; ++ i)
        res += dt[id][i]*x[i];
    return res - y[id];
}

double computeCost(){
    double sum = 0;
    for(int i = 0; i < n; ++ i){
        double tmpsum = compute(i);
        sum += tmpsum*tmpsum;
    }
    return sum/(2.0*n);
}

double computeDelta(int j){
    double delta = 0;
    for(int i = 0; i < n; ++ i){
        double cost = compute(i);
        delta += cost*dt[i][j];
    }
    return delta*lambda/(double)n;
}

void ml(){
    srand((unsigned)time(0));
    for(int i = 0; i <= f; ++ i){
        x[i] = rand()*0.00001;
    }
    for(int k = 0; k < Iter; ++ k){
        double cost = computeCost();
     //   if(k > 29900)
     //       printf("cost = %.3lf\n", cost);
        for(int j = 0; j <= f; ++ j){
            double delta = computeDelta(j);
            nx[j] = x[j] - delta;
        }
        for(int j = 0; j <= f; ++ j){
            x[j] = nx[j];
        }
    }
}
    
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    scanf("%d%d",&f,&n);
    for(int i = 0; i < n; ++ i){
        dt[i][0] = 1.0;
        for(int j = 1; j <= f; ++ j)
            scanf("%lf",&dt[i][j]);
        scanf("%lf",&y[i]);
    }
    ml();
    scanf("%d",&t);
    while(t --){
        xt[0] = 1.0;
        for(int i = 1; i <= f; ++ i)
            scanf("%lf",&xt[i]);
        printf("%.2lf\n",cal());
    }
    return 0;
}
