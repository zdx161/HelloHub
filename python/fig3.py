from pylab import *

ax = gca()
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')
ax.xaxis.set_ticks_position('bottom')
ax.spines['bottom'].set_position(('data',0))
ax.yaxis.set_ticks_position('left')
ax.spines['left'].set_position(('data',0))

db = np.linspace(-56.0, 0, 16, endpoint = True)
amp = exp(db * 0.115129)
ax.plot(db, amp, linestyle = '-', label = "amplification")
legend(loc = 'upper left')

x = 6
y = (-56.) + (x - 1) * ((-34.) - (-56.)) / (20 - 1)
ax.plot(y, exp(y * 0.115129), 'ro')
x = 13
y = (-56.) + (x - 1) * ((-34.) - (-56.)) / (20 - 1)
ax.plot(y, exp(y * 0.115129), 'ro')

x = 20
y = (-34.) + (x - 20) * ((-11.) - (-34.)) / (60 - 20)
ax.plot(y, exp(y * 0.115129), 'ro')
x = 26
y = (-34.) + (x - 20) * ((-11.) - (-34.)) / (60 - 20)
ax.plot(y, exp(y * 0.115129), 'ro')
x = 33
y = (-34.) + (x - 20) * ((-11.) - (-34.)) / (60 - 20)
ax.plot(y, exp(y * 0.115129), 'ro')
x = 40
y = (-34.) + (x - 20) * ((-11.) - (-34.)) / (60 - 20)
ax.plot(y, exp(y * 0.115129), 'ro')
x = 46
y = (-34.) + (x - 20) * ((-11.) - (-34.)) / (60 - 20)
ax.plot(y, exp(y * 0.115129), 'ro')
x = 53
y = (-34.) + (x - 20) * ((-11.) - (-34.)) / (60 - 20)
ax.plot(y, exp(y * 0.115129), 'ro')

x = 60
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
ax.plot(y, exp(y * 0.115129), 'ro')
x = 66
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
ax.plot(y, exp(y * 0.115129), 'ro')
x = 73
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
ax.plot(y, exp(y * 0.115129), 'ro')
x = 80
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
ax.plot(y, exp(y * 0.115129), 'ro')
x = 86
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
ax.plot(y, exp(y * 0.115129), 'ro')
x = 93
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
ax.plot(y, exp(y * 0.115129), 'ro')
x = 100
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
ax.plot(y, exp(y * 0.115129), 'ro')

fig = figure()
plot(db, amp * 8192, linestyle = "-", label = "8192")
plot(db, amp * 4096, linestyle = "-", label = "4096")
plot(db, amp * 2048, linestyle = "-", label = "2048")
plot(db, amp * 1024, linestyle = "-", label = "1024")
legend(loc = 'upper left')


figure()
plot(db, amp * 4096, linestyle = '-', label = "f4.12")
legend(loc = 'upper left')

x = 6
y = (-56.) + (x - 1) * ((-34.) - (-56.)) / (20 - 1)
plot(y, exp(y * 0.115129) * 4096, 'ro')
x = 13
y = (-56.) + (x - 1) * ((-34.) - (-56.)) / (20 - 1)
plot(y, exp(y * 0.115129) * 4096, 'ro')

x = 20
y = (-34.) + (x - 20) * ((-11.) - (-34.)) / (60 - 20)
plot(y, exp(y * 0.115129) * 4096, 'ro')
x = 26
y = (-34.) + (x - 20) * ((-11.) - (-34.)) / (60 - 20)
plot(y, exp(y * 0.115129) * 4096, 'ro')
x = 33
y = (-34.) + (x - 20) * ((-11.) - (-34.)) / (60 - 20)
plot(y, exp(y * 0.115129) * 4096, 'ro')
x = 40
y = (-34.) + (x - 20) * ((-11.) - (-34.)) / (60 - 20)
plot(y, exp(y * 0.115129) * 4096, 'ro')
x = 46
y = (-34.) + (x - 20) * ((-11.) - (-34.)) / (60 - 20)
plot(y, exp(y * 0.115129) * 4096, 'ro')
x = 53
y = (-34.) + (x - 20) * ((-11.) - (-34.)) / (60 - 20)
plot(y, exp(y * 0.115129) * 4096, 'ro')

x = 60
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
plot(y, exp(y * 0.115129) * 4096, 'ro')
x = 66
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
plot(y, exp(y * 0.115129) * 4096, 'ro')
x = 73
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
plot(y, exp(y * 0.115129) * 4096, 'ro')
x = 80
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
plot(y, exp(y * 0.115129) * 4096, 'ro')
x = 86
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
plot(y, exp(y * 0.115129) * 4096, 'ro')
x = 93
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
plot(y, exp(y * 0.115129) * 4096, 'ro')
x = 100
y = (-11.) + (x - 60) * ((0) - (-11.)) / (100 - 60)
plot(y, exp(y * 0.115129) * 4096, 'ro')

show()
