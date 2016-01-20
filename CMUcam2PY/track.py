import sys
import time
import scipy
import serial
import numpy as np
import matplotlib.pyplot as plt

# read file with rgb
file = open("rgb.txt", "r")
line = file.readline()
line = (line[1:-1]).split(',')
rgbv = [float(i) for i in line]
print rgbv

# open serial port
ser = serial.Serial(port='/dev/ttyUSB0',baudrate=115200)

image = [['.' for i in range(143)] for u in range(87)]

# draw a box with ascii on terminal
def drawbox(xyv):
    image = [['.' for i in range(143)] for u in range(87)]
    for i in xrange(xyv[0],xyv[2]):
        for u in xrange(xyv[1],xyv[3]):
            image[i][u]='X'
    return image

def take(x):
    if(x==1):
        return ser.read()
    else:
        return [ser.read() for i in range(x)]

def takeuntil(x):
    a = []
    char = 0
    while(True):
        char = take(1)
        if(char!=x):
            a.append(char)
        else:
            return a

# restart camera
ser.write("RS \r")
time.sleep(0.5);
#rgbv=[35,0,196,146,255,230]
# ask camera to send tracking possition of RGB vector
com = str((("TC %d %d %d %d %d %d \r")%(255-rgbv[0],255-rgbv[1],255-rgbv[2],255-rgbv[3],255-rgbv[4],255-rgbv[5])))
ser.write(com)

while(True):
    data = []
    ser.flushInput()
    ser.flushOutput()
    takeuntil('T')

    data = ''.join(takeuntil('\r'))
    data = data.split(' ')
    print data
    print data[0]
    if(data[0]==''):
        print data[3:7]
        a = drawbox([int(data[3]),int(data[4]),int(data[5]),int(data[5])])
        #print a
        for i in range(len(a)):
            print ''.join(a[i])
        #plt.imshow(image2)

    #plt.show(block=False)
    time.sleep(0.012)
    sys.stderr.write("\x1b[2J\x1b[H")
    #plt.pause(0.0000001)
