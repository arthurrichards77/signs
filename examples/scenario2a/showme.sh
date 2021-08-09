#!/bin/bash
#python make_setup.py > setup.txt
../../bin/simtest result.csv $1
if [ -z $1 ]
then
  filestub='${PWD##*/}_nosigns'
else
  filestub="$1"
fi
python ../../lib/visualize_depots.py result.csv $filestub.0.png 0
python ../../lib/visualize_depots.py result.csv $filestub.99.png 99
python ../../lib/visualize_depots.py result.csv $filestub.199.png 199
python ../../lib/visualize_depots.py result.csv $filestub.299.png 299
python ../../lib/visualize_depots.py result.csv $filestub.399.png 399
python ../../lib/visualize_depots.py result.csv $filestub.499.png 499
python ../../lib/visualize_depots.py result.csv $filestub.mp4
