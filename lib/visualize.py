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

print(n_trips[-1][:])
print(numpy.shape(x_goal))
print(sum(n_trips[-1][:]))

all_goals = set([(row[4],row[5]) for row in resdata])
x_all_goals = [g[0] for g in all_goals]
y_all_goals = [g[1] for g in all_goals]
goal_list = [g for g in all_goals]

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
    for (i,g) in enumerate(goal_list):
        ax1.plot(g[0],g[1],cols[i%6]+'x')
    ax1.plot(x_curr[ii-4:ii+1],y_curr[ii-4:ii+1],'k-')
    total_trips = 0
    for jj in range(num_agents):
        colx = goal_list.index((x_goal[ii][jj],y_goal[ii][jj]))%6
        col = cols[colx]
        ax1.plot(x_curr[ii][jj],y_curr[ii][jj],col+'.')
        total_trips += n_trips[ii][jj]
    plt.title('Step {} with {} trips completed.'.format(ii,total_trips))

if time_step:
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
