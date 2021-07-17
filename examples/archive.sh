#!/bin/bash
if [$1 = ""]
then
  echo "$0 DIRNAME"
  exit
fi
filename=$1-$(date +%Y-%m-%d-%H-%M).tar.gz
echo "Archiving $1 to $filename"
tar -czvf $filename $1
