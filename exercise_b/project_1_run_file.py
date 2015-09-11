#Project 1
#File to run the c++ code and plot the data for different n

from pylab import *

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



n = 10

"""
import os as os

Run c++ code from here:

os.system("do something on terminal")
"""



"""
Fetching file from c++ code in built folder
"""
filename = '/Users/Ina/build/build-exercise_b-Desktop_Qt_5_5_0_clang_64bit-Debug/linear_eq_solution_n%s.txt' %n

x, v = read_file(filename)

plot(x,v, 'b')
hold('on')
plot(x,u(x), 'r')
xlabel('x')
ylabel('Solution')
title('Plot of analytic (red) and numerical solution (blue) with n=%s' %n) 
show()





