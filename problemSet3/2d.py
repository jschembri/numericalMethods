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

data= subprocess.Popen('./2d %s' % (calculated_time), shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE,stdin=subprocess.PIPE).communicate()
data = data[0].split(",")
x_values = data[data.index('iterations Start')+1:data.index("iterations End")]

y_newton_values = data[data.index('Newton Start')+1:data.index("Newton End")]
for i in range(0,len(y_newton_values)):
	y_newton_values[i] = float(y_newton_values[i])

y_fpi_values = data[data.index('fpi Start')+1:data.index("fpi End")]
for i in range(0,len(y_fpi_values)):
	y_fpi_values[i] = float(y_fpi_values[i])




plt.subplot(211)
plt.title('Convergence plot 2D')
plt.plot(x_values, y_newton_values, ms=12, label='Newton',linewidth=4)
plt.ylabel('Newton')
plt.yscale('log')

plt.subplot(212)
plt.plot(x_values, y_fpi_values, ms=12, label='FPI',linewidth=4)
plt.ylabel('FPI')
plt.yscale('log')



plt.xlabel('Iterations')



#plt.axis([0,4,0,1.5])

show()
