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
        myfile << "Time calculating: " << time_diag << " " << " seconds" << endl;
        myfile << "---------------------" << endl;
        for (int i=1; i<n+1; i++)
        {
            myfile << x[i] << "    " << solution[i] << endl;
        }
        myfile.close();
        cout << "Datafile done for n=" << n << endl;
}

void Forward_Bckward_Substitution(vec b, vec b_thilde, const vec x, const int n)
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
    cout << "Time for n=" << n << ":  " << time_diag << "seconds" << endl;

    //Sending the vectors to file:
    MakePlotFile(x, v, n, time_diag, "reduced"); //making plot file
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
        Forward_Bckward_Substitution(b, b_thilde, x, n);

        //Using the armadillo library with LU decomposition to solve the equations:
        vec a = -1.*ones<vec>(n+2); //two extra values on each side
        vec c = -1.*ones<vec>(n+2);
        mat A = zeros<mat>(n,n);
        for(int i = 0; i>=n; ++i)
        {
            for(int j=0; j>=n-1; ++j)
            {
                A(i,j) = c[j];
                A(i,i) = b[i+1];
                A(j,i) = a[j+1];
        }
        }
        A.print();
        cout << A << endl;

        //clocking the operations (only solve, not making file):
        clock_t start_lu, finish_lu; //declaring start and finish time
        start_lu = clock();

//do something here
        //lu(L,U,X)
        //X = solve(A,B)

        //stopping timer:
        finish_lu = clock();
        double time_lu = ( (finish_lu - start_lu)/((double)CLOCKS_PER_SEC ) );
        cout << "Time for n=" << n << ":  " << time_lu << "seconds" << endl;

        //Sending the vectors to file:
        MakePlotFile(x, v, n, time_lu, "lu"); //making plot file
    }

    return 0;
}

