"""
Project 1
File to run the c++ code and plot the data for different n
"""
from pylab import *
import os as os
"""
------------------------------------------------------------------------------------------
"""
#leser filen, lager arrays med dataen:
def read_file(filename):
    infile = open(filename, "r")
    infile_ = infile.readlines()

    x = []
    v = []
    
    for line in infile_:
		if len(line.split()) == 2:
			x.append(float(line.split()[0]))
			v.append(float(line.split()[1]))
    infile.close()

    return array(x), array(v)

def u(x):
	analytic_solution = 1 - (1 - exp(-10))*x - exp(-10*x)
	return analytic_solution

"""
------------------------------------------------------------------------------------------
"""

n = 10

"""
Run c++ code from here with n as command line argument:
"""
os.system('c++ -o main main.cpp')
os.system('./main %s' %n)

"""
Fetching file from c++ code
"""
filename = 'linear_eq_solution_n%s.txt' %n

x, v = read_file(filename)


plot(x,v, 'b')
hold('on')
plot(x,u(x), 'r')
legend(['Numerical', 'Analytic'], loc='lower left')
xlabel('x')
ylabel('Solution')
title('Plot of analytic and numerical solution with n=%s' %n) 
savefig('linear_eq_solution_plot_n%s.eps' %n)

show()





