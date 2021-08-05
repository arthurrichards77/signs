import os
import sys
sys.path.append(os.getcwd()+'/../../lib')
from process import process_files

filename_array = [fn for fn in os.listdir() if '.sh.o' in fn]
# print(filename_array)
output_file = '{}_conv.png'.format(os.path.basename(os.getcwd()))
process_files(filename_array, output_file)
