from pylab import *
from math import *

ax = gca()
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')
ax.xaxis.set_ticks_position('bottom')
ax.spines['bottom'].set_position(('data',0))
ax.yaxis.set_ticks_position('left')
ax.spines['left'].set_position(('data',0))


x = linspace(-32, 32, 2048, endpoint = True)
y = x**3 + x**2 + x 
ax.plot(x, y, color = "blue", linestyle = "-", label = "cubic")
legend(loc = 'upper left')


show()
