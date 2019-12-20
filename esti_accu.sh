#!/bin/bash

#This program is to estimate the accuracy of tex_seg.rb to compare my methods.
#This program use other far away directory text data. so please atention to change text data, directory structer.

array=()

#ls $1 | grep -E '^diff|^same' |
while read line
do
	array=(${array[@]} $line)
done << END
`ls $1 | grep -E '^diff|^same'`
END

echo ${array[*]}

for item in ${array[@]}
do
	echo ==============$item====================
	ruby tex_seg.rb ../my_segmentation/data/desrep_$item
	echo 
	echo
	echo
done
