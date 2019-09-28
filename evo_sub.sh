#!/bin/bash
#PBS -l nodes=1:ppn=1
#PBS -l walltime=96:00:00
cd $PBS_O_WORKDIR
# evo pop_size prob_mut prob_sel
./evo 3000 0.016 0.3
