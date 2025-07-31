#!/bin/bash

# conditional statements:

# POSIX - to maintain standards across UNIX based platforms

# syntax:

#if [ expression ]; then
#	statements
#elif [ expression ]; then
#	statements
#else
#	statements
#fi

# Comparing numbers:
#	-eq => equal to
#	-ne => not equal to
#	-gt => greater than
#	-lt => less than
#	-ge => greater than or equal to
#	-le => less than or equal to


#echo "Enter a number: "
#read num

#if [ $num -eq 10 ]; then
#	echo "Yes, it's equal"
#else
#	echo "Not equal"
#fi

# Comparing strings:
# 	= (two strings are equal)
# 	!= (two string not equal)
# 	-s (if string length is greater than zero)
# 	-z (if string length is equal to zero)
# 	both -s and -z are uniary operator

#	-n -> deletes newline character from the end of a string

#echo -n "Enter a string: "
#read str

#if [ "$str" -eq "john smith" ]; then
#	echo "yes, equal"
#else
#	echo "not equal"
#fi

# Checking file/directory and permissions
# 	-f => checks if the path given is a file
# 	-d => checks if the path given is a directory
# 	-e => checks if the path/file name exists
# 	-r => checks if the file/directory has a read permission
# 	-w => checks if the file/directory has a write permission
# 	-x => checks execute for file/directory
# 	-s => checks if the file length is greater than zero.


echo -n "Enter the file pathname: "
read filename

if [ -x "$filename" ]; then
	echo "yes, has execute permission"
else
	echo "no, does not have!"
fi
