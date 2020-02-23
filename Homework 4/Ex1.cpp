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
double Etheor = 3/2*Kb*T;

//Method declaration.
double MaxwellBoltzmann(double E);
double MCMC(int N_points);
double rms();

//Main.
int main(){
    cout<<MaxwellBoltzmann(0.3)<<endl;
    cout<<endl;
    for(int i=2; i<9; i++){
        int N_points = pow(10,i);
        cout<<i<<","<<MCMC(N_points)<<endl;
    }
    cout<<endl;
    cout<<3/2*Kb*T<<endl;
    
    cout<<endl;
    cout<<rms()<<endl;
    return 0;
}

//Methods.
double MaxwellBoltzmann(double E){
    double r = (2/sqrt(M_PI))*(N/V)*(sqrt(E)/pow(Kb*T,3/2))*exp(-(E/(Kb*T)));
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

double rms(){
    double summ = 0;
    for(int i=0; i<500; i++){
        double Ei = MCMC(1); 
        summ += pow(Ei-Etheor,2);
    }
    return sqrt(summ/500.0);
}
