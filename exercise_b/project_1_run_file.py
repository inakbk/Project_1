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

N = [10, 100, 1000, 10**4, 10**5, 10**6, 10**7, 10**8]
h = zeros(len(N))
relative_error = zeros(len(N))
i = 1

for n in N:
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

	figure(i)
	plot(x,v, 'b')
	hold('on')
	plot(x,u(x), 'r')
	legend(['Numerical', 'Analytic'], loc='lower left')
	xlabel('x')
	ylabel('Solution')
	title('Plot of analytic and numerical solution with n=%s' %n) 
	savefig('linear_eq_solution_plot_n%s.eps' %n)
	hold('off')

	#show()
	"""
	------------------------------------------------------------------------------------------
	Exercise c
	"""

	relative_error[i-1] = mean(log10(abs((v - u(x))/u(x)))) #extraxting rel. error for each n
#	print relative_error[i-1]
	"""
	#error for one n:
	figure(12)
	rel_err = log10(abs((v - u(x))/u(x)))
	plot(x,rel_err)
	#show()
	"""

	h[i-1] = 1./(n+1)
	i += 1

figure(12)
plot(log10(h), relative_error)
legend(['Relative error'], loc='lower left')
xlabel('$log_{10}(h)$', fontsize=18)
ylabel('Relative error', fontsize=18)
title('Plot of relative error with n=%s' %N) 
savefig('linear_eq_error_plot_N.eps')


show()








