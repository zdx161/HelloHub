from pylab import *

ax = gca()
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')
ax.xaxis.set_ticks_position('bottom')
ax.spines['bottom'].set_position(('data',0))
ax.yaxis.set_ticks_position('left')
ax.spines['left'].set_position(('data',0))


x = linspace(0, 16, 17, endpoint = False)
y = 100 * x / 15
ax.plot(x, y, color = "blue", linestyle = "-", label = "line")
ax.plot(x, y, 'ro')
legend(loc = 'upper left')
show()
