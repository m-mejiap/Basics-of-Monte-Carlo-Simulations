//Head.
#define _USE_MATH_DEFINES
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

//Variable declaration.
double l = 2;   //needle length
double d = 10;  //line spacing
double n = 10;  //number of niddles
int N = 100; //number of simultions

//Method declaration.
void piGuess();

//Main.
int main(){
    piGuess();
    return 0;
}

//Methods.
void piGuess(){
    ofstream outfile;
    outfile.open("averages.dat");
    
    for (int i=1; i<=7; i++){
        double pi_guess[N] = {};
        
        double Num = 0;
        double sum = 0;
        
        for (int j=0; j<N; j++){
            double N_hit = 0; //number of niddles wich are across the line
            
            
            for (int k=0; k<n; k++){
                double rotate = ((float)rand() / RAND_MAX) * (2*M_PI);
                double x_0 = (d*3)*((float)rand() / RAND_MAX);
                double y_0 = (d*5)*((float)rand() / RAND_MAX);
                double x_l = x_0 + l * cos(rotate);
                double y_l = y_0 + l * sin(rotate);
                if(x_0 <= 0 || x_l <= 0){
                    N_hit += 1;
                }
                else if(x_0 <= 10 && x_l >= 10){
                    N_hit += 1;
                }
                else if(x_l <= 10 && x_0 >= 10){
                    N_hit += 1;
                }
                else if(x_0 <= 20 && x_l >= 20){
                    N_hit += 1;
                }
                else if(x_l <= 20 && x_0 >= 20){
                    N_hit += 1;
                }
                else if(x_0 >= 30 || x_l >= 30){
                    N_hit += 1;
                }
            }

            if(N_hit>0){ //attention: this "if" is included in order to avoid division by 0 when n es too small.
                pi_guess[j] = (2*l*n)/(d*N_hit);
                Num += 1;
                sum += abs(pi_guess[j]-M_PI);
            }
        }
        
        outfile<<n<<", "<<sum/Num<<endl;
        
        n = 10*n;
    }
    
    outfile.close();
}