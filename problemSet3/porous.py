# Quasi 1D code
# created by Jeremy Schembr on November 8, 2012

from sys import argv
from matplotlib.patches import Patch
from pylab import *
import subprocess


if len(argv) < 2:
   calculated_time= "There is none"
else:
   script, calculated_time = argv

data= subprocess.Popen('./porous %s' % (calculated_time), shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE,stdin=subprocess.PIPE).communicate()
data = data[0].split(",")
x_values = data[data.index('iterations Start')+1:data.index("iterations End")]
for i in range(0,len(x_values)):
	x_values[i] = float(x_values[i])
y_values = data[data.index('fpi Start')+1:data.index("fpi End")]
for i in range(0,len(y_values)):
	y_values[i] = float(y_values[i])

#x_values = data[data.index('actual Start')+1:data.index("actual End")]
#for i in range(0,len(x_values)):
#	x_values[i] = float(x_values[i])
#y_values = data[data.index('error Start')+1:data.index("error End")]
#for i in range(0,len(y_values)):
#	y_values[i] = float(y_values[i])



plt.plot(x_values, y_values, ms=12, label='Porous',linewidth=4)
plt.ylabel('u')
#plt.yscale('log')

#plt.legend()
plt.xlabel('X-Location')

#plt.title('Porous Medium 1D equation m=2')
plt.title('Convergence Plot')

#plt.axis([0,4,0,1.5])

show()

