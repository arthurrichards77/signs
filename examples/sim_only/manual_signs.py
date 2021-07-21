import sys, os
sys.path.append(os.getcwd()+'/../../lib')
from sign_builder import make_mask, make_sign, save_signs

s1 = make_sign((0,0), # applies to everyone
               (64,64),
               (64,64),
               (0,0),
               (64,0),
               (2,0)) 

save_signs([s1],'manual_signs.csv')
