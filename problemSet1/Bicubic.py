# Lagrangian Interpolation for Problem Set #1
# Jeremy Schembri on Oct 12, 2012

# analytic C++ displays the analytic answer
from __future__ import division
from math import *
from matplotlib.patches import Patch
from pylab import *
import subprocess
from sys import argv

delta_values=[]
errors=[]
for delta in [0.0005, 0.001,0.002, 0.003, 0.004, 0.005,0.006,0.007, 0.008, 0.009, 0.01,0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1,0.15, 0.2,0.25,0.4,0.5]:
	max_error = float(subprocess.Popen('./twoD %s ' % (delta), shell=True, stdout=subprocess.PIPE,stderr=subprocess.PIPE,stdin=subprocess.PIPE).communicate()[0].split(",")[0])
	delta_values.append(delta)
	errors.append(max_error)
	print "%f|%.10g" % (delta, max_error)

plt.plot((delta_values), (errors),linewidth=4)
plt.yscale('log')
plt.xscale('log')
plt.xlabel('Log(Delta)')
plt.ylabel('Log(Error)')
plt.title('Bicubic Spline Error')
show()
