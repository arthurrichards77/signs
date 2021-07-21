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
x_curr=numpy.transpose([[row[2] for row in resdata if row[1]==ii] for ii in range(num_agents)])
y_curr=numpy.transpose([[row[3] for row in resdata if row[1]==ii] for ii in range(num_agents)])
x_goal=numpy.transpose([[row[4] for row in resdata if row[1]==ii] for ii in range(num_agents)])
y_goal=numpy.transpose([[row[5] for row in resdata if row[1]==ii] for ii in range(num_agents)])

all_goals = set([(row[4],row[5]) for row in resdata])
x_all_goals = [g[0] for g in all_goals]
y_all_goals = [g[1] for g in all_goals]
goal_list = [g for g in all_goals]

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
    for (i,g) in enumerate(goal_list):
        ax1.plot(g[0],g[1],cols[i%7]+'x')
    ax1.plot(x_sign,y_sign,'c+')
    ax1.plot(x_curr[ii-4:ii+1],y_curr[ii-4:ii+1],'k-')
    for jj in range(num_agents):
        for s in signdata:
             if (gray(x_curr[ii][jj])&s[2])^s[3]==0:
               if (gray(y_curr[ii][jj])&s[4])^s[5]==0:
                 if (gray(x_goal[ii][jj])&s[6])^s[7]==0:
                   if (gray(y_goal[ii][jj])&s[8])^s[9]==0:
                     if (gray(jj)&s[0]^s[1])==0:
                       ax1.plot(x_curr[ii][jj],y_curr[ii][jj],'rs')
        colx = goal_list.index((x_goal[ii][jj],y_goal[ii][jj]))%7
        col = cols[colx]
        ax1.plot(x_curr[ii][jj],y_curr[ii][jj],col+'.')

ani = animation.FuncAnimation(fig, animate, interval=50)
plt.show()
