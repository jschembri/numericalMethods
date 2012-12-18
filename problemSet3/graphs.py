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

data= subprocess.Popen('./convergenceRate %s' % (calculated_time), shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE,stdin=subprocess.PIPE).communicate()
data = data[0].split(",")
x_values = data[data.index('iterations Start')+1:data.index("iterations End")]
for i in range(0,len(x_values)):
	x_values[i] = float(x_values[i])
y_values = data[data.index('Bisection Start')+1:data.index("Bisection End")]
for i in range(0,len(y_values)):
	y_values[i] = float(y_values[i])

y_secant_values = data[data.index('Secant Start')+1:data.index("Secant End")]
for i in range(0,len(y_secant_values)):
	y_secant_values[i] = float(y_secant_values[i])

y_newton_values = data[data.index('Newton Start')+1:data.index("Newton End")]
for i in range(0,len(y_newton_values)):
	y_newton_values[i] = float(y_newton_values[i])

y_fpi_values = data[data.index('FPI Start')+1:data.index("FPI End")]
for i in range(0,len(y_fpi_values)):
	y_fpi_values[i] = float(y_fpi_values[i])

y_aikten_values = data[data.index('aikten Start')+1:data.index("aikten End")]
for i in range(0,len(y_aikten_values)):
	y_aikten_values[i] = float(y_aikten_values[i])




#plt.subplot(211)

#plt.plot(x_values, y_values, ms=12, label='Bisection',linewidth=4)
#plt.ylabel('Bisection')
#plt.yscale('log')

#plt.subplot(212)
#plt.plot(x_values, y_secant_values, ms=12, label='Secant',linewidth=4)
#plt.ylabel('Secant')
#plt.yscale('log')

plt.subplot(311)
plt.title('Convergence Plots')
plt.plot(x_values, y_newton_values, ms=12, label='Newton',linewidth=4)
plt.ylabel('Newton')
plt.yscale('log')

plt.subplot(312)
plt.plot(x_values, y_fpi_values, ms=12, label='FPI',linewidth=4)
plt.ylabel('FPI')
plt.yscale('log')

plt.subplot(313)
plt.plot(x_values, y_aikten_values, ms=12, label='Aikten',linewidth=4)
plt.ylabel('aikten')
plt.yscale('log')






#plt.legend()
plt.xlabel('Iterations')



#plt.axis([0,4,0,1.5])

show()

