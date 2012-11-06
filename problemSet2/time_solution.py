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
points = [7, 11, 15, 21, 29, 31,41,51,61,71,81]
schemes = ['simple', 'quadratic', 'average', 'weighted']




for scheme in schemes:
	y_time=[]
	for point in points:
		data= subprocess.Popen('./time_resolution %s %s' % (point, scheme), shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE,stdin=subprocess.PIPE).communicate()
		data = data[0].split(",")
		y_time.append(float(data[0]))
	plt.plot(points, y_time,label='%s'%scheme,linewidth=4)


plt.xlabel('N')
plt.ylabel('Time')
legend()
show()

