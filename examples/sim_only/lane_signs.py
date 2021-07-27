import sys, os
sys.path.append(os.getcwd()+'/../../lib')
from sign_builder import make_mask, make_sign, save_signs, gray

even_mask = (1,1)
odd_mask = (1,0)

# can't go left in odd Y lanes
s1 = make_sign((0,0), # applies to everyone
               (0,0),
               odd_mask,
               (0,0),
               (0,0),
               (3,0)) 

s2 = make_sign((0,0),
               (0,0),
               odd_mask,
               (0,0),
               (0,0),
               (6,4)) 

# can't go right in even Y lanes
s3 = make_sign((0,0),
               (0,0),
               even_mask,
               (0,0),
               (0,0),
               (3,2)) 

s4 = make_sign((0,0),
               (0,0),
               even_mask,
               (0,0),
               (0,0),
               (6,2)) 

# can't go UP in odd X lanes
s5 = make_sign((0,0),
               odd_mask,
               (0,0),
               (0,0),
               (0,0),
               (6,0)) 

s6 = make_sign((0,0),
               odd_mask,
               (0,0),
               (0,0),
               (0,0),
               (5,1)) 

# can't go DOWN in even X lanes
s7 = make_sign((0,0),
               even_mask,
               (0,0),
               (0,0),
               (0,0),
               (6,6)) 

s8 = make_sign((0,0),
               even_mask,
               (0,0),
               (0,0),
               (0,0),
               (5,5)) 

signs = [s1,s2,s3,s4,s5,s6,s7,s8]
    
save_signs(signs,'lane_signs.csv')
