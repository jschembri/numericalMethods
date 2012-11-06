# Python program to determine the Jacobian

from __future__ import division
from math import *
from matplotlib.patches import Patch
from pylab import *
import subprocess
from sys import argv
from datetime import datetime

print "Process | Number | Iterative | Matrix|" 
time_answer=[]
points = [3,5,10,15,20,25,30,35,40,45]
time_iterative=[]
loop_iterative=[]

for n in points:
	data= subprocess.Popen('./jacob %s' % n, shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE,stdin=subprocess.PIPE).communicate()
	data = data[0].split(",")
	time_iterative.append(float(data[0]))
	loop_iterative.append(float(data[1]))
	time_answer.append(float(data[2]))

plt.plot(points, time_iterative,linewidth=4)
plt.xlabel('N')
plt.ylabel('Time(seconds)')
plt.title('Time required for Jacobian Iteration')
show()

