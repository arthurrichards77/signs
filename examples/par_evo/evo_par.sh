# build the scenario
python make_setup.py > setup.txt
# command for one run
EVO_RUN='../../bin/evo 10 0.2 0.3 0.1 0.001 0.000001'
# run four evolutions in parallel
# they will communicate via 'traveller.csv'
${EVO_RUN} | grep "Saving new" &
sleep 2 # need a sleep between each one so they randomize differently
${EVO_RUN} | grep "Saving new" &
sleep 2
${EVO_RUN} | grep "Saving new" &
sleep 2
${EVO_RUN} | grep "Saving new"
