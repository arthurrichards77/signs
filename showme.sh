#!/bin/bash
./simtest result.csv $1
python visualize.py result.csv $1
