#!usr/bin/bash

#make
ulimit -t 900

for i in `seq $2 33`; 
do 
  echo Estado $i:
  time ./othello -a $1 -s $i
done
