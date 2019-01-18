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
double chain[10][10];
int v1, stepcount=0;
double prev, current, compare, temp=2.0, coupl=1, h=-0.5;
//'temp' is the temperature of the bath, 'coupl' is the constant coefficient of (-J1.J2) in the Hamiltonian, h is the polarising magnetic field
//The Boltzmann constant is taken to be unity.
int main()
{
    srand ( time(NULL) );
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
        {
            v1=rand()%100;
            if(v1<50)
                chain[i][j]=-1;
            else
                chain[i][j]=1;
        }
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            cout<<chain[i][j]<<" ";
        }
        cout<<endl;
    }
    current=energy();
    cout<<"The present energy is "<<current<<" units."<<endl;
    cout<<"The present magnetisation is "<<magnetisation()<<endl;
    for(int sweep=0;sweep<10000;sweep++)
        for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
            {
                prev=current;
                chain[i][j]*=-1;
                current=energy();
                if(current>prev)
                {
                    v1=rand()%100;
                    compare=exp((prev-current)/temp);
                    if(compare*100<v1)
                    {
                        chain[i][j]*=-1;
                        current=prev;
                    }
                }
            }
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            cout<<chain[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"The final energy is "<<current<<" units."<<endl;
    cout<<"The final magnetisation is "<<magnetisation()<<endl;
}
double energy()
{
    double en=0;
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
        {
            en-=h*chain[i][j];
            if(i<9)
                en-=coupl*chain[i][j]*chain[i+1][j];
            if(i==9)
                en-=coupl*chain[i][j]*chain[0][j];
            if(j<9)
                en-=coupl*chain[i][j]*chain[i][j+1];
            if(j==9)
                en-=coupl*chain[i][j]*chain[i][0];
        }
}
double magnetisation()
{
    double sum=0;
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            sum+=chain[i][j];
    return (sum/100);
}
