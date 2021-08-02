#!/bin/bash
#PBS -l nodes=1:ppn=1
#PBS -l walltime=48:00:00
cd $PBS_O_WORKDIR
echo "Array ID=${PBS_ARRAYID}"
ARG_STR=$(head -n ${PBS_ARRAYID} params.txt | tail -1)
echo "Arguments are ${ARG_STR}"
# evo pop_size prob_mut prob_sel prob_rep w_signs w_bits
../../bin/evo ${ARG_STR}
