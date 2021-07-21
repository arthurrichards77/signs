#!/bin/bash
python make_setup.py > setup.txt
../bin/simtest result.csv $1
python ../lib/visualize.py result.csv $1
