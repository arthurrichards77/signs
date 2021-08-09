import sys
import csv

import numpy
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time

start_time = time.time()

if len(sys.argv)<3:
  print('{} resultfile outputfile [timestep]'.format(sys.argv[0]))
  exit()
else:
  filename=sys.argv[1]
  outputfilename=sys.argv[2]
if len(sys.argv)>3:
  time_step = int(sys.argv[3])
else:
  time_step = None
if len(sys.argv)>4:
  print('{} resultfile outputfile [timestep]'.format(sys.argv[0]))
  exit()

loc = None
a_max = 0
goals = set([])
depots = set([])          
with open('setup.txt', 'r') as setupfile:
    setupreader = csv.reader(setupfile, delimiter=',')
    for row in setupreader:
        if row[0]=='W':
            mapsize = (int(row[1]), int(row[2]))
        elif row[0]=='A':
            a_max = a_max + 1
            if loc:
                depots.add(loc)
        elif row[0]=='G':
            loc = (int(row[1]), int(row[2]))

print('Identified {} depots'.format(len(depots)))
gx = [g[0] for g in depots]
gy = [g[1] for g in depots]

resdata = []
maxstep = 0

with open(filename, 'r') as csvfile:
  resreader = csv.reader(csvfile, delimiter=',')
  for row in resreader:
    resdata.append([int(v) for v in row])
    maxstep = int(row[0])

mapsize = resdata[0]
resdata = resdata[1:]

num_agents = 1+max([row[1] for row in resdata])
num_frames = max([row[0] for row in resdata])

x_curr=numpy.transpose([[row[2] for row in resdata if row[1]==ii] for ii in range(num_agents)])
y_curr=numpy.transpose([[row[3] for row in resdata if row[1]==ii] for ii in range(num_agents)])
x_goal=numpy.transpose([[row[4] for row in resdata if row[1]==ii] for ii in range(num_agents)])
y_goal=numpy.transpose([[row[5] for row in resdata if row[1]==ii] for ii in range(num_agents)])
n_trips=numpy.transpose([[row[6] for row in resdata if row[1]==ii] for ii in range(num_agents)])

# initial_points = set([(x_curr[0][jj],y_curr[0][jj]) for jj in range(num_agents)])
# all_goals = set([(row[4],row[5]) for row in resdata])
# all_depots = all_goals.intersection(initial_points)
# print('Identified {} depots'.format(len(all_depots)))
# x_all_depots = [g[0] for g in all_depots]
# y_all_depots = [g[1] for g in all_depots]

op_time = time.time() - start_time
print('Loading data took {} seconds.'.format(op_time))
start_time = time.time()

fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)

cols = 'rgbmyk'

def animate(ii):
    if ii%100==0:
        print('Rendering step {}'.format(ii))
    ax1.clear()
    ax1.axis('equal')
    ax1.plot([-1, mapsize[0], mapsize[0], -1, -1],[-1, -1, mapsize[1], mapsize[1], -1],'r-')
    #ax1.plot(x_all_depots,y_all_depots,'ks')
    ax1.plot(x_curr[ii-4:ii+1],y_curr[ii-4:ii+1],'k-')
    ax1.plot(gx, gy, 'co', ms=20)
    total_trips = 0
    for jj in range(num_agents):
        colx = jj%6
        col = cols[colx]
        ax1.plot(x_curr[ii][jj],y_curr[ii][jj],col+'.')
        ax1.plot(x_goal[ii][jj],y_goal[ii][jj],col+'x')
        total_trips += n_trips[ii][jj]
    plt.title('Step {} with {} trips completed.'.format(ii,total_trips))

if time_step != None:
  print('Saving snapshot {} to file {}'.format(time_step,outputfilename))
  animate(time_step)
  plt.savefig(outputfilename)
else:
  print('Saving animation of {} frames to file {}'.format(num_frames,outputfilename))
  ani = animation.FuncAnimation(fig, animate, interval=50, frames=num_frames)
  Writer = animation.writers['ffmpeg']
  writer = Writer(fps=15, metadata=dict(artist='Me'), bitrate=1800)
  ani.save(outputfilename, writer=writer)

op_time = time.time() - start_time
print('Visualization took {} seconds.'.format(op_time))
