import sys
import csv

import numpy
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time

def gray(x):
  return (x ^ (x>>1))

if len(sys.argv)<2:
  print("""visualize results.csv [signfile.csv]""")
  #exit()
  filename='result.csv'
else:
  filename=sys.argv[1]

resdata = []
maxstep = 0

with open(filename, 'r') as csvfile:
  resreader = csv.reader(csvfile, delimiter=',')
  for row in resreader:
    resdata.append([int(v) for v in row])
    maxstep = int(row[0])

mapsize = resdata[0]
resdata = resdata[1:]

num_agents = max([row[1] for row in resdata])
x_data=numpy.transpose([[row[2] for row in resdata if row[1]==ii] for ii in range(num_agents)])
y_data=numpy.transpose([[row[3] for row in resdata if row[1]==ii] for ii in range(num_agents)])

goals = set([(row[4],row[5]) for row in resdata])
x_goals = [g[0] for g in goals]
y_goals = [g[1] for g in goals]

x_sign = []
y_sign = []
signdata = []
if len(sys.argv)>2:
   signfile=sys.argv[2]
   with open(signfile, 'r') as csvfile:
       signreader = csv.reader(csvfile, delimiter=',')
       for row in signreader:
           signdata.append([int(v) for v in row[1:]])
for x in range(mapsize[0]):
  for y in range(mapsize[1]):
    for s in signdata:
      if (gray(x)&s[2])^s[3]==0:
        if (gray(y)&s[4])^s[5]==0:
          x_sign.append(x)
          y_sign.append(y)

fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)

cols = 'rgbcmyk'

def animate(ii):
    ax1.clear()
    ax1.axis('equal')
    ax1.plot([-1, 1+mapsize[0], 1+mapsize[0], -1, -1],[-1, -1, 1+mapsize[1], 1+mapsize[1], -1],'r-')
    ax1.plot(x_goals,y_goals,'gx')
    ax1.plot(x_sign,y_sign,'c+')
    ax1.plot(x_data[ii],y_data[ii],'k.')
    ax1.plot(x_data[ii-4:ii+1],y_data[ii-4:ii+1],'-')

ani = animation.FuncAnimation(fig, animate, interval=10)
plt.show()
