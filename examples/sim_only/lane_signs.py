import sys, os
sys.path.append(os.getcwd()+'/../../lib')
from sign_builder import make_mask, make_sign, save_signs, gray

s1 = make_sign((0,0), # applies to everyone
               (0,0),
               (1,0),
               (0,0),
               (0,0),
               (3,0)) 

s2 = make_sign((0,0),
               (0,0),
               (1,0),
               (0,0),
               (0,0),
               (6,4)) 

s3 = make_sign((0,0),
               (0,0),
               (1,1),
               (0,0),
               (0,0),
               (3,2)) 

s4 = make_sign((0,0),
               (0,0),
               (1,1),
               (0,0),
               (0,0),
               (6,2)) 

s5 = make_sign((0,0),
               (1,0),
               (0,0),
               (0,0),
               (0,0),
               (6,0)) 

s6 = make_sign((0,0),
               (1,0),
               (0,0),
               (0,0),
               (0,0),
               (5,1)) 

s7 = make_sign((0,0),
               (1,1),
               (0,0),
               (0,0),
               (0,0),
               (6,6)) 

s8 = make_sign((0,0),
               (1,1),
               (0,0),
               (0,0),
               (0,0),
               (5,5)) 

signs = [s1,s2,s3,s4,s5,s6,s7,s8]
    
save_signs(signs,'lane_signs.csv')
