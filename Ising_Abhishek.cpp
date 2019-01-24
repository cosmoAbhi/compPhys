#include <iostream>
#include <fstream>
#include <cmath>
#include <fstream>
#include <math.h>
#include <sstream>
#include <cstdlib>
#include <time.h>
using namespace std;

double energy();
double magnetisation();
int dim=10;
double chain [10][10];
//NOTE that due to limitations in dynamic array allocations in C++, the array size in the declaration must be changed manually while changing 'dim'.
int v1, stepcount=0;
double prev, current, compare, dE, fin_energy=0, fin_mag=0, temp=0.5, coupl=1, h=0;
int MC=1000;
/*Adjustable parameters are:
temp (temperature of the bath), 
coupl (coupling coefficient of neighbouring spin interaction term in the Hamiltonian), 
h (external magnetic field), 
MC (no. of Monte Carlo steps), 
dim (dimension of chain).*/
int main()
{
    srand ( time(NULL) );
    for(int i=0;i<dim;i++)
        for(int j=0;j<dim;j++)
        {
            v1=rand()%100;
            if(v1<50)
                chain[i][j]=-1;
            else
                chain[i][j]=1;
        }
    for(int i=0;i<dim;i++)
    {
        for(int j=0;j<dim;j++)
        {
            cout<<chain[i][j]<<" ";
        }
        cout<<endl;
    }
    current=energy();
    cout<<"The present energy per site is "<<current/dim/dim<<endl;
    cout<<"The present magnetisation per site is "<<magnetisation()<<"."<<endl;
    ofstream write;
    write.open("output.txt");
    for(int sweep=0;sweep<MC;sweep++)
    {
        for(int i=0;i<dim;i++)
        {
            for(int j=0;j<dim;j++)
            {
                prev=energy();
                chain[i][j]*=-1;
                current=energy();
                dE = current - prev;
                chain[i][j] *= -1;
                //cout << dE << endl;
                if (dE <= 0)
                {
                    chain[i][j] *= -1;
                    current = current + dE;
                }
                else if(dE > 0)
                {
                    v1=rand()%100;
                    compare=exp(-(dE)/temp);
                    if(compare*100>v1)
                    {
                        chain[i][j]*=-1;
                        current=current + dE;
                    }
                }
            }
        }
        if (sweep >= MC/2){
        fin_energy+=current;
        fin_mag+=magnetisation();
        }
        //cout<<endl;

    //cout<<sweep<<"  "<<current<<"   "<<magnetisation()<<endl;
        write<<sweep<<" "<<current<<"   "<<magnetisation()<<endl;
    }
    for(int i=0;i<dim;i++)
    {
        for(int j=0;j<dim;j++)
        {
            cout<<chain[i][j]<<" ";
        }
        cout<<endl;
    }
    fin_energy=fin_energy*2/MC;
    fin_mag=fin_mag*2/MC;
    cout<<"The final average energy per site over "<<(MC/2)<<" cycles is "<<fin_energy/dim/dim<<endl;
    cout<<"The final average magnetisation per site over "<<(MC/2)<<" cycles is "<<magnetisation()<<"."<<endl;
}
double energy()
{
    double en=0;
    for(int i=0;i<dim;i++)
        for(int j=0;j<dim;j++)
        {
            en-=h*chain[i][j];
            if(i<(dim-1))
                en-=coupl*chain[i][j]*chain[i+1][j];
            if(i==(dim-1))
                en-=coupl*chain[i][j]*chain[0][j];
            if(j<(dim-1))
                en-=coupl*chain[i][j]*chain[i][j+1];
            if(j==(dim-1))
                en-=coupl*chain[i][j]*chain[i][0];
        }
        return (en);
}
double magnetisation()
{
    double sum=0;
    for(int i=0;i<dim;i++)
        for(int j=0;j<dim;j++)
            sum+=chain[i][j];
    return (sum/dim/dim);
}
