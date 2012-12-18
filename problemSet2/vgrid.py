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
points = [7, 11, 15, 21, 29, 31,41,51,61,71,81,101,201,301,401,441,511]
loop = 100
schemes = ['simple', 'quadratic', 'average', 'weighted']




y_time=[]
r =[]
for point in points:
	data= subprocess.Popen('./vgrid %s %s' % (point, loop), shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE,stdin=subprocess.PIPE).communicate()
	data = data[0].split(",")
	y_time.append(float(data[0]))
	r.append(float(data[1]))

print points
print y_time
print r
plt.plot(points, y_time,linewidth=4)
plt.xlabel('N')
plt.ylabel('Time(seconds)')
plt.title('V-Grid')
#legend()
show()

