# delete old results
rm log.txt
rm *.csv
# build scenario
python make_setup.py > setup.txt
# evo popsize probmut probsel probrep alpha beta probexch
../../bin/evo 50 0.2 0.5 0.1 0.001 0.000001 0.01 | tee log.txt
