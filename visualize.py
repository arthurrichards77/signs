import sys
import csv

import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time

if len(sys.argv)<2:
  print("""visualize results.csv""")
  #exit()
  filename='result.csv'
else:
  filename=sys.argv[1]

resdata = []
maxstep = 0

with open(filename, 'r') as csvfile:
  resreader = csv.reader(csvfile, delimiter=',')
  for row in resreader:
    #print(row)
    resdata.append([int(v) for v in row])
    maxstep = int(row[0])

mapsize = resdata[0]
resdata = resdata[1:]

num_agents = max([row[1] for row in resdata])
agent_data=[[row for row in resdata if row[1]==ii] for ii in range(num_agents)]
 
fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)

cols = 'rgbcmyk'

def animate(ii):
    ax1.clear()
    ax1.axis('equal')
    ax1.plot([-1, 1+mapsize[0], 1+mapsize[0], -1, -1],[-1, -1, 1+mapsize[1], 1+mapsize[1], -1],'r-')
    for jj in range(num_agents):
      ax1.plot(agent_data[jj][ii][2],agent_data[jj][ii][3],cols[jj%7]+'.')
      if ii>5:
        ax1.plot([agent_data[jj][ih][2] for ih in range(ii-4,ii+1)],
                 [agent_data[jj][ih][3] for ih in range(ii-4,ii+1)],cols[jj%7]+'-')
ani = animation.FuncAnimation(fig, animate, interval=10)
plt.show()
