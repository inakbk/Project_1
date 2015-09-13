"""
Project 1
File to run the c++ code and plot the data for different n

C++ code with LU decomposition needs to be run in QT Creator first to avoid (weird) compilation error:

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
		if len(line.split()) >= 4:
			time = float(line.split()[4])
    infile.close()

    return array(x), array(v), time

def u(x):
	analytic_solution = 1 - (1 - exp(-10))*x - exp(-10*x)
	return analytic_solution

"""
------------------------------------------------------------------------------------------
"""

N = [10, 100]#, 1000, 10**4]#, 10**5]#, 10**6, 10**7, 10**8]
h = zeros(len(N))
relative_error = zeros(len(N))
relative_error_lu = zeros(len(N))
time_diag = zeros(len(N))
time_lu = zeros(len(N))
i = 1

for n in N:
	"""
	Run c++ code from here with n as command line argument:
	"""
	os.system('c++ -o main main.cpp')
	os.system('./main %s' %n)

	"""
	Fetching file from c++ code
	C++ code with LU decomposition needs to be run in QT Creator first to avoid (weird) compilation error..
	"""
	filename_subst = 'linear_eq_solution_reduced_n%s.txt' %n
	filename_lu = '/Users/Ina/build/build-exercise_d-Desktop_Qt_5_5_0_clang_64bit-Debug/linear_eq_solution_lu_n%s.txt' %n

	x, v, time_diag[i-1] = read_file(filename_subst)
	x_lu, v_lu, time_lu[i-1] = read_file(filename_lu)
	
	figure(i)
	plot(x,v, 'b')
	hold('on')
	plot(x_lu,v_lu, 'g')
	plot(x,u(x), 'r')
	legend(['Numerical subst.','Numerical lu dec.', 'Analytic solution'], fontsize=18, loc='lower left')
	xlabel('x', fontsize=18)
	ylabel('Solution', fontsize=18)
	title('Plot of analytic and numerical solutions with n=%s ' %n, fontsize=18) 
	savefig('linear_eq_solution_plot_all_num_n%s.eps' %n)
	hold('off')

	"""
	------------------------------------------------------------------------------------------
	Exercise c,d
	"""

	relative_error[i-1] = mean((abs((v - u(x))/u(x)))) #extraxting rel. error for each n
	relative_error_lu[i-1] = mean((abs((v_lu - u(x))/u(x)))) 

	h[i-1] = 1./(n+1)
	i += 1

figure(12)
subplot(211)
grid('on')
loglog(h, relative_error, 'ko-')
hold('on')
loglog(h, relative_error_lu, 'ro-')
legend(['Relative error subst.', 'Relative error lu dec.'], fontsize=14, loc='lower left')
xlabel('h', fontsize=18)
ylabel('Relative error', fontsize=18)
title('Plot of relative error for both numerical methods with n=%s' %N, fontsize=16) 
savefig('linear_eq_error_plot_all_num_N%s.eps' %N[-1])
hold('off')

#figure(13)
subplot(212)
loglog(h, time_diag, 'bo-')
hold('on')
loglog(h, time_lu, 'go-')
legend(['Time subst.', 'Time lu dec.'], fontsize=14, loc='lower left')
xlabel('h', fontsize=18)
ylabel('Time [sec]', fontsize=18)
title('Plot of execution time for both numerical methods with %s' %N, fontsize=16) 
savefig('linear_eq_time_plot_all_num_N%s.eps' %N[-1])

tight_layout()

show()








