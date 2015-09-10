//Exercise b, algorithm for solving the set of linear equations
//a_i*v_(i-1) + b_i*v_i + c_i*v_(i+1) = h*h*f(x_i)

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

vec f(vec x) //call by f(x[i])
{
    return 100.*exp(-10.*x);
}

int main()
{
    const int n = 10;
    const double h = 1./(n+1);

    //creating vectors a, b, c:
    vec a = -1.*ones<vec>(n);
    vec b = 2.*ones<vec>(n);
    vec c = -1.*ones<vec>(n);

    a[0] = 0;
    a[n-1] = 0;
    c[0] = 0;
    c[n-1] = 0;

    //creating vector v and x and b_thilde
    vec v = zeros<vec>(n);
    vec x = linspace<vec>(0, 1, n+2);
    vec b_thilde = h*h*f(x);

    cout << b_thilde << endl;
/*
    //algorithm: a[i]*v[i-1] + b[i]*v[i] + c[i]*v[i+1] = h*h*f(x[i])
    for(int i = 1; i < n; ++i)
    {
        b[i] = b[i] - (a[i]*c[i-1])/b[i-1]; //b' one iteration
        b_thilde[i] = b_thilde[i] - (a[i]*b_thilde[i-1])/b[i-1];

    }
*/


    return 0;
}

