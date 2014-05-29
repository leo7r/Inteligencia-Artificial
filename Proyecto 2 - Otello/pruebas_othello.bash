#!usr/bin/bash

make
ulimit -t 180

for i in `seq $2 33`; 
do 
  echo Estado $i:
  ./othello -a $1 -s $i
done
