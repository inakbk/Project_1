//Exercise b, algorithm for solving the set of linear equations
//a_i*v_(i-1) + b_i*v_i + c_i*v_(i+1) = h*h*f(x_i)

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
void MakePlotFile(const vec x, const vec solution, const int n, const double time_diag)
{
    ofstream myfile;
        string filename = "linear_eq_solution_n" + to_string(n) + ".txt";
        myfile.open (filename);
        myfile << "Data:" << "  "<< "x" << "     " << "Solution" << endl;
        myfile << "Time calculating: " << time_diag << " seconds" << endl;
        myfile << "---------------------" << endl;
        for (int i=1; i<n+1; i++)
        {
            myfile << x[i] << "    " << solution[i] << endl;
        }
        myfile.close();
}

int main(int argc, char *argv[], char *argv[])
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

        //clocking the operations (only solve, not making file):
        clock_t start_diag, finish_diag; //declaring start and finish time
        start = clock()

        //forward substitution:
        for(int i = 2; i < n+1; ++i) //starting from second row till last
        {
            b[i] = b[i] - (a[i]*c[i-1])/b[i-1]; //b' one iteration
            b_thilde[i] = b_thilde[i] - (a[i]*b_thilde[i-1])/b[i-1];
        }

        //backward substitution:
        for(int i = n; i > 1; --i) //starting from last row n to i==1
        {
            b_thilde[i-1] = b_thilde[i-1] - (c[i-1]*b_thilde[i])/b[i];
        }

        /*Final solution, dividing by b[i-1] after backward sust. to
         *  find final solution v */
        vec v = b_thilde/b;
        finish_diag = clock();
        double time_diag = ( (finish_diag - start_diag)/CLOCKS_PER_SEC );
        cout << "Time for n=" << n << " :  " << time_diag << endl;

        MakePlotFile(x, v, n, time_diag); //making plot file in built folder

        cout << "Datafile done for n=" << n << endl;

    }

    return 0;
}

