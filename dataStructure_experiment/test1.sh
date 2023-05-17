#!/usr/bin/bash
make
mkdir -p ./result
echo "data_size,AVLtree,array" > ./result/output1.csv
count=10
#1000000
while [ $count -le 10000 ]
do
   python3 ./dataset/mkdata.py $count
   ./main ./dataset/exdata.csv >> ./result/output1.csv
   count=$((count + 10))
done
#./main ./dataset/tdata.csv > ./result/output.txt
make clean
