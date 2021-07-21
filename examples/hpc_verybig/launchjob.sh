#!/bin/bash
rm *.sh.*
rm *.csv
python make_setup.py > setup.txt
array_size=$(cat params.txt | wc -l)
echo "Submitting array of $array_size jobs"
qsub evo_sub.sh -t 1-$array_size
qstat -t -u $LOGNAME
