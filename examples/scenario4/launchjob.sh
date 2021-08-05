#!/bin/bash
rm *.sh.*
rm *.csv
# remove as inconsistent random number generation across versions
# python make_setup.py > setup.txt
array_size=$(cat params.txt | wc -l)
job_name=${PWD##*/}
echo "Submitting array of $array_size jobs as $job_name"
qsub evo_sub.sh -N $job_name -t 1-$array_size
qstat -t -u $LOGNAME
