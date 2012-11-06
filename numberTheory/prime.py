# problem looking at solving for primes using a few methods and testing the time
from __future__ import division
from sys import argv
from math import *
from matplotlib.patches import Patch
from pylab import *
from datetime import datetime
import subprocess


script, prime_number = argv


t0 = datetime.now()
data= subprocess.Popen('./prime %s' % prime_number, shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE,stdin=subprocess.PIPE).communicate()
data = data[0].split(",")

print "Process | Time(s) | Standard Deviation | Max Error" 

x_values = data[data.index('X Values Start')+1:data.index("X Values End")]
for i in range(0,len(x_values)):
   x_values[i] = float(x_values[i])
t1 = datetime.now()
time = (t1-t0).seconds
#print "%s | %s | %.3f | %.3f " % ("Upwind", time, std, max_element)

y_values = data[data.index('Y Values Start')+1:data.index("Y Values End")]
for i in range(0,len(y_values)):
   y_values[i] = float(y_values[i])

x_lagrange = data[data.index('X Lagrange Start')+1:data.index("X Lagrange End")]
for i in range(0,len(x_lagrange)):
   x_lagrange[i] = float(x_lagrange[i])

y_lagrange = data[data.index('Y Lagrange Start')+1:data.index("Y Lagrange End")]
for i in range(0,len(y_lagrange)):
   y_lagrange[i] = float(y_lagrange[i])

x_lagrange_values = data[data.index('X Lagrange Values Start')+1:data.index("X Lagrange Values End")]
for i in range(0,len(x_lagrange_values)):
   x_lagrange_values[i] = float(x_lagrange_values[i])

y_lagrange_values = data[data.index('Y Lagrange Values Start')+1:data.index("Y Lagrange Values End")]
for i in range(0,len(y_lagrange_values)):
   y_lagrange_values[i] = float(y_lagrange_values[i])





plt.plot(x_values, y_values, mfc='red', ms=12, label='Analytical')
plt.plot(x_lagrange_values, y_lagrange_values,'x')
plt.plot(x_lagrange, y_lagrange)
plt.xlabel('X Values')
plt.ylabel('Y Values')
plt.title('First Plot')
plt.axis([1,15,-1.5,1.5])
legend()
show()

