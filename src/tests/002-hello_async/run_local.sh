#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "usage: ./run_local.sh <num_parties>"
  exit 1
fi

num_parties=$1
cd build
for (( i=1; i<=$num_parties; i++ ))
do
    printf -v hostname "mpc%04d" $i
    echo $hostname
    nohup ./player $i $1 8000 &> ../logs/log-$hostname.txt &
    sleep 0.01
done
wait
