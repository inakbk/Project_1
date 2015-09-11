//Exercise b, algorithm for solving the set of linear equations
//a_i*v_(i-1) + b_i*v_i + c_i*v_(i+1) = h*h*f(x_i)

#include <iostream>
#include <armadillo>
#include <cstdlib>
//#include <stdio.h>

using namespace std;
using namespace arma;

vec f(vec x) //call by f(x[i])
{
    return 100.*exp(-10.*x);
}

void MakePlotFile(const vec x, const vec solution, int n)
{
    ofstream myfile;
        string filename = "solver" + to_string(n);

        myfile.open ("solver_n.txt");
        myfile << "x" << "     " << "solution (u/v)" << endl;
        for (i=0; i<=n+1; i++){
            myfile << x_mat(i) << "    " << x2(i) << endl;
        }
        myfile.close();
}

int main()
{
    const int n = 10;
    const double h = 1./(n+1);

    /*creating vectors a, b, c of same length as x, so one extra
     * value on beginning/end of array*/
    vec a = -1.*ones<vec>(n+2);
    vec b = 2.*ones<vec>(n+2);
    vec c = -1.*ones<vec>(n+2);

    //outside range of matrix
    a[1] = 0;
    c[n] = 0;

    //creating vector x and b_thilde
    vec x = linspace<vec>(0, 1, n+2);
    vec b_thilde = h*h*f(x);

    //cout << b << endl;
    //cout << b_thilde << endl;

    //forward substitution:
    for(int i = 2; i < n+1; ++i) //starting from second row till last
    {
        b[i] = b[i] - (a[i]*c[i-1])/b[i-1]; //b' one iteration
        b_thilde[i] = b_thilde[i] - (a[i]*b_thilde[i-1])/b[i-1];
    }

    //cout << b << endl;
    //cout << b_thilde << endl;

    //backward substitution:
    for(int i = n; i > 1; --i) //starting from last row n to i==1
    {
        //dividing by b[i-1] after backward sust. to find final sol.:
        b_thilde[i-1] = b_thilde[i-1] - (c[i-1]*b_thilde[i])/b[i];
    }

    //Final solution:
    vec v = b_thilde/b;

    cout << solution << endl;
    //cout << b_thilde << endl;
    //cout << b << endl;


    return 0;
}

