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
           
x_max = max([s[2] for s in signdata])
y_max = max([s[4] for s in signdata])
xg_max = max([s[6] for s in signdata])
yg_max = max([s[8] for s in signdata])
a_max = max([s[0] for s in signdata])

mapsize = (128,128)
a_max = 163

move_codes = [(-1,1),
              (0,1),
              (1,1),
              (1,0),
              (1,-1),
              (0,-1),
              (-1,-1),
              (-1,0)]

def plot_sign(s):
  
    print(s)
    fig = plt.figure()

    ax1 = fig.add_subplot(2,2,1)
    xs = []
    ys = []
    ax1.set_title('Pos: (X AND {}) XOR {}, (Y AND {}) XOR {}'.format(s[2],s[3],s[4],s[5]))
    for x in range(mapsize[0]):
        for y in range(mapsize[1]):
            if (gray(x)&s[2])^s[3]==0:
                if (gray(y)&s[4])^s[5]==0:
                       xs.append(x)
                       ys.append(y)
    ax1.plot(xs,ys,'b+')
    ax1.plot([-1, 1+mapsize[0], 1+mapsize[0], -1, -1],[-1, -1, 1+mapsize[1], 1+mapsize[1], -1],'r-')


    ax2 = fig.add_subplot(2,2,2)    
    xs = []
    ys = []
    ax2.set_title('Goal: (X AND {}) XOR {}, (Y AND {}) XOR {}'.format(s[6],s[7],s[8],s[9]))
    for x in range(mapsize[0]):
        for y in range(mapsize[1]):
            if (gray(x)&s[6])^s[7]==0:
                if (gray(y)&s[8])^s[9]==0:
                       xs.append(x)
                       ys.append(y)
    ax2.plot(xs,ys,'g+')
    ax2.plot([-1, 1+mapsize[0], 1+mapsize[0], -1, -1],[-1, -1, 1+mapsize[1], 1+mapsize[1], -1],'r-')

    ax3 = fig.add_subplot(2,2,3)    
    ids = []
    ax3.set_title('Agent: (ID AND {}) XOR {}'.format(s[0],s[1]))
    for a in range(a_max):
            if (gray(a)&s[0])^s[1]==0:
                       ids.append(a)
    ax3.plot(ids,ids,'c+')
    ax3.plot([-1,1+a_max],[-1,1+a_max],'r-')

    ax4 = fig.add_subplot(2,2,4)    
    mvs = []
    ax4.set_title('Move: (Code AND {}) XOR {}'.format(s[10],s[11]))
    for m in range(8):
            if (gray(m)&s[10])^s[11]==0:
                       mvs.append(m)
    ax4.plot([move_codes[m][0] for m in mvs],[move_codes[m][1] for m in mvs],'m+')
    ax4.plot([-2, 2, 2, -2, -2],[-2, -2, 2, 2, -2],'r-')

                                              
for s in signdata:
    plot_sign(s)
plt.show()

