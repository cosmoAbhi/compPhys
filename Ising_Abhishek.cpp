#include <iostream>
#include <fstream>
#include <cmath>
#include <fstream>
#include <math.h>
#include <sstream>
#include <cstdlib>
#include <time.h>
using namespace std;

//std::mt19937 generator (123);
//std::uniform_real_distribution<double> dis(0.0, 1.0);
double energy();
double chain[10][10];
int v1, stepcount=0;
double prev, current, compare, temp=2.5;
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
    cout<<"The present energy is "<<current<<" J."<<endl;
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
    cout<<"The final energy is "<<current<<" J."<<endl;
}
double energy()
{
    double en=0;
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
        {
            if(i<9)
                en-=chain[i][j]*chain[i+1][j];
            if(j<9)
                en-=chain[i][j]*chain[i][j+1];
        }
}
