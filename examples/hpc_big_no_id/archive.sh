#!/bin/bash
filename=${PWD##*/}-$(date +%Y-%m-%d-%H-%M).tar.gz
echo "Archiving contents to $filename"
tar -czvf ../$filename *.*
