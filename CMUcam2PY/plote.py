import sys
import time
import scipy
import serial
import numpy as np
import matplotlib.pyplot as plt

ser = serial.Serial(port='/dev/ttyUSB0',baudrate=57600)

#take serial data
def take(x):
    if(x==1):
        return ser.read()
    else:
        return [ser.read() for i in range(x)]

#take serial data until
def takeuntil(x):
    a = []
    char = 0
    while(True):
        char = take(1)
        if(char!=x):
            a.append(char)
        else:
            return a

c=[0]*300
d=np.arange(300)
#cler the first line
a = takeuntil('\n')

fig = plt.figure()
ax = fig.add_subplot(111)
line, = ax.plot(d,c)
fig.canvas.draw()
plt.show(block=False)
plt.autoscale(enable=True)

#plot data
while(True):
    a = takeuntil('\n')
    b = ''.join(a)
    del c[0]
    try:
        c.append(float(b))
    except ValueError:
        c.append(c[-1])

    print c
    print d
    print len(c)
    print len(d)
    line.set_ydata(c)

    fig.canvas.draw()
    ax.relim()
    ax.autoscale_view(True,True,True)
    time.sleep(0.001)
