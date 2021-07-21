#!/bin/bash
rm result.csv setup.txt log.txt
python make_setup.py > setup.txt
sha1sum -c setup.txt.sha1

../bin/simtest result.csv res_1205_006_000060_1204993940.csv | tee log.txt

err_test_failed=99

res=$(grep '163 agents' log.txt)
if [ -z "$res" ]
then
  echo 'ERR : Wrong number of agents'
  exit $err_test_failed
else
  echo 'OK : test had 163 agents'
fi

res=$(grep '6 signs' log.txt)
if [ -z "$res" ]
then
  echo 'ERR : Wrong number of signs'
  exit $err_test_failed
else
  echo 'OK : test loaded 6 signs'
fi

res=$(grep '1205 trips' log.txt)
if [ -z "$res" ]
then
  echo 'ERR : Wrong number of trips'
  exit $err_test_failed
else
  echo 'OK : test did 1205 trips'
fi

sha1sum -c result.csv.sha1
