#!/bin/sh
RESULTDIR=result/
h=$(hostname)
if [ "$h" = "gal-i1.uncc.edu" ]; then
    echo Do not run this on the headnode of the cluster, use qsub!
    exit 1
fi
if [ ! -d $RESULTDIR ]; then
    mkdir $RESULTDIR
fi
source ../params.sh
echo starting time is $(date)
for n in $PREFIXSUM_NS; do
    for t in $THREADS; do
        ./prefixsum "$n" "$t" >/dev/null 2>$RESULTDIR/prefixsum_"$n"_"$t"
    done
done
echo ending time is $(date)
