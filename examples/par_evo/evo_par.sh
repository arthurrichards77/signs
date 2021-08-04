# remove old results
rm log*.txt
rm res*.csv
rm traveller.csv
# build the scenario
python make_setup.py > setup.txt
# command for one run
EVO_RUN='../../bin/evo 10 0.2 0.3 0.1 0.001 0.000001 0.01 0'
# run four evolutions in parallel
# they will communicate via 'traveller.csv'
${EVO_RUN} | tee log1.txt | grep "Saving new" &
${EVO_RUN} | tee log2.txt | grep "Saving new" &
${EVO_RUN} | tee log3.txt | grep "Saving new" &
${EVO_RUN} | tee log4.txt | grep "Saving new" &
wait
