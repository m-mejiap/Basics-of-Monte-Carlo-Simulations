//Head.
#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include <time.h>
using namespace std;

//Constant declaration.
double Kb = 8.6173324*pow(10,-5);
double T = 600;
double N = 6.02140857*pow(10,23);
double V = 1;
double Etheor = 3*Kb*T/2;

//Method declaration.
double MaxwellBoltzmann(double E);
double MCMC(int N_points);
double rms(int N_runs);

//Main.
int main(){
    for(int i=2; i<9; i++){
        int N_points = pow(10,i);
        cout<<i<<","<<MCMC(N_points)<<endl;
    }
    
    cout<<endl;
    cout<<rms(500)<<endl;
    return 0;
}

//Methods.
double MaxwellBoltzmann(double E){
    double a = Kb*T;
    double r = (2/sqrt(M_PI))*(N/V)*(sqrt(E)/sqrt(pow(a,3)))*exp(-(E/a));
    return r;
}

double MCMC(int N_points){
    double sum = 0;
    double deltax_max = 0.001;
    double x = 0.3;
    double p = MaxwellBoltzmann(x);
    sum += x;
    for(int i=0; i<N_points; i++){
        double x_0 = x;
        double u = (-2)*(double(rand())/double(RAND_MAX))-1;
        double x_prime = x+(u*deltax_max);
        double p_prime = MaxwellBoltzmann(x_prime);
        if(p_prime/p >= 1){
            x = x_prime;
            p = p_prime;
        }
        else{
            double u_new = double(rand())/double(RAND_MAX);
            if(p_prime/p >= u_new){
                x = x_prime;
                p = p_prime;
            }
            else{
                x = x_0;
            }
        }
    }
    sum += x;
    return sum/double(N_points);
}

double rms(int N_runs){
    ofstream outfile;
    outfile.open("data.dat");
    double summ = 0;
    for(int i=1; i<=N_runs; i++){
        double Ei = MCMC(1); 
        double deltaE = Ei-Etheor;
        summ += pow(deltaE,2);
        outfile<<deltaE<<", "<<sqrt(summ/double(i))<<endl;
    }
    outfile.close();
    return sqrt(summ/double(N_runs));
}
