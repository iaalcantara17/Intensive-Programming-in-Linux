#!/bin/bash

printf "Please provide an integer: "
read int1

printf "Please provide a second integer: "
read int2

printf "Which of the following operations would you like to perform, +, -, *, /, **: "
read op

if [ "$op" = "+" ]; then
	printf "%d\n" $((int1 + int2))

elif [ "$op" = "-" ]; then
	printf "%d\n" $((int1 - int2))

elif [ "$op" = "*" ]; then
	printf "%d\n" $((int1 * int2))

elif [ "$op" = "/" ]; then
	printf "%d\n" $((int1 / int2))

elif [ "$op" = "**" ]; then
	printf "%d\n" $((int1 ** int2))
else
	printf "That is not a valid operator, please type a valid operator\n"
fi
