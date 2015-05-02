from pylab import *

ax = gca()
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')
ax.xaxis.set_ticks_position('bottom')
ax.spines['bottom'].set_position(('data',0))
ax.yaxis.set_ticks_position('left')
ax.spines['left'].set_position(('data',0))


x = linspace(1, 20, 5, endpoint = True)
y = (-56.) + (x - 1) * ((-34.) - (-56.)) / (20 - 1)
ax.plot(x, y)
x = 6
y = (-56.) + (x - 1) * ((-34.) - (-56.)) / (20 - 1)
ax.plot(x, y, 'bo')
x = 13
y = (-56.) + (x - 1) * ((-34.) - (-56.)) / (20 - 1)
ax.plot(x, y, 'bo')



x = linspace(20, 60, 10, endpoint = True)
y = (-34.) + (x - 20) * ((-11.) - (-34.)) / (60 - 20)
ax.plot(x, y)
x = 20
y = (-34.) + (x - 20) * ((-11.) - (-34.)) / (60 - 20)
ax.plot(x, y, 'bo')
x = 26
y = (-34.) + (x - 20) * ((-11.) - (-34.)) / (60 - 20)
ax.plot(x, y, 'bo')
x = 33
y = (-34.) + (x - 20) * ((-11.) - (-34.)) / (60 - 20)
ax.plot(x, y, 'bo')
x = 40
y = (-34.) + (x - 20) * ((-11.) - (-34.)) / (60 - 20)
ax.plot(x, y, 'bo')
x = 46
y = (-34.) + (x - 20) * ((-11.) - (-34.)) / (60 - 20)
ax.plot(x, y, 'bo')
x = 53
y = (-34.) + (x - 20) * ((-11.) - (-34.)) / (60 - 20)
ax.plot(x, y, 'bo')



x = linspace(60, 100, 10, endpoint = True)
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
ax.plot(x, y)
x = 60
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
ax.plot(x, y, 'bo')
x = 66
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
ax.plot(x, y, 'bo')
x = 73
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
ax.plot(x, y, 'bo')
x = 80
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
ax.plot(x, y, 'bo')
x = 86
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
ax.plot(x, y, 'bo')
x = 93
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
ax.plot(x, y, 'bo')
x = 100
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
ax.plot(x, y, 'bo')


ax.plot(0, -60., 'bo')

show()
