#!/bin/bash
#PBS -l nodes=1:ppn=1
#PBS -l walltime=12:00:00
#PBS -t 1-10
cd $PBS_O_WORKDIR
echo "Array ID=${PBS_ARRAYID}"
ARG_STR=$(head -n ${PBS_ARRAYID} params.txt | tail -1)
echo "Arguments are ${ARG_STR}"
# evo pop_size prob_mut prob_sel
./evo ${ARG_STR}
