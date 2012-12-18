# Python program to determine the Jacobian

from __future__ import division
from math import *
from matplotlib.patches import Patch
from pylab import *
import subprocess
from sys import argv
from datetime import datetime

#print "Process | Number | Iterative | Matrix|" 
n = 51

data= subprocess.Popen('./residual %s %s %s' % (15, 'Jacobian',1000), shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE,stdin=subprocess.PIPE).communicate()
data = data[0].split("\n")
x = []
y = []

for i in range(0, len(data)-1):
	x.append( float(data[i].split(",")[0]))
	y.append( pow(10,-3)*float(data[i].split(",")[1]))
	

plt.plot(x, y,linewidth=4)
plt.xlabel('Loops')
plt.ylabel('Residual')
plt.yscale('log')
plt.title('Jacobian Convergence')
# legend()
show()

