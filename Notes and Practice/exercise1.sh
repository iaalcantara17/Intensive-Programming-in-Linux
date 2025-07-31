#!/bin/bash

#echo -n "Type in a file name: "
#read filename

#if [ -f "$filename" ]; then
#	cp "$filename" "${filename}.bak"
#else
#	echo "This file does not exist lil bro"
#fi

echo "Type in a valid file name: "
read filename

if [ -z "$filename" ]; then
	echo "prompt is empty"
fi

if [ -f "$filename" ]; then
	tail "$filename"
else
	echo "file does not exist!"
	exit 100
fi
