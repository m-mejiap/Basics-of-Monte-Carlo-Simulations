//Head.
#define _USE_MATH_DEFINES
#include <fstream>
#include <iostream>
#include <cmath>
#include <time.h>
using namespace std;

//Method declaration.
double direct_sampling(int N);
double importance_sampling(int N);

//Main.
int main(){
    cout<<"DS:"<<endl;
    for(int i=2;i<=6;i++){
        int N = pow(10,i);
        clock_t t1, t2;
        t1 = clock();
        double r = direct_sampling(N);
        t2 = clock();
        cout<<"N = "<<N<<", error = "<<r-0.946997089979748<<", Time: "<<difftime(t2,t1)/CLOCKS_PER_SEC<<endl;
    }
    
    cout<<"IS:"<<endl;
    for(int i=2;i<=6;i++){
        int N = pow(10,i);
        clock_t t1, t2;
        t1 = clock();
        double r = importance_sampling(N);
        t2 = clock();
        cout<<"N = "<<N<<", error = "<<r-0.946997089979748<<", Time: "<<difftime(t2,t1)/CLOCKS_PER_SEC<<endl;
    }
    return 0; 
}

//Methods.
double direct_sampling(int N){
    double sum = 0;
    for(int i=0; i<N; i++){
        double x = 10 * (double(rand()) / double(RAND_MAX));
        sum += exp(x*log(2) - 2 - log(tgamma(x+1)));
    }
    return double(10*sum/N);
}

double importance_sampling(int N){
    double sum = 0;
    for(int i=0; i<N; i++){
        double r = double(rand()) / double(RAND_MAX);
        double G_inv = -log2(1-(1023*r/1024));
        double f_g = exp(G_inv*log(2) - 2 - log(tgamma(G_inv+1)));
        double g_g = exp(-(G_inv*log(2)));
        sum += f_g/g_g;
    }
    return double(sum/N);
}
