#!/usr/bin/bash
make
mkdir -p ./result
echo "AVLtree,array" > ./result/output2.csv
count=1
while [ $count -le 1000 ]
do
    ./main ./dataset/tdata.csv >> ./result/output2.csv
    count=$((count + 1))
done
make clean
