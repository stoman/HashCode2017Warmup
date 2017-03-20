#! /bin/bash

FILENAME1=$1

gnuplot -e "datafile='${FILENAME1}';outputname='${FILENAME1}.png'" plot_balloons.plg
