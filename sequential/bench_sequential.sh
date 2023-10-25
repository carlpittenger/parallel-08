#!/bin/sh
RESULTDIR=result/
h=$(hostname)
if [ "$h" = "gal-i1.uncc.edu" ];then
echo Do not run this on the headnode of the cluster, use sbtach!
exit 1
fi
if [ ! -d $RESULTDIR ];then
mkdir $RESULTDIR
fi
source ../params.sh
echo starting time is $(date)
for n in $PREFIXSUM_NS;do
./prefixsum_seq $n >/dev/null 2>$RESULTDIR/prefixsum_seq_$n
done
for n in $MERGESORT_NS;do
./mergesort_seq $n >/dev/null 2>${RESULTDIR}mergesort_seq_$n
done
echo ending time is $(date)
