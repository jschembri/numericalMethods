# Python program to determine the Jacobian

from __future__ import division
from math import *
from matplotlib.patches import Patch
from pylab import *
import subprocess
from sys import argv
from datetime import datetime

print "Process | Number | Iterative | Matrix|" 
jacob_time_answer=[]
jacob_points = [3,5,10,15,20,25,30,35,40,45,50]

jacob_time_iterative=[]
jacob_loop_iterative=[]

gs_points = jacob_points
gs_time_iterative=[]
gs_loop_iterative=[]
gs_time_answer=[]


for n in jacob_points:
	data= subprocess.Popen('./iterative %s %s' % (n, 'Jacobian'), shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE,stdin=subprocess.PIPE).communicate()
	data = data[0].split(",")
	jacob_time_iterative.append(float(data[0]))
	jacob_loop_iterative.append(float(data[1]))
	jacob_time_answer.append(float(data[2]))


for n in gs_points:
	data= subprocess.Popen('./iterative %s %s' % (n, 'Gauss-Seidel'), shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE,stdin=subprocess.PIPE).communicate()
	data = data[0].split(",")
	gs_time_iterative.append(float(data[0]))
	gs_loop_iterative.append(float(data[1]))
	gs_time_answer.append(float(data[2]))


plt.plot(jacob_points, jacob_time_iterative,label='Jacobian',linewidth=4)
plt.plot(gs_points, gs_time_iterative,label='Gauss_Seidel',linewidth=4)
plt.xlabel('N')
plt.ylabel('Loop Iteration')
legend()
show()

