# Python program to determine the Jacobian

from __future__ import division
from math import *
from matplotlib.patches import Patch
from pylab import *
import subprocess
from sys import argv
from datetime import datetime

#print "Process | Number | Iterative | Matrix|" 
time_answer=[]
omegas = [0, 0.25, 0.5, 1,1.5,1.75,1.9,2.0]
points = [10,15,20,25,30,35,40,45,50,60]




for omega in omegas:
	y_time_iterative=[]
	y_loop_iterative=[]
	y_time_answer=[]
	for n in points:
		data= subprocess.Popen('./iterative %s %s %s' % (n, 'SOR', omega), shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE,stdin=subprocess.PIPE).communicate()
		data = data[0].split(",")
		y_time_iterative.append(float(data[0]))
		y_loop_iterative.append(float(data[1]))
		y_time_answer.append(float(data[2]))
	#print points
	#print y_time_iterative
	plt.plot(points, y_loop_iterative,label='%s'%omega,linewidth=4)


plt.xlabel('N')
plt.ylabel('Time(seconds)')
plt.title('Loops required for SOR Scheme with different Omegas')
legend()
show()

