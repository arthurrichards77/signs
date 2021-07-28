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
    
def make_masks_exact(start_value,end_value,num_bits):
    #print(start_value,end_value)
    signs = set([])
    mask = 2**num_bits - 1
    patt = gray(start_value)
    val_below = (start_value-1)%(2**num_bits)
    val_above = (end_value+1)%(2**num_bits)
    #print(val_above,val_below)
    for ii in range(start_value,end_value):
        mask_err = (gray(ii+1) & mask)^patt
        new_mask = mask^mask_err
        new_patt = patt&new_mask
        if (gray(val_above) & new_mask)^new_patt == 0:
            signs.add((mask,patt))
            mask = 2**num_bits - 1
            patt = gray(ii+1)
        elif (gray(val_below) & new_mask)^new_patt == 0:
            signs.add((mask,patt))
            mask = 2**num_bits - 1
            patt = gray(ii+1)
        else:
            mask = new_mask
            patt = new_patt
    signs.add((mask,patt))
    return(signs)
    
    
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
    
if __name__=='__main__':
    lower = 1
    upper = 7
    (mask,patt) = make_mask(lower,upper,4)
    print(mask)
    signs = make_masks_exact(lower,upper,4)
    print(signs)
    for ii in range(16):
        print('{}: M:{} E:{}'.format(ii,
                                     (gray(ii) & mask) ^ patt,
                                     [(gray(ii) & m) ^ p for (m,p) in signs]))
                                     
