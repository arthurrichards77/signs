# evo popsize probmut probsel probrep alpha beta probexch
rm log.txt
rm *.csv
../../bin/evo 50 0.2 0.5 0.1 0.001 0.000001 0.01 | tee log.txt
