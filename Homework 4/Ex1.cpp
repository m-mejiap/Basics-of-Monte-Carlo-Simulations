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
double MCMC(int N_points, double deltax_max);

//Main.
int main(){
    ofstream outfile;
    outfile.open("data.dat");
    double max = 0.001;
    for(int i=1; i<= 30; i++){
        outfile<<max<<", "<<MCMC(500, max)<<endl;
        max += 0.01;
    }
    outfile.close();
    
    outfile.open("data2.dat");
    double optimal_max = 0.121;
    int N_points;
    for(int i=2; i<= 8; i++){
        N_points = pow(10,i);
        outfile<<N_points<<", "<<MCMC(N_points, optimal_max)<<endl;
    }
    outfile.close();
    return 0;
}

//Methods.
double MaxwellBoltzmann(double E){
    double a = Kb*T;
    double r = (2/sqrt(M_PI))*(N/V)*(sqrt(E)/sqrt(pow(a,3)))*exp(-(E/a));
    return r;
}

double MCMC(int N_points, double deltax_max){
    double sum = 0;
    double sum_rms = 0;
    double x = 0.3;
    double p = MaxwellBoltzmann(x);
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
        sum += x;
        double Ei = sum/double(i+1);
        double resta = Ei - Etheor;
        sum_rms += pow(resta,2);
    }
    double rms = sqrt(sum_rms/double(N_points));
    double Eprom = double(sum)/double(N_points);
    return rms;
}