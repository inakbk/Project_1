//Exercise b, algorithm for solving the set of linear equations
//a_i*v_(i-1) + b_i*v_i + c_i*v_(i+1) = tilde_b_i

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

double f(double x) //call by f(x)
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

    /*
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;*/

    //creating vector v
    vec v = zeros<vec>(n);

    //and x?
    vec x = linspace<vec>(0, 1, n+2);

    cout << x[1] << " " << h << endl;

    /*for(int i = 0; i < n; ++i)
    {
        //algorithm
    }
*/


    return 0;
}

