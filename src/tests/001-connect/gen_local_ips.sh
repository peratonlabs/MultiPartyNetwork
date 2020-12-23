#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "usage: ./gen_local_ips.sh <num_parties>"
  exit 1
fi

num_parties=$1

for (( i=1; i<=$num_parties; i++ ))
do
    printf -v hostname "mpc%04d" $i
    echo "127.0.0.1 $hostname"
done
