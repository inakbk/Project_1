/*Exercise b, algorithm for solving the set of linear equations
 * with two different methods and timing them
 * a_i*v_(i-1) + b_i*v_i + c_i*v_(i+1) = h*h*f(x_i)*/

#include <iostream>
#include <armadillo>
#include <cstdlib>
#include <time.h>
//#include <stdio.h> printf function

using namespace std;
using namespace arma;

vec f(vec x) //call by f(x[i])
{
    return 100.*exp(-10.*x);
}

//Function to make file to plot with in python
void MakePlotFile(const vec x, const vec solution, const int n, const double time_diag, string FileName)
{
    ofstream myfile;
        string filename = "linear_eq_solution_" + FileName + "_n" + to_string(n) + ".txt";
        myfile.open (filename);
        myfile << "Data:" << "  "<< "x" << "     " << "Solution" << endl;
        myfile << "Time calculating with " << FileName << ": "  << time_diag << " " << " seconds" << endl;
        myfile << "---------------------" << endl;
        for (int i=1; i<n+1; i++)
        {
            myfile << x[i] << "    " << solution[i] << endl;
        }
        myfile.close();
        cout << "Datafile done for n=" << n << endl;
}

void Forward_Backward_Substitution(vec b, vec b_thilde, const vec x, const int n)
{
    //clocking the operations (only solve, not making file):
    clock_t start_diag, finish_diag; //declaring start and finish time
    start_diag = clock();

    //forward substitution:
    for(int i = 2; i < n+1; ++i) //starting from second row till last
    {
        b[i] = b[i] - 1/b[i-1]; //b' one iteration
        b_thilde[i] = b_thilde[i] + b_thilde[i-1]/b[i-1];
    }

    //backward substitution:
    for(int i = n; i > 1; --i) //starting from last row n to i==1
    {
        b_thilde[i-1] = b_thilde[i-1] + b_thilde[i]/b[i];
    }

    /*Final solution, dividing by b[i-1] after backward sust. to
     *  find final solution v */
    vec v = b_thilde/b;

    //stopping timer:
    finish_diag = clock();
    double time_diag = ( (finish_diag - start_diag)/((double)CLOCKS_PER_SEC ) );
    cout << "Substitution: Time for n=" << n << ":  " << time_diag << "seconds" << endl;

    //Sending the vectors to file:
    MakePlotFile(x, v, n, time_diag, "reduced"); //making plot file
    //v.print();
}


void solve_lu(vec b, vec b_thilde, const vec x, const int n)
{
    int a = -1.;
    int c = -1.;
    //creating A, L, U and making shure b_thilde has right dim.:
    mat A = zeros<mat>(n,n);
    mat L = zeros<mat>(n,n);
    mat U = zeros<mat>(n,n);
    b_thilde.shed_row(0);
    b_thilde.shed_row(n);
    for(int i=0, j=1; (i<=n-1) && (j<=n-1); ++i, ++j)
    {
        A(i,j) = c;
        A(i,i) = b[i+1];
        A(j,i) = a;
    }
    A(n-1,n-1) = b[n];

    //clocking the operations (only solve, not making file):
    clock_t start_lu, finish_lu; //declaring start and finish time
    start_lu = clock();

    lu(L,U,A);
    //size(L).print();
    vec y = solve(L,b_thilde);
    //size(y).print();
    vec v = solve(U,y);
    //v.print();

    //stopping timer:
    finish_lu = clock();
    double time_lu = ( (finish_lu - start_lu)/((double)CLOCKS_PER_SEC ) );
    cout << "LU solve: Time for n=" << n << ":  " << time_lu << "seconds" << endl;

    //Sending the vectors to file:
    //MakePlotFile(x, v, n, time_lu, "lu"); //making plot file
}


int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        cout << "No arguments. Give 'n' on command line. Eks n=10: 10" << endl;
        exit(1);
    }
    else
    {
        const int n = atof(argv[1]);
        const double h = 1./(n+1);

        /*Creating vectors b of same length as x, so one extra
         * value on beginning/end of array.
         * a and c is constantly -1, removing them to reduce number of
         * floating point operations (b is changing, not a or c)*/
        vec b = 2.*ones<vec>(n+2);

        //creating vector x and b_thilde
        vec x = linspace<vec>(0, 1, n+2);
        vec b_thilde = h*h*f(x);

        /*Solving equations by forward/backward substitution:
         * (b, b_thilde, x and n not changed in main() so they can be
         * used for next method) */
        Forward_Backward_Substitution(b, b_thilde, x, n);
        //cout << "-----" << endl;

        //Using the armadillo library with LU decomposition to solve the equations:
        solve_lu(b, b_thilde, x, n);

    }

    return 0;
}

