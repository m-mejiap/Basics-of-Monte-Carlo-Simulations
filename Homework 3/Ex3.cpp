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
double hit_and_miss(int N);
double stratified_sampling(int N);
double partially_SS(int N);

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
    
    cout<<"SS:"<<endl;
    for(int i=2;i<=6;i++){
        int N = pow(10,i);
        clock_t t1, t2;
        t1 = clock();
        double r = stratified_sampling(N);
        t2 = clock();
        cout<<"N = "<<N<<", error = "<<r-0.946997089979748<<", Time: "<<difftime(t2,t1)/CLOCKS_PER_SEC<<endl;
    }
    
    cout<<"H&M:"<<endl;
    for(int i=2;i<=6;i++){
        int N = pow(10,i);
        clock_t t1, t2;
        t1 = clock();
        double r = hit_and_miss(N);
        t2 = clock();
        cout<<"N = "<<N<<", error = "<<r-0.946997089979748<<", Time: "<<difftime(t2,t1)/CLOCKS_PER_SEC<<endl;
    }
    
    cout<<"PSS:"<<endl;
    for(int i=2;i<=6;i++){
        int N = pow(10,i);
        clock_t t1, t2;
        t1 = clock();
        double r = partially_SS(N);
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
    return double(10*sum)/double(N);
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
    return double(sum)/double(N);
}

double hit_and_miss(int N){
    double minx = 0;
    double maxx = 10;
    double miny = 0;
    double maxy = 0.28798091427502787;
    int n_hits = 0;
    double Ve = (maxy-miny)*(maxx-minx);
    for(int i=0; i<N; i++){
        double rx = (maxx-minx) * (double(rand()) / double(RAND_MAX)) + minx;
        double ry = (maxy-miny) * (double(rand()) / double(RAND_MAX)) + miny;
        double f = exp(rx*log(2) - 2 - log(tgamma(rx+1)));
        if(f-ry>0){
            n_hits += 1;
        }
    }
    return double(Ve)*double(n_hits)/double(N);
}

double stratified_sampling(int N){
    double sum = 0;
    for(int i=0; i<N; i++){
        double mini = 10/N * i;
        double maxi = 10/N * (i+1);
        double r = (maxi-mini) * (double(rand()) / double(RAND_MAX)) + mini;
        double f = exp(r*log(2) - 2 - log(tgamma(r+1)));
        sum += f;
    }
    return (10/double(N))*sum;
}

double partially_SS(int N){
    double sum = 0;
    double points = N/100;
    for(int i=0;i<100; i++){
        double mini = 10/100 * i;
        double maxi = 10/100 * (i+1);
        for(int j=0; j<points; j++){
            double r = (maxi-mini) * (double(rand()) / double(RAND_MAX)) + mini;
            double f = exp(r*log(2) - 2 - log(tgamma(r+1)));
            sum += f;
        }
    }
    return (10/double(N))*sum;
}