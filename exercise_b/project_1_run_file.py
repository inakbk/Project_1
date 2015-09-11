#Project 1
#File to run the c++ code from 

from pylab import *

"""
import os as os

Run c++ code from here:

os.system("do something on terminal")
"""


"""
Fetching file from c++ code in built folder
"""

def read_file(filename):
#leser filen, lager arrays med dataen og kaller paa funksjonene over og plotter
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


n = 10
#filename = "Users/Ina/build/build-exercise_b-Desktop_Qt_5_5_0_clang_64bit-Debug/linear_eq_solution_n%s.txt" %n
filename = "linear_eq_solution_n%s.txt" %n

x, y = read_file(filename)

print x
print "------"
print y
plot(x,y)
#show()
