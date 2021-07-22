import sys, os
sys.path.append(os.getcwd()+'/../../lib')
from sign_builder import make_mask, make_sign, save_signs, gray

s1 = make_sign((0,0), # applies to everyone
               make_mask(115,125,8),
               (64,64),
               (0,0),
               make_mask(0,7,8),
               (2,0)) 

s2 = make_sign((0,0),
               make_mask(32,56,8),
               make_mask(40,80,8),
               (255,gray(50)),
               (255,gray(5)),
               (2,2))

s3 = make_sign((0,0),
               make_mask(32,56,8),
               make_mask(80,120,8),
               (255,gray(50)),
               (255,gray(5)),
               (2,2))

signs = [s1,s2,s3]

for y in range(80,100):
    s = make_sign((0,0),
               (255,gray(100)),
               (255,gray(y)),
               (255,gray(100)),
               (255,gray(100)),
               (7,gray(1)))
    signs.append(s[:])
    s = make_sign((0,0),
               make_mask(98,99,8),
               (255,gray(y)),
               (255,gray(100)),
               (255,gray(100)),
               (2,2))
    signs.append(s[:])
    s = make_sign((0,0),
               make_mask(101,102,8),
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
               make_mask(98,99,8),
               (255,gray(y)),
               (255,gray(100)),
               (255,gray(100)),
               (2,2))
    signs.append(s[:])
    s = make_sign((0,0),
               make_mask(101,102,8),
               (255,gray(y)),
               (255,gray(100)),
               (255,gray(100)),
               (2,0))
    signs.append(s[:])
    
save_signs(signs,'manual_signs.csv')
