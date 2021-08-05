import sys
import csv

import numpy
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time

def gray(x):
  return (x ^ (x>>1))

if len(sys.argv)<2:
  print("""plot_signs signfile.csv""")
  exit()
else:
  filename=sys.argv[1]

x_sign = []
y_sign = []
signdata = []

with open(filename, 'r') as csvfile:
    signreader = csv.reader(csvfile, delimiter=',')
    for row in signreader:
        signdata.append([int(v) for v in row[1:]])
print('Loaded {} signs'.format(len(signdata)))
           
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

move_codes = [(-1,1),
              (0,1),
              (1,1),
              (1,0),
              (1,-1),
              (0,-1),
              (-1,-1),
              (-1,0)]

def plot_sign(s, filename=None):
  
    print(s)
    fig = plt.figure()

    ax1 = fig.add_subplot(1,3,1)
    xs = []
    ys = []
    ax1.set_title('Position: $((x \cdot {}) \oplus {}=0)$ \n $ \wedge ((y \cdot {}) \oplus {}=0)$'.format(s[2],s[3],s[4],s[5]))
    for x in range(mapsize[0]):
        for y in range(mapsize[1]):
            if (gray(x)&s[2])^s[3]==0:
                if (gray(y)&s[4])^s[5]==0:
                       xs.append(x)
                       ys.append(y)
    ax1.plot(xs,ys,'b.',markersize=1)
    ax1.plot([-1, mapsize[0], mapsize[0], -1, -1],[-1, -1, mapsize[1], mapsize[1], -1],'r-')
    ax1.set_aspect('equal', 'box')


    ax2 = fig.add_subplot(1,3,2)    
    xs = []
    ys = []
    ax2.set_title('Goal: $((x_g \cdot {}) \oplus {}=0) $ \n $ \wedge ((y_g \cdot {}) \oplus {}=0)$'.format(s[6],s[7],s[8],s[9]))
    for x in range(mapsize[0]):
        for y in range(mapsize[1]):
            if (gray(x)&s[6])^s[7]==0:
                if (gray(y)&s[8])^s[9]==0:
                       xs.append(x)
                       ys.append(y)
    ax2.plot(xs,ys,'g.',markersize=1)
    ax2.plot(gx,gy,'k+')
    ax2.plot([-1, mapsize[0], mapsize[0], -1, -1],[-1, -1, mapsize[1], mapsize[1], -1],'r-')
    ax2.set_aspect('equal', 'box')

    ax4 = fig.add_subplot(1,3,3)    
    mvs = []
    ax4.set_title('Move: $(m \cdot {}) \oplus {}=0$'.format(s[10],s[11]))
    for m in range(8):
            if (gray(m)&s[10])^s[11]==0:
                       mvs.append(m)
    ax4.plot([move_codes[m][0] for m in mvs],[move_codes[m][1] for m in mvs],'rx',
             markersize=12)
    ax4.plot([-1.5, 1.5, 1.5, -1.5, -1.5],[-1.5, -1.5, 1.5, 1.5, -1.5],'m-')
    ax4.plot([-0.5, 0.5, 0.5, -0.5, -0.5],[-1.5, -1.5, 1.5, 1.5, -1.5],'m-')
    ax4.plot([-1.5, 1.5, 1.5, -1.5, -1.5],[-0.5, -0.5, 0.5, 0.5, -0.5],'m-')
    ax4.set_aspect('equal', 'box')
    
    fig.tight_layout(h_pad=1.0,w_pad = 1.0)
    
    if filename:
      print('Saving to {}'.format(filename))
      fig.savefig(filename,dpi=300)
                                              
for (i,s) in enumerate(signdata):
    plot_sign(s,'{}.s{}.pdf'.format(filename,i))
#plt.show()

