#!/bin/bash
for img in pos/*.*; do
	filename=${img}
	newfile=${filename%.*}
   	#newfile=${filename%.*} | cut -d/ -f2-
   	f=${newfile#*/}
   	#echo /new_pos/$f
   	convert "$filename" "new_pos/$f.jpg"
    	echo "convert $filename to new_pos/$f.jpg"
done