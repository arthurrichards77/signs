def gray(x):
    return(x ^ (x>>1))

def make_mask(start_value,end_value,num_bits):
    #print(num_bits)
    mask = 2**num_bits - 1
    patt = gray(start_value)
    #print(mask,patt)
    for ii in range(start_value,end_value):
        mask_err = (gray(ii+1) & mask)^patt
        mask = mask^mask_err
        patt = patt&mask
        #print(mask,patt)
    return(mask,patt)
    
def make_sign(a_mask,x_mask,y_mask,xg_mask,yg_mask,mv_mask):
    s = [a_mask[0],a_mask[1],
         x_mask[0],x_mask[1],
         y_mask[0],y_mask[1],
         xg_mask[0],xg_mask[1],
         yg_mask[0],yg_mask[1],
         mv_mask[0],mv_mask[1]]
    return(s)

def save_signs(signset,filename):
    f = open(filename,'w')
    for s in signset: 
        str = 'S'
        for e in s:
            str = str + ',{}'.format(e) 
        print(str)  
        f.write(str + '\n')
    f.close()
    
#m,p = make_mask(0,3,3)

