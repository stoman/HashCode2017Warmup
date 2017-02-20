#! /bin/bash

FILENAME=$1

if [ "$FILENAME" != "" ]; then
    gnuplot -e "datafile='${FILENAME}.dat';datafile2='${FILENAME}.ans.dat'; outputname='${FILENAME}.png'" plot.plg
else
    echo "Please enter a filename"
fi
