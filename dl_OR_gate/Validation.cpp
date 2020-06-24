// Lian Tongda
// Tokyo Institute of Technology

#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<sstream>
#include<istream>
#include<iomanip>

using namespace std;

double ReLU(double x)
{
    if(x > 0)
        return x;
    else
        return 0.0;
}

int main()
{
    //    Parameters
    const int BS = 4;
    const int D_IN = 2;
    const int D_OUT = 1;
    const int h = 5;
    
    double X[BS][D_IN], Y[BS][D_OUT] ;
    double YP[BS][D_OUT] = {0};
    double w1[D_IN][h], w2[h][D_OUT];
    
    double H[BS][h] = {0}, HR[BS][h] = {0};
    double loss = 0.0;
    
//    Read in validation set X and Y
    ifstream xfile("X_validation_set.txt");
    for(int i = 0 ; i < BS ; i++){
    for(int j = 0; j < D_IN ; j++){
        xfile >> X[i][j];
    }}
    xfile.close();
       
    ifstream yfile("Y_validation_set.txt");
    for(int i = 0 ; i < BS ; i++){
    for(int j = 0; j < D_OUT ; j++){
        yfile >> Y[i][j];
    }}
    yfile.close();
    
//    Read in weight matrix w1 and w2
    ifstream w1file("w1.txt");
    for(int i = 0; i < D_IN ; i++){
    for(int j = 0 ; j < h ; j++){
        w1file >> w1[i][j];
    }}
    w1file.close();
    
    ifstream w2file("w2.txt");
    for(int i = 0; i < h ; i++){
    for(int j = 0 ; j < D_OUT ; j++){
        w2file >> w2[i][j];
    }}
    w2file.close();
    
//    cout<<"w1:"<<endl;
//    for(int i = 0; i < D_IN ; i++){
//        for(int j = 0 ; j < h ; j++){
//            cout << w1[i][j]<< " ";
//        }
//        cout<<endl;
//    }
//
//    cout<<"w2:"<<endl;
//    for(int i = 0; i < h ; i++){
//        for(int j = 0 ; j < D_OUT ; j++){
//            cout<< w2[i][j] <<" ";
//        }
//        cout<<endl;
//    }

//    Forward pass
    for(int i = 0 ; i < BS; i++){
    for(int j = 0 ; j < h; j++){
    for(int k = 0; k < D_IN ; k++){
        H[i][j] += X[i][k] * w1[k][j];
    }}}
    
    for(int i = 0 ; i < BS; i++){
    for(int j = 0 ; j < h; j++){
        HR[i][j] = ReLU(H[i][j]);
    }}
    
    for(int i = 0 ; i < BS; i++){
    for(int j = 0 ; j < D_OUT; j++){
    for(int k = 0; k < h ; k++){
        YP[i][j] += HR[i][k] * w2[k][j];
    }}}

//    Compute mean squared error
    for(int i = 0 ; i < BS; i++){
    for(int j = 0 ; j < D_OUT; j++){
        loss += (YP[i][j] - Y[i][j]) * (YP[i][j] - Y[i][j]);
    }}

    cout<<"YP:" << endl;
    for(int i = 0; i < BS ; i++){
    for(int j = 0 ; j < D_OUT ; j++){
        cout << YP[i][j] << " ";
    }cout << endl;}
     cout<<"loss: "<< loss <<endl;
    
    return 0;
}

