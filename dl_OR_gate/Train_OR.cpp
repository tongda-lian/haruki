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
    const int epochs = 20000000;
    const int display = 10000;
    const int BS = 4;
    const int D_IN = 2;
    const int D_OUT = 1;
    const int h = 5;
    const double learning_rate = 1.0e-5;
    
    double X[BS][D_IN], Y[BS][D_OUT], XT[D_IN][BS];
    double YP[BS][D_OUT] = {0}, GYP[BS][D_OUT] = {0};
    double w2T[D_OUT][h];
    
    //    give initial value to weight matrix
    double w1[D_IN][h] = {
        {1.0 , -1.0, 1.0, -1.0 , 1.0},
        {-1.0, 1.0, -1.0 , 1.0, 1.0}
    };
    
    double w2[h][D_OUT] = {
        {1.0}, {-1.0} , {1.0},{-1.0} , {1.0}
    };
    
    //    double w1[D_IN][h], w2[h][D_OUT];
    //    ifstream w1file("w1.txt");
    //       for(int i = 0; i < D_IN ; i++){
    //           for(int j = 0 ; j < h ; j++){
    //               w1file >> w1[i][j];
    //           }
    //       }
    //       w1file.close();
    //
    //       ifstream w2file("w2.txt");
    //       for(int i = 0; i < h ; i++){
    //           for(int j = 0 ; j < D_OUT ; j++){
    //               w2file >> w2[i][j];
    //           }
    //       }
    //       w2file.close();
    
    double Gw1[D_IN][h] = {0}, Gw2[h][D_OUT] = {0}, GH[BS][h] = {0};
    double H[BS][h] = {0}, HR[BS][h] = {0}, HRT[h][BS] = {0};
    double loss = 0, loss_old = 10000.0;
    
    //    Read in train set X and Y
    ifstream xfile("X_train_set.txt");
    for(int i = 0 ; i < BS ; i++){
    for(int j = 0; j < D_IN ; j++){
        xfile >> X[i][j];
    }}
    xfile.close();
    
    //    Initialize transposed matrix of X
    for(int i = 0 ; i < BS ; i++){
    for(int j = 0; j < D_IN ; j++){
        XT[j][i] = X[i][j];
    }}
    
    ifstream yfile("Y_train_set.txt");
    for(int i = 0 ; i < BS ; i++){
    for(int j = 0; j < D_OUT ; j++){
        yfile >> Y[i][j];
    }}
    yfile.close();
    
    for(int epoch = 1; epoch <= epochs ; epoch ++){
        //    forward pass
        //    H = X * w1
        for(int i = 0 ; i < BS; i++){
        for(int j = 0 ; j < h; j++){
        for(int k = 0; k < D_IN ; k++){
            H[i][j] += X[i][k] * w1[k][j];
        }}}
        
        //    Rectified Linear Unit, ReLU
        for(int i = 0 ; i < BS; i++){
        for(int j = 0 ; j < h; j++){
            HR[i][j] = ReLU(H[i][j]);
        }}
        
        for(int i = 0 ; i < BS; i++){
        for(int j = 0 ; j < D_OUT; j++){
        for(int k = 0; k < h ; k++){
            YP[i][j] += HR[i][k] * w2[k][j];
        }}}
        
//    Compute mean squared error and print
        for(int i = 0 ; i < BS; i++){
        for(int j = 0 ; j < D_OUT; j++){
            loss += (YP[i][j] - Y[i][j]) * (YP[i][j] - Y[i][j]);
        }}
        
        if(epoch % display ==0)
        {cout<< "The loss of "<<epoch <<" step is : " << loss <<endl;}
        
//        backward pass: gridents of loss with respect to w2
        //     gradient of yp
        for(int i = 0 ; i < BS; i++){
        for(int j = 0 ; j < D_OUT; j++){
            GYP[i][j] = 2.0 * (YP[i][j] - Y[i][j]);
        }}
        //        HRT
        for(int i = 0 ; i < BS; i++){
        for(int j = 0 ; j < h; j++){
            HRT[j][i] = HR[i][j];
        }}
        //        Gw2
        for(int i = 0 ; i < h; i++){
        for(int j = 0 ; j < D_OUT; j++){
        for(int k = 0; k < BS ; k++){
            Gw2[i][j] += HRT[i][k] * GYP[k][j];
        }}}
        
//      backward pass: gridents of loss with respect to w1
        for(int i = 0 ; i < h ; i++){
        for(int j = 0 ; j < D_OUT ; j++){
            w2T[j][i] = w2[i][j];
        }}
        
        for(int i = 0 ; i < BS; i++){
        for(int j = 0 ; j < h; j++){
        for(int k = 0; k < D_OUT ; k++){
            GH[i][j] += GYP[i][k] * w2T[k][j];
        }}}
        
        for(int i = 0 ; i < BS; i++){
        for(int j = 0 ; j < h; j++){
            GH[i][j] = ReLU(GH[i][j]);
        }}
        
        for(int i = 0 ; i < D_IN; i++){
        for(int j = 0 ; j < h; j++){
        for(int k = 0; k < BS ; k++){
            Gw1[i][j] += XT[i][k] * GH[k][j];
        }}}
        
//        Update weights
        for(int i = 0 ; i < D_IN ; i++){
        for(int j = 0 ; j < h ; j++){
            w1[i][j] -= learning_rate * Gw1[i][j];
        }}
        
        for(int i = 0 ; i < h ; i++){
        for(int j = 0 ; j < D_OUT ; j++){
            w2[i][j] -= learning_rate * Gw2[i][j];
        }}
        
//       Set matrics back to 0
        for(int i = 0 ; i < BS ; i++){
        for(int j = 0 ; j < h ; j++){
            H[i][j] = 0.0; HR[i][j] = 0.0; HRT[j][i] = 0.0;
            GH[i][j] = 0.0;
        }}
        
        for(int i = 0 ; i < BS ; i++){
        for(int j = 0 ; j < D_OUT ; j++){
            YP[i][j] = 0.0; GYP[i][j] = 0.0;
        }}
        
        for(int i = 0 ; i < D_IN ; i++){
        for(int j = 0 ; j < h ; j++){
            Gw1[i][j] = 0.0;
        }}
        
        for(int i = 0 ; i < h ; i++){
        for(int j = 0 ; j < D_OUT ; j++){
            Gw2[i][j] = 0.0;
        }}
        
        if(loss > loss_old)
        {
            cout<< "At step " << epoch << " min loss: " << loss <<endl;
            break;
        }
        
        loss_old = loss;
        loss = 0.0;
        
}    // For End
    
//    Write out weigh matrix w1 and w2 for validation
    ofstream writew1("w1.txt");
    for(int i = 0 ; i < D_IN ; i++){
        for(int j = 0 ; j < h ; j++){
            writew1 << w1[i][j] << " " ;
        }
        writew1 << "\n" ;
    }
    writew1.close();
    
    ofstream writew2("w2.txt");
    for(int i = 0 ; i < h ; i++){
        for(int j = 0 ; j < D_OUT ; j++){
            writew2 << w2[i][j] << " " ;
        }
        writew2 << "\n" ;
    }
    writew2.close();
    
    cout << "Train Ends." << endl;
    return 0;
}

// Lian Tongda
// Tokyo Institute of Technology

//cout<<"Y:"<<endl;
//    for(int i = 0 ; i < BS ;i++)
//    {
//        for(int j = 0 ; j < D_OUT ;j++)
//        {
//            cout<< Y[i][j] <<" " ;
//        }
//        cout<<endl;
//    }

//cout<<"X:"<<endl;
//    for(int i = 0 ; i < BS ;i++)
//    {
//        for(int j = 0 ; j < D_IN ;j++)
//        {
//            cout<< X[i][j] <<" " ;
//        }
//        cout<<endl;
//    }
