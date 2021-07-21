import sys, os
sys.path.append(os.getcwd()+'/../../lib')
from sign_builder import make_mask, make_sign, save_signs, gray

s1 = make_sign((0,0), # applies to everyone
               (64,64),
               (64,64),
               (0,0),
               (64,0),
               (2,0)) 

signs = []

for y in range(80,100):
    s = make_sign((0,0),
               (255,gray(100)),
               (255,gray(y)),
               (255,gray(100)),
               (255,gray(100)),
               (7,gray(1)))
    signs.append(s[:])
    s = make_sign((0,0),
               (255,gray(99)),
               (255,gray(y)),
               (255,gray(100)),
               (255,gray(100)),
               (2,2))
    signs.append(s[:])
    s = make_sign((0,0),
               (255,gray(101)),
               (255,gray(y)),
               (255,gray(100)),
               (255,gray(100)),
               (2,0))
    signs.append(s[:])

for y in range(101,120):
    s = make_sign((0,0),
               (255,gray(100)),
               (255,gray(y)),
               (255,gray(100)),
               (255,gray(100)),
               (7,gray(5)))
    signs.append(s[:])
    s = make_sign((0,0),
               (255,gray(99)),
               (255,gray(y)),
               (255,gray(100)),
               (255,gray(100)),
               (2,2))
    signs.append(s[:])
    s = make_sign((0,0),
               (255,gray(101)),
               (255,gray(y)),
               (255,gray(100)),
               (255,gray(100)),
               (2,0))
    signs.append(s[:])
    
save_signs(signs,'manual_signs.csv')
