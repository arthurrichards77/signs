# run four evolutions in parallel
# they will communicate via 'traveller.csv'
# need a sleep between each one so they randomize differently
./evo_run.sh | grep "Saving new" &
sleep 2
./evo_run.sh | grep "Saving new" &
sleep 2
./evo_run.sh | grep "Saving new" &
sleep 2
./evo_run.sh | grep "Saving new"
